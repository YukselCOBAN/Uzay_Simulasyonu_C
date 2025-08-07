#ifndef KAYAC_GEZEGEN_H
#define KAYAC_GEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen gezegen;
} KayacGezegen;

KayacGezegen* kayacGezegenOlustur(const char* gezegenAdi, int birGunSaati, Zaman gezegendekiTarih);
double kayacGezegenYaslanmaOrani(Gezegen* gezegen);
void KayacGezegenYokEt(KayacGezegen* gezegen);


#endif
