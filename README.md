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
| 8 | Time server using UDP | `exp8_Timeserver.c`, `exp8_Timeclient.c` |
| 9 | File transfer using TCP | `exp9_Fileserver.c`, `exp9_Fileclient.c` |

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

## 4. Quick command reference

| Experiment | Compile | Run |
|---|---|---|
| 5 – TCP Matrix | `gcc exp5_server.c -o exp5_server` and `gcc exp5_client.c -o exp5_client` | `./exp5_server` then `./exp5_client` |
| 6 – UDP Translator | `gcc exp6_udpserver.c -o exp6_udpserver` and `gcc exp6_udpclient.c -o exp6_udpclient` | `./exp6_udpserver` then `./exp6_udpclient` |
| 8 – UDP Time | `gcc exp8_Timeserver.c -o exp8_Timeserver` and `gcc exp8_Timeclient.c -o exp8_Timeclient` | `./exp8_Timeserver` then `./exp8_Timeclient` |
| 9 – TCP File Transfer | `gcc exp9_Fileserver.c -o exp9_Fileserver` and `gcc exp9_Fileclient.c -o exp9_Fileclient` | `./exp9_Fileserver` then `./exp9_Fileclient` |

For each client/server experiment, start the server before the client. Use separate terminals.

---
## All the best!

**Wishing every student the very best for the Computer Networks Lab External Examination!**

Prepare well, practise each program, understand the logic instead of only memorising the code, and stay confident during the examination.

**Good luck, everyone! May you all achieve excellent results!**
