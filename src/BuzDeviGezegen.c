/**
 *
 *     Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr         1/A GRUBU
 *     08.05.2025 
 *     BuzDeviGezegen.c
 */
#include "BuzDeviGezegen.h"
#include <stdlib.h>
#include <string.h>

BuzDeviGezegen *buzDeviGezegenOlustur(const char *gezegenAdi, int birGunSaati, Zaman gezegendekiTarih)
{
    BuzDeviGezegen *buzDeviGezegen = (BuzDeviGezegen *)malloc(sizeof(BuzDeviGezegen));
    if (!buzDeviGezegen)
        return NULL;

    buzDeviGezegen->gezegen.gezegenAdi = strdup(gezegenAdi);
    buzDeviGezegen->gezegen.birGunSaati = birGunSaati;
    buzDeviGezegen->gezegen.gezegendekiTarih = gezegendekiTarih;
    buzDeviGezegen->gezegen.gezegendekiSaat = 0;
    buzDeviGezegen->gezegen.nufus = 0;
    buzDeviGezegen->gezegen.gezegenTuru = BUZ_DEVI_GEZEGEN;
    buzDeviGezegen->gezegen.yaslanmaOrani = buzDeviGezegenYaslanmaOrani;

    return buzDeviGezegen;
}

double buzDeviGezegenYaslanmaOrani(Gezegen *gezegen)
{
    return 0.05; // Buz devlerinde yaşlanma oranı
}

void BuzDeviGezegenYokEt(BuzDeviGezegen *gezegen)
{
    if (gezegen == NULL)
        return;

    if (gezegen->gezegen.gezegenAdi != NULL)
        free(gezegen->gezegen.gezegenAdi);

    if (gezegen->gezegen.gezegendekiTarih != NULL)
        zamanYokEt(gezegen->gezegen.gezegendekiTarih);

    free(gezegen);
}
