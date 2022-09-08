import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
import os

class Linear_QNet(nn.Module):
    def __init__(self,input_size, hidden_size, output_size):
        super().__init__()
        self.linear1 = nn.Linear(input_size, hidden_size)
        self.linear2 = nn.Linear(hidden_size, output_size)

    # Prediction function that is used to take the input (11 state vector) and pass it through neural network to get output (3 element vector)
    def forward(self, x):
        # Non-linear activations are what create the complex mappings between the model’s inputs and outputs.
        # They are applied after linear transformations to introduce nonlinearity, helping neural networks learn a wide variety of phenomena.
        x = F.relu(self.linear1(x))
        x = self.linear2(x)
        return x

    # Save function snake model for future use
    def save(self, file_name='snake_model.pth'):
        model_folder_path = 'snake_model'
        if not os.path.exists(model_folder_path):
            os.makedirs(model_folder_path)
        file_name = os.path.join(model_folder_path, file_name)
        torch.save(self.state_dict(),file_name)

class QTrainer:
    def __init__(self, model, lr, gamma):
        # LEARNING RATE NOTE
        # The learning rate controls how quickly the model is adapted to the problem.
        # Smaller learning rates require more training epochs given the smaller changes made to the weights each update,
        # whereas larger learning rates result in rapid changes and require fewer training epochs.
        self.lr = lr
        # GAMMA NOTE
        # The fact that the discount rate is bounded to be smaller than 1 is a mathematical trick to make an infinite sum finite. This helps proving the convergence of certain algorithms.
        # In practice, the discount factor could be used to model the fact that the decision maker is uncertain about if in the next decision instant the world (e.g., environment / game / process ) is going to end.
        # The discount factor essentially determines how much the reinforcement learning agents cares about rewards in the distant future relative to those in the immediate future. If γ=0,
        # the agent will be completely myopic and only learn about actions that produce an immediate reward. If γ=1, the agent will evaluate each of its actions based on the sum total of all of its future rewards.
        self.gamma = gamma
        self.model = model
        self.optimer = optim.Adam(model.parameters(), lr=self.lr)
        self.criterion = nn.MSELoss()

    def train_step(self, state, action, reward, next_state, done):
        self.state = torch.tensor(state, dtype=torch.float)
        self.next_state = torch.tensor(next_state, dtype=torch.float)
        self.action = torch.tensor(action, dtype=torch.long)
        self.reward = torch.tensor(reward, dtype=torch.float)
        self.done = done
        self.convert_tensor_to_vector()
        # 1. Predicted Q value with current state
        self.pred = self.model(self.state)
        self.target = self.pred.clone()
        for idx in range(len(self.done)):
            self.idx = idx
            self.determine_Q_value()
        self.determine_loss_and_backpropagete()

    # We had a short memory training then we would only pass one value
    # of state, action, reward, move so we need to convert them into a vector, so we had used
    # unsqueezed function.
    def convert_tensor_to_vector(self):
        if(len(self.state.shape) == 1):
            self.state = torch.unsqueeze(self.state, 0)
            self.next_state = torch.unsqueeze(self.next_state, 0)
            self.action = torch.unsqueeze(self.action, 0)
            self.reward = torch.unsqueeze(self.reward, 0)
            self.done = (self.done, )

    def determine_Q_value(self):
        Q_new = self.reward[self.idx]
        if not self.done[self.idx]:
            # Bellman equation, Q_new = reward + gamma * max(next_predicted Qvalue)
            Q_new = self.reward[self.idx] + self.gamma * torch.max(self.model(self.next_state[self.idx]))
        self.target[self.idx][torch.argmax(self.action).item()] = Q_new

    def determine_loss_and_backpropagete(self):
        # Zeroing out gradients
        self.optimer.zero_grad()
        # Calculate the mean squared error between the new Q value and previous Q value and
        loss = self.criterion(self.target, self.pred)
        # Backpropagate that loss for weight updation.
        loss.backward()
        self.optimer.step()


