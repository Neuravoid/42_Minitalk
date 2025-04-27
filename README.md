
# Minitalk

Welcome to **Minitalk**, a project developed as part of the 42 curriculum.  
This program implements a simple communication protocol between two processes (server and client) using Unix signals (`SIGUSR1` and `SIGUSR2`) to transmit messages bit by bit.

## Project Overview

- **Server**: Receives messages sent bit-by-bit via signals and reconstructs them into characters.
- **Client**: Sends a string message to the server process by encoding each character into signals.

The communication is fully asynchronous and showcases process handling and signal manipulation at a low system level.

## Features

- Server and client implemented in pure C.
- Bit-by-bit transmission of strings using Unix signals.
- Proper handling of connection and message integrity.
- Error management (invalid PID, empty messages, etc.).
- Memory management without leaks (validated with `valgrind`).

## Installation

### Requirements
- Unix-based OS (Linux / macOS)
- `gcc` compiler
- `make`

### Clone the repository
```bash
git clone https://github.com/your_username/minitalk.git
cd minitalk
```

### Compile
```bash
make
```

## Usage

### Start the server
```bash
./server
```
The server will display its **PID**. Example:
```
Server PID: 12345
```

### Start the client
```bash
./client [SERVER_PID] [MESSAGE]
```
Example:
```bash
./client 12345 "Hello, world!"
```

The message will be transmitted to the server process, and the server will print the message once completely received.

## How It Works

- Each character is sent **bit-by-bit**.
- `SIGUSR1` represents a binary `1`, `SIGUSR2` represents a binary `0`.
- The server captures these signals, reconstructs each character, and prints the final message.
- After each character transmission, the client waits for an acknowledgment (optional bonus).

## Bonus Features (if implemented)

- Acknowledgment system between client and server.
- Unicode / Extended ASCII character support.
- Support for multi-message sessions.
- Error reporting and handling for invalid scenarios.

## Notes

- Proper use of `malloc` and `free` ensures no memory leaks.
- Good practice of Unix signal handling, including signal blocking and safe reception.
- Respect for the norm and project rules of 42.

## License

This project is part of the 42 School curriculum and follows its academic honesty policy.
