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
#### > Penyelesaian
#### > Penjelasan
#### > Dokumentasi
#### > Revisi
---

### **`Soal 2`**

`>Rayyan`

### > Isi Soal
#### > Penyelesaian
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
[Source] [DD/MM/YY hh:mm:ss]: [Command] [Additional-info]

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
- actions.c

- paddock.c

- driver.c

#### > Dokumentasi
#### > Revisi

---

### **`Soal 4`**
`>Andre`

### > Isi Soal
#### > Penyelesaian
#### > Penjelasan
#### > Dokumentasi
#### > Revisi
