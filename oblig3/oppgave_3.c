#include <stdio.h>
#include <stdlib.h>

struct prosess
{
   int nummer; 
   char status;
   float start_tid;
   float CPU_tid;
};

// Funksjon for å kopiere en prosess-struktur
struct prosess *kopier(struct prosess p) {
    // Allokerer minne for den nye strukturen
    struct prosess *ny_prosess = (struct prosess *)malloc(sizeof(struct prosess));

    // Sjekker om allokeringen var vellykket
    if (ny_prosess == NULL) {
        printf("Kunne ikke allokere minne for ny prosess.\n");
        exit(0); // Avslutter programmet med feilmelding
    }

    // Kopierer verdiene fra p til ny_prosess
    *ny_prosess = p;

    return ny_prosess;
}

int main( )
{
   FILE* fil;
   struct prosess *P;
   int i, n;

   // Åpner fil
   fil = fopen("prosess.txt", "r");
   if (fil == NULL)
   {
      printf("Feil i åpning av fil");
      exit(0);
   }

   // Leser antall prosesser
   fscanf(fil, "%d", &n);

   // Oppretter en dynamisk array med strukturer
   P = (struct prosess *) malloc(n * sizeof(struct prosess));

   // Leser inn dataene fra fil
   for (i = 0; i < n; i++)
     fscanf(fil, "%d %c %f %f",
	    &P[i].nummer, &P[i].status, &P[i].start_tid, &P[i].CPU_tid);

   // Skriver ut innleste data
   for (i = 0; i < n; i++)
     printf("Nr: %3d  Status: %c  Start: %5.2f  CPU: %5.2f\n",
	    P[i].nummer, P[i].status, P[i].start_tid, P[i].CPU_tid);

   // Eksempel på bruk av kopier-funksjonen
    struct prosess prosess1 = {1, 'A', 10.5, 2.3};
    struct prosess *kopi = kopier(prosess1);

    // Endrer en verdi i kopien for å vise at de er uavhengige
    kopi->status = 'B';

    printf("Original: nummer=%d, status=%c\n", prosess1.nummer, prosess1.status);
    printf("Kopi: nummer=%d, status=%c\n", kopi->nummer, kopi->status);

    // Frigjør allokert minne
    free(kopi);
}
