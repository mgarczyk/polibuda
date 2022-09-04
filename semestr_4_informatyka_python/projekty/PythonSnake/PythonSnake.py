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
        self.close_game = False
        self.reward = 0
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

    def game_step(self):
        if self.is_collision():
            self.close_game = True
            self.closing_game()
        self.event_listener()
        self.create_body()
        self.draw_food()
        self.eat_food()
        self.earned_reward_message()
        self.clock.tick(25)
        pygame.display.update()

    def event_listener(self):
        for event in pygame.event.get():
            self.event = event
            self.handle_quit_event()
            self.handle_keydown_event()

    def handle_quit_event(self):
        if self.event.type == pygame.QUIT:  # QUIT event
            self.game_over = True

    def handle_keydown_event(self):
        if self.event.type == pygame.KEYDOWN: # KEYDOWN event
            if self.event.key == pygame.K_LEFT or self.event.key == pygame.K_a:
                self.x_change = -self.snake_block
                self.y_change = 0
            elif self.event.key == pygame.K_RIGHT or self.event.key == pygame.K_d:
                self.x_change = self.snake_block
                self.y_change = 0
            elif self.event.key == pygame.K_DOWN or self.event.key == pygame.K_s:
                self.y_change = self.snake_block
                self.x_change = 0
            elif self.event.key == pygame.K_UP or self.event.key == pygame.K_w:
                self.y_change = -self.snake_block
                self.x_change = 0

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
            PythonSnakeMusic.playing_exceeding_sound()
            return True

    def eat_yourself(self):
        for block in self.snake_body[:-1]:
            if block == self.snake_face:  # Sytuacja gdy głowa snake'a spotka się z fragmentem jego ciała (przegrana).
                PythonSnakeMusic.playing_eating_yourself_sound()
                return True


    def closing_game(self): # Po przegraniu gry wyświetlamy widomość na ekranie i czekamy na działanie użytowkika (reset lub zakończenie gry)
        while self.close_game == True:
            self.window_size.fill(BLACK)
            self.losing_message()
            self.closing_listener()
            pygame.display.update()

    def losing_message(self):
        self.lose_message = self.font_style.render('You lose! Press Q to quit or R to restart.', True, RED)
        self.window_size.blit(self.lose_message, [WIDTH/3, HEIGHT/2])

    def closing_listener(self):
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    self.close_game = False # that end closing_game loop and screen
                    self.game_over = True   # then that end main loop that end the game
                if event.key == pygame.K_r:
                    self.starting_parameters_of_snake()

    # Cały czas patrzymy na pozycję głowy węża to ona jest śledzona, jej koordynaty są zapisywane do tablicy snake_body.
    # Na podstawie jej aktualnej pozycji, poprzednich znanych pozycji oraz prawdziwej długośći węża (len_of_snake) możemy go narysować.
    # Mając poprzednie pozycje głowy, możemy narysować ciało węża.
    def create_body(self):
        self.actual_y += self.y_change
        self.actual_x += self.x_change
        self.snake_face = [self.actual_x, self.actual_y]
        self.snake_body.append(self.snake_face)
        self.move_animation()
        self.draw_body()

    # Gdy długość snake_body (tablicy z aktualną oraz poprzednimi koordynatami głowy) przekroczy, reczywsitą długość węża,
    # należy usunąć pierszy elemnt z tej tablicy (jest to de facto obszar kratka za ostatnim blokiem reperzentującym ciało
    # węża i narysować ponownie, co przy odpowiednim odświeżaniu (FPS) wygląda jak ruch.
    def move_animation(self):
        if len(self.snake_body) > self.len_of_snake:
            del self.snake_body[0]

    def draw_body(self):
        self.window_size.fill(OLDLCDGREEN) # Przed narysowaniem węża należy wyczyścić całą planszę, innaczej każdy punkt przez który przeszła głowa węża byłby w jego kolorze do końca gry.
        for block in self.snake_body:
            pygame.draw.rect(self.window_size, LIGHTYELLOW, pygame.Rect(block[0], block[1], 10, 10))

    def draw_food(self):
        pygame.draw.rect(self.window_size, ORANGE, [self.food_x, self.food_y, self.snake_block, self.snake_block])

    def eat_food(self):
        if self.actual_x == self.food_x and self.actual_y == self.food_y:
            print("Dobre, pomarańczowe.")
            self.food_coordinates()
            self.len_of_snake += 1
            self.reward += 10
            PythonSnakeMusic.playing_eating_sound()

    def food_coordinates(self):
        self.food_x = round(random.randrange(0, WIDTH - self.snake_block) / 20) * 10
        self.food_y = round(random.randrange(0, WIDTH - self.snake_block) / 20) * 10

    def earned_reward_message(self):
        self.earning_messagew = self.font_style.render(f'Your points: {self.reward}', True, LIGHTYELLOW)
        self.window_size.blit(self.earning_messagew, [WIDTH / 35, HEIGHT / 20])
        pygame.display.update()




SnakeGame = PythonSnake()
# game loop
while not SnakeGame.game_over:
    SnakeGame.game_step()




