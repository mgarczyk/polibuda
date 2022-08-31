#IMPORTS
import pygame
import time
import random

#CONSTANTS
ORANGE = (204, 85, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
WIDTH = 800
HEIGHT = 600


class PythonSnake:
    def __init__(self):
        pygame.init()
        self.window_size = pygame.display.set_mode((WIDTH, HEIGHT))
        self.font_style = pygame.font.SysFont('Calibri', 30)
        self.clock = pygame.time.Clock()
        self.snake_block = 10
        self.snake_speed = 40
        pygame.display.set_caption('PythonSnake')
        self.game_loop()
        pygame.quit()


    def game_loop(self):
        self.game_over = False
        self.close_game = False
        self.actual_x = WIDTH / 2  # starting  position in x axis
        self.actual_y = HEIGHT / 2  # starting position in y axis
        self.foodx = round(random.randrange(0, WIDTH - self.snake_block) / 10.0) * 10.0
        self.foody = round(random.randrange(0, WIDTH - self.snake_block) / 10.0) * 10.0
        while not self.game_over:
            self.closing_game()
            self.event_listener()
            self.exceeding_dimensions()
            self.create_snake()
            self.create_food()
            self.eating_food()
            pygame.display.update()
            self.clock.tick(self.snake_speed)



    def event_listener(self):
        for event in pygame.event.get():
            self.event = event
            self.handling_quit_event()
            self.handling_keydown_event()

    def handling_quit_event(self):
        if self.event.type == pygame.QUIT:  # QUIT event
            self.game_over = True

    def handling_keydown_event(self):
        if self.event.type == pygame.KEYDOWN: # KEYDOWN event
            if self.event.key == pygame.K_LEFT:
                self.actual_x -= self.snake_block
            elif self.event.key == pygame.K_RIGHT:
                self.actual_x += self.snake_block
            elif self.event.key == pygame.K_DOWN:
                self.actual_y += self.snake_block
            elif self.event.key == pygame.K_UP:
                self.actual_y -= self.snake_block

    def exceeding_dimensions(self):
        if self.actual_x >= WIDTH or self.actual_x < 0 or self.actual_y >= HEIGHT or self.actual_y < 0:
            self.close_game = True

    def closing_game(self):
        while self.close_game:
            self.window_size.fill(WHITE)
            self.losing_message()
            pygame.display.update()
            self.closing_listener()

    def losing_message(self):
        self.lose_message = self.font_style.render('You lose! Press Q to quit or R to restart.', True, RED)
        self.window_size.blit(self.lose_message, [WIDTH/3, HEIGHT/2])
        pygame.display.update()

    def closing_listener(self):
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    self.game_over = True
                    self.close_game = False
                if event.key == pygame.K_r:
                    self.game_loop()

    def create_snake(self):
        self.window_size.fill(WHITE)
        pygame.draw.rect(self.window_size, BLUE, pygame.Rect(self.actual_x, self.actual_y, 10, 10))

    def create_food(self):
        pygame.draw.rect(self.window_size, ORANGE, [self.foodx, self.foody, self.snake_block, self.snake_block])

    def eating_food(self):
        if self.actual_x == self.foodx and self.actual_y == self.foody:
            print("Dobre, pomarańczowe.")



StartSnake = PythonSnake()
quit()
