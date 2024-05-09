# PRAKTIKUM SISOP-3-2024-MH-IT13

**KELOMPOK IT13**
| Nama | NRP |
|---------------------------|------------|
|Muhamad Arrayyan | 5027231014 |
|Hazwan Adhikara Nasution | 5027231017 |
|Muhammad Andrean Rizq Prasetio | 5027231052 |

## Pengantar

Laporan resmi ini dibuat terkait dengan praktikum modul 3 sistem operasi yang telah dilaksanakan pada tanggal 1 Mei 2024 hingga tanggal 11 Mei 2024. Praktikum modul 3 terdiri dari 4 soal yang dikerjakan oleh kelompok praktikan yang terdiri dari 3 orang selama waktu tertentu.

Kelompok IT13 melakukan pengerjaan modul 3 ini dengan pembagian sebagai berikut:

- Soal 1 dikerjakan oleh Muhamad Arrayyan
- Soal 2 dikerjakan oleh Muhamad Arrayyan
- Soal 3 dikerjakan oleh Hazwan Adhikara Nasution
- Soal 4 dikerjakan oleh Muhammad Andrean Rizq Prasetio

Sehingga dengan demikian, Pembagian bobot pengerjaan soal menjadi (Rayyan 40%, Hazwan 30%, Andre 30%).

Kelompok IT13 juga telah menyelesaikan tugas praktikum modul 3 yang telah diberikan dan telah melakukan demonstrasi kepada Asisten lab. Dari hasil praktikum yang telah dilakukan sebelumnya, maka diperoleh hasil sebagaimana yang dituliskan pada setiap bab di bawah ini.

## Ketentuan

Struktur Repository Seperti Berikut:

```bash
—soal_1:
	— auth.c
	— rate.c
	— db.c
                                    
—soal_2:
	— dudududu.c
				
—soal_3:
	— actions.c
	— driver.c
	— paddock.c
				
—soal_4:
	— client/
		— client.c 
	— server/
		— server.c

```

---

### **`Soal 1`**

`>Rayyan`

### > Isi Soal
Pada zaman dahulu pada galaksi yang jauh-jauh sekali, hiduplah seorang Stelle. Stelle adalah seseorang yang sangat tertarik dengan Tempat Sampah dan Parkiran Luar Angkasa. Stelle memulai untuk mencari Tempat Sampah dan Parkiran yang terbaik di angkasa. Dia memerlukan program untuk bisa secara otomatis mengetahui Tempat Sampah dan Parkiran dengan rating terbaik di angkasa. Programnya berbentuk microservice sebagai berikut:

a.) Dalam **auth.c** pastikan file yang masuk ke folder **new-entry** adalah file csv dan berakhiran  *trashcan* dan *parkinglot*. Jika bukan, program akan secara langsung akan delete file tersebut. 
- Contoh dari nama file yang akan diautentikasi:
  - belobog_trashcan.csv
  - osaka_parkinglot.csv

b.) Format data (Kolom)  yang berada dalam file csv adalah seperti berikut:
- ![image](https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/150534107/01bb68b7-ae4b-4023-9ce3-21dabaf97b97)
- ![image](https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/150534107/5d9a3678-712d-473e-b3a2-e0184385456c)

c.) File csv yang lolos tahap autentikasi akan dikirim ke shared memory. 

d.) Dalam **rate.c**, proses akan mengambil data csv dari shared memory dan akan memberikan output Tempat Sampah dan Parkiran dengan Rating Terbaik dari data tersebut.
- Contoh :
  - ![image](https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/150534107/6d206812-e0d7-46a5-bb3f-64c2cdfd3b59)

e.) Pada **db.c**, proses bisa memindahkan file dari **new-data** ke folder **microservices/database, WAJIB MENGGUNAKAN SHARED MEMORY**

f.) Log semua file yang masuk ke folder microservices/database ke dalam file db.log dengan contoh format sebagai berikut:
- [DD/MM/YY hh:mm:ss] [type] [filename]
  - ex : `[07/04/2024 08:34:50] [Trash Can] [belobog_trashcan.csv]`
