#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 64 // Maksimalt antall rader/kolonner
#define N_THREADS 4 // Antall tråder

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX]; // Matriser
int N; // Antall rader og kolonner

char *filnavn_A = "A.txt", *filnavn_B = "B.txt", *filnavn_C = "C.txt";

// Leser inn N og dataene for A og B fra filer
void les_AB() {
    FILE *fil_A, *fil_B;
    int tmp, i, j;

    fil_A = fopen(filnavn_A, "r");
    fil_B = fopen(filnavn_B, "r");
    if (fil_A == NULL || fil_B == NULL) {
        printf("Feil: Kan ikke åpne fil\n");
        exit(-1);
    }

    fscanf(fil_A, "%d", &N);
    if (N > MAX) {
        printf("Feil: N > %d\n", MAX);
        exit(-1);
    }
    fscanf(fil_B, "%d", &tmp);
    if (N != tmp) {
        printf("Feil: Matrisene har ulike dimensjoner\n");
        exit(-1);
    }

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            fscanf(fil_A, "%d", &A[i][j]);
            fscanf(fil_B, "%d", &B[i][j]);
        }

    fclose(fil_A);
    fclose(fil_B);
}

// Skriver resultatet C = AB ut til fil
void skriv_C() {
    FILE *fil_C;
    int i, j;

    fil_C = fopen(filnavn_C, "w");
    if (fil_C == NULL) {
        printf("Feil: Kan ikke åpne fil\n");
        exit(-1);
    }

    fprintf(fil_C, "%d\n", N);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            fprintf(fil_C, "%d ", C[i][j]);
        fprintf(fil_C, "\n");
    }

    fclose(fil_C);
}

// Funksjon for å beregne en fjerdedel av matrisen
void *multipliser_del_AB(void *arg) {
    int start_row = *(int *)arg;
    int end_row = start_row + N / N_THREADS;
    int i, j, k;

    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N_THREADS];
    int start_rows[N_THREADS];
    int i;

    les_AB(); // Leser matrise A og B

    // Starter N_THREADS tråder som beregner en fjerdedel av matrisen
    for (i = 0; i < N_THREADS; i++) {
        start_rows[i] = i * (N / N_THREADS); // Start rad for hver tråd
        pthread_create(&threads[i], NULL, multipliser_del_AB, &start_rows[i]);
    }

    // Venter til alle trådene er ferdig
    for (i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    skriv_C(); // Skriver resultatmatrisen C til fil

    return 0;
}

