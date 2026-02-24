#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int nilai[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &nilai[i]);
    }

    int kode;
    scanf("%d", &kode);

    int total = 0;

    if (kode == 1) {
        for (int i = 0; i < N; i += 2) {
            total += nilai[i];
        }
    } else if (kode == 2) {
        for (int i = 1; i < N; i += 2) {
            total += nilai[i];
        }
    } else {
        printf("Kode kelompok tidak valid.\n");
        return 1;
    }

    printf("%d\n", total);

    return 0;
}