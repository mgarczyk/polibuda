# Description
Client-server connection based on the socket library.

SERVER:
1) Listening.
2) Not a good password (wait for the good one).
3) We provide the path to the file.
4) Send this file byte by byte to the client.
5) After sending, close the socket responsible for a given client on the server.
6) We keep listening.


CLIENT:
1) Password / access code (maybe you have some?). List of passwords on the server in the form of a file (hashes, you may not need to).
2) Receive byte by byte and build from that file.
3) After picking up, we lock the client.
4) The End.
