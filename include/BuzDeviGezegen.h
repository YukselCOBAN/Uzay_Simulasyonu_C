#ifndef BUZDEVIGEZEGEN_H
#define BUZDEVIGEZEGEN_H

#include "Gezegen.h"
#include "Zaman.h"

// BuzDeviGezegen, içinde bir Gezegen barındıran özel bir türdür
typedef struct
{
    Gezegen gezegen;
} BuzDeviGezegen;

// Gezegen * döndürmesi polymorphism için idealdir
BuzDeviGezegen *buzDeviGezegenOlustur(const char *gezegenAdi, int birGunSaati, Zaman gezegendekiTarih);

// Bu özel yaşlanma oranı fonksiyonu
double buzDeviGezegenYaslanmaOrani(Gezegen *gezegen);

void BuzDeviGezegenYokEt(BuzDeviGezegen *gezegen);

#endif
