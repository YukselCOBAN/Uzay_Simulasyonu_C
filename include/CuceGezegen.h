#ifndef CUCE_GEZEGEN_H
#define CUCE_GEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen gezegen;
} CuceGezegen;

CuceGezegen* cuceGezegenOlustur(const char* gezegenAdi, int birGunSaati, Zaman gezegendekiTarih);
double cuceGezegenYaslanmaOrani(Gezegen* gezegen);
void CuceGezegenYokEt(CuceGezegen* gezegen);


#endif
