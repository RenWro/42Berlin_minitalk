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

- ### About pid_t (Process ID Type)

The `pid_t` (Process ID Type) is a data type defined in the POSIX standard library (`sys/types.h`) that represents a process identifier (Process ID or simply PID).  
It is used to store values that identify processes in the operating system.

- It is a signed integer type, usually represented as `int`, but the exact implementation may vary between operating systems.
- It is used to identify processes in system calls such as `fork()`, `kill()`, `wait()`, and `getpid()`.

• The client takes two parameters:
◦ The server PID.
◦ The string to send.

In Minitalk, the client sends bits to the server one by one.

A signal is a way for a process to communicate asynchronously with another process or the kernel.
Each signal has a unique integer identifier. In this case we could only use these two signals: SIGUSR1 and SIGUSR2.

SIGUSR1 represents bit 1
SIGUSR2 represents bit 0
  

### 🌍 Global Variables and Their Use in Minitalk

#### 🔹 What is a Global Variable?
A **global variable** is a variable that is declared outside of all functions, making it accessible throughout the entire program. Unlike **local variables**, which are only available inside the function they are declared in, a global variable **retains its value across function calls** and can be modified by any part of the program.

#### 🔹 How to Declare a Global Variable in C:
```c
#include <stdio.h>

int g_counter = 0; // Global variable

void increment_counter() {
    g_counter++; // Modifying the global variable
    printf("Counter: %d\n", g_counter);
}

int main() {
    increment_counter();
    increment_counter();
    return 0;
}
```

### 🛠 Why Use a Global Variable in Minitalk?

In the **Minitalk client**, we use a **global variable `g_reply`** to track whether the **server has acknowledged a received bit**.

- Since **signals (`SIGUSR1`, `SIGUSR2`) are handled asynchronously**, we need a way to **store the acknowledgment status** between function calls.
- A **local variable inside `signal_reception()` would not work**, because it would be destroyed after the function ends.
- The **global variable persists across function calls**, allowing us to track when the server sends `SIGUSR1` in response.

### How is the server aknowledging each received message by sending a signal to the client?

The info->si_pid is a field in the siginfo_t structure that contains the process ID (PID) of the sender of the signal. This is used in the handle_signal function to identify which process sent the signal and to send an acknowledgment signal back to that process.

```c
void	handle_signal(int signal, siginfo_t *info, void *context)
{
    static int	current_bit = 0;

    (void)context;
    if (signal == SIGUSR1)
        g_message.current_char = (g_message.current_char << 1) | 1;
    else if (signal == SIGUSR2)
        g_message.current_char = (g_message.current_char << 1);
    current_bit++;
    if (current_bit == 8)
    {
        process_character();
        current_bit = 0;
    }
    if (kill(info->si_pid, SIGUSR1) == -1) // send acknowledgment signal to the client
        exit(EXIT_FAILURE);
}
```

In this code, info->si_pid is used to get the PID of the client process that sent the signal. The kill function is then used to send a SIGUSR1 signal back to the client to acknowledge that the server has received and processed the bit.

This acknowledgment mechanism ensures that the client knows when the server has successfully received each bit of the message, allowing the client to send the next bit.


### How to start the server step-by-step?

1. Compile the Project: make
2. Start the Server: ./server
3. Retrieve the PID: Server running with PID: 12345
4. Open a New Terminal for the Client and start client: ./client 12345 "Hello, Minitalk! 😊"
5. (Optional) Send Multiple Messages such as:
./client 12345 "First message."
./client 12345 "Second message."
./client 12345 "Third message."
6. To manually stop the server, press Ctrl + C or kill 12345




