#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur som lagrer data om en page frame
struct page_frame
{
   int id;   // Page-ID/-number
   int load; // Tidspunkt da pagen ble lagt inn i RAM
   int last; // Tidspunkt da pagen siste ble referert til
   int R;    // Referenced bit
   int M;    // Modified bit
};

// Globale variabler
int T = 300;           // Systemtid, settes til passende verdi
int N;                 // Antall prosesser
struct page_frame *PF; // Peker til array med page frames

// read_file(): Leser data for N page frames fra fil. Pages skal
// ligge sortert på ankomsttid. Alle data må være ikke-negative
// heltall. Alle tider oppgis i hele tidsenheter. Filformat:
//
//    N
//    id load last R M
//    id load last R M
//    id load last R M
//    ...
//
void read_file(char *filename)
{
   int i;
   FILE *p_file;
   
   // Åpner fil og sjekker for feil i åpning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   { 
      printf("Feil ved åpning av filen \"%s\"\n", filename); 
      exit(-1);
   }

   // Leser antall page frames
   fscanf(p_file, "%d", &N);

   // Oppretter array med plass til alle pages
   PF = (struct page_frame *) malloc(N * sizeof(struct page_frame));

   // Leser inn en og en page frame.
   for (i = 0; i < N; i++)
      fscanf(p_file, "%d %d %d %d %d", &PF[i].id, &PF[i].load,
	      &PF[i].last, &PF[i].R, &PF[i].M);
   fclose(p_file);
}

//first_in_first_out(): Simulering av page replacement med FIFO

// Oppgave 1:
void first_in_first_out() {
    printf("First-In-First-Out \n");

    int oldest_index = -1;
    int min_load_time = __INT_MAX__; // Start med en høy verdi, for å være sikker på at den oppdateres.

    // Finn siden med laveste `load`-verdi (eldste innlasting)
    for (int i = 0; i < N; i++) {
        if (PF[i].load < min_load_time) {
            min_load_time = PF[i].load;
            oldest_index = i;
        }
    }

    // Hvis vi fant en side, skriv ut dens detaljer
    if (oldest_index != -1) {
        printf("Page: %d   Loaded: %d   Last ref: %d   R: %d   M: %d\n",
               PF[oldest_index].id, PF[oldest_index].load, PF[oldest_index].last,
               PF[oldest_index].R, PF[oldest_index].M);
    }
}


//least_recently_used(): Simulering av page replacement med LRU

// Oppgave 2:
void least_recently_used(){
  printf("Least Recently Used \n");

  int lru_index = -1;
  int min_last_ref = __INT_MAX__;

  // Gå gjennom alle sidene og finn den laveste "last"-verdi
  for (int i = 0; i < N; i++) {
    if (PF[i].last < min_last_ref) {
      min_last_ref = PF[i].last;
      lru_index = i;
    }
  }
   // Hvis vi har funnet en side, skriv ut dens detaljer
  if (lru_index != -1) {
    printf("Page: %d   Loaded: %d   Last ref: %d   R: %d   M: %d\n",
	   PF[lru_index].id, PF[lru_index].load, PF[lru_index].last,
           PF[lru_index].R, PF[lru_index].M);
    }
}

//second_chance(): Simulering av page replacement med Second Chance

// Oppgave 3: Fikk ikke helt til denne.
void second_chance() {
    printf("Second Chance\n");

    int index = 0; // Startposisjon i sirkulær liste
    while (1) {
        // Sjekk referansebiten til den gjeldende siden
        if (PF[index].R == 0) {
            // Hvis `R` er 0, velg siden for utskifting og skriv ut informasjon
            printf("Page: %d   Loaded: %d   Last ref: %d   R: %d   M: %d\n",
                   PF[index].id, PF[index].load, PF[index].last,
                   PF[index].R, PF[index].M);
            // Her kan du implementere logikk for å bytte ut siden, hvis nødvendig
            break;
        }
	else {
            // Hvis `R` er 1, gi siden en ny sjanse og sett `R` til 0
            PF[index].R = 0;
        }
        // Flytt til neste side (sirkulær liste)
        index = (index + 1) % N;
    }
}


// main(): Leser filnavn med page frame data, leser inndata fra fil og
// kjører tre ulike page replacement algoritmer
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn prosessdataene
   read_file(filename);

   // Simulerer page replacement
   first_in_first_out();
   least_recently_used();
   second_chance();
}
