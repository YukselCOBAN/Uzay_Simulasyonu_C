/**
 *
 *     Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr       1/A GRUBU
 *     06.05.2025
 *     Gezegen.c
 */
#include <stddef.h>
#include <stdlib.h> // malloc, free
#include <string.h> // strcpy, strlen, strcmp
#include <stdio.h>
#include <time.h>

#include "BuzDeviGezegen.h"
#include "GazDeviGezegen.h"
#include "KayacGezegen.h"
#include "CuceGezegen.h"
#include "Gezegen.h"
#include "Zaman.h"
#include "UzayAraci.h"

// Yeni bir gezegen oluşturma ve başlangıç tarihini ayarlama:
Gezegen *gezegenOlustur(const char *adi, Zaman gezegendekiTarih)
{
    // Bellekten yeni bir Gezegen struct'ı için yer ayırma işlemi:
    Gezegen *yeniGezegen = (Gezegen *)malloc(sizeof(Gezegen));
    if (yeniGezegen == NULL)
    {
        perror("Hafıza tahsisi başarısız");
        return NULL;
    }
    yeniGezegen->gezegenAdi = strdup(adi);
    // ad kopyalama başarısızsa, ayrılan belleği serbest bırakır:
    if (adi != NULL && yeniGezegen->gezegenAdi == NULL)
    {
        free(yeniGezegen);
        return NULL;
    }
    // Gezegen tarihini zamanOlustur fonksiyonuyla oluşturdum:
    yeniGezegen->gezegendekiTarih = zamanOlustur(gezegendekiTarih->gun, gezegendekiTarih->ay, gezegendekiTarih->yil, 0); // Başlangıç saati 0
    // Eğer zaman oluşturma başarısızsa, öncekileri temizle ve NULL döner
    if (gezegendekiTarih != NULL && yeniGezegen->gezegendekiTarih == NULL)
    {
        free(yeniGezegen->gezegenAdi);
        free(yeniGezegen);
        return NULL;
    }
    yeniGezegen->birGunSaati = 0;
    yeniGezegen->nufus = 0;
    yeniGezegen->gezegendekiSaat = 0;
    yeniGezegen->gezegenTuru = KAYAC_GEZEGEN;
    yeniGezegen->yaslanmaOrani = yaslanmaOrani;
    return yeniGezegen;
}

int gezegenGetTur(Gezegen *g)
{
    if (g == NULL)
        return -1;
    return g->gezegenTuru;
}

Gezegen *altGezegenOlustur(char *isim, int tur, Zaman zaman, int gunSaati)
{
    Gezegen *g = NULL;

    switch (tur)
    {
    case 0:
        g = (Gezegen *)kayacGezegenOlustur(isim, gunSaati, zaman);
        break;
    case 1:
        g = (Gezegen *)gazDeviGezegenOlustur(isim, gunSaati, zaman);
        break;
    case 2:
        g = (Gezegen *)buzDeviGezegenOlustur(isim, gunSaati, zaman);
        break;
    case 3:
        g = (Gezegen *)cuceGezegenOlustur(isim, gunSaati, zaman);
        break;
    default:
        return NULL;
    }

    if (g != NULL)
        gezegenSetBirGunSaati(g, gunSaati);

    return g;
}

// Gezegen türüne göre yaşlanma oranını belirler
double yaslanmaOrani(Gezegen *gezegen)
{
    printf("gezegen - yaslanmaOrani çalıştı (Hatalı)\n");
    double oran = 1.0;

    switch (gezegen->gezegenTuru)
    {
    case BUZ_DEVI_GEZEGEN:
        oran = 0.5; // Buz Devi gezegenlerinde yaşlanma
        break;
    case CUCE_GEZEGEN:
        oran = 0.01; // Cüce gezegenlerde yaşlanma
        break;
    case GAZ_DEVI_GEZEGEN:
        oran = 0.1; // Gaz devi gezegenlerde yaşlanma
        break;
    case KAYAC_GEZEGEN:
        oran = 1.0; // Kayaç gezegenlerde normal yaşlanma
        break;
    }

    return oran;
}

// Gezegenin tarihinin, verilen çıkış tarihi ile aynı gün olup olmadığını kontrol eder
int gezegenSaatUygunMu(Gezegen *gezegen, Zaman cikisTarihi)
{
    if (gezegen->gezegendekiTarih->yil == cikisTarihi->yil &&
        gezegen->gezegendekiTarih->ay == cikisTarihi->ay &&
        gezegen->gezegendekiTarih->gun == cikisTarihi->gun)
    {
        return 1; // Aynı gün ise uygun
    }
    return 0; // Aynı gün değilse uygun değil
}

// Gezegen adını değiştirir ve önceki adı bellekten temizler:
void gezegenSetAd(Gezegen *gezegen, const char *ad)
{
    if (gezegen == NULL)
        return;
    if (gezegen->gezegenAdi != NULL)
    {
        free(gezegen->gezegenAdi);
    }
    gezegen->gezegenAdi = strdup(ad);
}

