# Experiment 5 – Matrix Type Identification Using TCP

## Algorithm for Server

1. Start the program.
2. Create a TCP socket.
3. Set the server address and port number.
4. Bind the socket to the server address.
5. Listen for client connections.
6. Accept a connection from the client.
7. Receive the order of the matrix from the client.
8. Receive the matrix from the client.
9. Check the matrix elements using two loops.
10. Check whether all elements above and below the main diagonal are zero.
11. If all non-diagonal elements are zero, identify it as a Diagonal Matrix.
12. Otherwise, check whether all elements below the main diagonal are zero.
13. If true, identify it as an Upper Triangular Matrix.
14. Otherwise, check whether all elements above the main diagonal are zero.
15. If true, identify it as a Lower Triangular Matrix.
16. Otherwise, identify it as Neither Upper nor Lower nor Diagonal.
17. Send the matrix type to the client.
18. Close the client and server sockets.
19. Stop the program.

## Algorithm for Client

1. Start the program.
2. Create a TCP socket.
3. Set the server address and port number.
4. Connect to the server.
5. Read the order of the matrix from the user.
6. Generate a matrix with random 0s and 1s.
7. Display the generated matrix.
8. Send the matrix order to the server.
9. Send the matrix to the server.
10. Receive the matrix type from the server.
11. Display the matrix type.
12. Close the socket.
13. Stop the program.
