import torch
import torch.nn as nn
import os


class Linear_QNetwork(nn.Module): # class that initialize neural network
    def __init__(self, input_size, hidden_size, output_size):
        super().__init__()
        self.linear_1 = nn.Linear(input_size, hidden_size)
        self.linear_1 = nn.Linear(hidden_size, output_size)

    def forward(self, x):  # prediction function that is used to take the input (11 state vector) and pass it through neural network to get output (3 element vector)
        x = nn.functional.relu(self.linear_1(x))
        x = self.linear_2(x)
        return x

    def save(self, file_name = 'snake_model.pth'):
        model_folder_path = 'model'
        file_name = os.path.join(model_folder_path, file_name)
        print(file_name)
        torch.save(self.state_dict(), file_name)
