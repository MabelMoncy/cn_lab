# Experiment 3 – Capturing and Analyzing SMTP Packets Using Wireshark

> **Course:** Computer Networks Lab  
> **Experiment:** 3  
> **Platform:** Linux / Pop!_OS  
> **Capture interface:** Loopback (`lo`)  
> **SMTP server:** `aiosmtpd` on `localhost:8025`

## 1. Aim

To capture and analyze SMTP packets using Wireshark and identify:

- Source and destination IP addresses
- Client and server port numbers
- SMTP server port number
- SMTP commands and response codes
- Email message content (Internet Message Format – IMF)

## 2. Requirements

- A computer running Linux
- Python 3
- Wireshark (already installed in the lab system)
- Telnet client
- `aiosmtpd` Python module

> **Note:** This guide does not include Wireshark installation because Wireshark is already available on the lab computers.

## 3. Python setup for the SMTP server

The experiment uses a local SMTP server created with the Python package `aiosmtpd`. It listens on port `8025`. No real email account or external SMTP server is needed.

### 3.1 Check whether aiosmtpd is already available

Open a terminal and run:

```bash
python3 -m aiosmtpd --help
```

- If the command displays the module's help information, `aiosmtpd` is available. You can proceed to **Section 4**.
- If it displays `No module named aiosmtpd`, follow the installation steps below.

> In some lab environments, the required Python module may already be installed. If it is available, there is no need to install it again.

### 3.2 Create a Python virtual environment (only if aiosmtpd is missing)

First, check that virtual-environment support is available:

```bash
python3 -m venv --help
```

If it is not available, install the support package:

```bash
sudo apt update
sudo apt install python3-venv
```

Create a virtual environment:

```bash
python3 -m venv ~/smtp-env
```

Activate it:

```bash
source ~/smtp-env/bin/activate
```

The terminal prompt should now begin with `(smtp-env)`.

Install `aiosmtpd` inside the virtual environment:

```bash
python -m pip install aiosmtpd
```

### Why is a virtual environment used?

Recent Ubuntu-based systems, including Pop!_OS, may prevent `pip` from installing packages directly into the system-managed Python environment. This protection is known as PEP 668 and may show an `externally-managed-environment` error.

A virtual environment keeps the package separate from the operating system's Python installation. Do not use `--break-system-packages` for this experiment.

### 3.3 Activate the environment in future sessions

If you installed `aiosmtpd` in `~/smtp-env`, activate that environment whenever you open a new terminal for this experiment:

```bash
source ~/smtp-env/bin/activate
```

If `aiosmtpd` was already available in the lab's Python environment, this activation step is not required.

## 4. Check the loopback interface

The SMTP client and server run on the same computer. Therefore, capture their traffic on the loopback interface.

Run:

```bash
ip link show lo
```

The output should contain an entry similar to:

```text
lo: <LOOPBACK,UP,LOWER_UP> ...
```

If the interface is down, enable it:

```bash
sudo ip link set lo up
```

Open the already-installed Wireshark application and confirm that `lo` (Loopback) appears in the interface list.

## 5. Capture the SMTP communication

Use two separate terminals:

- **Terminal 1:** SMTP server
- **Terminal 2:** SMTP client (Telnet)

### Step 1 – Start the SMTP server

In Terminal 1, activate the virtual environment only if you created one:

```bash
source ~/smtp-env/bin/activate
```

Start the SMTP server:

```bash
python -m aiosmtpd -n -l localhost:8025
```

Keep this terminal open. It may appear idle while waiting for a connection; this is expected.

### Step 2 – Start packet capture in Wireshark

1. Open Wireshark.
2. Select the **`lo` (Loopback)** interface.
3. Click **Start Capturing Packets**.

Start capturing before connecting with Telnet so that the connection setup and SMTP conversation are recorded.

### Step 3 – Connect to the SMTP server

Open Terminal 2 and run:

```bash
telnet localhost 8025
```

If Telnet is not available, install its client package:

```bash
sudo apt install telnet
```

A successful connection should show output similar to:

```text
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
220 localhost Python SMTP ...
```

The server greeting begins with `220`, which means that the SMTP service is ready.

Depending on how `localhost` resolves on your system, the connection may use IPv4 (`127.0.0.1`) or IPv6 (`::1`).

### Step 4 – Identify the client

At the Telnet prompt, enter:

```text
HELO localhost
```

