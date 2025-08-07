#ifndef UZAYARACI_H
#define UZAYARACI_H

#include "Zaman.h"
#include "Gezegen.h"
#include "Kisi.h"

typedef struct UzayAraci
{
    char *uzayAraciAdi;
    char *cikisGezegeni;
    char *varisGezegeni;
    Zaman cikisTarihi;
    int hedefeKalanSaat;
    char *durumu;
    int yolcuSayisi;
    Kisi **kisiler;
    Gezegen *gezegenCikis;
    Gezegen *gezegenVaris;
    Zaman hedefeVaracagiTarih;
    int saatOlarakMesafe;
    int cikisGunSaat;
    int varisGunSaat;
} UzayAraci;

// Fonksiyon prototipleri
void UzayAraciOlustur(UzayAraci *uzayAraci, const char *uzayAraciAdi, const char *cikisGezegeni, const char *varisGezegeni, const char *cikisTarihiStr, int saat_olarak_mesafe);
void yolcuEkle(UzayAraci *uzayAraci, Kisi *kisi);
void yolculariKontrolEt(UzayAraci *uzayAraci);
void yolcuSayisiniGuncelle(UzayAraci *uzayAraci);
void varisTarihiHesapEt(UzayAraci *uzayAraci);
void guncelleDurum(UzayAraci *uzayAraci, Gezegen *cikisGezegeniPtr, int gezegenSayisi);
void uzayAraciYazdir(UzayAraci *uzayAraci);
void yazdirUzayAraclari(UzayAraci **uzayAraclari, int aracSayisi);
void UzayAraciSerbestBirak(UzayAraci *uzayAraci);

#endif
