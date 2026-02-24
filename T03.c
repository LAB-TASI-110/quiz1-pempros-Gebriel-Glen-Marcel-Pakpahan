#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ORDER 160

typedef enum {
    DITERIMA,       
    DICUCI,        
    DISETRIKA,     
    SIAP_ANTAR,     
    SELESAI         
} StatusLaundry;

typedef struct {
    int id;
    char nim[10];
    char nama[50];
    int kodeAsrama; 
    float berat;
    StatusLaundry status;
} Pesanan;


Pesanan daftarPesanan[MAX_ORDER];
int jumlahPesanan = 0;
int nextID = 1;


const char *namaAsrama[] = {
    "Rusun 1", "Rusun 2", "Rusun 3", "Rusun 4",
    "Sopo Jati", "Sopo Peniel", "Kembar 1", "Kembar 2"
};


const char* getStatusString(StatusLaundry s) {
    switch(s) {
        case DITERIMA: return "Menunggu";
        case DICUCI: return "Proses Cuci";
        case DISETRIKA: return "Setrika/Pack";
        case SIAP_ANTAR: return "Siap Antar";
        case SELESAI: return "Selesai";
        default: return "Unknown";
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



void tambahPesanan() {
    if (jumlahPesanan >= MAX_ORDER) {
        printf("Kapasitas penyimpanan penuh!\n");
        return;
    }

    Pesanan p;
    p.id = nextID++;
    
    printf("\n--- Form Penerimaan Laundry (Drop Point) ---\n");
    printf("Masukkan NIM: ");
    scanf("%s", p.nim);
    clearBuffer(); 

    printf("Masukkan Nama: ");
    fgets(p.nama, 50, stdin);
    p.nama[strcspn(p.nama, "\n")] = 0; 

    printf("\nPilih Asrama:\n");
    for (int i = 0; i < 8; i++) {
        printf("%d. %s\n", i+1, namaAsrama[i]);
    }
    printf("Pilihan (1-8): ");
    int pilihanAsrama;
    scanf("%d", &pilihanAsrama);
    
    if (pilihanAsrama < 1 || pilihanAsrama > 8) {
        printf("Asrama tidak valid! Set default ke Rusun 1.\n");
        p.kodeAsrama = 0;
    } else {
        p.kodeAsrama = pilihanAsrama - 1;
    }

    printf("Berat Laundry (kg): ");
    scanf("%f", &p.berat);

    p.status = DITERIMA;

    daftarPesanan[jumlahPesanan] = p;
    jumlahPesanan++;

 
    printf("\n=> Pesanan berhasil dicatat! ID Lacak: %d\n", p.id);
}

void updateStatus() {
    int idCari, found = 0;
    printf("\n--- Update Status Operasional ---\n");
    printf("Masukkan ID Pesanan: ");
    scanf("%d", &idCari);

    for (int i = 0; i < jumlahPesanan; i++) {
        if (daftarPesanan[i].id == idCari) {
            found = 1;
            printf("Status saat ini: %s\n", getStatusString(daftarPesanan[i].status));
            printf("Update ke:\n");
            printf("1. Proses Cuci\n");
            printf("2. Setrika/Packing\n");
            printf("3. Siap Antar (Delivery)\n");
            printf("4. Selesai (Diterima Mahasiswa)\n");
            printf("Pilihan: ");
            
            int stat;
            scanf("%d", &stat);
            
            if (stat >= 1 && stat <= 4) {
                daftarPesanan[i].status = (StatusLaundry)stat;
                printf("=> Status berhasil diperbarui menjadi: %s\n", getStatusString(daftarPesanan[i].status));
            } else {
                printf("Pilihan tidak valid.\n");
            }
            break;
        }
    }
    if (!found) printf("ID Pesanan tidak ditemukan.\n");
}

void lihatDaftar() {

    printf("\n===============================================================================\n");
    printf("%-4s | %-10s | %-15s | %-12s | %-6s | %-12s\n", 
           "ID", "NIM", "Nama", "Asrama", "Berat", "Status");
    printf("===============================================================================\n");
    
    for (int i = 0; i < jumlahPesanan; i++) {
        printf("%-4d | %-10s | %-15s | %-12s | %-6.1f | %-12s\n",
               daftarPesanan[i].id,
               daftarPesanan[i].nim,
               daftarPesanan[i].nama,
               namaAsrama[daftarPesanan[i].kodeAsrama],
               daftarPesanan[i].berat,
               getStatusString(daftarPesanan[i].status));
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("Total Cucian Terdaftar: %d Kantong\n", jumlahPesanan);
}



int main() {
    int menu;
    

    daftarPesanan[0] = (Pesanan){nextID++, "11322001", "Ucok", 0, 2.5, DITERIMA}; 
    daftarPesanan[1] = (Pesanan){nextID++, "11322002", "Butet", 4, 3.0, SIAP_ANTAR}; 
    jumlahPesanan = 2;

    do {
        printf("\n=== SISTEM TRACKING LAUNDRY IT DEL ===\n");
        printf("1. Terima Laundry Baru (Pickup)\n");
        printf("2. Update Status (Cuci/Setrika/Antar)\n");
        printf("3. Lihat Daftar Cucian\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &menu);
        clearBuffer();

        switch (menu) {
            case 1: tambahPesanan(); break;
            case 2: updateStatus(); break;
            case 3: lihatDaftar(); break;
            case 4: printf("Sistem dimatikan. Horas!\n"); break;
            default: printf("Menu tidak valid.\n");
        }
    } while (menu != 4);

    return 0;
}