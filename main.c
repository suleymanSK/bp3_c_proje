#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * @file main.c
 * @description Bu dosyada proje.c dosyasındaki fonksiyonları test ettim. 1.PROJE
 * @date 23.12.2024
 * @author Suleyman salih kuloglu suleyman.kuloglu@stu.fsm.edu.tr
 */

int main() {
    int birimSayisi = 0;
    int *calisanSayilari = NULL;
    Birim *birimler = NULL;

    // Yeni birim ve calisan olustur
    Birim birim = birimOlustur("Muhasebe", 1);
    Birim birim2 = birimOlustur("Mudur", 2);
    Calisan calisan1 = calisanOlustur("Ahmet", "Yilmaz", 1, 7500.0, 2020);
    Calisan calisan2 = calisanOlustur("Ayse", "Demir", 1, 1000.0, 2012);
    Calisan calisan3 = calisanOlustur("ssK", "ssK", 1, 3000.0, 2013);
    Calisan calisan4 = calisanOlustur("Ayhan", "Akdas", 2, 10000.0, 2017);
    Calisan calisan5 = calisanOlustur("Furkan", "Sen", 2, 15000.0, 2010);

    


    // Calisanlari birime ekle
    int calisanSayisi1 = 0;
    birimeCalisanEkle(&birim, calisan1, &calisanSayisi1);
    birimeCalisanEkle(&birim, calisan2, &calisanSayisi1);
    birimeCalisanEkle(&birim, calisan3, &calisanSayisi1);
    int calisanSayisi2 = 0;
    birimeCalisanEkle(&birim2, calisan4, &calisanSayisi2);
    birimeCalisanEkle(&birim2, calisan5, &calisanSayisi2);
    // Tum birim bilgilerini yazdir
    printf("Muhasebe Birimi Bilgileri:\n");
    birimBilgileriYazdir(&birim);
    for (int i = 0; i < calisanSayisi1; i++) {
        calisanBilgileriYazdir(&birim.birimCalisanlar[i]);
    }
     printf("\nMudur Birimi Bilgileri:\n");
    birimBilgileriYazdir(&birim2);
    for (int i = 0; i < calisanSayisi2; i++) {
        calisanBilgileriYazdir(&birim2.birimCalisanlar[i]);
    }

    // Maas ortalamasi hesapla
     float ortalama1 = birimMaasOrtalamasi(&birim, calisanSayisi1);
    printf("\nMuhasebe Birimi Maas Ortalamasi: %.2f\n", ortalama1);

    float ortalama2 = birimMaasOrtalamasi(&birim2, calisanSayisi2);
    printf("\nMudur Birimi Maas Ortalamasi: %.2f\n", ortalama2);

    // Ortalama uzeri maas alanlari yazdir
    printf("\nMuhasebe Birimi Ortalama Ustu Maas Alan Calisanlar:\n");
    ortalamaUstuMaasCalisanlar(&birim, calisanSayisi1);

    printf("\nMudur Birimi Ortalama Ustu Maas Alan Calisanlar:\n");
    ortalamaUstuMaasCalisanlar(&birim2, calisanSayisi2);

    // Maas guncelleme

    float yeni_maas=4500;
    for (int i = 0; i < calisanSayisi1; i++)
    {   
    
        maasGuncelle(&birim.birimCalisanlar[i],calisanSayisi1,yeni_maas,ortalama1);
    
    }


    // Birim bilgilerini diziye aktar
    birimSayisi = 2;
    calisanSayilari = malloc(birimSayisi * sizeof(int));
    birimler = malloc(birimSayisi * sizeof(Birim));
    birimler[0] = birim;
    calisanSayilari[0] = calisanSayisi1;
    birimler[1] = birim2;
    calisanSayilari[1] = calisanSayisi2;

    // Bilgileri dosyaya yaz
    dosyayaYaz(birimler, birimSayisi, calisanSayilari, "veriler");

    // Dosyadan bilgileri oku
    Birim *okunanBirimler = NULL;
    int okunanBirimSayisi;
    int *okunanCalisanSayilari = NULL;
    dosyadanOku(&okunanBirimler, &okunanBirimSayisi, &okunanCalisanSayilari, "veriler");

    // Okunan bilgileri yazdir
    printf("\nDosyadan Okunan Birimler:\n");
    tumBirimBilgileriYazdir(okunanBirimler, okunanBirimSayisi);
    for (int i = 0; i < okunanBirimSayisi; i++) {
        printf("\nBirim: %s\n", okunanBirimler[i].birimAdi);
        for (int j = 0; j < okunanCalisanSayilari[i]; j++) {
            calisanBilgileriYazdir(&okunanBirimler[i].birimCalisanlar[j]);
        }
    }

    // Bellek temizleme
    for (int i = 0; i < okunanBirimSayisi; i++) {
        free(okunanBirimler[i].birimAdi);
        for (int j = 0; j < okunanCalisanSayilari[i]; j++) {
            free(okunanBirimler[i].birimCalisanlar[j].calisanAdi);
            free(okunanBirimler[i].birimCalisanlar[j].calisanSoyadi);
        }
        free(okunanBirimler[i].birimCalisanlar);
    }
    free(okunanBirimler);
    free(okunanCalisanSayilari);

    free(calisanSayilari);
    free(birimler);

    return 0;
}


