#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int score = 0;

void endGame(int sig);
void timeout(int sig);
void error(char *msg);
int catchSignal(int sig, void(*handler)(int));

int main() {
  catchSignal(SIGALRM, timeout);
  catchSignal(SIGINT, endGame);
  srandom(time(0));
  while(1) {
    int a = random() % 11;
    int b = random() % 11;
    char txt[4];
    alarm(5);
    printf("What is %ix%i? ", a, b);
    fgets(txt, 4, stdin);
    int answer = atoi(txt);
    if(answer == a*b) {
      score++;
    }
    else {
      printf("\nWrong! Score: %i\n", score);
    }
  }
  return 0;
}

c


int catchSignal(int sig, void(*handler)(int)) {
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(sig, &action, NULL);
}

void endGame(int sig) {
  printf("Final Score: %i\n", score);
  exit(0);
}

void timeout(int sig) {
  printf("Time's up!!");
  raise(SIGINT);
}