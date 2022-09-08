import torch
import random
import numpy as np
from collections import deque
from PythonSnakeAI import PythonSnake, Direction, SNAKE_BLOCK
from PythonSnakeModel import Linear_QNet, QTrainer
from PythonSnakePlot import plot
BATCH_SIZE = 1000
MAX_MEMORY = 100_000
LR = 0.001



class Python_Snake_Agent:
    def __init__(self):
        self.n_game = 0
        self.epsilon = 0
        self.gamma = 0.9
        self.memory = deque(maxlen=MAX_MEMORY) # Deque is preferred over a list in the cases where we need quicker append and pop operations from both the ends of the container.
        # Create model
        self.model = Linear_QNet(11, 256, 3)
        self.trainer = QTrainer(self.model, lr=LR, gamma=self.gamma)


    def get_state(self, game):
        self.game = game
        self.get_actual_postion()
        self.get_next_postion_based_on_direction()
        self.get_direction_of_snake()
        self.set_input_data()
        return np.array(self.state, dtype=int)

    def get_actual_postion(self):
        self.head = self.game.head # postion of snake head
        self.actual_x = self.head[0] # head[0] postion in x axis,
        self.actual_y = self.head[1] # head[1] position in y axis

    def get_next_postion_based_on_direction(self):
        self.point_left = (self.actual_x - SNAKE_BLOCK, self.actual_y)
        self.point_right = (self.actual_x + SNAKE_BLOCK, self.actual_y)
        self.point_up = (self.actual_x, self.actual_y - SNAKE_BLOCK)
        self.point_down = (self.actual_x, self.actual_y + SNAKE_BLOCK)

    def get_direction_of_snake(self):
        self.dir_left = self.game.direction == Direction.LEFT
        self.dir_right = self.game.direction == Direction.RIGHT
        self.dir_up = self.game.direction == Direction.UP
        self.dir_down = self.game.direction == Direction.DOWN

    def set_input_data(self):

        self.state = [
            # Danger Straight
            (self.dir_up and self.game.is_collision(self.point_up)) or
            (self.dir_down and self.game.is_collision(self.point_down)) or
            (self.dir_left and self.game.is_collision(self.point_left)) or
            (self.dir_right and self.game.is_collision(self.point_right)),

            # Danger right
            (self.dir_up and self.game.is_collision(self.point_right)) or
            (self.dir_down and self.game.is_collision(self.point_left)) or
            (self.dir_left and self.game.is_collision(self.point_up)) or
            (self.dir_right and self.game.is_collision(self.point_down)),

            #Danger Left
            (self.dir_up and self.game.is_collision(self.point_left)) or
            (self.dir_down and self.game.is_collision(self.point_right)) or
            (self.dir_right and self.game.is_collision(self.point_up)) or
            (self.dir_left and self.game.is_collision(self.point_down)),

            # Move Direction
            self.dir_left,
            self.dir_right,
            self.dir_up,
            self.dir_down,

            #Food Location
            self.game.food[0] < self.actual_x, # food is in left
            self.game.food[0] > self.actual_x, # food is in right
            self.game.food[1] < self.actual_y, # food is up
            self.game.food[1] > self.actual_y  # food is down
        ]

    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))  # Popleft if memory exceed

    def train_long_memory(self):
        if len(self.memory) > BATCH_SIZE:
            mini_sample = random.sample(self.memory, BATCH_SIZE)
        else:
            mini_sample = self.memory
        states, actions, rewards, next_states, dones = zip(*mini_sample)
        self.trainer.train_step(states, actions, rewards, next_states, dones)

    def train_short_memory(self, state, action, reward, next_state, done):
        self.trainer.train_step(state, action, reward, next_state, done)

    def get_action(self, state):
        # Random moves: tradeoff explotation / exploitation
        self.epsilon = 80 - self.n_game
        final_move = [0, 0, 0]
        if random.randint(0, 200) < self.epsilon:
            move = random.randint(0, 2)
            final_move[move] = 1
        else:
            state0 = torch.tensor(state, dtype=torch.float)
            prediction = self.model(state0)  # prediction by model
            move = torch.argmax(prediction).item()
            final_move[move] = 1
        return final_move


def train_model():
    while True:
        try:
            check_model = input("Did you want use saved model or create new? "
                                "\nEnter Y if saved or N if new: ")
            if check_model in ["Y", "y", "N", "n"]:
                break
            raise ValueError
        except ValueError:
            print("Podano błędne dane spróbuj ponownie.")

    plot_scores = []
    plot_mean_scores = []
    total_score = 0
    record = 0
    agent = Python_Snake_Agent()
    game = PythonSnake()

    if check_model == "Y" or check_model == 'y':
        agent.model.load_state_dict(torch.load('snake_model/snake_model.pth'))

    while True:
        actual_state = agent.get_state(game)
        final_move = agent.get_action(actual_state)
        reward, done, score = game.game_step(final_move)
        state_new = agent.get_state(game)
        agent.train_short_memory(actual_state, final_move, reward, state_new, done)
        agent.remember(actual_state, final_move, reward, state_new, done)
        if done:
            # Train long memory, plot result
            game.set_start_parameters()
            agent.n_game += 1
            agent.train_long_memory()
            if score > record:  # Remember new highscore
                record = score
                agent.model.save()
            print('Game:', agent.n_game, 'Score:', score, 'Record:', record)
            plot_scores.append(score)
            total_score += score
            mean_score = total_score / agent.n_game
            plot_mean_scores.append(mean_score)
            plot(plot_scores, plot_mean_scores)


if(__name__=="__main__"):
    train_model()
