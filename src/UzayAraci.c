/**
 *
 *    Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr        1/A GRUBU
 *    02.05.2025
 *    UzayAraci.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UzayAraci.h"
#include "Zaman.h"
#include "Gezegen.h" // Gezegen struct'ı için

// Uzay aracını oluşturna ve başlangıç değerlerini atama:
void UzayAraciOlustur(UzayAraci *uzayAraci, const char *uzayAraciAdi, const char *cikisGezegeni, const char *varisGezegeni, const char *cikisTarihiStr, int saat_olarak_mesafe)
{
    // Temel bilgileri kopyalayıp atıyorum:
    uzayAraci->uzayAraciAdi = strdup(uzayAraciAdi);
    uzayAraci->cikisGezegeni = strdup(cikisGezegeni);
    uzayAraci->varisGezegeni = strdup(varisGezegeni);
    uzayAraci->durumu = strdup("Bekliyor");

    // İlk ayarlamalar:
    uzayAraci->kisiler = NULL;
    uzayAraci->gezegenCikis = NULL;
    uzayAraci->gezegenVaris = NULL;
    uzayAraci->hedefeKalanSaat = saat_olarak_mesafe;
    uzayAraci->yolcuSayisi = 0;
    uzayAraci->cikisGunSaat = 0;
    uzayAraci->varisGunSaat = 0;

    uzayAraci->cikisTarihi = zamanOlustur(0, 0, 0, 0);
    uzayAraci->hedefeVaracagiTarih = NULL;
}

// Uzay aracına yolcu ekleme
void yolcuEkle(UzayAraci *uzayAraci, Kisi *kisi)
{
    // Bellekte yolcu listesi yeniden boyutlandırılır(dinamik olarak)
    Kisi **yeniKisiler = realloc(uzayAraci->kisiler, sizeof(Kisi *) * (uzayAraci->yolcuSayisi + 1));

    uzayAraci->kisiler = yeniKisiler;
    uzayAraci->kisiler[uzayAraci->yolcuSayisi] = kisi;
    uzayAraci->yolcuSayisi++;
}

// Yolcuların hepsi ölmüş mü kontrol ederiz:
void yolculariKontrolEt(UzayAraci *uzayAraci)
{
    int herkesOlmus = 1;
    for (int i = 0; i < uzayAraci->yolcuSayisi; i++)
    {
        if (uzayAraci->kisiler[i]->yasiyor)
        {
            herkesOlmus = 0;
            return;
        }
    }
    if (herkesOlmus)
    {
        free(uzayAraci->durumu);
        uzayAraci->durumu = strdup("İMHA");
    }
}

// Ölü yolcular listeden çıkarılır:
void yolcuSayisiniGuncelle(UzayAraci *uzayAraci)
{
    int yeniIndex = 0;
    for (int i = 0; i < uzayAraci->yolcuSayisi; i++)
    {
        if (uzayAraci->kisiler[i]->yasiyor)
        {
            uzayAraci->kisiler[yeniIndex++] = uzayAraci->kisiler[i];
        }
    }
    uzayAraci->yolcuSayisi = yeniIndex;
    Kisi **yeniKisiler = realloc(uzayAraci->kisiler, sizeof(Kisi *) * yeniIndex);
    if (yeniKisiler != NULL || yeniIndex == 0)
    {
        uzayAraci->kisiler = yeniKisiler;
    }
}
// Uzay aracının varış tarihi hesaplama işlemi:
void varisTarihiHesapEt(UzayAraci *uzayAraci)
{
    if (!uzayAraci || !uzayAraci->gezegenCikis || !uzayAraci->gezegenVaris || !uzayAraci->cikisTarihi || !uzayAraci->hedefeVaracagiTarih)
    {
        return;
    }

    // Gerekli zaman bilgileri alınır:
    Zaman gezegenTarihiCikis = uzayAraci->gezegenCikis->gezegendekiTarih;
    Zaman gezegenTarihiVaris = uzayAraci->gezegenVaris->gezegendekiTarih;
    Zaman cikisTarihi = uzayAraci->cikisTarihi;

    int gunUzunluguSaatVaris = uzayAraci->gezegenVaris->birGunSaati;
    int gunUzunluguSaatCikis = uzayAraci->gezegenCikis->birGunSaati;

    // Bekleme süresi (gezegende) saat cinsinden hesaplanır:
    int farkGun = zamanFarkiGun(gezegenTarihiCikis, cikisTarihi);
    int beklemeSaat = farkGun * gunUzunluguSaatCikis;

    // Toplam yolculuk saati:
    int toplamSaat = beklemeSaat + uzayAraci->hedefeKalanSaat;
    int varisGun = toplamSaat / gunUzunluguSaatVaris;
    int varisSaat = toplamSaat % gunUzunluguSaatVaris;

    // Varış tarihi hesaplanır:
    Zaman kopya = zamanOlustur(gezegenTarihiVaris->gun, gezegenTarihiVaris->ay, gezegenTarihiVaris->yil, varisSaat);
    zamanEkle(kopya, varisGun);

    uzayAraci->hedefeVaracagiTarih = kopya;
}

// Uzay aracının durumu güncellemek:
void guncelleDurum(UzayAraci *uzayAraci, Gezegen *cikisGezegeniPtr, int gezegenSayisi)
{
    yolculariKontrolEt(uzayAraci);
    if (uzayAraci->durumu != NULL &&
        (strcmp(uzayAraci->durumu, "İMHA") == 0 || strcmp(uzayAraci->durumu, "Vardı") == 0))
    {
        return;
    }
    // Çıkış tarihine ulaşıldıysa durum "Yolda" olarak değiştirilir
    if (cikisGezegeniPtr != NULL)
    {
        char gezegenTarihiStr[20];
        struct tm tmTarih = zamanToTm(cikisGezegeniPtr->gezegendekiTarih);
        strftime(gezegenTarihiStr, sizeof(gezegenTarihiStr), "%d.%m.%Y", &tmTarih);

        char cikisTarihiStr[20];
        struct tm tmCikis = zamanToTm(uzayAraci->cikisTarihi);
        strftime(cikisTarihiStr, sizeof(cikisTarihiStr), "%d.%m.%Y", &tmCikis);

        if (strcmp(gezegenTarihiStr, cikisTarihiStr) == 0)
        {
            free(uzayAraci->durumu);
            uzayAraci->durumu = strdup("Yolda");
        }
    }
}

// Bilgileri yazdırma işlemi (istenilen formatta):
void uzayAraciYazdir(UzayAraci *uzayAraci)
{
    if (!uzayAraci || !uzayAraci->uzayAraciAdi)
    {
        return;
    }
    printf("%-20s", uzayAraci->uzayAraciAdi);
    printf("%-11s", uzayAraci->durumu ? uzayAraci->durumu : "Bilinmiyor");
    printf("%-9s", uzayAraci->cikisGezegeni ? uzayAraci->cikisGezegeni : "Bilinmiyor");
    printf("%-13s", uzayAraci->varisGezegeni ? uzayAraci->varisGezegeni : "Bilinmiyor");

    if (uzayAraci->durumu && strcmp(uzayAraci->durumu, "İMHA") == 0)
    {
        printf("%-24s", "--");
        printf("%-13s\n", " --");
    }
    else
    {
        printf("%-25d", uzayAraci->hedefeKalanSaat);
        if (uzayAraci->hedefeVaracagiTarih)
        {
            printf("%02d.%02d.%04d\n",
                   uzayAraci->hedefeVaracagiTarih->gun,
                   uzayAraci->hedefeVaracagiTarih->ay,
                   uzayAraci->hedefeVaracagiTarih->yil);
        }
    }
}

void yazdirUzayAraclari(UzayAraci **uzayAraclari, int aracSayisi)
{
    printf("Uzay Araclari:\n");
    printf("%-17s%-12s%-10s%-11s%-25s%-15s\n",
           "Araç Adı", "     Durum", "   Çıkış", "    Varış", "        Hedefe Kalan Saat", "        Hedefe Varacağı Tarih");
    for (int i = 0; i < aracSayisi; i++)
    {
        if (uzayAraclari[i])
        {
            uzayAraciYazdir(uzayAraclari[i]);
        }
    }
}

// Uzay aracını serbest bırakma işlemi:
void UzayAraciSerbestBirak(UzayAraci *uzayAraci)
{
    if (uzayAraci != NULL)
    {
        free(uzayAraci->uzayAraciAdi);
        free(uzayAraci->cikisGezegeni);
        free(uzayAraci->varisGezegeni);
        free(uzayAraci->durumu);
        if (uzayAraci->cikisTarihi != NULL)
        {
            zamanYokEt(uzayAraci->cikisTarihi);
        }
        if (uzayAraci->kisiler != NULL)
        {
            for (int i = 0; i < uzayAraci->yolcuSayisi; i++)
            {
                if (uzayAraci->kisiler[i] != NULL)
                {
                    kisiYokEt(uzayAraci->kisiler[i]);
                }
            }
            free(uzayAraci->kisiler);
        }

        if (uzayAraci->hedefeVaracagiTarih != NULL)
        {
            zamanYokEt(uzayAraci->hedefeVaracagiTarih);
        }
        free(uzayAraci);
    }
}