- Contoh direktori awal:
  - ![image](https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/150534107/fde2df2d-0f32-4806-a575-14301af17f3a)
- Contoh direktori akhir setelah dijalankan **auth.c** dan **db.c**:
  - ![image](https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/150534107/de2ea53f-31fc-40ac-b535-446c4189da6f)

#### > Penyelesaian
### **`dudududu.c`**

```bash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

int string_to_number(char *str) {
    if (strcmp(str, "nol") == 0) return 0;
    if (strcmp(str, "satu") == 0) return 1;
    if (strcmp(str, "dua") == 0) return 2;
    if (strcmp(str, "tiga") == 0) return 3;
    if (strcmp(str, "empat") == 0) return 4;
    if (strcmp(str, "lima") == 0) return 5;
    if (strcmp(str, "enam") == 0) return 6;
    if (strcmp(str, "tujuh") == 0) return 7;
    if (strcmp(str, "delapan") == 0) return 8;
    if (strcmp(str, "sembilan") == 0) return 9;
    if (strcmp(str, "sepuluh") == 0) return 10;
    if (strcmp(str, "seratus") == 0) return 100;
    return -1; // If not a valid number string
}

void number_to_words(int num, char *result) {
    char *ones[] = {"nol", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan", "sepuluh"};
    char *teens[] = {"sepuluh", "sebelas", "dua belas", "tiga belas", "empat belas", "lima belas", "enam belas", "tujuh belas", "delapan belas", "sembilan belas"};
    char *tens[] = {"", "sepuluh", "dua puluh", "tiga puluh", "empat puluh", "lima puluh", "enam puluh", "tujuh puluh", "delapan puluh", "sembilan puluh"};

    if (num == 100) {
        strcpy(result, "seratus");
    } else if (num >= 0 && num <= 10) {
        strcpy(result, ones[num]);
    } else if (num >= 11 && num <= 19) {
        strcpy(result, teens[num - 10]);
    } else if (num >= 20 && num <= 99) {
        if (num % 10 == 0) {
            strcpy(result, tens[num / 10]);
        } else {
            sprintf(result, "%s %s", tens[num / 10], ones[num % 10]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <operation>\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(pipefd[1]);
        int result;
        read(pipefd[0], &result, sizeof(result));

        char result_words[50];
        number_to_words(result, result_words);

        char operation[20];
        char input1[10], input2[10];
        if (strcmp(argv[1], "-kali") == 0) {
            strcpy(operation, "perkalian");
            read(pipefd[0], input1, sizeof(input1));
            read(pipefd[0], input2, sizeof(input2));
            printf("hasil %s %s dan %s adalah %s.\n", operation, input1, input2, result_words);
        } else if (strcmp(argv[1], "-tambah") == 0) {
            strcpy(operation, "penjumlahan");
            read(pipefd[0], input1, sizeof(input1));
            read(pipefd[0], input2, sizeof(input2));
            printf("hasil %s %s dan %s adalah %s.\n", operation, input1, input2, result_words);
        } else if (strcmp(argv[1], "-kurang") == 0) {
            strcpy(operation, "pengurangan");
            read(pipefd[0], input1, sizeof(input1));
            read(pipefd[0], input2, sizeof(input2));
            if (result < 0) {
                printf("ERROR pada pengurangan\n");
            } else if (result == 0) {
                printf("hasil pengurangan %s dan %s adalah %s.\n", input1, input2, result_words);
            } else {
                printf("hasil %s %s dan %s adalah %s.\n", operation, input1, input2, result_words);
            }
        } else if (strcmp(argv[1], "-bagi") == 0) {
            strcpy(operation, "pembagian");
            read(pipefd[0], input1, sizeof(input1));
            read(pipefd[0], input2, sizeof(input2));
            if (result == -1) {
                printf("ERROR pada pembagian nol\n");
            } else {
                printf("hasil %s %s dan %s adalah %s.\n", operation, input1, input2, result_words);
            }
        }

        time_t rawtime;
        struct tm *timeinfo;
        char log_message[200];
        char operation_str[20];
        char time_str[20];

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(time_str, sizeof(time_str), "%d/%m/%y %H:%M:%S", timeinfo);

        if (strcmp(argv[1], "-kali") == 0) {
            strcpy(operation_str, "KALI");
            snprintf(log_message, sizeof(log_message), "[%s] [%s] %s kali %s sama dengan %s", time_str, operation_str, input1, input2, result_words);
        } else if (strcmp(argv[1], "-tambah") == 0) {
            strcpy(operation_str, "TAMBAH");
            snprintf(log_message, sizeof(log_message), "[%s] [%s] %s tambah %s sama dengan %s", time_str, operation_str, input1, input2, result_words);
        } else if (strcmp(argv[1], "-kurang") == 0) {
            strcpy(operation_str, "KURANG");
            if (result < 0) {
                snprintf(log_message, sizeof(log_message), "[%s] [%s] ERROR pada pengurangan", time_str, operation_str);
            } else if (result == 0) {
                snprintf(log_message, sizeof(log_message), "[%s] [%s] %s kurang %s sama dengan %s", time_str, operation_str, input1, input2, result_words);
            } else {
                snprintf(log_message, sizeof(log_message), "[%s] [%s] %s kurang %s sama dengan %s", time_str, operation_str, input1, input2, result_words);
            }
        } else if (strcmp(argv[1], "-bagi") == 0) {
            strcpy(operation_str, "BAGI");
            if (result == -1) {
                snprintf(log_message, sizeof(log_message), "[%s] [%s] ERROR pada pembagian nol", time_str, operation_str);
	    } else {
	        snprintf(log_message, sizeof(log_message), "[%s] [%s] %s bagi %s sama dengan %s", time_str, operation_str, input1, input2, result_words);
	    }
        }

        FILE *log_file = fopen("histori.log", "a");
        if (log_file == NULL) {
            perror("fopen");
            return 1;
        }

        fprintf(log_file, "%s\n", log_message);
        fclose(log_file);

        close(pipefd[0]);
    } else {
        close(pipefd[0]);

        char input1[10], input2[10];
        printf("Masukkan dua angka (dalam bahasa): ");
        scanf("%s %s", input1, input2);

        int num1 = string_to_number(input1);
        int num2 = string_to_number(input2);

        if (num1 == -1 || num2 == -1) {
            printf("Input tidak valid.\n");
            close(pipefd[1]);
            return 1;
        }

        int result;
        if (strcmp(argv[1], "-kali") == 0) result = num1 * num2;
        else if (strcmp(argv[1], "-tambah") == 0) result = num1 + num2;
        else if (strcmp(argv[1], "-kurang") == 0) result = num1 - num2;
        else if (strcmp(argv[1], "-bagi") == 0) {
            if (num2 == 0) {
                result = -1;
            } else {
                result = floor(num1 / num2);
            }
        }

        write(pipefd[1], &result, sizeof(result));
        write(pipefd[1], input1, sizeof(input1));
        write(pipefd[1], input2, sizeof(input2));

        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}
```
#### > Penjelasan
#### > Dokumentasi
#### > Revisi
---