The server should return a successful `250` response.

### Step 5 – Specify the sender

Enter:

```text
MAIL FROM:<sender@test.com>
```

Expected response:

```text
250 OK
```

### Step 6 – Specify the recipient

Enter:

```text
RCPT TO:<receiver@test.com>
```

Expected response:

```text
250 OK
```

### Step 7 – Compose and send the email

Enter:

```text
DATA
```

Expected response:

```text
354 End data with <CR><LF>.<CR><LF>
```

Now type the email headers and body. Press Enter at the end of each line:

```text
From: sender@test.com
To: receiver@test.com
Subject: SMTP Test Mail

This is a test email sent for SMTP packet analysis.
It contains a header section and a message body.
```

To finish the email, type a single dot on a new line:

```text
.
```

Expected response:

```text
250 OK
```

### Step 8 – Terminate the SMTP session

Enter:

```text
QUIT
```

Expected response:

```text
221 Bye
```

The SMTP session is now closed.

## 6. Filter and stop the capture

Return to Wireshark.

In the **Display Filter** bar, enter:

```text
tcp.port == 8025
```

Press Enter. This filter displays TCP packets where either the source or destination port is `8025`.

Stop the capture using **Capture → Stop** (or the red Stop button).

To save the capture:

1. Select **File → Save As**.
2. Choose a suitable folder.
3. Save the file with a `.pcapng` extension, for example:

```text
experiment-3-smtp-capture.pcapng
```

## 7. Analyze the captured packets

### 7.1 Source and destination IP addresses

1. Select a packet in the packet list.
2. Expand **Internet Protocol Version 4** or **Internet Protocol Version 6** in the Packet Details pane.
3. Read the source and destination addresses.

Because both applications run on the same computer, both addresses should be loopback addresses:

- IPv4 loopback: `127.0.0.1`
- IPv6 loopback: `::1`

**Observed in our capture:**

| Field | Observed value |
|---|---|
| Source IP | `::1` |
| Destination IP | `::1` |

`::1` is the IPv6 loopback address. It serves the same local-host purpose as IPv4 address `127.0.0.1`.

### 7.2 Client and server port numbers

1. Select a packet travelling from the client to the server.
2. Expand **Transmission Control Protocol** in Packet Details.
3. Read **Source Port** and **Destination Port**.

For a client-to-server packet:

- Source Port = client port (dynamically assigned)
- Destination Port = server port (`8025`)

For a server-to-client packet, the source and destination ports are reversed.

**Observed in our capture:**

| Field | Observed value |
|---|---:|
| Client port | `44488` |
| Server port | `8025` |

The client port is temporary and may be different in another run.

### 7.3 SMTP server port number

The SMTP server was started with:

```bash
python -m aiosmtpd -n -l localhost:8025
```

Therefore, its listening port for this experiment is `8025`. The commonly used standard SMTP server port is `25`.

### 7.4 SMTP commands and response codes

Use **Follow TCP Stream** to inspect the SMTP conversation:

1. Right-click a packet belonging to the SMTP connection.
2. Select **Follow → TCP Stream**.
3. Read the client and server communication in the window.

Commands and response codes to identify:

| Command / code | Meaning |
|---|---|
| `HELO` | Identifies the client to the server |
| `MAIL FROM` | Specifies the sender email address |
| `RCPT TO` | Specifies the recipient email address |
| `DATA` | Starts the email message content |
| `QUIT` | Terminates the SMTP session |
| `220` | Service ready |
| `250` | Requested action completed successfully |
| `354` | Start mail input; end with a single dot |
| `221` | Service closing the transmission channel |

### 7.5 Internet Message Format (IMF) content

In the **Follow TCP Stream** window, locate the content sent after the `DATA` command.

Identify the email fields:

| Field | Value in this experiment |
|---|---|
| From | `sender@test.com` |
| To | `receiver@test.com` |
| Subject | `SMTP Test Mail` |
| Message body | `This is a test email sent for SMTP packet analysis. It contains a header section and a message body.` |

The email headers and message body are carried as part of the SMTP DATA exchange. This email content is referred to as the Internet Message Format (IMF) content in the experiment.

## 8. Observations from our completed run

These values were observed in the actual capture completed on our Pop!_OS system:

