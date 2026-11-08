# Experiment 8 – Time Server Using UDP

## Algorithm for Server

1. Start the program.
2. Create a UDP socket.
3. Set the server address and port number.
4. Bind the socket to the server address.
5. Display "UDP Time Server Running...".
6. Wait for a request from a client using `recvfrom()`.
7. Receive the client's request and address.
8. Get the current system time.
9. Convert the time into a readable string.
10. Send the time string to the client using `sendto()`.
11. Repeat the process to serve other client requests.

## Algorithm for Client

1. Start the program.
2. Create a UDP socket.
3. Set the server address and port number.
4. Prepare the request message "TIME".
5. Send the request to the server using `sendto()`.
6. Wait for the server's response using `recvfrom()`.
7. Receive the time sent by the server.
8. Display the server time.
9. Close the socket.
10. Stop the program.