### **`Soal 2`**

`>Rayyan`

### > Isi Soal
Max Verstappen 🏎️ seorang pembalap F1 dan programer memiliki seorang adik bernama Min Verstappen (masih SD) sedang menghadapi tahap paling kelam dalam kehidupan yaitu perkalian matematika, Min meminta bantuan Max untuk membuat kalkulator perkalian sederhana (satu sampai sembilan). Sembari Max nguli dia menyuruh Min untuk belajar perkalian dari web (referensi) agar tidak bergantung pada kalkulator.
**(Wajib menerapkan konsep pipes dan fork seperti yang dijelaskan di modul Sisop. Gunakan 2 pipes dengan diagram seperti di modul 3).**

a.) Sesuai request dari adiknya Max ingin nama programnya dudududu.c. Sebelum program parent process dan child process, ada input dari user berupa 2 string. Contoh input: tiga tujuh. 

b.) Pada parent process, program akan mengubah input menjadi angka dan melakukan perkalian dari angka yang telah diubah. Contoh: tiga tujuh menjadi 21. 

c.) Pada child process, program akan mengubah hasil angka yang telah diperoleh dari parent process menjadi kalimat. Contoh: `21` menjadi “dua puluh satu”.

d.) Max ingin membuat program kalkulator dapat melakukan penjumlahan, pengurangan, dan pembagian, maka pada program buatlah argumen untuk menjalankan program : 
- I.   perkalian	: ./kalkulator -kali
- II.  penjumlahan	: ./kalkulator -tambah
- III. pengurangan	: ./kalkulator -kurang
- IV.  pembagian	: ./kalkulator -bagi

