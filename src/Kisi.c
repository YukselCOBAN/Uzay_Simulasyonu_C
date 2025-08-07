/** 
* 
*     Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr      1/A GRUBU
*     07.05.2025
*     Kisi.c
*/ 
#include "Kisi.h"
#include <stdlib.h>
#include <string.h>
#include "Gezegen.h"

// Güvenli bir şekilde string kopyalamak için yardımcı bir fonksiyon:
static char *stringKopyala(const char *kaynak)
{
    if (kaynak == NULL)
        return NULL;

    // Kaynağın uzunluğu kadar bellek ayırıyorum (null karakter dahil ->\0)
    char *hedef = (char *)malloc(strlen(kaynak) + 1);
    if (hedef == NULL)
        return NULL;
    strcpy(hedef, kaynak);
    return hedef;
}

// Yeni bir Kisi nesnesi oluşturdum:
Kisi *kisiOlustur(const char *isim, int yas, double kalanOmur, const char *uzayAraciAdi, UzayAraci *uzayAraci)
{
    // Kisi yapısı için bellekte yer ayırıyorum
    Kisi *kisi = (Kisi *)malloc(sizeof(Kisi));
    if (kisi == NULL)
        return NULL; // Bellek ayırma başarısızsa NULL döner

    // İsmi kopyalayıp yapıya ekliyorum
    kisi->isim = stringKopyala(isim);
    if (isim != NULL && kisi->isim == NULL)
    {
        free(kisi);
        return NULL;
    }
    // Uzay aracı adını da aynı şekilde kopyalıyorum
    kisi->bulunduguUzayAraciAdi = stringKopyala(uzayAraciAdi);
    if (uzayAraciAdi != NULL && kisi->bulunduguUzayAraciAdi == NULL)
    {
        free(kisi->isim);
        free(kisi);
        return NULL;
    }
    kisi->yas = yas;
    kisi->kalanOmur = kalanOmur;
    kisi->yasiyor = 1;                  // Başlangıçta kişi hayatta
    kisi->bulunanUzayAraci = uzayAraci; // Uzay aracını atıyorum

    return kisi;
}


// Her saat geçtiğinde yapılan işlemler:
void kisiSaatGecir(Kisi *kisi, Gezegen *gez)
{
    if (kisi == NULL )
        return;

    if (kisi->yasiyor && kisi->kalanOmur > 0)
    {
        if (gez)
        {
            kisi->kalanOmur -= gez->yaslanmaOrani(gez);
        }
        else
            kisi->kalanOmur--; //  Kişi hayattaysa ve hâlâ ömrü kaldıysa bir saat geçince ömründen 1 eksiltiyorum

        if (kisi->kalanOmur <= 0)
        {
            kisi->yasiyor = 0;
            kisi->bulunanUzayAraci = NULL; // Artık bir uzay aracında bulunmuyor kişinin ömrü bittiyse
        }
    }
}

// Kişiyi ve ona ait kaynakları sistemden temizliyorum
void kisiYokEt(Kisi *kisi)
{
    if (kisi == NULL)
        return;
    if (kisi->isim != NULL) // Kopyalanan ismi bellekte serbest bırakıyorum
    {
        free(kisi->isim);
    }
    if (kisi->bulunduguUzayAraciAdi != NULL)
    {
        free(kisi->bulunduguUzayAraciAdi); // Kopyalanan uzay aracı adını da serbest bırakıyorum
    }
    free(kisi); // Son olarak Kisi yapısını serbest bırakıyorum
}
