import pygame
import random
from enum import Enum
import numpy as np


pygame.init()
font = pygame.font.SysFont('arial', 25)

class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    UP = 3
    DOWN = 4

WHITE = (255, 255, 255)
RED = (200,0,0)
BLUE1 = (0, 0, 255)
BLUE2 = (0, 100, 255)
BLACK = (0,0,0)
ORANGE = (204, 85, 0)
LIGHTYELLOW = (255, 255, 153)
OLDLCDGREEN =  (168, 198, 78)
SNAKE_BLOCK = 20
SPEED = 40


class PythonSnake:

    def __init__(self, w=640, h=480):
        self.w = w
        self.h = h
        self.display = pygame.display.set_mode((self.w, self.h))
        pygame.display.set_caption('Snake')
        self.clock = pygame.time.Clock()
        self.set_start_parameters()


    def set_start_parameters(self):
        self.direction = Direction.RIGHT
        self.head = (self.w/2, self.h/2)
        self.actual_x = self.head[0]
        self.actual_y = self.head[1]
        self.snake = [self.head,
                      (self.actual_x - SNAKE_BLOCK, self.actual_y),
                      (self.actual_x - (2 * SNAKE_BLOCK), self.actual_y)]
        self.score = 0
        self.frame_iteration = 0
        self.food = None
        self.create_food()


    def create_food(self):
        food_x = random.randint(0, (self.w - SNAKE_BLOCK) // SNAKE_BLOCK) * SNAKE_BLOCK
        food_y = random.randint(0, (self.h - SNAKE_BLOCK) // SNAKE_BLOCK) * SNAKE_BLOCK
        self.food = (food_x, food_y)
        if self.food in self.snake:
            self.create_food()

    def game_step(self, action):
        self.frame_iteration += 1
        self.quit_listener()
        self.response_to_action(action)   # Refresh the head position.
        self.snake.insert(0, self.head)
        reward = 0
        game_over = False
        if self.is_collision() or self.end_if_too_much_frames_without_point():
            game_over = True
            reward = -10
            return reward, game_over, self.score
        if self.head == self.food:
            self.score += 1
            reward = 10
            self.create_food()
        else:
            # Snake moves, after each movement we refresh the position of the head,
            # and we must remember to remove the oldest known position,
            # which is now behind his body and shouldn't be colored as the body.
            self.snake.pop()
        self.draw_game()
        self.clock.tick(SPEED)
        return reward, game_over, self.score

    def quit_listener(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

    def is_collision(self, snake_head = None):
        if snake_head is None:
            snake_head = self.head
        x = snake_head[0]
        y = snake_head[1]
        if self.exceed_dimensions(x, y) or self.eat_yourself(snake_head):
            return True
        return False

    def exceed_dimensions(self, x, y):
        if x > self.w - SNAKE_BLOCK or x < 0 or y > self.h - SNAKE_BLOCK or y < 0:
            return True

    def eat_yourself(self, snake_head):
        if snake_head in self.snake[1:]:
            return True

    def end_if_too_much_frames_without_point(self):
        if self.frame_iteration > 100*len(self.snake):
            return True

    def draw_game(self):
        self.display.fill(OLDLCDGREEN)
        for pt in self.snake:
            x = pt[0]
            y = pt[1]
            pygame.draw.rect(self.display, LIGHTYELLOW, pygame.Rect(x, y, SNAKE_BLOCK, SNAKE_BLOCK))
        pygame.draw.rect(self.display, ORANGE, pygame.Rect(self.food[0], self.food[1], SNAKE_BLOCK, SNAKE_BLOCK))
        self.draw_score()

    def draw_score(self):
        text = font.render("Score: " + str(self.score), True, WHITE)
        self.display.blit(text, [0, 0])
        pygame.display.flip()

    def response_to_action(self, action): # The function converts the action taken by the neural network into the game interface
        self.clock_wise = [Direction.RIGHT, Direction.DOWN, Direction.LEFT, Direction.UP]
        self.index = self.clock_wise.index(self.direction)
        self.set_direction(action)
        self.move_snake()

    def set_direction(self, action):
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

    # We look at the position of the snake's head all the time, it is tracked, its coordinates are saved to the snake array.
    # Based on it current position, previous known positions (where now the body is) we can draw the snake.
    # It's important only head postion is needed to draw snake.

    def move_snake(self):
        self.actual_x = self.head[0]
        self.actual_y = self.head[1]
        if self.direction == Direction.RIGHT:
            self.actual_x += SNAKE_BLOCK
        elif self.direction == Direction.LEFT:
            self.actual_x -= SNAKE_BLOCK
        elif self.direction == Direction.DOWN:
            self.actual_y += SNAKE_BLOCK
        elif self.direction == Direction.UP:
            self.actual_y -= SNAKE_BLOCK
        self.head = (self.actual_x, self.actual_y)
