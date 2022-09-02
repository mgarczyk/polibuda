# Description
1.Two programs / projects:

# Server side

- The application asks the user for login and password. Then this data is sent via the socket to the client verification program.

- When in the database (txt file, unless it's easier for someone to SQL) this user is found after login and password, the verification program sends the relevant information back.

- Users are entered into the database "manually" by editing the txt / SQL insert file outside the program.

- If a given user is not found, the verification program also sends an appropriate message that will prohibit the client's application from proceeding
Passwords and logins canceled in plaintext.

- When the client's website interprets that the login was unsuccessful, it asks the user for the login and password until it is successful
When the login was successful -> point 2.

# Client side

- Each user has its own folder created on the first successful login

- after logging in, the user is asked what he wants to do "what do you want to do? store text, store image, show files, inspect {file}, exit?"

- logged user can create txt notes and put pictures in his folder (by entering the path):

- store text command - asks for the name of the txt file to be created and then for its content. Then the file is saved in the user folder

- store image command - asks for the path to the image on the PC. The picture is then saved in the user's directory

- logged user can use the command "show files" to display all the names of files in a folder, make sure that it is known whether the file is an image or a txt

- logged user can use command "inspect {filename}" to read the file. if it is a txt we print its content in the terminal, if the image is displayed:
the contents of the file ... are: ..........

- after executing any command except exit user is asked again what he wants to do.
 If the command execution was successful, what is described above, if not, the user is informed about the error / missing file etc. Exit closes the program.
