#include <stdio.h>

int main() {
  int S = 0;
  int n;

  // Løkke for å gå gjennom tallene fra 0-100
  for (n = 0; n <= 100; n++){
    S += n * n;
  }

  // Skriver ut summen
  printf("Summen S fra 0 til 100 er: %d\n", S);

  // Avslutter programmet
  return 0;

}
