//library includes
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

//function declarations
void error (char *msg);
int read_in(int socket, char *buf, int len);
int open_listener();
void bind_socket(int socket, int port);
int say(int socket, char *s);
void handle_shutdown(int sig);

//variable declarations
int listener_d;
char *prompts[] = {
  "knock, knock!\n",
  "oscar\n",
  "oscar stupid question, get a stupid answer!\n",
  "incorrect response, I'm afraid\n"
};
char *responses[] = {
  "who's there?\r",
  "oscar who?\r"
};

//main entrypoint
int
main(int argc, char *argv[]) {
  
  //register interrupt handler
  if(catch_signal(SIGINT, handle_shutdown) == -1)
    error("Cannot register interrupt handler!");
  
  //create listener socket
  listener_d = open_listener();
  
  //bind listener to port 30000
  bind_socket(listener_d, 30000);
  
  //begin listening on socket
  if(listen(listener_d, 10) == -1)
    error("Can't listen on port!");
  puts("Waiting for client connections...\n");
  
  //create client socket holder
  struct sockaddr_storage client_addr;
  unsigned int address_size = sizeof(client_addr);
  
  //ignore waiting for children
  signal(SIGCHLD, SIG_IGN);
  
  //accept connections and talk to clients
  char buffer[256];
  while(1) {
    
    //wait for connection
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    if(connect_d == -1)
      error("Can't open client socket");
    puts("Client connected!\n");
    
    //for a child process to accept a client
    if(fork() == 0) {
      
      //close listener
      close(listener_d);
      
      //prompt connected client 1st time
      if(say(connect_d, prompts[0]) == -1) {
	puts("Client Disconnected\n");
	close(connect_d);
	exit(0);
      }
      
      //read response 1
      read_in(connect_d, buffer, 14);
      printf("\n%s\n", buffer);
      if(strcmp(buffer, responses[0]) != 0) {
	say(connect_d, prompts[3]);
	puts("Client Disconnected\n");
	close(connect_d);
	exit(0);
      }
      
      //prompt connected client 2nd time
      if(say(connect_d, prompts[1]) == -1) {
	puts("Client Disconnected\n");
	close(connect_d);
	exit(0);
      }
      
      //read response 2
      read_in(connect_d, buffer, 12);
      printf("\n%s\n", buffer);
      if(strcmp(buffer, responses[1]) != 0) {
	say(connect_d, prompts[3]);
	puts("Client Disconnected\n");    
	close(connect_d);
	exit(0);
      }
      
      //confirm success and close
      say(connect_d, prompts[2]);
      say(connect_d, "Nice knowin' ya!\n");
      puts("Client Disconnected\n");
      close(connect_d);
      
      //exit child process
      exit(0);
    }
    
    
    close(connect_d);
    
  }
  
  //exit program
  return 0;
  
}

//print error
void
error(char *msg) {
  
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
  
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

//open listener socket
int
open_listener() {
  int s = socket(PF_INET, SOCK_STREAM, 0);
  if(s == 1)
    error("Can't open socket");
  
  return s;
}

//bind socket to port
void
bind_socket(int socket, int port) {
  
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  
  int reuse = 1;
  if(setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    error("Cant reuse socket");
  if(bind(socket, (struct sockaddr *) &name, sizeof(name)) == -1)
    error("Cannot bind port!");
  
}

//write characters to socket
int
say(int socket, char *s) {
  
  int result = send(socket, s, strlen(s), 0);
  
  if(result == -1)
    fprintf(stderr, "%s: %s\n", "Error talking to client", strerror(errno));
  
  return result;

}

//catch shutdown signal
void
handle_shutdown(int sig) {
  
  if(listener_d)
    close(listener_d);
  
  fprintf(stderr, "Later Gator!!\n");
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
