#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur som lagrer data om en prosess
struct process
{
   int id;      // Prosess-ID
   int arrive;  // Tidspunkt da prosessen ble satt inn i kø 
   int cpu;     // Total CPU-tid som prosessen krever
   int start;   // Tidspunkt da prosessen startet å kjøre
   int end;     // Tidspunkt da prosessen er ferdig
};

// Globale variabler
int T = 0;         // Systemtid, starter simulering ved tid lik 0
int N;             // Antall prosesser
struct process *P; // Peker til array med prosessene

// read_file(): Leser data for N prosesser fra fil. Prosessene skal
// ligge sortert på ankomsttid. Alle data må være ikke-negative
// heltall. Alle tider oppgis i hele tidsenheter. Filformat:
//
//    N
//    id arrive CPU
//    id arrive CPU
//    id arrive CPU
//    ...
//
void read_file(char *filename)
{
   int i, last_arrive = 0;
   FILE *p_file;
   
   // Åpner fil og sjekker for feil i åpning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   { 
      printf("Feil ved åpning av filen \"%s\"\n", filename); 
      exit(-1);
   }

   // Leser antall prosesser
   fscanf(p_file, "%d", &N);

   // Oppretter array med plass til alle prosessene
   P = (struct process *) malloc(N * sizeof(struct process));

   // Leser inn en og en prosess. Prosessene skal ligge sortert på
   // ankomsttid i filen, hvis ikke gis en feilmelding.
   for (i = 0; i < N; i++)
   {
      fscanf(p_file, "%d %d %d", &P[i].id, &P[i].arrive, &P[i].cpu);
      P[i].start = P[i].end = 0;
      
      if (P[i].arrive < last_arrive)
      { 
	 printf("Feil i ankomsttider, prosess %d\n", P[i].id); 
         exit(-1);
      }
      last_arrive = P[i].arrive;
   }
   fclose(p_file);
}

// simulate(): Simulering av batch scheduling. "Kjører" til alle
// prosessene er ferdige.
void simulate(){
  int i, j, total_turnaround = 0, total_wait = 0;
  int current_time = 0, completed = 0, min_index;
  int min_cpu, is_process_available;

  printf("P  Arrive  CPU  Start  End\n");

  while (completed < N) {
    min_cpu = __INT_MAX__; // Høy verdi, for å senere finne minste
    min_index = -1;
    is_process_available = 0;

    // Finn prosessen som har ankommet og har kortest CPU-tid
    for (i = 0; i < N; i++) {
      if (P[i].arrive <= current_time && P[i].end == 0) {
	is_process_available = 1;
	if (P[i].cpu < min_cpu) {
	  min_cpu = P[i].cpu;
	  min_index = i;
	}
      }
    }
    // Hvis ingen prosess er tilgjengelig, øk systemtiden til neste prosess
        if (!is_process_available) {
            current_time++;
            continue;
        }

        // Utfør den valgte prosessen (med kortest CPU-tid)
        P[min_index].start = current_time;
        P[min_index].end = P[min_index].start + P[min_index].cpu;
        current_time = P[min_index].end;  // Oppdater systemtiden
        completed++;  // En prosess fullført

        // Skriv ut prosessinformasjon
        printf("%d    %d      %d     %d     %d\n", P[min_index].id, P[min_index].arrive, P[min_index].cpu, P[min_index].start, P[min_index].end);

        // Beregn turnaround-tid (sluttid - ankomsttid)
        total_turnaround += P[min_index].end - P[min_index].arrive;

        // Beregn ventetid (starttid - ankomsttid)
        total_wait += P[min_index].start - P[min_index].arrive;
  }
  
  // Beregn og skriv ut gjennomsnittlig turnaround-tid og ventetid
    double avg_turnaround = (double) total_turnaround / N;
    double avg_wait = (double) total_wait / N;

    printf("\nAverage turnaround:  %.2f\n", avg_turnaround);
    printf("Average wait-time :   %.2f\n", avg_wait);
  
}


// main(): Leser filnavn med prosessdata, leser fil og kjører scheduling
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn prosessdataene
   read_file(filename);

   // Simulerer batch-scheduling
   simulate();
}
