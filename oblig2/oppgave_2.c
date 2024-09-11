#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Lager funksjon, ettersom dette er en repetativ oppgave.
int getRandomNumber() 
  {
    return (rand() % 100000); // returnerer ett tilfeldig tall mellom 0 og 100_000
  }

int main()
{
  int Array[1000];
  int i, tall;
 
  // Initierer trekkingen av randomtall med nåværende tid som "seed"
  srand(time(NULL));

  for (i = 0; i < 1000; i++)
    {
      tall = getRandomNumber(); // Henter tall fra funksjon
      Array[i] = tall; // legger til nytt tall hvor telleren i for-løkken brukes for å indexere
    }

  // Setter disse verdiene til det "motsatte" av det ønskede, ettersom det vil resultere i riktige verdier i for-loopen og if-sjekkene.
  int storst = 0, minst = 100000;

  for (i = 0; i < 1000; i++)
    { //Bruker if på begge, ettersom de er uavhengige av hverandre.
      if (Array[i] > storst) // Gjør en sjekk på om næværende index er større enn forrige verdi som ble sett på som størst
	storst = Array[i];
      if (Array[i] < minst) // Gjør en sjekk på om næværende index er mindre en forrige verdi som ble sett på som minst
	minst = Array[i];
    }

  // Skriver ut resultatene for verifikasjon
    printf("Største tall: %d\n", storst);
    printf("Minste tall: %d\n", minst);
  
  return 0;
}
