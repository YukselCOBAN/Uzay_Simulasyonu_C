/**
 *
 *     Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr        1/A GRUBU
 *     08.05.2025
 *     CuceGezegen.c
 */
#include "CuceGezegen.h"
#include <stdlib.h>
#include <string.h>

CuceGezegen* cuceGezegenOlustur(const char* gezegenAdi, int birGunSaati, Zaman gezegendekiTarih)
{
    CuceGezegen* cuceGezegen = (CuceGezegen*)malloc(sizeof(CuceGezegen));
    if (!cuceGezegen) return NULL;

    cuceGezegen->gezegen.gezegenAdi = strdup(gezegenAdi);
    cuceGezegen->gezegen.birGunSaati = birGunSaati;
    cuceGezegen->gezegen.gezegendekiTarih = gezegendekiTarih;
    cuceGezegen->gezegen.gezegendekiSaat = 0;
    cuceGezegen->gezegen.nufus = 0;
    cuceGezegen->gezegen.gezegenTuru = CUCE_GEZEGEN;
    cuceGezegen->gezegen.yaslanmaOrani = cuceGezegenYaslanmaOrani;

    return cuceGezegen;
}

double cuceGezegenYaslanmaOrani(Gezegen* gezegen)
{
    return 0.01;
}

void CuceGezegenYokEt(CuceGezegen* gezegen)
{
    if (gezegen == NULL)
        return;

    if (gezegen->gezegen.gezegenAdi != NULL)
        free(gezegen->gezegen.gezegenAdi);

    if (gezegen->gezegen.gezegendekiTarih != NULL)
        zamanYokEt(gezegen->gezegen.gezegendekiTarih);

    free(gezegen);
}
