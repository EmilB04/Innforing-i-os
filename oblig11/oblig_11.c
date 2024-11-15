#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

#define M 100 // Maks. antall ulike typer ressurser
#define N 100 // Maks. antall prosesser
int m;        // Antall ulike typer ressurser
int n;        // Antall prosesser
int E[M];     // Exists: Totalt antall av hver type ressurs
int A[M];     // Available: Antall tilgjengelige ressursforekomster
int C[N][M];  // Current: Antall ressurser hver prosess holder
int R[N][M];  // Request: Antall ressurser hver prosess trenger


// read_file(): Leser prosess- og ressursdata fra fil. Alle data må
// være ikke-negative heltall.
//
void read_file(char *filename)
{
   int i, j;
   FILE *p_file;
   
   // Åpner fil og sjekker for feil i åpning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   { 
      printf("Feil ved åpning av filen \"%s\"\n", filename); 
      exit(-1);
   }

   // Leser antall prosesser og ressurstyper
   fscanf(p_file, "%d %d", &m, &n);

   // Leser totalt antall ressurser av hver type
   for (i = 0; i < m; i++)
     fscanf(p_file, "%d", &E[i]);      
                            
   // Leser antall ressurser av hver type som hver prosess holder
   for (i = 0; i < n; i++)      
      for (j = 0; j < m; j++) 
         fscanf(p_file, "%d", &C[i][j]);
                            
   // Leser antall ressurser av hver type som hver prosess trenger
   for (i = 0; i < n; i++)      
      for (j = 0; j < m; j++) 
	fscanf(p_file, "%d", &R[i][j]);

   // Beregner antall tilgjengelige ressurser av hver type
   for (i = 0; i < m; i++) 
   {
      A[i] = E[i];
      for (j = 0; j < n; j++)    
         A[i] -= C[j][i];
   }
}


// safe(): Kjører Bankers for å sjekke om systemet er i safe tilstand
//
int safe()
{
    int Work[M];       // Midlertidig array for tilgjengelige ressurser
    int Finish[N];     // Array som sporer om en prosess kan fullføres
    int i, j, k;       // Tellere/index

    // Kopierer tilgjengelige ressurser til Work
    for (i = 0; i < m; i++) {
        Work[i] = A[i];
    }

    // Initierer Finish-arrayet til FALSE for alle prosesser
    for (i = 0; i < n; i++) {
        Finish[i] = FALSE;
    }

    // Teller antall fullførte prosesser
    int count = 0;
    while (count < n) {
        int found = FALSE;

        // Sjekker hver prosess for muligheten til å kjøre
        for (i = 0; i < n; i++) {
            if (Finish[i] == FALSE) {
                // Sjekker om ressursene er tilstrekkelige for prosess i
                int canAllocate = TRUE;
                for (j = 0; j < m; j++) {
                    if (R[i][j] > Work[j]) {
                        canAllocate = FALSE;
                        break;
                    }
                }

                // Hvis prosess i kan kjøre, markeres den som ferdig
                if (canAllocate) {
		  printf("p%d can run    A = [ ", i + 1);
                    for (k = 0; k < m; k++) {
                        Work[k] += C[i][k];  // Returnerer ressursene
			printf("%d ", Work[k]);
                    }
		    printf("]\n");
                    Finish[i] = TRUE;       // Merker prosessen som ferdig
                    found = TRUE;
                    count++;

                    // Utskrift av prosessrekkefølgen
                    
                }
            }
        }

        // Hvis ingen prosess kan kjøre, er systemet i en usikker tilstand
        if (!found) {
	  printf("No more proccesses can run\n");
            return FALSE;
        }
    }

    // Alle prosesser kan fullføres i en sikker sekvens
    return TRUE;
}



// main(): Leser filnavn med prosess- og ressursdata fra fil og kjører
// Bankers algoritme
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn data fra fil
   read_file(filename);
   
   // Simulerer Bankers
   if (safe())
     printf("Safe\n");
   else
     printf("Unsafe\n");
}