Beberapa hari kemudian karena Max terpaksa keluar dari Australian Grand Prix 2024 membuat Max tidak bersemangat untuk melanjutkan programnya sehingga kalkulator yang dibuatnya cuma menampilkan hasil positif jika bernilai negatif maka program akan print “ERROR” serta cuma menampilkan bilangan bulat jika ada bilangan desimal maka dibulatkan ke bawah.

e.) Setelah diberi semangat, Max pun melanjutkan programnya dia ingin (pada child process) kalimat akan di print dengan contoh format : 
- I.   perkalian	: “hasil perkalian tiga dan tujuh adalah dua puluh satu.”
- II.  penjumlahan	: “hasil penjumlahan tiga dan tujuh adalah sepuluh.”
- III. pengurangan	: “hasil pengurangan tujuh dan tiga adalah empat.”
- IV.  pembagian	: “hasil pembagian tujuh dan tiga adalah dua.”

f.) Max ingin hasil dari setiap perhitungan dicatat dalam sebuah log yang diberi nama histori.log. Pada parent process, lakukan pembuatan file log berdasarkan data yang dikirim dari child process. 
- Format: [date] [type] [message]
- Type: KALI, TAMBAH, KURANG, BAGI
- Ex:
  - [10/03/24 00:29:47] [KALI] tujuh kali enam sama dengan empat puluh dua.
  - [10/03/24 00:30:00] [TAMBAH] sembilan tambah sepuluh sama dengan sembilan belas.
  - [10/03/24 00:30:12] [KURANG] ERROR pada pengurangan.

#### > Penyelesaian
### **`auth.c`**

```bash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>

int main() {
    int key = 87654321;
    DIR *dir = opendir("new-data");
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;
    int shm_key = 87654321;
    while ((entry = readdir(dir)) != NULL) {
        if ((strstr(entry->d_name, "trashcan.csv") || strstr(entry->d_name, "parkinglot.csv"))) {
            int shmid = shmget(shm_key, 1024, IPC_CREAT | 0666);
            if (shmid == -1) {
                perror("shmget");
                exit(1);
            }

            char *shared_memory = shmat(shmid, NULL, 0);
            if (shared_memory == (char *) -1) {
                perror("shmat");
                exit(1);
            }

            strcpy(shared_memory, entry->d_name);

            shmdt(shared_memory);

            // Increment key buat shared memory segment selanjutnya
            shm_key++;
        } else {
            char filePath[1024];
            snprintf(filePath, sizeof(filePath), "new-data/%s", entry->d_name);
            remove(filePath);
        }
    }

    closedir(dir);

    return 0;
}
```
### **`rate.c`**

