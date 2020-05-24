# Messenger program
  - Created by : Sangryu Park (psrpsj@gmail.com)
  - Program language used : C

## 1. How to run program
  - The program do have Makefile that support to build the program.
  ### make all (or simply make) : will compile all file (both client and server) need to run.
  ### make client : will compile client.c and produce client.
  ### make server : will compile server.c and produce server.
  ### make clean : delete all file that were produce during process.

## 2. Program description
  - The program execute the chatting program between client and server back and forth. With UDP Socket Programmning, able to communicate with proper connection.
  - Assumption : The program will send message from client side first and server will reply it to client. Also the client is the only one has the option to terminate the program.

## 3. Any bugs or issue
  - During the program, the program will run until the user enter "end". To detect, used strcmp function from <string.h>. However if strcmp properly works, the strcmp should result 0, but actually it returns 10. In the program, therefore it has input of 10 in order to work.
