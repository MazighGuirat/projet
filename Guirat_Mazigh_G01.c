#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

// Guirat Mazigh G01
// Projet de SE TP 

// Declarer Les Matrices A, B, C :
int A[N][N];
int B[N][N];
int C[N][N];

// Declarer La Matrice Tampon T :
int T[N][N];

// Dimensions des matrices :
int n1, m1, n2, m2;

// Semaphores et mutex pour la synchronisation
sem_t empty, full;
pthread_mutex_t mutex;

//Producteur
void *producer(void *arg) {
    int i, j, k;
    for (i = 0; i < n1; ++i) {
        for (j = 0; j < m2; ++j) {
            int result = 0;
            for (k = 0; k < m1; ++k) {
                result += B[i][k] * C[k][j];
            }

            sem_wait(&empty);
            pthread_mutex_lock(&mutex);
            T[i][j] = result;
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
        }
    }

    pthread_exit(NULL);
}

//Consummateur
void *consumer(void *arg) {
    int i, j;
    for (i = 0; i < n1; ++i) {
        for (j = 0; j < m2; ++j) {
            sem_wait(&full);
            pthread_mutex_lock(&mutex);

            A[i][j] = T[i][j];

            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Définir les dimensions et initialiser les matrices B et C avec des valeurs aléatoires
    n1 = N;
    m1 = N;
    n2 = N;
    m2 = N;
    int i, j;

    // Initialise les sémaphores et le mutex
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Seed pour les valeurs aléatoires
    srand(time(NULL));

    printf("\n**************************************************************************************\n");
    printf("\n Projet de SE TP \n");
    printf("\n Guirat Mazigh G01 \n");
    printf("\n**************************************************************************************\n");

    // Remplir les matrices B et C avec des valeurs aléatoires
    printf(" Matrice B:\n");
    for (i = 0; i < n1; ++i) {
        for (j = 0; j < m1; ++j) {
            B[i][j] = rand() % 10;
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    printf("\n**************************************************************************************\n");
    printf(" Matrice C:\n");
    for (i = 0; i < n2; ++i) {
        for (j = 0; j < m2; ++j) {
            C[i][j] = rand() % 10;
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("\n**************************************************************************************\n");
    // Créer des threads de production et de consommation
    pthread_t producer_thread, consumer_thread;

    // Lancement du thread du producteur
    pthread_create(&producer_thread, NULL, producer, NULL);

    // Lancement du thread consommateur
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Attend la fin des threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Détruire les sémaphores et les mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    // Affiche la matrice résultat A
    printf(" Matrice A (Result):\n");
    for (i = 0; i < n1; ++i) {
        for (j = 0; j < m2; ++j) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n**************************************************************************************\n");
    return 0;
}