```bash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int baseKey = 87654321; 
    int shmid;
    char *shared_memory;

    for (int i = 0; ; i++) {
        int key = baseKey + i; 
        shmid = shmget(key, 1024, 0666);
        if (shmid == -1) {
            break;
        }
        shared_memory = shmat(shmid, NULL, 0);
        if (shared_memory == (char *) -1) {
            perror("shmat");
            exit(1);
        }

        printf("Contents of shared memory: %s\n", shared_memory);
      
        char *filename = shared_memory;
        const char *type;
        if (strstr(filename,"trashcan.csv")){
            type = "Trash can";
        } else {
            type = "Parking lot";
        }
        char fullpath[1024];
        strcpy(fullpath, "/home/rrayyaann/sisop/percobaan/m3s1/new-data/"); 
        strcat(fullpath, filename); 
        printf("Attempting to open file at: %s\n", fullpath);
        FILE *file = fopen(fullpath, "r");
        if (!file) {
            perror("fopen");
            exit(1);
        }

        char line[1024];
        float maxRating = 0.0;
        char bestName[256] = {0};

        while (fgets(line, sizeof(line), file)) {
            char *name = strtok(line, ",");
            char *rating_str = strtok(NULL, ",");
            float rating = atof(rating_str);

            if (rating > maxRating) {
                maxRating = rating;
                strcpy(bestName, name);
            } else if (rating == maxRating) {
                strcat(bestName, ", "); 
                strcat(bestName, name);
            }
        }

        fclose(file);

        printf("Type: %s\n", type);
        printf("Filename: %s\n", filename);
        printf("------------\n");
        printf("Name: %s\n", bestName);
        printf("Rating: %.1f\n\n", maxRating);

        shmdt(shared_memory);
    }

    return 0;
}
```
### **`db.c`**

```bash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

int main() {
    int key = 87654321;
    int shmid;
    char *shared_memory;

    for (int i=0; ; i++){
        key += i;
        int shmid = shmget(key, 1024, 0666);
        if (shmid == -1) {
            break;
        }

        shared_memory = shmat(shmid, NULL, 0);
        if (shared_memory == (char *) -1) {
            perror("shmat");
            exit(1);
        }

        // Baca shared memory
        char *filename = shared_memory;
        const char *type;
            if (strstr(filename,"trashcan.csv")){
                type = "Trash can";
            } else {
                type = "Parking lot";
            }

        // Move file ke directory database
        char source_path[256], db_path[256];
        snprintf(source_path, sizeof(source_path), "/home/rrayyaann/sisop/percobaan/m3s1/new-data/%s", filename);
        snprintf(db_path, sizeof(db_path), "database/%s", filename);
        if (rename(source_path, db_path) == -1) {
            perror("rename");
            printf("Failed to move file");
        } else {
            printf("File moved successfully");
        }

        // Log ke db.log
        FILE *log_file = fopen("database/db.log", "a");
        if (log_file == NULL) {
            perror("fopen");
            exit(1);
        }
      
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "[%d/%m/%y %H:%M:%S]", timeinfo);

        fprintf(log_file, "%s [%s] [%s]\n", buffer, type, filename);
        fclose(log_file);

        shmdt(shared_memory);
    }
    
    return 0;
}
```
#### > Penjelasan
#### > Dokumentasi
#### > Revisi

---

### **`Soal 3`**

`>Hazwan`

### > Isi Soal
Shall Leglerg🥶 dan Carloss Signs 😎 adalah seorang pembalap F1 untuk tim Ferrari 🥵. Mobil F1 memiliki banyak pengaturan, seperti penghematan ERS, Fuel, Tire Wear dan lainnya. Pada minggu ini ada race di sirkuit Silverstone. Malangnya, seluruh tim Ferrari diracun oleh Super Max Max pada hari sabtu sehingga seluruh kru tim Ferrari tidak bisa membantu Shall Leglerg🥶 dan Carloss Signs 😎 dalam race. Namun, kru Ferrari telah menyiapkan program yang bisa membantu mereka dalam menyelesaikan race secara optimal. Program yang dibuat bisa mengatur pengaturan - pengaturan dalam mobil F1 yang digunakan dalam balapan. Programnya ber ketentuan sebagai berikut:

a. Pada program actions.c, program akan berisi function function yang bisa di call oleh paddock.c

