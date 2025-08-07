#ifndef KISI_H
#define KISI_H

#include <stdbool.h>

typedef struct UzayAraci UzayAraci;
typedef struct Gezegen Gezegen;

typedef struct Kisi
{
    char *isim;                  
    int yas;                    
    double kalanOmur;               
    char *bulunduguUzayAraciAdi;
    int yasiyor;               
    UzayAraci *bulunanUzayAraci; 
} Kisi;

// Fonksiyon prototipleri
static char *stringKopyala(const char *kaynak);
Kisi *kisiOlustur(const char *isim, int yas, double kalanOmur, const char *uzayAraciAdi, UzayAraci *uzayAraci);
void kisiSaatGecir(Kisi *kisi, Gezegen *gez);
void kisiYokEt(Kisi *kisi);


#endif 
