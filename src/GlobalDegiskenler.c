/** 
* 
*    Yüksel Çoban      yuksel.coban@ogr.sakarya.edu.tr       1/A GRUBU
*    11.05.2025
*    GlobalDegiskenler.c
*/ 
#include <stdlib.h>
#include "GlobalDegiskenler.h"

// tüm gezegenlerin listesini tutuyorum.Başlangıçta bu ve asagıdaki tüm listeler boş.
Gezegen **gezegenler = NULL;

// tüm uzay araçlarının listesini tutuyorum.
UzayAraci **uzayAraclari = NULL;

// tüm kişilerin listesini tutuyorum.
Kisi **kisiler = NULL;

// Gezegen sayısını saklıyorum.
int gezegenSayisi = 0;

// Şimdilik sıfır.
int uzayAracSayisi = 0;

// Başlangıçta sıfır.
int kisiSayisi = 0;
