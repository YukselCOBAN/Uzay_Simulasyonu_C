/**
 *
 *      Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr        1/A GRUBU
 *      03.05.2025
 *      Zaman.c
 */
#include "Zaman.h"

#include <stdio.h>
#include <stdlib.h>

// Ay günleri dizisi(gerçek ay günleri için)
static const int ayGunleri[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Zaman oluşturma fonksiyonu (malloc ile dinamik bellek tahsisi)
Zaman zamanOlustur(int gun, int ay, int yil, int saat)
{
    Zaman yeniZaman = (Zaman)malloc(sizeof(struct zaman));
    if (yeniZaman == NULL)
    {
        printf("Hafıza tahsisi başarısız!\n");
        return NULL;
    }
    yeniZaman->gun = gun;
    yeniZaman->ay = ay;
    yeniZaman->yil = yil;
    yeniZaman->saat = saat;
    return yeniZaman;
}

// Yıl mı kontrolü
int artikYilMi(int yil)
{
    return (yil % 4 == 0 && (yil % 100 != 0 || yil % 400 == 0));
}

void zamanArtir(Zaman t)
{
    if (!t)
        return;

    int ayGun = ayGunleri[t->ay - 1];
    if (t->ay == 2 && artikYilMi(t->yil))
        ayGun++; // 28->29

    t->gun++;
    if (t->gun > ayGun)
    {
        t->gun = 1;
        t->ay++;
        if (t->ay > 12)
        {
            t->ay = 1;
            t->yil++;
        }
    }
}

// Tarihe gün ekleme fonksiyonu
void zamanEkle(Zaman t, int eklenecekGun)
{
    if (!t)
        return;

    while (eklenecekGun > 0)
    {
        int ayGun = ayGunleri[t->ay - 1];
        if (t->ay == 2 && artikYilMi(t->yil))
            ayGun++;

        int kalanGun = ayGun - t->gun;
        if (eklenecekGun > kalanGun)
        {
            eklenecekGun -= (kalanGun + 1);
            t->gun = 1;
            t->ay++;
            if (t->ay > 12)
            {
                t->ay = 1;
                t->yil++;
            }
        }
        else
        {
            t->gun += eklenecekGun;
            eklenecekGun = 0;
        }
    }
}

// Tarihler arasındaki farkı (gün cinsinden) hesaplama
int zamanFarkiGun(Zaman t1, Zaman t2)
{
    int fark = 0;
    Zaman tnew = zamanOlustur(t1->gun, t1->ay, t1->yil, t1->saat);
    while (tnew->gun != t2->gun || tnew->ay != t2->ay || tnew->yil != t2->yil)
    {
        // t1 = zamanEkle(t1, 1);
        zamanArtir(tnew);

        fark++;
    }
    zamanYokEt(tnew);
    return fark;
}

// struct tm yapısına dönüştürme
struct tm zamanToTm(Zaman z)
{
    struct tm zaman;
    zaman.tm_year = z->yil - 1900; // Yıl - 1900 formatına dönüştürülmeli
    zaman.tm_mon = z->ay - 1;      // Ay 0-11 arası olduğundan 1 çıkartıyoruz
    zaman.tm_mday = z->gun;
    zaman.tm_hour = z->saat;
    zaman.tm_min = 0;
    zaman.tm_sec = 0;
    zaman.tm_isdst = -1;
    return zaman;
}

// time_t türüne dönüştürme
time_t zamanToTime(Zaman z)
{
    struct tm tmZaman = zamanToTm(z);
    return mktime(&tmZaman);
}

// Varış zamanını hesaplama:
// Zaman varisZamaniHesapla(Zaman cikisZamani, int mesafeSaat, Zaman gezegenCikisZamani, int cikisGunSaat, int varisGunSaat)
// {
//     int toplamSaat = mesafeSaat;
//     int varisGun = toplamSaat / varisGunSaat;
//     int varisSaat = toplamSaat % varisGunSaat;

//     Zaman varisZaman = zamanEkle(gezegenCikisZamani, varisGun);
//     varisZaman->saat = varisSaat;

//     return varisZaman;
// }

// Dinamik bellek tahsis edilen Zaman nesnesini serbest bırakma:
void zamanYokEt(Zaman zaman)
{
    if (zaman != NULL)
    {
        free(zaman); // Hafızayı serbest bırakır.
    }
}
