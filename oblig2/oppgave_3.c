#include <stdio.h>

long fib(int n){
  if (n <= 0){
    return 0; // Fordi F_0 = 0
  }
  else if (n == 1) {
    return 1; // Fordi F_1 = 1
  }
  else {
    return fib(n - 1) + fib(n - 2);
  }
}

int main()
{
  int n;
    FILE *fil;

    // Åpner filen "fibonacci.txt" for skriving
    fil = fopen("fibonacci.txt", "w");
    if (fil == NULL) {
        printf("Feil ved åpning av filen.\n");
        return 1;
    }

    // Input fra bruker, for n-verdi
    printf("Skriv inn et positivt heltall : ");
    scanf("%d", &n);

    // Beregner og skriver Fibonacci-tallene til filen
    for (int i = 0; i <= n; i++) {
        fprintf(fil, "F_%d = %ld\n", i, fib(i));
    }


    // Lukker filen
    fclose(fil);
    printf("Fibonaccitallene er lagret i filen 'fibonacci.txt'.\n");
    return 0;
}
