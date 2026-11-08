# Computer Networks Lab – Exam Programs

A collection of Computer Networks laboratory programs for practice and external examination preparation.

This repository contains C programs for Experiments 5–10. Each experiment includes the required client/server programs where applicable, along with commands to compile and run them on Linux.

> **Best wishes to all students appearing for the lab examination!**  
> Stay calm, understand the logic, practise the commands, and check your output carefully. Wishing you all the very best and great success in your examination!

---

## Contents

| Experiment | Topic | Programs |
|---|---|---|
| 5 | Matrix type identification using TCP | `exp5_server.c`, `exp5_client.c` |
| 6 | Client-server communication using UDP (abbreviation translator) | `exp6_udpserver.c`, `exp6_udpclient.c` |
| 7 | Multi-user chat server using TCP | `exp7_Chatserver.c`, `exp7_Chatclient.c` |
| 8 | Time server using UDP | `exp8_Timeserver.c`, `exp8_Timeclient.c` |
| 9 | File transfer using TCP | `exp9_Fileserver.c`, `exp9_Fileclient.c` |
| 10 | Packet capture using raw sockets | `exp10_packet.c` |

---

## 1. Requirements

- Linux operating system (Ubuntu, Pop!\_OS, or another Linux distribution).
- GCC compiler.
- Git.
- A terminal.
- For Experiment 7, POSIX threads support (`pthread`), provided by the system's C library/toolchain.
- For Experiment 10, administrator privileges (`sudo`) to create and use a raw packet socket.

Check whether GCC and Git are installed:

```bash
gcc --version
git --version
```

If GCC is not installed on Ubuntu/Pop!\_OS:

```bash
sudo apt update
sudo apt install build-essential git
```

---

## 2. Clone the repository

Open a terminal and move to the directory where you want to keep the project.

```bash
git clone https://github.com/MabelMoncy/cn_lab
```



Move into the cloned repository:

```bash
cd cn_lab
```

For example, if the cloned folder is named `network_lab_exam`:

```bash
cd cn_lab
```

List the files:

```bash
ls
```

Make sure the experiment source files are present.

---

## 3. General notes before running

- Open a **separate terminal for the server and the client**.
- Start the server first, then start the client.
- Run the commands from the repository directory, unless the command says otherwise.
- Keep the server terminal open while testing the client.
- The programs use port `8080`. If another program is already using that port, stop that program before running the experiment.
- For client/server programs that connect to `127.0.0.1`, run both programs on the same computer.
- Press `Ctrl + C` to stop a server that runs continuously.
- If a command reports that a source file does not exist, check its spelling and capitalization with `ls`. Linux filenames are case-sensitive.

---

# Experiment 5 – Matrix Type Identification Using TCP

### Files

- `exp5_server.c`
- `exp5_client.c`

### Compile

Run these commands separately:

```bash
gcc exp5_server.c -o exp5_server
gcc exp5_client.c -o exp5_client
```

### Run

**Terminal 1 – Server**

```bash
./exp5_server
```

**Terminal 2 – Client**

```bash
./exp5_client
```

Enter the matrix order when the client asks for it. The client generates and displays a matrix, sends it to the server, and displays the matrix type returned by the server.

---

# Experiment 6 – Client-Server Communication Using UDP

### Files

- `exp6_udpserver.c`
- `exp6_udpclient.c`

### Compile

```bash
gcc exp6_udpserver.c -o exp6_udpserver
gcc exp6_udpclient.c -o exp6_udpclient
```

### Run

**Terminal 1 – Server**

```bash
./exp6_udpserver
```

**Terminal 2 – Client**

```bash
./exp6_udpclient
```

Enter a sentence containing abbreviations when prompted by the client. The server translates the supported abbreviations and sends the translated sentence back.

---

# Experiment 7 – Multi-User Chat Server Using TCP

### Files

- `exp7_Chatserver.c`
- `exp7_Chatclient.c`

### Compile

Use `-pthread` when compiling both programs:

```bash
gcc -pthread exp7_Chatserver.c -o exp7_Chatserver
gcc -pthread exp7_Chatclient.c -o exp7_Chatclient
```

### Run

Open at least **three terminals**.

**Terminal 1 – Server**

```bash
./exp7_Chatserver
```

**Terminal 2 – Client 1**

```bash
./exp7_Chatclient
```

**Terminal 3 – Client 2**

```bash
./exp7_Chatclient
```

Type a message in either client. The server forwards it to the other connected clients; the sender does not receive its own message back from the server.

You can open more client terminals to test multiple users, subject to the server's configured client limit.

---

# Experiment 8 – Time Server Using UDP

### Files

- `exp8_Timeserver.c`
- `exp8_Timeclient.c`

### Compile

```bash
gcc exp8_Timeserver.c -o exp8_Timeserver
gcc exp8_Timeclient.c -o exp8_Timeclient
```

### Run

