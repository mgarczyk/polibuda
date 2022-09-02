# Description

1.register or login:

- user is asked: "what do you want to do? login, registration, exit?"

- /register command creates a user in the user base - txt file - also checks the uniqueness of logins.

- /login command - we check if the user with the given login and password exists in the txt database. if the password and login are correct, the user gains access to the commands described below in point 2.

-use some hash function to store passwords safely

- exit exits the program

- unsuccessful attempts to register and login repeat the question

- registration success - the user is informed about the success but still has to log in

- login success - points 2.
2.
- Each user has its own folder created during registration

- after logging in, the user is asked what he wants to do "what do you want to do? store text, store image, show files, inspect {file}, exit?"

- logged user can create txt notes and put pictures in his folder (by entering the path):

- /store text command - asks for the name of the txt file to be created and then for its content. Then the file is saved in the user folder

- /store image command - asks for the path to the image on the PC. The picture is then saved in the user's directory

- logged user can use the command /show files to display all the names of files in a folder, make sure that it is known whether the file is an image or a txt

- logged user can use command /inspect {filename} to read the file. if it is a txt we print its content in the terminal, if the image is displayed:
the contents of the file ... are: ..........

- after executing any command except exit user is asked again what he wants to do.
 If the command execution was successful, what is described above, if not, the user is informed about the error / missing file etc. Exit closes the program.
