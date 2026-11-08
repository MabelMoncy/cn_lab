# Experiment 10 – Packet Capture Using Raw Socket

## Algorithm

1. Start the program.
2. Create a raw packet socket to receive all Ethernet protocols.
3. Allocate memory for the packet buffer.
4. If socket creation or memory allocation fails, display an error and stop.
5. Initialize the packet count to zero.
6. Display "Packet Capture Started... (Ctrl+C to stop)".
7. Continuously receive packets using `recvfrom()`.
8. Check whether the received packet is large enough to contain Ethernet and IP headers.
9. If the packet is too small, ignore it and continue.
10. Read the Ethernet header.
11. Check whether the packet contains an IPv4 packet.
12. If it is not an IPv4 packet, ignore it and continue.
13. Read the IP header.
14. Extract the source IP address and destination IP address.
15. Increase the packet count.
16. Display the packet number, packet size, source IP address and destination IP address.
17. Repeat packet capture until the program is stopped.
18. Close the raw socket and free the allocated memory.
19. Stop the program.