**Terminal 1 – Server**

```bash
./exp8_Timeserver
```

**Terminal 2 – Client**

```bash
./exp8_Timeclient
```

The client sends a time request to the server. The server reads the current system time and sends it back to the client.

The time server continues running so that it can respond to further client requests. Stop it with `Ctrl + C` when finished.

---

# Experiment 9 – File Transfer Using TCP

### Files

- `exp9_Fileserver.c`
- `exp9_Fileclient.c`

### Compile

```bash
gcc exp9_Fileserver.c -o exp9_Fileserver
gcc exp9_Fileclient.c -o exp9_Fileclient
```

### Prepare a test file

Create a small text file in the server's current working directory:

```bash
echo "This is a test file for the TCP file transfer experiment." > sample.txt
```

The client requests a filename, and the server looks for that file in the server process's current working directory. For this test, enter:

```text
sample.txt
```

### Run

**Terminal 1 – Server**

```bash
./exp9_Fileserver
```

**Terminal 2 – Client**

```bash
./exp9_Fileclient
```

When prompted, enter the filename:

```text
sample.txt
```

The client displays the server response and the file contents if the file exists. If it does not exist, the server sends an error message.

> **Important:** The requested file must be available in the directory from which the server is running. The server handles client requests using child processes created with `fork()`.

---

# Experiment 10 – Packet Capture Using Raw Socket

### File

- `exp10_packet.c`

### Compile

```bash
gcc exp10_packet.c -o exp10_packet
```

### Run

Raw packet capture requires permission to create an `AF_PACKET` raw socket. Run the executable with `sudo`:

```bash
sudo ./exp10_packet
```

The program captures IPv4 packets and displays:

- Packet number
- Packet size
- Source IP address
- Destination IP address

To stop packet capture, press:

```text
Ctrl + C
```

> **Permission note:** `sudo` is required when running this program because raw packet sockets need elevated privileges on a typical Linux system. Compile the program normally; `sudo` is needed for execution, not compilation. Only capture traffic on systems and networks where you have permission.

---

## 4. Quick command reference

| Experiment | Compile | Run |
|---|---|---|
| 5 – TCP Matrix | `gcc exp5_server.c -o exp5_server` and `gcc exp5_client.c -o exp5_client` | `./exp5_server` then `./exp5_client` |
| 6 – UDP Translator | `gcc exp6_udpserver.c -o exp6_udpserver` and `gcc exp6_udpclient.c -o exp6_udpclient` | `./exp6_udpserver` then `./exp6_udpclient` |
| 7 – TCP Chat | `gcc -pthread exp7_Chatserver.c -o exp7_Chatserver` and `gcc -pthread exp7_Chatclient.c -o exp7_Chatclient` | `./exp7_Chatserver` then run two or more clients |
| 8 – UDP Time | `gcc exp8_Timeserver.c -o exp8_Timeserver` and `gcc exp8_Timeclient.c -o exp8_Timeclient` | `./exp8_Timeserver` then `./exp8_Timeclient` |
| 9 – TCP File Transfer | `gcc exp9_Fileserver.c -o exp9_Fileserver` and `gcc exp9_Fileclient.c -o exp9_Fileclient` | `./exp9_Fileserver` then `./exp9_Fileclient` |
| 10 – Packet Capture | `gcc exp10_packet.c -o exp10_packet` | `sudo ./exp10_packet` |

For each client/server experiment, start the server before the client. Use separate terminals.

---

## 5. Troubleshooting

### `Address already in use`

Another process may already be using port `8080`. Stop the earlier server process before starting the new one.

### `Connection refused`

Check that the server is running before starting the client. Also confirm that both programs use the expected port and address.

### `Permission denied` in Experiment 10

Run the packet capture executable with:

```bash
sudo ./exp10_packet
```

### `No such file or directory`

Check the current directory and exact filename:

```bash
pwd
ls
```

Remember that uppercase and lowercase letters are different in Linux filenames.

### `gcc: command not found`

Install GCC and the build tools:

```bash
sudo apt update
sudo apt install build-essential
```

---

## 6. Final checklist

Before the lab examination, make sure you can:

- [ ] Clone the repository and enter the project directory.
- [ ] Compile each C program separately.
- [ ] Start the server before the client.
- [ ] Run client and server in separate terminals.
- [ ] Run two or more clients for the chat experiment.
- [ ] Provide a valid test filename for the file transfer experiment.
- [ ] Run the packet capture program using `sudo`.
- [ ] Explain the main steps of each experiment's algorithm.
- [ ] Identify the purpose of important socket functions such as `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, `recv()`, `sendto()` and `recvfrom()`.

---

## All the best!

**Wishing every student the very best for the Computer Networks Lab External Examination!**

Prepare well, practise each program, understand the logic instead of only memorising the code, and stay confident during the examination.

**Good luck, everyone! May you all achieve excellent results!**
