#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSG_SIZE 512

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
} msg;


int main(int argc, char* argv[]){

  key_t key = 1234;
  int msgid = msgget(key, 0666 | IPC_CREAT);
  if(msgid == -1){
    perror("msgid error!");
    exit(1);
  }

  char input_message[MSG_SIZE];
  printf("Enter the message to server : ");
  fgets(input_message, MSG_SIZE, stdin);

  while(strcmp(input_message, "END") != 0){
    strcpy(msg.msg_text, input_message);
    msg.msg_type = 1;
    int result = msgsnd(msgid, &msg, sizeof(msg), 0);
    if(result < 0){
      printf("Error during sending message");
    }
    printf("Enter the message to server or enter END to end server : ");
    fgets(input_message, MSG_SIZE, stdin);
  }

  msgctl(msgid, IPC_RMID, NULL);
  printf("---- Messenger Successfully Terminated ----");

  return 0;
}
