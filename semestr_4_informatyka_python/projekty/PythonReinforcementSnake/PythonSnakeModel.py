import torch
import torch.nn as nn
import torch.optim as optim
import os


class Linear_QNetwork(nn.Module): # class that initialize neural network

    def __init__(self, input_size, hidden_size, output_size):
        super().__init__()
        self.linear_1 = nn.Linear(input_size, hidden_size)
        self.linear_1 = nn.Linear(hidden_size, output_size)

    def forward(self, x):  # prediction function that is used to take the input (11 state vector) and pass it through neural network to get output (3 element vector)
        # Non-linear activations are what create the complex mappings between the model’s inputs and outputs.
        # They are applied after linear transformations to introduce nonlinearity, helping neural networks learn a wide variety of phenomena.
        x = nn.functional.relu(self.linear_1(x))
        x = self.linear_2(x)
        return x

    def save(self, file_name = 'snake_model.pth'): # saving snake model for future use
        model_folder_path = 'model'
        file_name = os.path.join(model_folder_path, file_name)
        torch.save(self.state_dict(), file_name)


class Q_Trainer:
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
        self.model = model # model definied by class Linear_QModel
        # Adaptive Moment Estimation is an algorithm for optimization technique for gradient descent.
        # The method is really efficient when working with large problem involving a lot of data or parameters.
        self.optimer = optim.Adam(model.parameters(), lr=self.lr)
        # Many layers inside a neural network are parameterized, i.e. have associated weights and biases that are optimized during training.
        # Subclassing nn.Module automatically tracks all fields defined inside your model object,
        #  and makes all parameters accessible using your model’s parameters() or named_parameters() methods.
        self.criterion = nn.MSELoss()

    def train_step(self, state, action, reward, next_state, done):
        state, action, reward, next_state, done = self.prepare_data(state, action, reward. score, next_state, done)
        # Predict Q value with current state
        pred = self.model(state).cuda() # take actual state of the model
        target = pred.clone().cuda()
        for idx in range(len(done)): # our memory is fillied in range of done
            # Bellman equation, Q_new = reward + gamma * max(next_predicted Qvalue)
            if not done[idx]:
                Q_new = reward[idx] + self.gamma * torch.max(self.model(next_state[idx])).cuda()
            target[idx][torch.argmax(action).item()] = Q_new
            self.optimer.zero_grad()
            # Calculate the mean squared error between the new Q value and previous Q value and
            # backpropagate that loss for weight updation.
            loss = self.criterion(target, pred)
            loss.backward()
            self.optimer.step()


    def prepare_data(self, state, action, reward, next_state, done): # convert data to tensors, and then to vectors for short memory training
        state = torch.tensor(state, dtype=torch.float).cuda()
        next_state = torch.tensor(next_state, dtype=torch.float).cuda()
        action = torch.tensor(action, dtype=torch.float).cuda()
        reward = torch.tensor(reward, dtype=torch.float).cuda()
        if len(state.shape()) == 1: # convert tensor to vector
            state = torch.unsqueeze(state, 0).cuda()
            next_state = torch.unsqueeze(next_state , 0).cuda()
            action = torch.unsqueeze(action, 0).cuda()
            reward = torch.unsqueeze(reward, 0).cuda()
            done = (done, )
        return state, next_state, action, reward, done







