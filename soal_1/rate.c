#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>
#include <libgen.h>

#define SHM_SIZE 1024

typedef struct {
    char name[100];
    float rating;
} Place;

void rate_best(int shm_id) {
    Place *places = (Place *)shmat(shm_id, NULL, 0);
    if (places == (Place *)-1) {
        perror("shmat");
        exit(1);
    }

    int num_places = SHM_SIZE / sizeof(Place);
    Place best_trashcan = {"", -1};
    Place best_parkinglot = {"", -1};

    for (int i = 0; i < num_places; i++) {
        if (strcmp(places[i].name, "") == 0) {
            break;
        }

        if (strstr(places[i].name, "Trash Can") && places[i].rating > best_trashcan.rating) {
            best_trashcan = places[i];
        }

        if (strstr(places[i].name, "Parking Lot") && places[i].rating > best_parkinglot.rating) {
            best_parkinglot = places[i];
        }
    }

    if (best_trashcan.rating != -1) {
        printf("Best Trash Can: %s (Rating: %.2f)\n", best_trashcan.name, best_trashcan.rating);
    } else {
        printf("No Trash Can found.\n");
    }

    if (best_parkinglot.rating != -1) {
        printf("Best Parking Lot: %s (Rating: %.2f)\n", best_parkinglot.name, best_parkinglot.rating);
    } else {
        printf("No Parking Lot found.\n");
    }

    shmdt(places);
}

int main() {
    key_t key = ftok("rate.c", 65);
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    rate_best(shm_id);

    return 0;
}
