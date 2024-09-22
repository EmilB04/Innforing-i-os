#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t child = fork();

  if (child < 0) {
    perror("fork");
    return 1; // Feil ved opprettelse av barneprosess
  }
  else if (child == 0) {
    // Barneprosess
    execvp("ping", (char *[]){"ping", "vg.no", NULL});
  }
  else {
    // Forelderprosess
    sleep(5);
    kill(child, SIGTERM); // Terminerer barneprosessen
    wait(NULL); // Venter på barneprosessen
  }
  return 0;

  /*
    Jeg velger faktisk å bruke SIGTERM her framfor SIGKILL eller SIGINT ettersom SIGTERM gir prosessen som foregår
    en sjanse til å fullføre og rydde opp, fremfor å terminere den uten forvarsel. I andre tilfellerm, kan SIGKILL
    føre til dataødeleggelser eller andre feil.
   */
}
