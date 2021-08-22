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
  char received_message[MSG_SIZE];
  char input_message[MSG_SIZE];
  struct sockaddr_in service_addr;
  socklen_t addrlen;

  //Create socket
  sockfd = socket(AF_INET, SOCK_DGRAM,0);
  if(sockfd < 0){
    perror("Socket creation error");
    exit(1);
  }

  memset(&service_addr, 0, sizeof(service_addr));
  service_addr.sin_family = AF_INET;
  service_addr.sin_port = htons(PORT);
  service_addr.sin_addr.s_addr = INADDR_ANY;

  printf("Enter message to send or enter end to terminamte process\n");
  printf("Message : ");
  fgets(input_message, MSG_SIZE, stdin);
  sendto(sockfd, (const char *)input_message, strlen(input_message), 0, (const struct sockaddr *) &service_addr, sizeof(service_addr));

  while(strcmp(input_message, "end\n") != 0){
    received = recvfrom(sockfd, (char *)received_message, MSG_SIZE, 0, (struct sockaddr *)&service_addr, &addrlen);
    received_message[received] = '\0';
    printf("Arrived message : %s", received_message);
    printf("Enter message to send or enter end to terminamte process\n");
    printf("Message : ");
    fgets(input_message, MSG_SIZE, stdin);
    sendto(sockfd, (const char *)input_message, strlen(input_message), 0, (const struct sockaddr *) &service_addr, sizeof(service_addr));
  }

  printf("---- Messenger Successfully Terminated ----");
  close(sockfd);
  return 0;
}
