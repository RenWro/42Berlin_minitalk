# 42Berlin_minitalk
Minitalk is a project that aims to build a communication program in the form of a client and a server

---
<h2>Overview</h2>

The Minitalk project is a network communication project that involves two main components: a client and a server. The client is responsible for sending messages to the server, while the server receives and displays the messages.

The communication between the client and server is achieved using UNIX signals. The client converts each character of the message into a binary representation and sends it to the server using the SIGUSR1 and SIGUSR2 signals. The server receives the signals, converts the binary representation back into characters, and displays the received message.

The project requires the implementation of both the client and server programs, as well as handling various edge cases and error conditions. It also involves handling signal handling and synchronization between the client and server processes.

### Objective
The goal of the MiniTalk project is to create a **server** and a **client** that communicate with each other using **sockets** (network communication).  
The **server** should be ready to receive messages from the client and print the received message.  
Messages are sent asynchronously through **Unix signals** (`SIGUSR1` and `SIGUSR2`), which requires the client to send the message bit by bit (in binary) to the server.

### Key Challenges
- **Understanding Unix signals**: In MiniTalk, messages are sent and received through signals, and the client needs to send each bit of the message using `SIGUSR1` (for 0) and `SIGUSR2` (for 1).
  
- **Binary message encoding**: The client must encode the message to be sent to the server and send the bits via signals. The server, in turn, must decode these signals to reconstruct the original message.
  
- **Handling asynchronous signals**: Since the system uses asynchronous signals, the server must be able to handle these signals while performing other tasks.
