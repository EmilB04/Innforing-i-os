#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_WAIT 2000000

pthread_mutex_t mutex;           
pthread_cond_t cond_var;         // Betingelsesvariabel for å vekke blokkerte tråder
int blocked_threads = 0;         // Teller antall blokkerte tråder

void *terningkast(void *nr)
{
   while(1)
   {
      int terning = rand() % 6 + 1;

      pthread_mutex_lock(&mutex);  // Lås mutexen før vi endrer på delt data

      if (terning == 1) {
         blocked_threads++;  // Øk antall blokkerte tråder
         printf("Tråd %3ld -> %d (%d)\n", (long)nr, terning, blocked_threads);
         
         // Blokkerer tråden på betingelsesvariabelen
         pthread_cond_wait(&cond_var, &mutex);
      } 
      else if (terning == 6) {
         printf("Tråd %3ld -> %d (%d)\n", (long)nr, terning, blocked_threads);
         
         // Send signal for å vekke en blokkert tråd
         if (blocked_threads > 0) {
            blocked_threads--;  // Reduser antall blokkerte tråder
            pthread_cond_signal(&cond_var);
         }
      } 
      else {
         printf("Tråd %3ld -> %d\n", (long)nr, terning);
      }

      pthread_mutex_unlock(&mutex);  // Lås opp mutexen etter endringene
      usleep(rand() % MAX_WAIT + 1);  // Vent før neste terningkast
   }
}

int main()
{
   int n;
   long i;
   pthread_t *threads;

   printf("n? ");
   scanf("%d", &n);

   threads = malloc(n * sizeof(pthread_t));  // Alloker plass for n tråder

   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&cond_var, NULL);  // Initialiserer betingelsesvariabel

   // Opprett n tråder som kjører terningkast-funksjonen
   for (i = 0; i < n; i++)
      pthread_create(&threads[i], NULL, terningkast, (void *)i);

   for (i = 0; i < n; i++) {
    pthread_join(threads[i], NULL);  // Vent på at alle trådene skal fullføre
   }

   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond_var);
}
