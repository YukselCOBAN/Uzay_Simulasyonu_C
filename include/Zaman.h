#ifndef ZAMAN_H
#define ZAMAN_H

#include <time.h> // struct tm ve time_t kullanımı için

// Zaman yapısı:
typedef struct zaman
{
    int gun;  
    int ay;   
    int yil;  
    int saat; 
} *Zaman;     

//Fonksiyon prototipleri
Zaman zamanOlustur(int gun, int ay, int yil, int saat);
int artikYilMi(int yil);
void zamanArtir(Zaman t);
void zamanEkle(Zaman t, int eklenecekGun);
int zamanFarkiGun(Zaman t1, Zaman t2);
struct tm zamanToTm(Zaman z);
time_t zamanToTime(Zaman z);
Zaman varisZamaniHesapla(Zaman cikisZamani, int mesafeSaat, Zaman gezegenCikisZamani, int cikisGunSaat, int varisGunSaat);
void zamanYokEt(Zaman zaman);


#endif 
