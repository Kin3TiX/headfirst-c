//Sample Program - Signal Handling & Alarms
//Header Includes
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <termios.h>

//Function Declarations
//Handler Functions
void diediedie(int sig);
void howdy(int sig);
//Handler Register Function
int catchSignal(int signum, void(*handler)(int));
//Other
void flushBuffer(FILE *fp);

//Variable declarations
//Declare interrupted flag
static int interrupted = 0;

//Program entrypoint
int main() {
  
  //Register interrupt hander, catch errors
  if(catchSignal(SIGINT, diediedie) == -1) {
    fprintf(stderr, "Could not register interrupt handler");
    exit(2);
  }
  
  //Register alarm handler, catch errors
  if(catchSignal(SIGALRM, howdy) == -1) {
    fprintf(stderr, "Could not register alarm handler");
    exit(2);
  }
  
  //Create initial alarm trigger
  alarm(3);
  
  //Do something stupid while waiting for signals
  char name[30];
  printf("Enter your name: ");
  //Keep waiting for user input even if interrupted by alarm signal
  while(1) {
    fgets(name, 30, stdin);
    if(interrupted) {
      // reset interrupted flag
      interrupted = 0;
      //flushBuffer(stdin);
      tcflush(fileno(stdin), TCIFLUSH);
    }
    else {
      //echo user input and break out
      printf("Hello %s\n", name);
      break;
    }
  }
  
  //end program
  return 0;
  
}

//interrupt handler definition
void diediedie(int sig) {
  
  //write some stuff, exit program
  puts("Goodbye world!");
  exit(1);
  
}

//alarm handler definition
void howdy(int sig) {
  //set interrupted flag
  interrupted = 1;
  //write some annoying message
  puts("howdy!");
  //set another alarm trigger
  alarm(3);
}

//signal handler registration function definition
int catchSignal(int signum, void(*handler)(int)) {
  
  //register handler
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(signum, &action, NULL);
  
}

//function to flush a character buffer
void flushBuffer(FILE *fp) {
  char ch;
  while((ch = fgetc(fp)) != EOF && ch != '\n') {}
}