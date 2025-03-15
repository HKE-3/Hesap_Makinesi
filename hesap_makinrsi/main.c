#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 100

void clearInputBuffer() {
    while (getchar() != '\n');
}

void showHistory() {
    FILE *file = fopen("hesap_sonuc.txt", "r");
    if (file == NULL) {
        printf("\nHenüz geçmiþ kayýt bulunmuyor.\n");
        return;
    }

    printf("\n===== GECMIS ISLEMLER =====\n");
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int main() {
    char op;
    double numbers[MAX_NUMBERS];
    int count;
    double result;
    FILE *file = fopen("hesap_sonuc.txt", "a");
    if (file == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    while (1) {
        printf("\n===== GELISMIS HESAP MAKINESI =====\n");
        printf("\nToplama (+), Cikarma (-), Carpma (*), Bolme (/), Us alma (^), Mod alma (%%)\n");
        printf("Trigonometrik islemler: sin (s), cos (c), tan (t), log (l), Cikis (q), Gecmis (h)\n");
        printf("Islem secin: ");
        if (scanf(" %c", &op) != 1) {
            printf("Gecersiz giris!\n");
            clearInputBuffer();
            continue;
        }

        if (op == 'q') {
            printf("Cikis yapiliyor...\n");
            break;
        }
        if (op == 'h') {
            showHistory();
            continue;
        }

        if (op == 's' || op == 'c' || op == 't' || op == 'l' || op == '^') {
            printf("Bir sayi girin: ");
            if (scanf("%lf", &numbers[0]) != 1) {
                printf("Gecersiz sayi girisi!\n");
                clearInputBuffer();
                continue;
            }
            switch (op) {
                case 's': result = sin(numbers[0]); break;
                case 'c': result = cos(numbers[0]); break;
                case 't': result = tan(numbers[0]); break;
                case 'l':
                    if (numbers[0] > 0)
                        result = log(numbers[0]);
                    else {
                        printf("Hata! Logaritma negatif veya 0 olamaz.\n");
                        continue;
                    }
                    break;
                case '^':
                    printf("Us degerini girin: ");
                    if (scanf("%lf", &numbers[1]) != 1) {
                        printf("Gecersiz sayi girisi!\n");
                        clearInputBuffer();
                        continue;
                    }
                    result = pow(numbers[0], numbers[1]);
                    break;
            }
        } else {
            printf("Kac sayi gireceksiniz? ");
            if (scanf("%d", &count) != 1 || count < 2 || count > MAX_NUMBERS) {
                printf("Gecersiz sayi adedi! (En az 2, en fazla %d sayi girilebilir.)\n", MAX_NUMBERS);
                clearInputBuffer();
                continue;
            }

            printf("%d sayiyi girin: ", count);
            for (int i = 0; i < count; i++) {
                if (scanf("%lf", &numbers[i]) != 1) {
                    printf("Gecersiz sayi girisi!\n");
                    clearInputBuffer();
                    continue;
                }
            }

            result = numbers[0];
            for (int i = 1; i < count; i++) {
                switch (op) {
                    case '+': result += numbers[i]; break;
                    case '-': result -= numbers[i]; break;
                    case '*': result *= numbers[i]; break;
                    case '/':
                        if (numbers[i] != 0)
                            result /= numbers[i];
                        else {
                            printf("Hata! Sifira bolme tanimsizdir.\n");
                            result = NAN;
                            break;
                        }
                        break;
                    default:
                        printf("Gecersiz islem!\n");
                        continue;
                }
            }
        }

        printf("Sonuc: %.2lf\n", result);
        fprintf(file, "Islem: %c, Sonuc: %.2lf\n", op, result);
    }

    fclose(file);
    return 0;
}

