#IMPORTS
import pygame
import random
import numpy as np
import math
from enum import Enum
from collections import namedtuple


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
        self.set_start_parameters()

    def set_start_parameters(self):
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
        self.snake_head = (self.actual_x, self.actual_y)
        self.snake_body  = [self.snake_head]
        self.frame_iteration = 0
        self.len_of_snake = 1
        PythonSnakeMusic.play_background_music()

    def game_step(self):
        if self.is_collision(): # zabezpieczamy się przed sytuacją w której snake ani nie zdobywa nagrody, ani kary
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
            self.prepare_action()
            self.prepare_action()
            self.move_response()

    def handle_quit_event(self):
        if self.event.type == pygame.QUIT:  # QUIT event
            self.game_over = True

    def prepare_action(self):
        self.action = [1, 0, 0]
        if self.event.type == pygame.KEYDOWN: # KEYDOWN event
            if self.event.key == pygame.K_LEFT or self.event.key == pygame.K_a:
                self.action = [0, 0, 1]
            elif self.event.key == pygame.K_RIGHT or self.event.key == pygame.K_d:
                self.action = [0, 1, 0]


    def move_response(self): # Funkcja konwertuje akcje podjętą przez sieć neuronową, na interfejs gry
        self.clock_wise = [Direction.RIGHT, Direction.DOWN, Direction.LEFT, Direction.UP]
        self.index = self.clock_wise.index(self.direction)
        self.choose_diretion()
        self.change_direction()

    def choose_diretion(self):
        if np.array_equal(self.action, [1, 0, 0]):
            self.direction = self.clock_wise[self.index] # [1,0,0] -> Prosto (dalej w tym samym kierunku)
        elif np.array_equal(self.action, [0, 1, 0]):  # [0,1,0] -> Skręt w prawo.
            # W uproszczeniu sieć reaguje z perspektywy głowy węża.
            # Np. poruszamy się w dół (indeks = 2), nowy indeks to (2+1)%4 = 3,
            # snake skręca z naszej perspektywy w lewo, ale ze swojej w prawo, co jest odpowiednią reakcją środowiska na decyzję sieci neuronowej.
            next_index = (self.index + 1) % 4
            self.direction = self.clock_wise[next_index]
        elif np.array_equal(self.action, [0, 0, 1]):
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


    def is_collision(self, snake_head = None):
        if snake_head is None:
            snake_head = self.snake_head
        if snake_head[0] >= WIDTH or snake_head[0] < 0 or snake_head[1] >= HEIGHT or snake_head[1] < 0:
            PythonSnakeMusic.playing_exceeding_sound()
            return True
        for block in self.snake_body[:-1]:
            if block == self.snake_head:
                PythonSnakeMusic.playing_eating_yourself_sound()
                return True
        return False


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
                    self.set_start_parameters()

    # Cały czas patrzymy na pozycję głowy węża to ona jest śledzona, jej koordynaty są zapisywane do tablicy snake_body.
    # Na podstawie jej aktualnej pozycji, poprzednich znanych pozycji oraz prawdziwej długośći węża (len_of_snake) możemy go narysować.
    # Mając poprzednie pozycje głowy, możemy narysować ciało węża.
    def create_body(self):
        self.actual_y += self.y_change
        self.actual_x += self.x_change
        self.snake_head = (self.actual_x, self.actual_y)
        self.snake_body.append(self.snake_head)
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




