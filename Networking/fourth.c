//library includes
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>

//defines
char *remote_address = "127.0.0.1";
char *remote_domain = "en.wikipedia.org";
short remote_port = 80;

//declarations
int addr_connect(char *add, short port);
int domain_connect(char *domain, short port);
void error(char *msg);
int read_in(int socket, char *buf, int len);
int say(int socket, char *s);
void handle_shutdown(int sig);
int catch_signal(int sig, void(*handler)(int));

//program entrypoint
int
main(int argc, char *argv[]) {
  
  int s;
  char buf[255];
  char rec[255];
  
  //register interrupt handler
  if(catch_signal(SIGINT, handle_shutdown) == -1)
    error("Cannot register interrupt handler!");
  
  //connect to domain
  s = domain_connect(remote_domain, remote_port);
  if(s == -1)
    error("Could not connect to domain");
  
  /*
  //connect to address
  s = addr_connect(remote_address, remote_port) == -1);
  if(s == -1)
    error("Could not connect to address");
  */
  
  //sleep(3);
  sprintf(buf, "GET /wiki/%s http/1.1\r\n", argv[1]);
  printf("\nbuffer = %s\n", buf);
  say(s, buf);
  say(s, "Host: en.wikipedia.org\r\n\r\n");
  
  /*
  int bytesRead = recv(s, rec, 255, 0);
  while(bytesRead) {
    if(bytesRead == -1)
      error("Cant read from server");
    rec[bytesRead] = '\0';
    printf("%s", rec);
    bytesRead = recv(s, rec, 255, 0);
  }
  */
  
  int bytesRead = read_in(s, rec, 255);
  
  rec[bytesRead] = '\0';
  printf("\nRead %i bytes, %s\n", bytesRead, rec);
  
  close(s);
  return 0;
 
}

//connect client to remote port using numeric address
int
addr_connect(char *add, short port) {

  int s = socket(PF_INET, SOCK_STREAM, 0);
  if(s == -1)
    error("Cant open socket");
  struct sockaddr_in si;

  memset(&si, 0, sizeof(si));
  si.sin_family = PF_INET;
  si.sin_addr.s_addr = inet_addr(add);
  si.sin_port = htons(port);

  return connect(s, (struct sockaddr *) &si, sizeof(si));

}

//connect client to remote port using DNS
int
domain_connect(char *domain, short port) {
  
  struct addrinfo *res;
  struct addrinfo hints;
  char str_port[6];
  
  sprintf(str_port, "%d", port);
  printf("%s, %s, %i", domain, str_port, port);
  //sleep(3);
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  
  if(getaddrinfo(domain, str_port, &hints, &res) == -1)
    error("Cant resolve domain name");
  else
    printf("\n%i, %i, %i\n", res->ai_family, res->ai_socktype, res->ai_protocol);
  int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(s == -1)
    error("Cant open socket");
  int status = connect(s, res->ai_addr, res->ai_addrlen);
  if(status == -1)
    error("Cant connect");
  freeaddrinfo(res);
  
  return s;
  
}

//read characters from socket
int
read_in(int socket, char *buf, int len) {
  
  char *s = buf;
  int slen = len;
  int c = recv(socket, s, slen, 0);
  
  while((c > 0) && (s[c-1] != '\n')) {
    s += c;
    slen -= c;
    c = recv(socket, s, slen, 0);
  }
  
  if(c < 0)
    return c;
  else if(c == 0)
    buf[0] = '\0';
  else
    s[c-1] = '\0';
  
  return len - slen;
  
}

//write characters to socket
int
say(int socket, char *s) {
  
  int result = send(socket, s, strlen(s), 0);
  
  if(result == -1)
    fprintf(stderr, "%s: %s\n", "Error talking to server", strerror(errno));
  
  return result;

}

//print error
void
error(char *msg) {
  
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
  
}

//catch shutdown signal
void
handle_shutdown(int sig) {
  
  fprintf(stderr, "Signal shutdown...\n");
  exit(0);
  
}

//create signal handler
int catch_signal(int sig, void(*handler)(int)) {
  
  struct sigaction action;
  
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  
  return sigaction(sig, &action, NULL);

}