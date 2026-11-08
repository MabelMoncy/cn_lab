# Experiment 7 – Multi-User Chat Server Using TCP

## Algorithm for Server

1. Start the program.
2. Create a TCP socket.
3. Initialize the mutex lock.
4. Set the server address and port number.
5. Bind the socket to the server address.
6. Listen for client connections.
7. Display "Server running on port 8080".
8. Repeat the following steps:
   1. Accept a client connection.
   2. Check whether the maximum number of clients has been reached.
   3. If the limit is reached, close the new client connection.
   4. Otherwise, add the client socket to the client list.
   5. Create a new thread to handle that client.
9. In the client-handling thread, receive messages from the client.
10. Add a null character at the end of each received message.
11. Lock the mutex and send the message to all other connected clients.
12. Unlock the mutex.
13. When a client disconnects, remove it from the client list and close its socket.
14. Continue accepting other clients.

## Algorithm for Client

1. Start the program.
2. Create a TCP socket.
3. Set the server address and port number.
4. Connect to the server.
5. Create a separate thread to receive messages from the server.
6. In the receiving thread, continuously receive and display messages.
7. In the main thread, read a message from the user.
8. Send the message to the server.
9. Repeat receiving and sending messages while the connection is active.
10. Close the socket when the client exits.
11. Stop the program.
