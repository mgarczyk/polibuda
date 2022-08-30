import pygame

class PythonSnake:
    def __init__(self):
        pygame.init()
        self.WindowSize = pygame.display.set_mode((400,300))
        pygame.display.set_caption('PythonSnake')
        self.GameLoop()
        pygame.quit()

    def GameLoop(self):
        self.StillPlaying = True
        while self.StillPlaying:
            self.DidUserStillPlaying()

    def DidUserStillPlaying(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.StillPlaying = False


StartSnake = PythonSnake()
quit()
