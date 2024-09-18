#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  int n, i;

  // Input - positivit heltall
  printf("Skriv inn et positivt heltall - lengde på array: ");
  scanf("%d", &n);

  // Sjekk på om tallet er et heltall
  if (n <=0) {
    printf("Heltallet må være positivt. \n");
      return 1;
  }

  // Allokerer minne for array
  int *A = (int*)malloc(n * sizeof(int));

  if (A == NULL) {
    printf("Kunne ikke allkolere minne. \n");
    return 1;
  }

  // Input - heltall
  printf("Skriv in heltall - fyll opp array: \n");
  for (i = 0; i < n; i ++){
    scanf("%d", &A[i]);
  }
  
  // Print array
  printf("Elementer i Array A: \n");
  for (i = 0; i < n; i++){
    printf("Arrayplass[%d] = %d\n", i, A[i]);
  }

  // Array is omvendt rekkefølge
  printf("\nElementene i Array A, i omvendt rekkefølge:\n");
  for (i = n - 1; i >= 0; i--) {
    printf("Arrayplass[%d] = %d\n", i, A[i]);
  }



  free(A);
  return 0;
}
