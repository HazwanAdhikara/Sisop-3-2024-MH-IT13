#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <math.h>

#define LOG_FILE "histori.log"

void addLog(const char* type, const char* message) {
    time_t current_time;
    char timestamp[20];

    time(&current_time);
    strftime(timestamp, 20, "[%d/%m/%y %H:%M:%S]", localtime(&current_time));

    FILE* log_file = fopen(LOG_FILE, "a");
    if (log_file) fprintf(log_file, "%s [%s] %s\n", timestamp, type, message);
    fclose(log_file);
}

void numberToWords(int number, char* words);


void calculate(int operand1, int operand2, const char* operation) {
    int result;
    char message[1024];
    char operand1_str[20], operand2_str[20], result_str[512];

    // Mengonversi angka menjadi kata
    numberToWords(operand1, operand1_str);
    numberToWords(operand2, operand2_str);

    if (strcmp(operation, "-kali") == 0) {
        result = operand1 * operand2;
        numberToWords(result, result_str);
        snprintf(message, sizeof(message), "hasil perkalian %s dan %s adalah %s.", operand1_str, operand2_str, result_str);
        addLog("KALI", message);
        printf("%s\n", message);
    } else if (strcmp(operation, "-tambah") == 0) {
        result = operand1 + operand2;
        numberToWords(result, result_str);
        snprintf(message, sizeof(message), "hasil penjumlahan %s dan %s adalah %s.", operand1_str, operand2_str, result_str);
        addLog("TAMBAH", message);
        printf("%s\n", message);
    } else if (strcmp(operation, "-kurang") == 0) {
        result = operand1 - operand2;
        if (result < 0) {
        printf("ERROR\n");
        snprintf(message, sizeof(message), "ERROR pada pengurangan.");
        addLog("KURANG", message);
        printf("%s\n", message);
        } else {
        numberToWords(result, result_str);
        snprintf(message, sizeof(message), "hasil pengurangan %s dan %s adalah %s.", operand1_str, operand2_str, result_str);
        addLog("KURANG", message);
        printf("%s\n", message);
        }
    } else if (strcmp(operation, "-bagi") == 0) {
        if (operand2 == 0) {
        printf("ERROR\n");
        snprintf(message, sizeof(message), "ERROR pada pembagian (divisi oleh nol).");
        addLog("BAGI", message);
        printf("%s\n", message);
        } else {
            result = operand1 / operand2;
        numberToWords(result, result_str);
        snprintf(message, sizeof(message), "hasil pembagian %s dan %s adalah %s.", operand1_str, operand2_str, result_str);
        addLog("BAGI", message);
        printf("%s\n", message);
        }
    }
}


void numberToWords(int number, char* words) {
    const char* ones[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    const char* teens[] = {"", "sebelas", "dua belas", "tiga belas", "empat belas", "lima belas", "enam belas", "tujuh belas", "delapan belas", "sembilan belas"};
    const char* tens[] = {"", "sepuluh", "dua puluh", "tiga puluh", "empat puluh", "lima puluh", "enam puluh", "tujuh puluh", "delapan puluh", "sembilan puluh"};

    if (number == 0) {
        strcpy(words, "nol");
    } else if (number < 10) {
        strcpy(words, ones[number]);
    } else if (number < 20) {
        strcpy(words, teens[number - 10]);
    } else if (number < 100) {
        strcpy(words, tens[number / 10]);
        if (number % 10 != 0) {
            strcat(words, " ");
            strcat(words, ones[number % 10]);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2 || (strcmp(argv[1], "-kali") != 0 && strcmp(argv[1], "-tambah") != 0 && strcmp(argv[1], "-kurang") != 0 && strcmp(argv[1], "-bagi") != 0)) {
        printf("Format: %s [-kali atau -tambah atau -kurang atau -bagi]\n", argv[0]);
        return 1;
    }

    char *operasi = argv[1];
    printf("Masukkan dua angka (dalam bentuk kata) untuk melakukan operasi %s:\n", operasi);
    char angka1_str[20], angka2_str[20];
    scanf("%s %s", angka1_str, angka2_str);

    int operand1, operand2;

    // Mengubah kata menjadi angka
    if (strcmp(angka1_str, "satu") == 0) operand1 = 1;
    else if (strcmp(angka1_str, "dua") == 0) operand1 = 2;
    else if (strcmp(angka1_str, "tiga") == 0) operand1 = 3;
    else if (strcmp(angka1_str, "empat") == 0) operand1 = 4;
    else if (strcmp(angka1_str, "lima") == 0) operand1 = 5;
    else if (strcmp(angka1_str, "enam") == 0) operand1 = 6;
    else if (strcmp(angka1_str, "tujuh") == 0) operand1 = 7;
    else if (strcmp(angka1_str, "delapan") == 0) operand1 = 8;
    else if (strcmp(angka1_str, "sembilan") == 0) operand1 = 9;

    if (strcmp(angka2_str, "satu") == 0) operand2 = 1;
    else if (strcmp(angka2_str, "dua") == 0) operand2 = 2;
    else if (strcmp(angka2_str, "tiga") == 0) operand2 = 3;
    else if (strcmp(angka2_str, "empat") == 0) operand2 = 4;
    else if (strcmp(angka2_str, "lima") == 0) operand2 = 5;
    else if (strcmp(angka2_str, "enam") == 0) operand2 = 6;
    else if (strcmp(angka2_str, "tujuh") == 0) operand2 = 7;
    else if (strcmp(angka2_str, "delapan") == 0) operand2 = 8;
    else if (strcmp(angka2_str, "sembilan") == 0) operand2 = 9;

    int pipefd[2];
    pipe(pipefd);
    pid_t child_pid = fork();

    if (child_pid == 0) {
        close(pipefd[1]);
        char result[256];
        read(pipefd[0], result, 256);
        printf("%s\n", result);
    } else {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        calculate(operand1, operand2, operasi);
    }

    return 0;
}
