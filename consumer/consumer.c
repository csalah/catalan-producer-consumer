/*
 * Choueb Salah
 * No Étudiant : 8749973
 * CSI3531 - Devoir 4
 * Question 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>

#define CLE 0x1111

#define MAX 1024

struct bloc_memoire {
    int etat;
    unsigned long long total;
    unsigned long long donnees[MAX];
};

//pour lire les donné une fois que le producteur est pret
void lire_catalan(struct bloc_memoire *memoire) {
    unsigned long long *ptr = memoire->donnees;

    printf("Lecture de %llu termes de Catalan:\n", memoire->total);
    for (unsigned long long i = 1; i <= memoire->total; i++) 
    {
        printf("%llu ", *ptr);
        ptr++;
    }
    printf("\n");
}

int main() {
    int id;
    struct bloc_memoire *memoire;

    id = shmget(CLE, sizeof(struct bloc_memoire), 0666 | IPC_CREAT);
    if (id == -1)
    {
        perror("Err:accès à la mémoire partagée échoué");
        return 1;
    }

    memoire = shmat(id, NULL, 0);
    if (memoire == (void *) -1){
        perror("Err: attachement échoué");
        return 1;
    }

    printf("Le consommateur attend la fin du producteur...\n");

    while (memoire->etat != 1) {
        sleep(1);
    }

    printf("Le producteur a terminé...... Début de la lecture\n");
    lire_catalan(memoire);

    if (shmdt(memoire) == -1){
        perror("Err: détachement échoué");
        return 1;
    }

    printf("Fin du processus consommateur!!!!!!\n");
    return 0;
}
