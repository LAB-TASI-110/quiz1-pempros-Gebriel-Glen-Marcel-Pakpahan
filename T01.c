#include <stdio.h>
#include <string.h>

// Definisi struktur untuk Menu Makanan
struct Menu {
    char kode[5];
    char nama[30];
    int harga;
};

// Definisi struktur untuk menyimpan pesanan sementara
struct Pesanan {
    char namaMenu[30];
    int porsiTotal;
    int hargaSatuan;
    int totalHarga;
};

int main() {
    // 1. Inisialisasi Daftar Menu sesuai Gambar
    struct Menu daftarMenu[] = {
        {"NGS", "Nasi Goreng Spesial", 15000},
        {"AP",  "Ayam Penyet",        20000},
        {"SA",  "Sate Ayam (10 Tusuk)", 25000},
        {"BU",  "Bakso Urat",         18000},
        {"MAP", "Mie Ayam Pangsit",   15000},
        {"GG",  "Gado-Gado",          15000},
        {"SAM", "Soto Ayam",          17000},
        {"RD",  "Rendang Daging",     25000},
        {"IB",  "Ikan Bakar",         35000},
        {"NUK", "Nasi Uduk Komplit",  20000}
    };
    
    int jumlahMenu = sizeof(daftarMenu) / sizeof(daftarMenu[0]);
    
    // Variabel untuk input dan proses
    char inputKode[10];
    int inputPorsiButet;
    struct Pesanan listPesanan[50]; // Menyimpan daftar belanjaan untuk struk
    int jumlahPesanan = 0;
    long totalBelanja = 0;

    printf("Masukkan Pesanan (Ketik 'END' untuk selesai):\n");

    // 2. Loop Input Pesanan
    while (1) {
        scanf("%s", inputKode);
        
        // Cek kondisi berhenti
        if (strcmp(inputKode, "END") == 0) {
            break;
        }

        scanf("%d", &inputPorsiButet);

        // Mencari menu berdasarkan kode
        int found = 0;
        for (int i = 0; i < jumlahMenu; i++) {
            if (strcmp(inputKode, daftarMenu[i].kode) == 0) {
                found = 1;
                
                // LOGIKA PORSI:
                // Input = Porsi Butet
                // Porsi Ucok = 2 * Porsi Butet
                // Total Porsi = Porsi Butet + Porsi Ucok
                int porsiUcok = inputPorsiButet * 2;
                int totalPorsiItem = inputPorsiButet + porsiUcok;
                
                int subtotal = totalPorsiItem * daftarMenu[i].harga;

                // Simpan ke dalam list pesanan untuk dicetak nanti
                strcpy(listPesanan[jumlahPesanan].namaMenu, daftarMenu[i].nama);
                listPesanan[jumlahPesanan].porsiTotal = totalPorsiItem;
                listPesanan[jumlahPesanan].hargaSatuan = daftarMenu[i].harga;
                listPesanan[jumlahPesanan].totalHarga = subtotal;
                
                totalBelanja += subtotal;
                jumlahPesanan++;
                break;
            }
        }
        
        if (!found) {
            printf("Menu dengan kode %s tidak ditemukan.\n", inputKode);
        }
    }

    // 3. Logika Kupon / Diskon
    // Pola berdasarkan gambar dan deskripsi: Kelipatan 100rb naik tingkatan warna
    char namaKupon[20] = "Tidak Ada";
    float persentaseDiskon = 0.0;

    if (totalBelanja >= 500000) {
        strcpy(namaKupon, "Kupon Hitam");
        persentaseDiskon = 0.25; // 25%
    } else if (totalBelanja >= 400000) {
        strcpy(namaKupon, "Kupon Hijau");
        persentaseDiskon = 0.20; // 20%
    } else if (totalBelanja >= 300000) {
        strcpy(namaKupon, "Kupon Merah");
        persentaseDiskon = 0.15; // 15%
    } else if (totalBelanja >= 200000) {
        strcpy(namaKupon, "Kupon Kuning");
        persentaseDiskon = 0.10; // 10%
    } else if (totalBelanja >= 100000) {
        strcpy(namaKupon, "Kupon Biru");
        persentaseDiskon = 0.05; // 5%
    }

    long jumlahDiskon = totalBelanja * persentaseDiskon;
    long totalBayar = totalBelanja - jumlahDiskon;

    // 4. Mencetak Struk (Output)
    printf("\n\n");
    printf("=======================================================\n");
    printf("%-25s %-8s %-10s %-10s\n", "Menu", "Porsi", "Harga", "Total");
    printf("=======================================================\n");

    for (int i = 0; i < jumlahPesanan; i++) {
        printf("%-25s %-8d %-10d %-10d\n", 
            listPesanan[i].namaMenu, 
            listPesanan[i].porsiTotal, 
            listPesanan[i].hargaSatuan, 
            listPesanan[i].totalHarga);
    }

    printf("=======================================================\n");
    printf("Subtotal           : Rp %ld\n", totalBelanja);
    if (persentaseDiskon > 0) {
        printf("Diskon (%s)  : Rp %ld\n", namaKupon, jumlahDiskon);
    } else {
        printf("Diskon             : -\n");
    }
    printf("-------------------------------------------------------\n");
    printf("Total Pembayaran   : Rp %ld\n", totalBayar);
    printf("=======================================================\n");

    return 0;
}