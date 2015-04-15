#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

void error (char *msg);

int main(int argc, char *argv[]) {
  char *advice[] = {
    "Take smaller bites\r\n",
    "Go for the tight jeans, they don't make you look fat.\r\n",
    "One word: inappropriate\r\n",
    "Just for today, be honest.\r\n",
    "You might want to rethink that haircut\r\n"
  };
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  
  int reuse = 1;
  if(setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    error("Cant reuse socket");
  
  if(bind(listener_d, (struct sockaddr *) &name, sizeof(name)) == -1)
    error("Cannot bind port!");
  
  listen(listener_d, 10);
  puts("Waiting for connection...\n");
  while(1) { 
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    char *msg = advice[rand() % 5];
    printf("Client connected\n");
    send(connect_d, msg, strlen(msg), 0);
    close(connect_d);
  }
  
  return 0;
  
}

void error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}