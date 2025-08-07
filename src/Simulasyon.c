/**
 *
 *      Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr      1/A GRUBU
 *      30.04.2025
 *      Simulasyon.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "GlobalDegiskenler.h"
#include "Gezegen.h"
#include "UzayAraci.h"
#include "Kisi.h"
#include "DosyaOkuma.h"
#include "Zaman.h"

// Global değişkenler
extern Gezegen **gezegenler;
extern UzayAraci **uzayAraclari;
extern Kisi **kisiler;

extern int gezegenSayisi;
extern int uzayAracSayisi;
extern int kisiSayisi;

time_t donguSayisi = 0; // Simülasyonda geçen toplam saat için

// Gezegen adını alıp, ilgili gezegen nesnesini döndüren yardımcı fonksiyon:
Gezegen *gezegenBul(const char *ad)
{
    if (ad == NULL)
        return NULL;
    for (int i = 0; i < gezegenSayisi; i++)
    {
        if (gezegenler[i] && gezegenler[i]->gezegenAdi && strcmp(gezegenler[i]->gezegenAdi, ad) == 0)
        {
            return gezegenler[i];
        }
    }
    return NULL;
}

// Her saatlik döngüde yapılacak işlemleri yöneten fonksiyon:
void ilerletSaat()
{

    //  Gezegenlerin zamanını 1 saat ileri almak için:
    for (int i = 0; i < gezegenSayisi; i++)
    {
        if (gezegenler[i])
            gezegenSaatGecir(gezegenler[i]);
    }

    //  Uzay araçlarını kontrol eder:
    for (int i = 0; i < uzayAracSayisi; i++)
    {
        UzayAraci *uzayAraci = uzayAraclari[i];

        if (!uzayAraci)
            continue;
        if (uzayAraci->durumu && strcmp(uzayAraci->durumu, "İMHA") == 0)
            continue;

        if (uzayAraci->durumu && strcmp(uzayAraci->durumu, "Bekliyor") == 0)
        {
            Gezegen *cikisGezegen = gezegenBul(uzayAraci->cikisGezegeni);
            if (cikisGezegen && uzayAraci->cikisTarihi && gezegenSaatUygunMu(cikisGezegen, uzayAraci->cikisTarihi))
            {
                free(uzayAraci->durumu);
                uzayAraci->durumu = strdup("Yolda");
            }
        }

        else if (uzayAraci->durumu && strcmp(uzayAraci->durumu, "Yolda") == 0)
        {
            if (uzayAraci->hedefeKalanSaat > 0)
                uzayAraci->hedefeKalanSaat--;

            if (uzayAraci->hedefeKalanSaat == 0)
            {
                free(uzayAraci->durumu);
                uzayAraci->durumu = strdup("Vardı");
            }
        }

        //  Durum güncelle
        Gezegen *cikisGezegeniPtr = gezegenBul(uzayAraci->cikisGezegeni);
        if (cikisGezegeniPtr)
            guncelleDurum(uzayAraci, cikisGezegeniPtr, gezegenSayisi);

        // Yolcu durumu kontrol
        yolculariKontrolEt(uzayAraci);

        // Yolcuların yaşını ilerlet
        for (int j = 0; j < uzayAraci->yolcuSayisi; j++)
        {
            Gezegen *gez = NULL;
            if (!strcmp(uzayAraci->durumu, "Bekliyor"))
                gez = uzayAraci->gezegenCikis;
            else if (!strcmp(uzayAraci->durumu, "Vardı"))
                gez = uzayAraci->gezegenVaris;

            if (uzayAraci->kisiler[j])
                kisiSaatGecir(uzayAraci->kisiler[j], gez);
        }

        //  Yolcu sayısını güncelle
        yolcuSayisiniGuncelle(uzayAraci);
    }

    // Gezegen nüfuslarını güncelle
    gezegenNufuslariniGuncelle(gezegenler, gezegenSayisi, kisiler, kisiSayisi);
}

// Her döngüde konsol ekranını temizlemek için kullanılan fonksiyon
void ekranTemizle()
{
    fflush(stdout);
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    // UTF-8 karakter desteğini aktif etmek için (Windows için)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Dosyalardan gezegen, araç ve kişi bilgilerini okur:
    gezegenler = gezegenlerDosyasiniOku(&gezegenSayisi);
    uzayAraclari = araclarDosyasiniOku(&uzayAracSayisi);
    kisiler = kisilerDosyasiniOku(&kisiSayisi, uzayAraclari, uzayAracSayisi);

    // Kişileri ilgili uzay araçlarına yerleştirir:
    for (int i = 0; i < kisiSayisi; i++)
    {
        for (int j = 0; j < uzayAracSayisi; j++)
        {
            if (kisiler[i] && uzayAraclari[j] && strcmp(kisiler[i]->bulunduguUzayAraciAdi, uzayAraclari[j]->uzayAraciAdi) == 0)
            {
                yolcuEkle(uzayAraclari[j], kisiler[i]);
                break;
            }
        }
    }

    // Araçların çıkış ve varış gezegen işaretçilerini ayarlamak için:
    for (int i = 0; i < uzayAracSayisi; i++)
    {
        for (int j = 0; j < gezegenSayisi; j++)
        {
            if (strcmp(uzayAraclari[i]->cikisGezegeni, gezegenler[j]->gezegenAdi) == 0)
                uzayAraclari[i]->gezegenCikis = gezegenler[j];
            if (strcmp(uzayAraclari[i]->varisGezegeni, gezegenler[j]->gezegenAdi) == 0)
                uzayAraclari[i]->gezegenVaris = gezegenler[j];
        }
    }

    // Araçların varış tarihlerini hesaplar:
    for (int i = 0; i < uzayAracSayisi; i++)
    {
        if (uzayAraclari[i] && uzayAraclari[i]->gezegenCikis != NULL && uzayAraclari[i]->gezegenVaris != NULL)
        {
            varisTarihiHesapEt(uzayAraclari[i]);
        }
    }

    while (1)
    {
        ekranTemizle(); // Ekranı temizler
        ilerletSaat();  // Simülasyonu bir saat ilerletir ve gerekli dinamik ve statik işlemleri yapar her döngüde
        donguSayisi++;

        yazdirGezegenBilgileri(gezegenler, gezegenSayisi); // Bilgileri yazdırmak için:
        printf("\n");
        yazdirUzayAraclari(uzayAraclari, uzayAracSayisi);

        int tamamlandi = 1; // Simülasyonun tamamlanıp tamamlanmadığını kontrol etmek için
        for (int i = 0; i < uzayAracSayisi; i++)
        {
            if ((strcmp(uzayAraclari[i]->durumu, "Bekliyor") == 0) || (strcmp(uzayAraclari[i]->durumu, "Yolda")) == 0)
            {
                tamamlandi = 0;
                break;
            }
        }

        printf("Toplam Geçen Saat: %ld\n", donguSayisi);

        if (tamamlandi)
        {
            printf("SİMÜLASYON TAMAMLANDI\n");

            // Belleği serbest bırakırız:
            for (int i = 0; i < kisiSayisi; i++)
                kisiYokEt(kisiler[i]);
            for (int i = 0; i < gezegenSayisi; i++)
            {
                gezegenYokEt(gezegenler[i]);
            }
            for (int i = 0; i < uzayAracSayisi; i++)
                UzayAraciSerbestBirak(uzayAraclari[i]);

            free(kisiler);
            free(gezegenler);
            free(uzayAraclari);

            break;
        }
    }

    return 0;
}
