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
  struct sockaddr_in service_addr;

  //Create socket
  sockfd = socket(AF_INET, SOCK_DGRAM,0);
  if(sockfd < 0){
    perror("Socket creation error");
    exit(1);
  }

  service_addr.sin_family = AF_INET;
  service_addr.sin_port = htons(PORT);
  service_addr.sin_addr.s_addr = INADDR_ANY;

  while(strcmp(input_message, "end") != 0){
    socklen_t addrlen;

    printf("Enter the message to send or end to terminate : ");
    fgets(input_message, MSG_SIZE - 1, stdin);

    sendto(sockfd, (const char *)input_message, strlen(input_message), 0, (const struct sockaddr *) &service_addr, sizeof(service_addr));

    received = recvfrom(sockfd, (char *)input_message, MSG_SIZE, 0, (struct sockaddr *)&service_addr, &addrlen);
    input_message[received] = '\0';
    printf("Arrived message : %s", input_message);
  }

  close(sockfd);
  printf("---- Messenger Successfully Terminated ----");

  return 0;
}