b. Action berisikan sebagai berikut:
- Gap [Jarak dengan driver di depan (float)]: Jika Jarak antara Driver dengan Musuh di depan adalah < 3.5s maka return Gogogo, jika jarak > 3.5s dan 10s return Push, dan jika jarak > 10s maka return Stay out of trouble.
- Fuel [Sisa Bensin% (string/int/float)]: Jika bensin lebih dari 80% maka return Push Push Push, jika bensin di antara 50% dan 80% maka return You can go, dan jika bensin kurang dari 50% return Conserve Fuel.
- Tire [Sisa Ban (int)]: Jika pemakaian ban lebih dari 80 maka return Go Push Go Push, jika pemakaian ban diantara 50 dan 80 return Good Tire Wear, jika pemakaian di antara 30 dan 50 return Conserve Your Tire, dan jika pemakaian ban kurang dari 30 maka return Box Box Box.
- Tire Change [Tipe ban saat ini (string)]: Jika tipe ban adalah Soft return Mediums Ready, dan jika tipe ban Medium return Box for Softs.

  	Contoh:
  
	`[Driver] : [Fuel] [55%]`

	`[Paddock]: [You can go]`

c. Pada paddock.c program berjalan secara daemon di background, bisa terhubung dengan driver.c melalui socket RPC.

d. Program paddock.c dapat call function yang berada di dalam actions.c.

e. Program paddock.c tidak keluar/terminate saat terjadi error dan akan log semua percakapan antara paddock.c dan driver.c di dalam file race.log

Format log:

`[Source] [DD/MM/YY hh:mm:ss]: [Command] [Additional-info]`

ex :

`[Driver] [07/04/2024 08:34:50]: [Fuel] [55%]`

`[Paddock] [07/04/2024 08:34:51]: [Fuel] [You can go]`

f. Program driver.c bisa terhubung dengan paddock.c dan bisa mengirimkan pesan dan menerima pesan serta menampilan pesan tersebut dari paddock.c sesuai dengan perintah atau function call yang diberikan.

g. Jika bisa digunakan antar device/os (non local) akan diberi nilai tambahan.

h. untuk mengaktifkan RPC call dari driver.c, bisa digunakan in-program CLI atau Argv (bebas) yang penting bisa send command seperti poin B dan menampilkan balasan dari paddock.c
		
ex:
- Argv:

`./driver -c Fuel -i 55%`

- in-program CLI:

`Command: Fuel`

`Info: 55%`

#### > Penyelesaian
- actions.c
```bash
#include <stdio.h>
#include <string.h>
#include "actions.h"

char *gap(float jarak)
{
    if (jarak < 3.5)
        return "Gogogo";
    else if (jarak >= 3.5 && jarak <= 10)
        return "Push";
    else
        return "Stay out of trouble";
}

char *fuel(int sisaBensin)
{
    if (sisaBensin > 80)
        return "Push Push Push";
    else if (sisaBensin >= 50 && sisaBensin <= 80)
        return "You can go";
    else
        return "Conserve Fuel";
}

char *tire(int sisaBan)
{
    if (sisaBan > 80)
        return "Go Push Go Push";
    else if (sisaBan >= 50 && sisaBan <= 80)
        return "Good Tire Wear";
    else if (sisaBan >= 30 && sisaBan < 50)
        return "Conserve Your Tire";
    else
        return "Box Box Box";
}

char *tireChange(char *tipeBan)
{
    if (strcmp(tipeBan, "Soft") == 0)
        return "Mediums Ready";
    else if (strcmp(tipeBan, "Medium") == 0)
        return "Box for Softs";
    else
        return "Pasang Dulu Ban Lu Brok";
}
```
  
