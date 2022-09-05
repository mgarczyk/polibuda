#IMPORTS
import pygame
import random
import numpy as np
import math
from enum import Enum
import PythonSnakeMusic


ORANGE = (204, 85, 0)
LIGHTYELLOW = (255, 255, 153)
OLDLCDGREEN =  (168, 198, 78)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
WIDTH = 800
HEIGHT = 600

class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    UP  = 3
    DOWN = 4

class PythonSnake:
    def __init__(self):
        pygame.init()
        self.window_size = pygame.display.set_mode((WIDTH, HEIGHT))
        self.font_style = pygame.font.SysFont('Calibri', 30)
        self.clock = pygame.time.Clock()
        pygame.display.set_caption('PythonSnake')
        self.starting_parameters_of_snake()

    def starting_parameters_of_snake(self):
        self.game_over = False
        self.score = 0
        self.frame_iteration = 0
        self.direction = Direction.RIGHT # starting direction
        self.actual_x = WIDTH / 2  # head  position in x axis
        self.actual_y = HEIGHT / 2  # head position in y axis
        self.x_change = 0
        self.y_change = 0
        self.snake_block = 10
        self.snake_speed = 50
        self.food_coordinates() # starting food coordiantes
        self.snake_body = [[self.actual_x, self.actual_y]]
        self.frame_iteration = 0
        self.len_of_snake = 1
        PythonSnakeMusic.play_background_music()

    def game_step(self, action):
        self.frame_iteration += 1
        self.quit_event_listener()
        if self.is_collision():
            self.game_over = True
            self.score += -1
            return self.game_over, self.score
        self.move_response(action)
        self.create_body()
        self.draw_food()
        self.eat_food()
        self.earned_reward_message()
        self.clock.tick(25)
        pygame.display.update()
        return self.game_over, self.score

    def quit_event_listener(self):
        for event in pygame.event.get():
            self.event = event
            if event.type == pygame.QUIT:  # QUIT event
                self.game_over = True


    def move_response(self, action): # The function converts the action taken by the neural network into the game interface
        self.clock_wise = [Direction.RIGHT, Direction.DOWN, Direction.LEFT, Direction.UP]
        self.index = self.clock_wise.index(self.direction)
        self.choose_diretion(action)
        self.change_direction()

    def choose_diretion(self, action):
        if np.array_equal(action, [1, 0, 0]):
            self.direction = self.clock_wise[self.index] # [1,0,0] -> Straight (further in the same direction)
        elif np.array_equal(action, [0, 1, 0]):  # [0,1,0] -> Turn right.
            # In simplified terms, the network reacts from the perspective of a snake's head.
            # E.g. we move down (index = 2), the new index is (2 + 1)% 4 = 3,
            # snake turns left from our perspective, but turns right from it's perspective, which is an appropriate reaction of the environment to the decision of the neural network.
            next_index = (self.index + 1) % 4
            self.direction = self.clock_wise[next_index]
        elif np.array_equal(action, [0, 0, 1]):
            next_index = (self.index - 1) % 4
            self.direction = self.clock_wise[next_index]
            print(self.direction)

    def change_direction(self):
            if self.direction == Direction.LEFT:
                self.x_change = -self.snake_block
                self.y_change = 0
            elif self.direction == Direction.RIGHT:
                self.x_change = self.snake_block
                self.y_change = 0
            elif self.direction == Direction.DOWN:
                self.y_change = self.snake_block
                self.x_change = 0
            elif self.direction == Direction.UP:
                self.y_change = -self.snake_block
                self.x_change = 0


    def is_collision(self):
        if self.exceed_dimensions() or self.eat_yourself():
            return True

    def exceed_dimensions(self):
        if self.actual_x >= WIDTH or self.actual_x < 0 or self.actual_y >= HEIGHT or self.actual_y < 0:
            return True

    def eat_yourself(self):
        for block in self.snake_body[:-1]:
            if block == self.snake_face:
                return True

    # We look at the position of the snake's head all the time, it is tracked, its coordinates are saved to the snake_body array.
    # Based on its current position, previous known positions and the true length of the snake (len_of_snake) we can draw it.
    # Having the previous head positions, we can draw the body of the snake.
    def create_body(self):
        self.actual_y += self.y_change
        self.actual_x += self.x_change
        self.snake_face = [self.actual_x, self.actual_y]
        self.snake_body.append(self.snake_face)
        self.move_animation()
        self.draw_body()

    # When the length of the snake_body (the table with the current and previous head coordinates) exceeds the real length of the snake,
    # the first element should be removed from this table (it is in fact the grid area behind the last block repeating the body
    # snake and redraw what looks like motion when properly refreshed (FPS).
    def move_animation(self):
        if len(self.snake_body) > self.len_of_snake:
            del self.snake_body[0]

    def draw_body(self):
        self.window_size.fill(OLDLCDGREEN)  # Before drawing the snake, clear the entire board, otherwise every point the snake's head passed through would be in its color for the rest of the game.
        for block in self.snake_body:
            pygame.draw.rect(self.window_size, LIGHTYELLOW, pygame.Rect(block[0], block[1], 10, 10))

    def draw_food(self):
        pygame.draw.rect(self.window_size, ORANGE, [self.food_x, self.food_y, self.snake_block, self.snake_block])

    def eat_food(self):
        if self.actual_x == self.food_x and self.actual_y == self.food_y:
            print("Dobre, pomarańczowe.")
            self.food_coordinates()
            self.len_of_snake += 1
            self.score += 1
            PythonSnakeMusic.playing_eating_sound()

    def food_coordinates(self):
        self.food_x = round(random.randrange(0, WIDTH - self.snake_block) / 20) * 10
        self.food_y = round(random.randrange(0, WIDTH - self.snake_block) / 20) * 10

    def earned_reward_message(self):
        self.earning_messagew = self.font_style.render(f'Your points: {self.score}', True, LIGHTYELLOW)
        self.window_size.blit(self.earning_messagew, [WIDTH / 35, HEIGHT / 20])
        pygame.display.update()






