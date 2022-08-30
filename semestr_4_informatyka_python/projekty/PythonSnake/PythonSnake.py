import pygame

class PythonSnake:
    def __init__(self):
        pygame.init()
        self.WindowSize = pygame.display.set_mode((400,300))
        pygame.display.set_caption('PythonSnake')
        self.GameLoop()
        pygame.quit()

    def GameLoop(self):
        self.PlayingGame = True
        while self.PlayingGame:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.PlayingGame = False


StartSnake = PythonSnake()
quit()
