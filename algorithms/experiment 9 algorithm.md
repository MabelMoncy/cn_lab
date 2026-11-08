# Experiment 9 – File Transfer Using TCP

## Algorithm for Server

1. Start the program.
2. Create a TCP socket.
3. Set the server address and port number.
4. Bind the socket to the server address.
5. Listen for client connections.
6. Display "File Server Running...".
7. Repeat the following steps:
   1. Accept a client connection.
   2. Create a child process using `fork()` to handle the client.
   3. In the child process, close the server socket.
   4. Receive the requested filename from the client.
   5. Open the requested file in read mode.
   6. Send the server process ID to the client.
   7. If the file does not exist, send an error message.
   8. Otherwise, read the file line by line and send its contents to the client.
   9. Close the file and client socket.
   10. End the child process.
   11. In the parent process, close its copy of the client socket and check for completed child processes.

## Algorithm for Client

1. Start the program.
2. Create a TCP socket.
3. Set the server address and port number.
4. Connect to the server.
5. Read the filename from the user.
6. Send the filename to the server.
7. Display "Response from Server:".
8. Receive the server response until the connection is closed.
9. Display the received response or file contents.
10. Close the socket.
11. Stop the program.
