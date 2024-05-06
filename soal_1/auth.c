#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>

#define SHM_SIZE 1024

void authenticate_file(const char *filename, int shm_id) {
    char *name = strdup(filename);
    char *base = basename(name);
    char *ext = strrchr(base, '.');
    if (ext && (strcmp(ext, ".csv") == 0)) {
        char *type = strtok(base, "_");
        if (type) {
            if ((strcmp(type, "belobog") == 0 && strstr(base, "trashcan")) ||
                (strcmp(type, "osaka") == 0 && strstr(base, "parkinglot"))) {
                printf("File %s is authenticated as %s.\n", filename, type);
            } else {
                printf("Invalid file type: %s\n", filename);
                // Delete file
                unlink(filename);
                free(name);
                return;
            }
        }
    } else {
        printf("Invalid file extension: %s\n", filename);
        // Delete file
        unlink(filename);
        free(name);
        return;
    }

    // Move file to shared memory
    FILE *fp = fopen(filename, "r");
    if (fp) {
        char buffer[SHM_SIZE];
        fread(buffer, sizeof(char), SHM_SIZE, fp);
        fclose(fp);
        char *shm = (char *)shmat(shm_id, NULL, 0);
        if (shm == (char *)-1) {
            perror("shmat");
            exit(1);
        }
        strncpy(shm, buffer, SHM_SIZE);
        shmdt(shm);
    } else {
        perror("fopen");
        exit(1);
    }

    free(name);
}

int main() {
    key_t key = ftok("auth.c", 65);
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    DIR *dir;
    struct dirent *ent;
    char *data_dir = "./new-data"; // Direktori yang akan di-scan
    if ((dir = opendir(data_dir)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {  // Regular file
                char filename[512];
                snprintf(filename, sizeof(filename), "%s/%s", data_dir, ent->d_name);
                authenticate_file(filename, shm_id);
            }
        }
        closedir(dir);
    } else {
        perror("opendir");
        exit(1);
    }
    
    return 0;
}