- paddock.c
```bash
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "actions.h"
#include <time.h>

#define PORT 8081

void raceLog(const char *source, const char *command, const char *addInfo)
{
    FILE *logFile = fopen("/home/zwaneee/sisop/modul3/server/race.log", "a");
    time_t current = time(0);
    struct tm *tm = localtime(&current);
    fprintf(logFile, "[%s] [%02d/%02d/%04d %02d:%02d:%02d]: [%s] [%s]\n", source, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec, command, addInfo);
    fclose(logFile);
}

int main()
{
    pid_t pid, sid;
    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    openlog("paddock", LOG_PID, LOG_DAEMON);
    syslog(LOG_NOTICE, "paddock started");

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *response;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        syslog(LOG_ERR, "Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        syslog(LOG_ERR, "Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        syslog(LOG_ERR, "Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            syslog(LOG_ERR, "Accept failed");
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, 1024);
        syslog(LOG_INFO, "Received: %s", buffer);

        char command[50], info[50];
        if (sscanf(buffer, "[%[^]]] : [%[^]]", command, info) == 2) // membaca string dengan format tertentu
        {
            if (strcmp(command, "Gap") == 0)
            {
                float jarak = atof(info);
                response = gap(jarak);
            }
            else if (strcmp(command, "Fuel") == 0)
            {

                int sisaBensin = atoi(info);
                response = fuel(sisaBensin);
            }
            else if (strcmp(command, "Tire") == 0)
            {

                int sisaBan = atoi(info);
                response = tire(sisaBan);
            }
            else if (strcmp(command, "TireChange") == 0)
            {
                response = tireChange(info);
            }
            else
            {
                response = "Command Tidak Diketahui";
            }
        }
        else
        {
            response = "Format pesan tidak valid";
        }
        raceLog("Driver", command, info);      // nyatet log
        raceLog("Paddock", command, response); // nyatet log
        send(new_socket, response, strlen(response), 0);
        syslog(LOG_INFO, "Response sent: %s", response);

        close(new_socket);
    }

    syslog(LOG_NOTICE, "paddock terminated");
    closelog();

    return EXIT_SUCCESS;
}

```

- driver.c
```bash
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define IP "127.0.0.1"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s -c COMMAND -i INFO\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Membaca Pesan
    char message[256];
    sprintf(message, "[%s] : [%s]", argv[2], argv[4]);

    // Mengirim Response
    send(sock, message, strlen(message), 0);

    // Menerima Response
    char buffer[1024] = {0};
    int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes_received < 0)
    {
        perror("Receive failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Response : %s\n", buffer);

    close(sock);

    return 0;
}

```
#### > Penjelasan
**actions.c**

1. `gap(float jarak)`

- Fungsi ini mengambil parameter float bernama jarak.
- Jika jarak kurang dari 3,5, fungsi mengembalikan "Gogogo".
- Jika jarak berada di antara 3,5 dan 10, fungsi mengembalikan "Push".
- Jika tidak, fungsi menyarankan untuk "Stay out of trouble".

2. `fuel(int sisaBensin)`
- Fungsi ini mengambil parameter int bernama sisaBensin.
- Jika sisaBensin lebih dari 80, fungsi menyarankan untuk "Push Push Push".
- Jika sisaBensin berada di antara 50 dan 80 , fungsi mengindikasikan bahwa Anda bisa melanjutkan perjalanan dengan pesan "You can go".
- Jika tidak, fungsi menyarankan untuk "Conserve Fuel" .

3. `tire(int sisaBan)`
- Fungsi ini mengambil parameter int bernama sisaBan.
- Jika sisaBan lebih dari 80, fungsi menyarankan untuk "Go Push Go Push".
- Jika sisaBan berada di antara 50 dan 80, fungsi menyatakan "Good Tire Wear".
- Jika sisaBan berada di antara 30 dan 50, fungsi menyarankan untuk "Conserve Your Tire".
- Jika tidak, fungsi menyarankan untuk pit stop dengan pesan "Box Box Box".
  
4. `tireChange(char *tipeBan)`
- Fungsi ini mengambil parameter char* bernama tipeBan.
- Jika tipeBan adalah "Soft", fungsi mengindikasikan bahwa "Mediums Ready".
- Jika tipeBan adalah "Medium", fungsi menyarankan untuk "Box for Softs".
- Jika tidak, fungsi dengan humor menyarankan untuk "Pasang Dulu Ban Lu Brok".

