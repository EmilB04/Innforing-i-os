#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

void sig_handler(int sig) // Hentet fra eksempelprogram med Ctrl+C
{
  printf("Slutt å mase, din lille sa**n.\n");
}



int main(){
  pid_t pid;
  pid = fork();

  if (pid == 0){ // Barneelement
    char input[100];
    while (1) {
      printf("Skriv noe (quit for å avslutte): ");
      scanf("%s", input);
      if (strcmp(input, "quit") == 0) { // Sammenlikner strenger med strcmp
	printf("Barneprosess avsluttes. \n");
	exit(0);
      }
      else {
	kill(getppid(), SIGUSR1);
	usleep(200000);
      }     
    }
  }
  else {    // Forelderprosessen
    signal(SIGUSR1, sig_handler);
    wait(NULL);
    printf("Forelderprosess avsluttes\n");

  }
}
