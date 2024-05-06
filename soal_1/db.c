#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>
#include <libgen.h>
#include <time.h>

#define SHM_SIZE 1024

void move_file(const char *filename, int shm_id) {
    char *name = strdup(filename);
    char *base = basename(name);
    
    // Move file to microservices/database folder using shared memory
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

        // Move file to microservices/database folder
        char new_filename[100];
        sprintf(new_filename, "./microservices/database/%s", base);
        if (rename(filename, new_filename) == 0) {
            // Log the file move operation in db.log
            time_t rawtime;
            struct tm *timeinfo;
            char buffer[80];

            time(&rawtime);
            timeinfo = localtime(&rawtime);

            strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", timeinfo);
            FILE *log_fp = fopen("./microservices/database/db.log", "a");
            if (log_fp) {
                fprintf(log_fp, "[%s] [%s]\n", buffer, base);
                fclose(log_fp);
            } else {
                perror("fopen");
                exit(1);
            }
        } else {
            perror("rename");
            exit(1);
        }
    } else {
        perror("fopen");
        exit(1);
    }

    free(name);
}

int main() {
    key_t key = ftok("db.c", 65);
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
                move_file(filename, shm_id);
            }
        }
        closedir(dir);
    } else {
        perror("opendir");
        exit(1);
    }

    return 0;
}
