#ifndef GEZEGEN_H
#define GEZEGEN_H

#include "Zaman.h"
#include "Kisi.h"

typedef enum
{
    BUZ_DEVI_GEZEGEN = 0,
    GAZ_DEVI_GEZEGEN,
    KAYAC_GEZEGEN,
    CUCE_GEZEGEN
} GezegenTuru;

typedef struct Gezegen
{
    char *gezegenAdi;
    int birGunSaati;
    Zaman gezegendekiTarih;
    int nufus;
    int gezegendekiSaat;
    GezegenTuru gezegenTuru;
    double (*yaslanmaOrani)(struct Gezegen *gezegen);
} Gezegen;

// Fonksiyon prototipleri
Gezegen *gezegenOlustur(const char *adi, Zaman gezegendekiTarih);
Gezegen *altGezegenOlustur(char *isim, int tur, Zaman zaman, int gunSaati);
double yaslanmaOrani(Gezegen *gezegen);
int gezegenSaatUygunMu(Gezegen *gezegen, Zaman cikisTarihi);
void gezegenSetAd(Gezegen *gezegen, const char *ad);
void gezegenSetBirGunSaati(Gezegen *gezegen, int gezegendekiBirGunSaati);
void gezegenSetGezegendekiTarih(Gezegen *gezegen, int gun, int ay, int yil);
void gezegenSaatGecir(Gezegen *gezegen);
void gezegenNufuslariniGuncelle(Gezegen **gezegenler, int gezegenSayisi, Kisi **kisiler, int kisiSayisi);
void yazdirGezegenBilgileri(Gezegen **gezegenler, int gezegenSayisi);
void gezegenYokEt(Gezegen *gezegen);
int gezegenGetTur(Gezegen *g);

#endif
