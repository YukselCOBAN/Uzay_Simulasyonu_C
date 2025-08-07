#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H
#define MAX_LINE_LENGTH 256

#include "UzayAraci.h" // UzayAraci yapısını kullanabilmek için
#include "Kisi.h"      // Kisi yapısını kullanabilmek için
#include "Gezegen.h"

// Fonksiyon prototipleri:
//  Uzay araçlarının dosyasını okuma
UzayAraci **araclarDosyasiniOku(int *araclarSayisi);

// Gezegenlerin dosyasını okuma
Gezegen **gezegenlerDosyasiniOku(int *gezegenlerSayisi);

// Kişilerin dosyasını okuma
Kisi **kisilerDosyasiniOku(int *kisilerSayisi, UzayAraci **araclarListesi, int araclarSayisi);

#endif
