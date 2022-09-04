# Description
A simple project aimed at introducing you to the basic possibilities of the pygame library.
The goal is achieved by implementing the Snake game with the help of this library.


#Important information on snake details:

1) We look at the position of the snake's head all the time, it is tracked, its coordinates are saved to the snake_body table.
2) On the basis of its current position, previous known positions and the true length of the snake (len_of_snake), we can draw it.
3) Having the previous head positions, we can draw the body of the snake.
4) When the length of the snake_body (the table with the current and previous head coordinates) exceeds the real length of the snake,
the first element should be removed from this table (it is in fact the grid area behind the last block repeating the body
snake) and redraw what looks like motion with proper refresh rate (FPS).

# Music
Music by <a href="https://pixabay.com/users/music_for_videos-26992513/?Jsource=link-attribution&amp;"> Music_For_Videos </a> from <a href = "https://pixabay.com//?Jsource=link-attribution&amp;Jsmedium=referral&amp;Jcampaign=music&amp;Jcontent=110855"> Pixabay </a>
