#IMPORTS
import pygame
import random
import python_snake_music

#CONSTANTS
ORANGE = (204, 85, 0)
LIGHTYELLOW = (255, 255, 153)
OLDLCDGREEN =  (168, 198, 78)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
WIDTH = 800
HEIGHT = 600


class PythonSnake:
    def __init__(self):
        pygame.init()
        self.window_size = pygame.display.set_mode((WIDTH, HEIGHT))
        self.font_style = pygame.font.SysFont('Calibri', 30)
        self.clock = pygame.time.Clock()
        self.snake_block = 10
        self.snake_speed = 50
        pygame.display.set_caption('PythonSnake')
        self.game_loop()
        pygame.quit()

    def game_loop(self):
        self.starting_parameters()
        while not self.game_over:
            self.closing_game()
            self.event_listener()
            self.exceeding_dimensions()
            self.create_snake()
            self.draw_food()
            self.eating_food()
            self.earning_points_message()
            self.clock.tick(25)
            pygame.display.update()

    def starting_parameters(self):
        self.game_over = False
        self.close_game = False
        self.actual_x = WIDTH / 2  # starting  position in x axis
        self.actual_y = HEIGHT / 2  # starting position in y axis
        self.x_change = 0
        self.y_change = 0
        self.food_coordinates() # starting food coordiantes
        self.snake_body = []
        self.len_of_snake = 1
        self.points = 0
        python_snake_music.play_background_music()



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

    def exceeding_dimensions(self):
        if self.actual_x >= WIDTH or self.actual_x < 0 or self.actual_y >= HEIGHT or self.actual_y < 0:
            self.close_game = True
            python_snake_music.playing_exceeding_sound()

    def closing_game(self): # Po przegraniu gry wyświetlamy widomość na ekranie i czekamy na działanie użytowkika (reset lub zakończenie gry)
        while self.close_game:
            self.window_size.fill(BLACK)
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

    # Cały czas patrzymy na pozycję głowy węża to ona jest śledzona, jej koordynaty są zapisywane do tablicy snake_body.
    # Na podstawie jej aktualnej pozycji, poprzednich znanych pozycji oraz prawdziwej długośći węża (len_of_snake) możemy go narysować.
    # Mając poprzednie pozycje głowy, możemy narysować ciało węża.
    def create_snake(self):
        self.actual_y += self.y_change
        self.actual_x += self.x_change
        self.snake_face = [self.actual_x, self.actual_y]
        self.snake_body.append(self.snake_face)
        self.moving_snake()
        print(self.snake_body)
        self.eating_yourself()
        self.draw_snake()

    # Gdy długość snake_body (tablicy z aktualną oraz poprzednimi koordynatami głowy) przekroczy, reczywsitą długość węża,
    # należy usunąć pierszy elemnt z tej tablicy (jest to de facto obszar kratka za ostatnim blokiem reperzentującym ciało
    # węża i narysować ponownie, co przy odpowiednim odświeżaniu (FPS) wygląda jak ruch.
    def moving_snake(self):
        if len(self.snake_body) > self.len_of_snake:
            del self.snake_body[0]

    def eating_yourself(self):
        for block in self.snake_body[:-1]:
            if block == self.snake_face:  # Sytuacja gdy głowa snake'a spotka się z fragmentem jego ciała (przegrana).
                python_snake_music.playing_eating_yourself_sound()
                self.close_game = True

    def draw_snake(self):
        self.window_size.fill(OLDLCDGREEN) # Przed narysowaniem węża należy wyczyścić całą planszę, innaczej każdy punkt przez który przeszła głowa węża byłby w jego kolorze do końca gry.
        for block in self.snake_body:
            pygame.draw.rect(self.window_size, LIGHTYELLOW, pygame.Rect(block[0], block[1], 10, 10))

    def draw_food(self):
        pygame.draw.rect(self.window_size, ORANGE, [self.food_x, self.food_y, self.snake_block, self.snake_block])

    def eating_food(self):
        if self.actual_x == self.food_x and self.actual_y == self.food_y:
            print("Dobre, pomarańczowe.")
            self.food_coordinates()
            self.len_of_snake += 1
            self.points += 10
            python_snake_music.playing_eating_sound()

    def food_coordinates(self):
        self.food_x = round(random.randrange(0, WIDTH - self.snake_block) / 20) * 10
        self.food_y = round(random.randrange(0, WIDTH - self.snake_block) / 20) * 10

    def earning_points_message(self):
        self.earning_messagew = self.font_style.render(f'Your points: {self.points}', True, LIGHTYELLOW)
        self.window_size.blit(self.earning_messagew, [WIDTH / 35, HEIGHT / 20])
        pygame.display.update()


StartSnake = PythonSnake()
quit()
