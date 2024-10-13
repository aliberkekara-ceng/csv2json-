#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {

    char ch, dizi[255] = {0}; // ch karakter okumak için, dizi ise virgüle kadar okuma sağlıyor
    int i = 0; // dizi için index değişkeni
    char *csvHeader[10]; // header-on için headerları tutan char pointer arrayi
    int k = 0;  // headerların ismi için index değişkeni
    int yeniObjeEklenmeKontrol = 0; // her obje başladığında { kullanımı için kontrol değişkeni
    int headerOFFDurumu = 0; // header durumu kotrol
    int isint = 1; // integer durumu kontrol

    FILE *fp = fopen(argv[1], "r");
    FILE *son = fopen(argv[2], "w");


    if (strcmp(argv[3], "header=ON") == 0) {
        while ((ch = getc(fp)) != '\n') {  //header taglerini okuma
            if (ch != ',' && ch != '"') {
                dizi[i++] = ch;
            } else if (ch == ',') {
                dizi[i++] = '\0';
                csvHeader[k] = (char *) malloc(i * sizeof(char));
                memcpy(csvHeader[k++], dizi, i);
                i = 0;
            }
        }

        if (ch == '\n') {
            dizi[i++] = '\0';
            csvHeader[k] = (char *) malloc(i * sizeof(char));
            memcpy(csvHeader[k], dizi, i);
            i = 0;
            k = 0;
        }
    } else
        headerOFFDurumu = 1;

    fprintf(son, "{\n");
    while ((ch = getc(fp)) != EOF) {
        if (yeniObjeEklenmeKontrol == 0) {
            fprintf(son, "\t{\n");
            yeniObjeEklenmeKontrol = 1;
        }
        if (ch != ',' && ch != '\n' && ch != '"') {
            if (!isdigit(ch) && !isspace(ch)) // rm
                isint = 0;        // rm
            dizi[i++] = ch;
        } else if (ch == ',') {
            if (headerOFFDurumu == 1) {   //header off ise oluştrulacak kolon işlemleri
                char kolonSayi[35] = {0};
                snprintf(kolonSayi, 35, "kolon%d", (k + 1));
                csvHeader[k] = (char *) malloc(strlen(kolonSayi) * sizeof(char));
                strcpy(csvHeader[k], kolonSayi);
            }
            dizi[i] = '\0';
            i = 0;
            if (isint == 0)            // okunan değerler yazdırılmaya başlıyor
                fprintf(son, "\t\t\"%s\":\"%s\",\n", csvHeader[k++], dizi);
            else
                fprintf(son, "\t\t\"%s\":%s,\n", csvHeader[k++], dizi);
            isint = 1;
        } else if (ch == '\n') {
            if (headerOFFDurumu == 1) {
                char kolonSayi[35] = {0};
                snprintf(kolonSayi, 35, "kolon%d", (k + 1));
                csvHeader[k] = (char *) malloc(strlen(kolonSayi) * sizeof(char));
                strcpy(csvHeader[k], kolonSayi);
            }
            dizi[i] = '\0';
            i = 0;
            if (isint == 0)
                fprintf(son, "\t\t\"%s\":\"%s\",\n", csvHeader[k++], dizi);
            else
                fprintf(son, "\t\t\"%s\":%s,\n", csvHeader[k++], dizi);
            isint = 1;
            k = 0;
            yeniObjeEklenmeKontrol = 0;
        }
    }
    dizi[i] = '\0';
    fprintf(son, "\t\t\"%s\":\"%s\"\n\t}\n", csvHeader[k], dizi);  // csv dosyasının son argümanı yazılıyor
    fprintf(son, "}");

    fclose(son);
    fclose(fp);
    return 0;
}
