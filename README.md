# Messenger program
  - Created by : Sangryu Park (psrpsj@gmail.com)
  - Program language used : C
  - Project for CSCI4061 - Intorduction to Operating Systemm at UMN in Spring 2020

## 1. How to run program
  - The program implemented Makefile.
    ```
    make all (or simply make) : will compile all file (both client and server) need to run.

    make client : will compile client.c and produce client.

    make server : will compile server.c and produce server.
    
    make clean : delete all file that were produce during process.

## 2. Program description
  - The program execute the messenger program between client and server back and forth. With UDP Socket Programmning, able to communicate with proper connection.

  - Assumption : The program will send message from client side first and server will reply it to client. Also the client is the only one to terminate the program.


