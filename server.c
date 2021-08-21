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
  int sockfd, received, cli_len;
  char input_message[MSG_SIZE];
  char received_message[MSG_SIZE];
  struct sockaddr_in service_addr, client_addr;
  socklen_t addrlen;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0){
    perror("sockfd error\n");
    exit(1);
  }

  memset(&service_addr, 0, sizeof(service_addr));
  memset(&client_addr, 0, sizeof(client_addr));

  service_addr.sin_family = AF_INET;
  service_addr.sin_addr.s_addr = INADDR_ANY;
  service_addr.sin_port = htons(PORT);

  if(bind(sockfd, (const struct sockaddr*)&service_addr, sizeof(service_addr)) < 0){
    perror("bind error\n");
    exit(1);
  }

  cli_len = sizeof(client_addr);

  received =  recvfrom(sockfd, (char *) received_message, MSG_SIZE, 0, (struct sockaddr *)&client_addr, &cli_len);
  received_message[received] = '\0';
  printf("Received message : %s", received_message);

  while(strcmp(received_message, "end\n") != 0){
    printf("Enter the message to send : ");
    fgets(input_message, MSG_SIZE, stdin);
    sendto(sockfd, (const char *)input_message, strlen(input_message), 0, (const struct sockaddr *)&client_addr, cli_len);
    received =  recvfrom(sockfd, (char *) received_message, MSG_SIZE, 0, (struct sockaddr *)&client_addr, &addrlen);
    received_message[received] = '\0';
    printf("Received message : %s", received_message);
  }

  close(sockfd);
  printf("---- Messenger Successfully Terminated ----");

  return 0;
}
