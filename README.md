# 42Berlin_minitalk
Minitalk is a project that aims to build a communication program in the form of a client and a server

---
<h2>Overview</h2>

The Minitalk project is a network communication project that involves two main components: a client and a server. The client is responsible for sending messages to the server, while the server receives and displays the messages.

The communication between the client and server is achieved using UNIX signals. The client converts each character of the message into a binary representation and sends it to the server using the SIGUSR1 and SIGUSR2 signals. The server receives the signals, converts the binary representation back into characters, and displays the received message.

The project requires the implementation of both the client and server programs, as well as handling various edge cases and error conditions. It also involves handling signal handling and synchronization between the client and server processes.
