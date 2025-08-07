/**
 *
 *     Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr        1/A GRUBU
 *     08.05.2025
 *     KayacGezegen.c
 */
#include "KayacGezegen.h"
#include <stdlib.h>
#include <string.h>

KayacGezegen* kayacGezegenOlustur(const char* gezegenAdi, int birGunSaati, Zaman gezegendekiTarih)
{
    KayacGezegen* kayacGezegen = (KayacGezegen*)malloc(sizeof(KayacGezegen));
    if (!kayacGezegen) return NULL;

    kayacGezegen->gezegen.gezegenAdi = strdup(gezegenAdi);
    kayacGezegen->gezegen.birGunSaati = birGunSaati;
    kayacGezegen->gezegen.gezegendekiTarih = gezegendekiTarih;
    kayacGezegen->gezegen.gezegendekiSaat = 0;
    kayacGezegen->gezegen.nufus = 0;
    kayacGezegen->gezegen.gezegenTuru = KAYAC_GEZEGEN;
    kayacGezegen->gezegen.yaslanmaOrani = kayacGezegenYaslanmaOrani;

    return kayacGezegen;
}

double kayacGezegenYaslanmaOrani(Gezegen* gezegen)
{
    return 1.0;
}

void KayacGezegenYokEt(KayacGezegen* gezegen)
{
    if (gezegen == NULL)
        return;

    if (gezegen->gezegen.gezegenAdi != NULL)
        free(gezegen->gezegen.gezegenAdi);

    if (gezegen->gezegen.gezegendekiTarih != NULL)
        zamanYokEt(gezegen->gezegen.gezegendekiTarih);

    free(gezegen);
}
