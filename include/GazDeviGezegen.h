#ifndef GAZ_DEVI_GEZEGEN_H
#define GAZ_DEVI_GEZEGEN_H

#include "Gezegen.h"

typedef struct
{
    Gezegen gezegen;
} GazDeviGezegen;

GazDeviGezegen *gazDeviGezegenOlustur(const char *gezegenAdi, int birGunSaati, Zaman gezegendekiTarih);
double gazDeviGezegenYaslanmaOrani(Gezegen *gezegen);
void GazDeviGezegenYokEt(GazDeviGezegen *gezegen);

#endif
