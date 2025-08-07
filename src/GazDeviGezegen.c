/**
 *
 *     Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr         1/A GRUBU
 *     08.05.2025
 *     GazDeviGezegen.c
 */
#include "GazDeviGezegen.h"
#include <stdlib.h>
#include <string.h>

GazDeviGezegen* gazDeviGezegenOlustur(const char* gezegenAdi, int birGunSaati, Zaman gezegendekiTarih)
{
    GazDeviGezegen* gazDeviGezegen = (GazDeviGezegen*)malloc(sizeof(GazDeviGezegen));
    if (!gazDeviGezegen) return NULL;

    gazDeviGezegen->gezegen.gezegenAdi = strdup(gezegenAdi);
    gazDeviGezegen->gezegen.birGunSaati = birGunSaati;
    gazDeviGezegen->gezegen.gezegendekiTarih = gezegendekiTarih;
    gazDeviGezegen->gezegen.gezegendekiSaat = 0;
    gazDeviGezegen->gezegen.nufus = 0;
    gazDeviGezegen->gezegen.gezegenTuru = GAZ_DEVI_GEZEGEN;
    gazDeviGezegen->gezegen.yaslanmaOrani = gazDeviGezegenYaslanmaOrani;

    return gazDeviGezegen;
}

double gazDeviGezegenYaslanmaOrani(Gezegen* gezegen)
{
    return 0.1;
}

void GazDeviGezegenYokEt(GazDeviGezegen* gezegen)
{
    if (gezegen == NULL)
        return;

    if (gezegen->gezegen.gezegenAdi != NULL)
        free(gezegen->gezegen.gezegenAdi);

    if (gezegen->gezegen.gezegendekiTarih != NULL)
        zamanYokEt(gezegen->gezegen.gezegendekiTarih);

    free(gezegen);
}
