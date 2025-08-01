#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#define LIMITE 1024

#define CLE_MEM 0x1111

//structure représentant la mémoire partagée
struct segment {
    int etat;
    unsigned long long taille;
    unsigned long long contenu[LIMITE];
};

//calcule la factorielle d’un nombre
unsigned long long factorielle(unsigned long long n) {
    unsigned long long resultat =1;
    for (unsigned long long i = 1; i <= n; i++) 
    {
        resultat *= i;
    }

    return resultat;
}

// génère les nombres de catalan et les garde en memoire
void remplir_sequence(unsigned long long *destination, unsigned long long total) {
    unsigned long long catalan = 1;
    for (unsigned long long i = 0; i < total; i++) {
        *destination = catalan;
        destination++;

        printf("Élément %llu inséré\n", i + 1);
        sleep(1);

        catalan = catalan * 2 * (2 * i + 1) / (i + 2);
    }

    printf("Fini la generation\n");
}


int main(int argc, char *argv[]) {
    unsigned long long quantite = 10;

    int mem_id;
    unsigned long long *zone;

    struct segment *memoire;

    // lit la quantité depuis la ligne de commande
    if (argc == 2) {
        if (sscanf(argv[1], "%llu", &quantite) == 1) 
        {
            printf("Nombre demandé: %llu\n", quantite);
        } else {
            fprintf(stderr, "Argument invalide!!!!! Valeur défaut:5\n");
        }
    }

    //création de la mémoire partagée
    mem_id = shmget(CLE_MEM, sizeof(struct segment), 0666 | IPC_CREAT);
    if (mem_id == -1) {
        perror("Err avec création mémoire partagée");
        return 1;
    }

    //attachement à la mémoire
    memoire = shmat(mem_id, NULL, 0);
    if (memoire == (void *) -1) {
        perror("Err avec attachement mémoire");
        return 1;
    }

    memoire->taille = quantite;
    zone = memoire->contenu;

    remplir_sequence(zone, quantite);
    memoire->etat = 1;

    if (shmdt(memoire) == -1) 
    {
        perror("Err détachement mémoire");
        return 1;
    }

    printf("Producteur terminé!!!!!\n");
    return 0;
}