// Gezegenin bir gününün kaç saat olduğunu ayarlar
void gezegenSetBirGunSaati(Gezegen *gezegen, int gezegendekiBirGunSaati)
{
    gezegen->birGunSaati = gezegendekiBirGunSaati;
}

// Gezegenin tarih bilgisini günceller
void gezegenSetGezegendekiTarih(Gezegen *gezegen, int gun, int ay, int yil)
{
    // Tarihin gün, ay, yıl değerlerini ayarlar
    gezegen->gezegendekiTarih->gun = gun;
    gezegen->gezegendekiTarih->ay = ay;
    gezegen->gezegendekiTarih->yil = yil;
}

// Gezegenin saat bilgisini bir artırır; gün sonunda tarihi bir gün ileri taşır
void gezegenSaatGecir(Gezegen *gezegen)
{
    gezegen->gezegendekiSaat++;
    if (gezegen->gezegendekiSaat >= gezegen->birGunSaati)
    {
        gezegen->gezegendekiSaat = 0;
        if (gezegen->gezegendekiTarih != NULL)
        {
            // Tarihe 1 gün ekle
            zamanArtir(gezegen->gezegendekiTarih);
        
        }
    }
}

// Tüm gezegenlerin nüfusunu sıfırlar, sonra kişiler üzerinden nüfusları günceller:
void gezegenNufuslariniGuncelle(Gezegen **gezegenler, int gezegenSayisi, Kisi **kisiler, int kisiSayisi)
{
    // Tüm gezegenlerin nüfusunu sıfırla
    for (int i = 0; i < gezegenSayisi; i++)
    {
        gezegenler[i]->nufus = 0;
    }

    for (int i = 0; i < kisiSayisi; i++)
    {
        Kisi *kisi = kisiler[i];

        // Kişi yaşıyor ve bulunduğu uzay aracı imha edilmemiş olmalı
        if (kisi->kalanOmur > 0 && kisi->bulunanUzayAraci != NULL &&
            strcmp(kisi->bulunanUzayAraci->durumu, "İMHA") != 0)
        {
            UzayAraci *arac = kisi->bulunanUzayAraci;

            // Bulunduğu gezegenin adı duruma göre belirlenir
            char *bulunduguGezegenAdi = NULL;

            if (strcmp(arac->durumu, "Vardı") == 0)
            {
                bulunduguGezegenAdi = arac->varisGezegeni;
            }
            else if (strcmp(arac->durumu, "Bekliyor") == 0)
            {
                bulunduguGezegenAdi = arac->cikisGezegeni;
            }

            if (bulunduguGezegenAdi != NULL)
            {
                for (int j = 0; j < gezegenSayisi; j++)
                {
                    if (strcmp(gezegenler[j]->gezegenAdi, bulunduguGezegenAdi) == 0)
                    {
                        gezegenler[j]->nufus++;
                        break;
                    }
                }
            }
        }
    }
}

void yazdirGezegenBilgileri(Gezegen **gezegenler, int gezegenSayisi)
{
    printf("Gezegenler:\n\t");
    for (int i = 0; i < gezegenSayisi; i++)
    {
        printf("-- %-4s --\t", gezegenler[i]->gezegenAdi);
    }
    printf("\n");

    // Tarih başlığı yazdır
    printf("Tarih:\t");
    for (int i = 0; i < gezegenSayisi; i++)
    {
        Zaman zaman = gezegenler[i]->gezegendekiTarih;

        // Tarih değerlerinin sıfır olup olmadığını kontrol et
        if (zaman->gun == 0 || zaman->ay == 0 || zaman->yil == 0)
        {
            perror("Geçersiz Tarih!");
        }
        else
        {
            // Ay'ı 2 basamaklı hale getir
            char ayStr[3];
            if (zaman->ay < 10)
                sprintf(ayStr, "0%d", zaman->ay); // Ay başına 0 ekle
            else
                sprintf(ayStr, "%d", zaman->ay);

            // Gün başına 0 EKLEME
            printf("%d.%s.%04d\t", zaman->gun, ayStr, zaman->yil);
        }
    }
    printf("\n");

    printf("Nüfus:\t");
    for (int i = 0; i < gezegenSayisi; i++)
    {
        printf("   %-10d\t", gezegenler[i]->nufus);
    }
    printf("\n");
}

// Gezegen bellekten temizlenir
void gezegenYokEt(Gezegen *gezegen)
{
    if (gezegen == NULL)
        return;

    switch (gezegen->gezegenTuru)
    {
    case GAZ_DEVI_GEZEGEN:
        GazDeviGezegenYokEt((GazDeviGezegen *)gezegen);
        break;
    case BUZ_DEVI_GEZEGEN:
        BuzDeviGezegenYokEt((BuzDeviGezegen *)gezegen);
        break;
    case KAYAC_GEZEGEN:
        KayacGezegenYokEt((KayacGezegen *)gezegen);
        break;
    case CUCE_GEZEGEN:
        CuceGezegenYokEt((CuceGezegen *)gezegen);
        break;
    default:
        // Bilinmeyen tür varsa, özel işlem yok
        break;
    }

    free(gezegen);
}
