# Description
A simple project aimed at introducing you to the possibilities of reinforcement learning (RL), one
with machine learning methods. The project is based on the snake game and an attempt to 'teach' a comupter as in
play this game. The model is designed based on the Pytorch library.


# Relevant information on details:

Input states:

1) Danger in front of the hose.
2) Danger to the right side of the snake's head.
3) Danger to the left of the snake's head.
4) Change direction to the left.
5) Change direction to the right.
6) Downward change of direction.
7) Upward change of direction.
8) Food on the left side of the snake's head.
9) Food from the right side of the snake's head.
10) Eating over the snake's head.
11) Eating under the snake's head left.

Output states:
1) Eat food (Reward)
2) Lost (Penalty)
3) Different situation (Neutral)

# Trivia

Module PythonSnakeGameAsAI.py gives you a chance to play the game from snake point of view.
You need only two keys to steering snake movement A or left arrow to turn left and D or right arrow to turn right.
That module is a little bit modified version of module PythonSnakeGameAI.py that basically is the environment that
our agent use to check outputs from neural network, to test is model is trained enough or not.
Playing in that version of the game should gives us a good look at how the data that the agent receives from the model for game control.


# Music
Music by <a href="https://pixabay.com/users/music_for_videos-26992513/?Jsource=link-attribution&amp" </a> Music_For_Videos from <a href = "https://pixabay.com//?Jsource=link-attribution&amp;Jsmedium=referral&amp;Jcampaign=music&amp;Jcontent=110855"> Pixabay </a>