**paddock.c**
1. `raceLog(const char *source, const char *command, const char *addInfo)`
- Fungsi ini bertanggung jawab untuk mencatat log ke file `/home/zwaneee/sisop/modul3/server/race.log`.
- Parameter:
	- `source`: String yang menunjukkan sumber log (misalnya “Driver” atau “Paddock”).
	- `command`: String yang berisi perintah atau tindakan yang dicatat.
	- `addInfo`: String yang berisi informasi tambahan terkait perintah.
- Fungsi membuka file log, menulis entri log dengan format tanggal dan waktu, dan kemudian menutup file.
  
2. `main()`
- Fungsi utama program.
- Langkah-langkah yang dilakukan:
	- Fork proses agar program berjalan sebagai daemon.
	- Mengatur hak akses file dengan `umask(0)`.
	- Membuat session ID baru dengan `setsid()`.
	- Mengubah direktori kerja ke root dengan `(chdir("/"))`.
	- Menutup file descriptor standar (stdin, stdout, stderr).
	- Membuka log dengan `openlog("paddock", LOG_PID, LOG_DAEMON)`.
	- Menerima koneksi dari socket dan memproses perintah yang diterima.
	- Mencatat log dan mengirim respons ke klien.
	- Menutup socket dan mengakhiri program.

3. `Pengolahan Perintah`
- Program menerima perintah dalam format `[command] : [info]`.
- Jika format sesuai, program memeriksa jenis perintah dan mengambil informasi terkait.
- Berdasarkan jenis perintah, program memanggil fungsi yang sesuai (seperti `gap`, `fuel`, `tire`, atau `tireChange`).
- Jika format tidak sesuai, program mengirim respons “Format pesan tidak valid”.
   
4. `Logging`
Setiap perintah yang diterima dan respons yang dikirim dicatat dalam log.
Log mencatat sumber (Driver atau Paddock), perintah, dan informasi terkait.

**driver.c**
1. Inisialisasi Socket dan Koneksi:
- Program ini bertanggung jawab untuk menginisialisasi socket dan melakukan koneksi ke server.
- Membuat socket dengan socket`(AF_INET, SOCK_STREAM, 0)`.
- Mengatur alamat server dengan `serv_addr.sin_family` dan `serv_addr.sin_port`.
- Mengonversi alamat IP ke format biner dengan `inet_pton(AF_INET, IP, &serv_addr.sin_addr)`.
- Membuat koneksi dengan `connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))`.

2. Membaca Pesan dan Mengirim Response:
- Program membaca perintah dan informasi dari argumen baris perintah.
- Menggabungkan perintah dan informasi menjadi pesan dengan `sprintf`.
- Mengirim pesan ke server dengan `send(sock, message, strlen(message), 0)`.

3. Menerima Response:
- Program menerima respons dari server dengan `recv(sock, buffer, sizeof(buffer), 0)`.
- Jika pengiriman respons gagal, program menampilkan pesan kesalahan.
- Jika berhasil, program mencetak respons ke layar.
  
#### > Dokumentasi
<img width="1710" alt="image" src="https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/151142830/665b1dbd-5a92-496c-aceb-782587d06a33">
<img width="1710" alt="image" src="https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/151142830/9d6013b4-0774-4a8e-833f-3c5416c25467">
<img width="1710" alt="image" src="https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/151142830/ae8ab9ee-5b68-4fb9-bb10-2568b5a71752">
<img width="1710" alt="image" src="https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/151142830/0f7780bb-aa8c-4254-a681-ee42e03871d8">
<img width="1710" alt="image" src="https://github.com/HazwanAdhikara/Sisop-3-2024-MH-IT13/assets/151142830/43dd05b2-c3e2-4672-b58f-4ec56d6280d2">


#### > Revisi

---

### **`Soal 4`**
`>Andre`

### > Isi Soal
#### > Penyelesaian
#### > Penjelasan
#### > Dokumentasi
#### > Revisi
