#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int palindrom(char *s1) {
    int len = strlen(s1);
    char *s2 = malloc(len + 1); // +1 for nok plass til null-tegnet

    // Reverserer s1 til s2
    for (int i = 0, j = len - 1; i < len; i++, j--) {
        s2[i] = s1[j];
    }
    s2[len] = '\0';

    int result = strcmp(s1, s2);
    free(s2); // Frigjør minnet

    return result == 0;
}

int main() {
    char str[100];
    printf("Skriv inn en streng: ");
    scanf("%s", str);

    if (palindrom(str)) {
        printf("'%s' er et palindrom\n", str);
    }
    else {
        printf("'%s' er ikke et palindrom\n", str);
    }

    return 0;
}

/*Alternativ måte i funksjonen:
// Sjekker om strengen er lik fra start og slutt (til midten)
  for (i = 0; i < (len / 2); i++) {
    if (s1[i] != s1[len - i - 1]){ // Sjekker motsatt side med hverandre
       return 0; // Returnerer False, hvis det er slik at ordet ikke er et palindrom
    }
  }
  return 1;
 */
