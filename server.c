#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MSG_SIZE 1024

int main(int argc, char** argv){
  int sockfd, received;
  char input_message[MSG_SIZE];
  char received_message[MSG_SIZE];
  struct sockaddr_in service_addr, client_addr;
  socklen_t addrlen;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0){
    perror("sockfd error\n");
    exit(1);
  }

  service_addr.sin_family = AF_INET;
  service_addr.sin_addr.s_addr = INADDR_ANY;
  service_addr.sin_port = htons(PORT);

  if(bind(sockfd, (const struct sockaddr*)&service_addr, sizeof(service_addr)) < 0){
    perror("bind error\n");
    exit(1);
  }

  received =  recvfrom(sockfd, (char *) received_message, MSG_SIZE, 0, (struct sockaddr *)&client_addr, &addrlen);
  received_message[received] = '\0';
  printf("Received message : %s\n", received_message);

  //while(strcmp(input_message, "end") != 0){
    printf("Enter the message to send : ");
    fgets(input_message, MSG_SIZE -1, stdin);
    sendto(sockfd, (const char *)input_message, strlen(input_message), 0, (const struct sockaddr *)&client_addr, sizeof(client_addr));
    //listen(sockfd, 1);
    received =  recvfrom(sockfd, (char *) input_message, MSG_SIZE, 0, (struct sockaddr *)&client_addr, &addrlen);
    received_message[received] = '\0';
    printf("Received message : %s\n", received_message);
  //}

  close(sockfd);
  printf("---- Messenger Successfully Terminated ----");

  return 0;
}
