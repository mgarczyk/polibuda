import pygame.mixer as mixer


def play_background_music():
        mixer.music.load('music/Jazz_happy_pixabay_110855.mp3')
        mixer.music.play(-1)


def playing_exceeding_sound():
        exceeding_sound = mixer.Sound('music/Cartoon_bonk_sound_effect.mp3')
        exceeding_sound.play()


def playing_eating_yourself_sound():
        eating_yourself_sound = mixer.Sound('music/Self_eating_sound.mp3')
        eating_yourself_sound.play()


def playing_eating_sound():
        eating_sound = mixer.Sound('music/Eating_sound_effect.mp3')
        eating_sound.play()


