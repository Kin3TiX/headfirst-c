#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

void error(char *msg);

int main() {
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  if(listender_d == -1)
    error("Can't open socket");
  
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = hton1(INADDR_ANY);
  int c = bind(listener_d, (struct sockaddr *) &name, sozeof(name));
  if(c == -1)
    error("Can't bind socket");
  
  if(listen(listener_d, 10) == -1)
    error("Can't listen");
  
  struct sockaddr_storage client_addr;
  unsigned int addr_size = sizeof(client_addr);
  int connect_d = accept(listener_d, (struct sockaddr *) &client_addr, &address_size);
  if(connect_d == -1)
    error("Can't open secondary socket");
  
  char *msg = "Internet Knock-Knock Protocol Server\r\nVersion 1.0\r\nKnock! Knock!\r\n> ";
  if(send(connect_d, msg, strlen(msg), 0) == -1)
    error("send error");
  
  return 0;
}

void error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}