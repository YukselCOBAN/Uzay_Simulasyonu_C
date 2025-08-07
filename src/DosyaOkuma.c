/**
 *
 *     Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr        1/A GRUBU
 *     01.05.2025
 *     DosyaOkuma.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GlobalDegiskenler.h"
#include "Gezegen.h"
#include "UzayAraci.h"
#include "Kisi.h"
#include "DosyaOkuma.h"
#include "Zaman.h"

UzayAraci **araclarDosyasiniOku(int *araclarSayisi)
{
    FILE *file = fopen("Araclar.txt", "r");
    if (!file)
    {
        perror("Araclar.txt dosyası açılamadı");
        return NULL;
    }
    *araclarSayisi = 0;
    UzayAraci **liste = NULL;
    char line[MAX_LINE_LENGTH];
    int satirSayaci = 0;
    int kapasite = 0;
    int boyut = sizeof(UzayAraci *);

    while (fgets(line, sizeof(line), file))
    {
        satirSayaci++;
        line[strcspn(line, "\n")] = '\0';

        char aracAdiTemp[64];
        char cikisGezegeniTemp[16];
        char varisGezegeniTemp[16];
        char cikisTarihiStr[20];
        int mesafe = 0;
        int gun = 0, ay = 0, yil = 0;

        int okunanAlanSayisi = sscanf(line, "%[^#]#%[^#]#%[^#]#%[^#]#%d", aracAdiTemp, cikisGezegeniTemp, varisGezegeniTemp, cikisTarihiStr, &mesafe);

        if (okunanAlanSayisi == 5)
        {
            int tarihOkundu = sscanf(cikisTarihiStr, "%d.%d.%d", &gun, &ay, &yil);
            if (tarihOkundu != 3)
            {
                tarihOkundu = sscanf(cikisTarihiStr, "%02d.%02d.%d", &gun, &ay, &yil);
                if (tarihOkundu != 3)
                {
                    fclose(file);
                    for (int i = 0; i < *araclarSayisi; i++)
                        free(liste[i]);
                    free(liste);
                    return NULL;
                }
            }
            Zaman cikisTarihi = zamanOlustur(gun, ay, yil, 0);
            if (!cikisTarihi)
            {

                fclose(file);

                for (int i = 0; i < *araclarSayisi; i++)
                    UzayAraciSerbestBirak(liste[i]);
                free(liste);
                return NULL;
            }

            UzayAraci *arac = malloc(sizeof(UzayAraci));
            if (!arac)
            {
                zamanYokEt(cikisTarihi);
                fclose(file);
                for (int i = 0; i < *araclarSayisi; i++)
                    free(liste);
                return NULL;
            }
            memset(arac, 0, sizeof(UzayAraci));
            arac->uzayAraciAdi = strdup(aracAdiTemp);
            arac->cikisGezegeni = strdup(cikisGezegeniTemp);
            arac->varisGezegeni = strdup(varisGezegeniTemp);
            arac->durumu = strdup("Bekliyor");
            arac->cikisTarihi = cikisTarihi;
            arac->hedefeKalanSaat = mesafe;
            arac->yolcuSayisi = 0;
            arac->kisiler = NULL;
            arac->gezegenCikis = NULL;
            arac->gezegenVaris = NULL;
            arac->hedefeVaracagiTarih = (Zaman)malloc(sizeof(Zaman));
            if (!arac->hedefeVaracagiTarih)
            {
                zamanYokEt(cikisTarihi);
                free(arac->uzayAraciAdi);
                free(arac->cikisGezegeni);
                free(arac->varisGezegeni);
                free(arac->durumu);
                free(arac);
                fclose(file);
                for (int i = 0; i < *araclarSayisi; i++)
                    free(liste[i]);
                free(liste);
                return NULL;
            }
            memset(arac->hedefeVaracagiTarih, 0, sizeof(Zaman));
            arac->saatOlarakMesafe = mesafe;
            arac->cikisGunSaat = 0;
            arac->varisGunSaat = 0;

            if (*araclarSayisi >= kapasite)
            {
                kapasite += 5;
                UzayAraci **temp = realloc(liste, kapasite * boyut);
                if (!temp)
                {
                    zamanYokEt(cikisTarihi);
                    free(arac->uzayAraciAdi);
                    free(arac->cikisGezegeni);
                    free(arac->varisGezegeni);
                    free(arac->durumu);
                    free(arac);
                    fclose(file);
                    for (int i = 0; i < *araclarSayisi; i++)
                        free(liste[i]);
                    free(liste);

                    return NULL;
                }
                liste = temp;
            }

            liste[*araclarSayisi] = arac;
            (*araclarSayisi)++;
        }
    }
    fclose(file);
    return liste;
}

Gezegen **gezegenlerDosyasiniOku(int *gezegenlerSayisi)
{
    FILE *file = fopen("Gezegenler.txt", "r");
    if (!file)
        return NULL;

    *gezegenlerSayisi = 0;
    Gezegen **liste = NULL;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        char gezegenAdi[32];
        int tur, gunSaati, gun, ay, yil;

        if (sscanf(line, "%[^#]#%d#%d#%d.%d.%d", gezegenAdi, &tur, &gunSaati, &gun, &ay, &yil) == 6)
        {
            Zaman zaman = zamanOlustur(gun, ay, yil, 0);
            if (!zaman)
                continue;

            Gezegen *g = altGezegenOlustur(gezegenAdi, tur, zaman, gunSaati);
            if (!g)
                continue;

            Gezegen **temp = realloc(liste, sizeof(Gezegen *) * (*gezegenlerSayisi + 1));
            if (!temp)
                continue;

            liste = temp;
            liste[*gezegenlerSayisi] = g;
            (*gezegenlerSayisi)++;
        }
    }

    fclose(file);
    return liste;
}

Kisi **kisilerDosyasiniOku(int *kisilerSayisi, UzayAraci **araclarListesi, int araclarSayisi)
{
    FILE *file = fopen("Kisiler.txt", "r");
    if (!file)
    {
        perror("Kisiler.txt dosyası açılamadı");
        return NULL;
    }

    *kisilerSayisi = 0;
    Kisi **liste = NULL;
    char line[MAX_LINE_LENGTH];
    int satirNumarasi = 0;

    while (fgets(line, sizeof(line), file))
    {
        satirNumarasi++;

        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, "#");
        if (!token)
            continue;
        char isim[32];
        strcpy(isim, token);

        token = strtok(NULL, "#");
        if (!token)
            continue;
        int yas = atoi(token);

        token = strtok(NULL, "#");
        if (!token)
            continue;
        double kalanOmur = strtod(token, NULL);

        token = strtok(NULL, "#");
        if (!token)
            continue;
        char aracAdi[32];
        strcpy(aracAdi, token);

        UzayAraci *uzayAraci = NULL;
        for (int i = 0; i < araclarSayisi; i++)
        {
            if (strcmp(araclarListesi[i]->uzayAraciAdi, aracAdi) == 0)
            {
                uzayAraci = araclarListesi[i];
                break;
            }
        }

        Kisi *kisi = kisiOlustur(isim, yas, kalanOmur, aracAdi, uzayAraci);
        if (!kisi)
        {
            fclose(file);
            return NULL;
        }

        (*kisilerSayisi)++;
        Kisi **temp = realloc(liste, (*kisilerSayisi) * sizeof(Kisi *));
        if (!temp)
        {
            free(kisi);
            fclose(file);
            return NULL;
        }
        liste = temp;
        liste[*kisilerSayisi - 1] = kisi;
    }

    fclose(file);
    return liste;
}