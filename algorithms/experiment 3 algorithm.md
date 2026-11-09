# Experiment 3 – Capturing and Analyzing SMTP Packets Using Wireshark

## Algorithm

1. Start.
2. Open Terminal 1 and start the SMTP server on port `8025` using `aiosmtpd`.
3. Open Wireshark and select the Loopback (`lo`) interface.
4. Start capturing packets in Wireshark.
5. Open Terminal 2 and connect to the SMTP server using `telnet localhost 8025`.
6. Type `HELO localhost` to identify the client.
7. Enter the sender address using `MAIL FROM` and the recipient address using `RCPT TO`.
8. Type `DATA` and enter the email headers and message body.
9. Type a single dot (`.`) on a new line to finish sending the email.
10. Type `QUIT` to close the SMTP session.
11. Apply the display filter `tcp.port == 8025` in Wireshark.
12. Stop the packet capture.
13. Analyze the captured packets to identify the source and destination IP addresses, client and server port numbers, SMTP commands, response codes, and email message content.
14. Stop.
