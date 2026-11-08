# Experiment 6 – Client-Server Communication Using UDP

## Algorithm for Server

1. Start the program.
2. Create a UDP socket.
3. Set the server address and port number.
4. Bind the socket to the server address.
5. Display "UDP Server Running...".
6. Wait for a message from the client using `recvfrom()`.
7. Receive the sentence from the client.
8. Display the received sentence.
9. Split the sentence into words.
10. Convert each word to lowercase and compare it with the abbreviation list.
11. Replace each known abbreviation with its full form.
12. Keep other words unchanged.
13. Send the translated sentence to the client using `sendto()`.
14. Display "Translated message sent.".
15. Close the socket.
16. Stop the program.

## Algorithm for Client

1. Start the program.
2. Create a UDP socket.
3. Set the server address and port number.
4. Read a sentence from the user.
5. Send the sentence to the server using `sendto()`.
6. Wait for the translated sentence using `recvfrom()`.
7. Receive the translated sentence from the server.
8. Display the translated sentence.
9. Close the socket.
10. Stop the program.
