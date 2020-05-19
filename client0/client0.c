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
char last_message[MSG_SIZE];
char input_message[MSG_SIZE];

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
} msg;

void checkMessage(int msg_id){
  msgrcv(msg_id, &msg, sizeof(msg), 1, 0);
  if(msg.msg_text == NULL){
    printf("No new message\n");
  }
  else if(strcmp(last_message, msg.msg_text) != 0){
    printf("New message arrived\n");
    strcpy(msg.msg_text, last_message);
    printf("Arrived message : %s", last_message);
  }
  else{
    printf("No new message\n");
  }
}

int sendMessage(int msg_id){
  int result;
  printf("Enter the message to server : ");
  fgets(input_message, MSG_SIZE, stdin);
  strcpy(msg.msg_text, input_message);
  msg.msg_type = 1;
  result = msgsnd(msg_id, &msg, sizeof(msg),0);
  if(result < 0){
    printf("Error during sending message! \n");
    return 1;
  }
  printf("Message successfully send");
  return 0;
}

int main(int argc, char* argv[]){
  int sending;
  key_t key = 1234;
  int msgid = msgget(key, 0666 | IPC_CREAT);
  printf("PASF");
  if(msgid == -1){
    perror("msgid error!");
    exit(1);
  }

  while(strcmp(input_message, "END") != 0){
    checkMessage(msgid);
    sendMessage(msgid);
  }

  msgctl(msgid, IPC_RMID, NULL);
  printf("---- Messenger Successfully Terminated ----");

  return 0;
}