| Item | Actual observation |
|---|---|
| Capture interface | `lo` (Loopback) |
| Transport protocol | TCP |
| Source IP | `::1` |
| Destination IP | `::1` |
| Client port | `44488` |
| SMTP server port | `8025` |
| SMTP commands | `MAIL FROM`, `RCPT TO`, `DATA`, `QUIT` were visible in the Follow TCP Stream view |
| SMTP response codes | `220`, `250`, `354`, `221` |
| Sender | `sender@test.com` |
| Recipient | `receiver@test.com` |
| Subject | `SMTP Test Mail` |
| Message body | Test message entered in the DATA phase |

**Note about HELO:** The procedure asks you to send `HELO localhost`. In the saved Follow TCP Stream screenshot from our run, the `HELO` text itself was not visible; the server greeting and subsequent `250 pop-os.local` response were visible. In a fresh run, check the stream to confirm the exact command and response rather than assuming every capture will show identical text.

**Note about IP addresses:** The lab handout lists `127.0.0.1` as the loopback address. Our actual capture used IPv6 loopback `::1`. Record the address shown by your own capture.

## 9. Troubleshooting

### Problem: `No module named aiosmtpd`

If the lab system does not already have the module, create and activate a virtual environment, then install it:

```bash
python3 -m venv ~/smtp-env
source ~/smtp-env/bin/activate
python -m pip install aiosmtpd
```

### Problem: `externally-managed-environment`

This means the system Python environment is managed by the operating system. Use the virtual-environment steps above. Do not force installation into system Python with `--break-system-packages`.

### Problem: `telnet: command not found`

Install the Telnet client:

```bash
sudo apt install telnet
```

### Problem: `lo` is missing in Wireshark

Check the interface:

```bash
ip link show lo
```

If it is down:

```bash
sudo ip link set lo up
```

If it still does not appear, ask the lab administrator to check the Wireshark capture permissions on that computer.

### Problem: No packets appear with the display filter

- Confirm that the SMTP server is still running in Terminal 1.
- Confirm that Wireshark is capturing on `lo`.
- Confirm that Telnet connected to port `8025`.
- Generate a new SMTP session while capture is running.
- Reapply this display filter:

```text
tcp.port == 8025
```

### Problem: The packets are labelled TCP instead of SMTP

The server uses the non-standard port `8025`. Wireshark may identify the packets as TCP rather than automatically labelling them SMTP.

Use **Right-click → Follow → TCP Stream** to inspect the SMTP text conversation. This is sufficient to identify the commands, responses, and email content.

## 10. Result

SMTP packets were successfully captured and analyzed using Wireshark. The source and destination IP addresses, client and server port numbers, SMTP commands, SMTP response codes, and email message content were identified and studied successfully.

## 11. Quick command reference

**Check whether aiosmtpd is available:**

```bash
python3 -m aiosmtpd --help
```

**Optional one-time Python setup, only if aiosmtpd is missing:**

```bash
python3 -m venv ~/smtp-env
source ~/smtp-env/bin/activate
python -m pip install aiosmtpd
```

**Start the SMTP server (Terminal 1):**

```bash
source ~/smtp-env/bin/activate
python -m aiosmtpd -n -l localhost:8025
```

If `aiosmtpd` is already installed in the system Python, the activation line is not needed.

**Connect from Terminal 2:**

```bash
telnet localhost 8025
```

**SMTP commands (enter one at a time):**

```text
HELO localhost
MAIL FROM:<sender@test.com>
RCPT TO:<receiver@test.com>
DATA
From: sender@test.com
To: receiver@test.com
Subject: SMTP Test Mail

This is a test email sent for SMTP packet analysis.
It contains a header section and a message body.
.
QUIT
```

**Wireshark display filter:**

```text
tcp.port == 8025
```

---

## Important reminders

- Wireshark is assumed to be already installed on the lab computer; this guide does not cover its installation.
- Check whether `aiosmtpd` is already available before installing it.
- If the module is available, no Python package installation is needed.
- If it is missing, use a virtual environment rather than modifying system Python.
- Start the SMTP server before connecting with Telnet.
- Start Wireshark capture on `lo` before sending SMTP commands.
- Keep the SMTP server terminal running until the session is finished.
- Enter SMTP commands in the Telnet terminal, not in Wireshark.
- End the email DATA section with a single dot (`.`) on a line by itself.
- Use the actual IP address and client port shown in your own capture; these may differ between runs.
- Save the `.pcapng` file if you need to submit or review the captured packets.
