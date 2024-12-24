#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
* @file proje1.c
* @description Bu dosyada proje1.h dosyasındaki fonksiyon prototiplerinin gövdeleri bulunmaktadır. Bu proje dinamik bellek, struct ve pointer kullandım.1.PROJE
* @date 23.12.2024
* @author Suleyman salih kuloglu suleyman.kuloglu@stu.fsm.edu.tr
*/


// 1. Birim oluşturma
Birim birimOlustur(const char *birimAdi, unsigned short int birimKodu) {
    Birim yeniBirim;
    //char türünden dinamik bir dizi (boyutu 30)
    yeniBirim.birimAdi = (char *)malloc(30 * sizeof(char));
    // parametre olarak verilen birimAdi'ni yeni yapıya kopyalar
    strcpy(yeniBirim.birimAdi, birimAdi);
    yeniBirim.birimKodu = birimKodu;
    yeniBirim.birimCalisanlar = (Calisan *)calloc(20, sizeof(Calisan));
    
    return yeniBirim;
}

// 2. Çalışan oluşturma
Calisan calisanOlustur(const char *calisanAdi, const char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili) {
    Calisan yeniCalisan;
    //char türünden dinamik bir dizi (boyutu 30)
    yeniCalisan.calisanAdi = (char *)malloc(30 * sizeof(char));
    yeniCalisan.calisanSoyadi = (char *)malloc(30 * sizeof(char));
    // parametre olarak verilen calisanAdi'ni yeni yapıya kopyalar
    strcpy(yeniCalisan.calisanAdi, calisanAdi);
    strcpy(yeniCalisan.calisanSoyadi, calisanSoyadi);
    yeniCalisan.birimKodu = birimKodu;
    yeniCalisan.maas = maas;
    yeniCalisan.girisYili = girisYili;
    
    return yeniCalisan;
}

// 3. Birime çalışan ekleme
void birimeCalisanEkle(Birim *birim, Calisan calisan, int *calisanSayisi) {
    birim->birimCalisanlar = realloc(birim->birimCalisanlar, (*calisanSayisi + 1) * sizeof(Calisan));
    birim->birimCalisanlar[*calisanSayisi] = calisan;
    (*calisanSayisi)++;
    
}

// 4. Çalışan bilgilerini yazdırma
void calisanBilgileriYazdir(const Calisan *calisan) {
    printf("\n");
    printf("Calisan Bilgileri:\n");
    printf("Ad: %s\nSoyad: %s\nBirim Kodu: %d\nMaas: %.2f\nGiris Yili: %d\n",
           calisan->calisanAdi, calisan->calisanSoyadi, calisan->birimKodu, calisan->maas, calisan->girisYili);
          
}

void birimBilgileriYazdir(const Birim *birim) {
    printf("Birim Adi: %s\nBirim Kodu: %d\n", birim->birimAdi, birim->birimKodu);
    
}

void tumBirimBilgileriYazdir(const Birim *birimler, int birimSayisi) {
    for (int i = 0; i < birimSayisi; i++) {
        birimBilgileriYazdir(&birimler[i]);
    }
    
}

float birimMaasOrtalamasi(const Birim *birim, int calisanSayisi) {
    float toplam = 0;
    for (int i = 0; i < calisanSayisi; i++) {
        toplam += birim->birimCalisanlar[i].maas;
    }
    
    return calisanSayisi ? toplam / calisanSayisi : 0;
}

 void ortalamaUstuMaasCalisanlar(const Birim *birim, int calisanSayisi) {
    float ortalama = birimMaasOrtalamasi(birim, calisanSayisi);
    for (int i = 0; i < calisanSayisi; i++) {
        if (birim->birimCalisanlar[i].maas > ortalama) {
            calisanBilgileriYazdir(&birim->birimCalisanlar[i]);
        }
    }
    
}

void enYuksekMaasCalisanlari(const Birim *birimler, int birimSayisi, int *calisanSayilari) {
    for (int i = 0; i < birimSayisi; i++) {
        float maxMaas = 0;
        Calisan *maxCalisan = NULL;
        for (int j = 0; j < calisanSayilari[i]; j++) {
            if (birimler[i].birimCalisanlar[j].maas > maxMaas) {
                maxMaas = birimler[i].birimCalisanlar[j].maas;
                maxCalisan = &birimler[i].birimCalisanlar[j];
            }
        }
        if (maxCalisan) {
            printf("Birim: %s\n", birimler[i].birimAdi);
            calisanBilgileriYazdir(maxCalisan);
        }
    }
    
}

void maasGuncelle(Calisan *calisanlar, int calisanSayisi, float yeniMaas,float ortalama) {
    
    for (int i = 0; i < calisanSayisi; i++) {
        if (2024 - calisanlar[i].girisYili > 10 && calisanlar[i].maas < yeniMaas && calisanlar[i].maas <ortalama) {
            calisanlar[i].maas = yeniMaas;
        }
    }
}

void dosyayaYaz(const Birim *birimler, int birimSayisi, int *calisanSayilari, const char *dosyaAdi) {
    FILE *dosya = fopen(dosyaAdi, "w");
    if (!dosya) {
        perror("Dosya acilamadi");
        return;
    }

    fwrite(&birimSayisi, sizeof(int), 1, dosya);
    for (int i = 0; i < birimSayisi; i++) {
        int birimAdiUzunluk = strlen(birimler[i].birimAdi) + 1;
        fwrite(&birimAdiUzunluk, sizeof(int), 1, dosya);
        fwrite(birimler[i].birimAdi, sizeof(char), birimAdiUzunluk, dosya);
        fwrite(&birimler[i].birimKodu, sizeof(unsigned short int), 1, dosya);
        fwrite(&calisanSayilari[i], sizeof(int), 1, dosya);
        for (int j = 0; j < calisanSayilari[i]; j++) {
            Calisan *calisan = &birimler[i].birimCalisanlar[j];
            int adUzunluk = strlen(calisan->calisanAdi) + 1;
            int soyadUzunluk = strlen(calisan->calisanSoyadi) + 1;
            fwrite(&adUzunluk, sizeof(int), 1, dosya);
            fwrite(calisan->calisanAdi, sizeof(char), adUzunluk, dosya);
            fwrite(&soyadUzunluk, sizeof(int), 1, dosya);
            fwrite(calisan->calisanSoyadi, sizeof(char), soyadUzunluk, dosya);
            fwrite(&calisan->birimKodu, sizeof(unsigned short int), 1, dosya);
            fwrite(&calisan->maas, sizeof(float), 1, dosya);
            fwrite(&calisan->girisYili, sizeof(int), 1, dosya);
        }
    }

    fclose(dosya);
}

void dosyadanOku(Birim **birimler, int *birimSayisi, int **calisanSayilari, const char *dosyaAdi) {
    FILE *dosya = fopen(dosyaAdi, "r");
    if (!dosya) {
        perror("Dosya acilamadi");
        return;
    }

    fread(birimSayisi, sizeof(int), 1, dosya);
    *birimler = malloc(*birimSayisi * sizeof(Birim));
    *calisanSayilari = malloc(*birimSayisi * sizeof(int));

    for (int i = 0; i < *birimSayisi; i++) {
        int birimAdiUzunluk;
        fread(&birimAdiUzunluk, sizeof(int), 1, dosya);
        (*birimler)[i].birimAdi = malloc(birimAdiUzunluk);
        fread((*birimler)[i].birimAdi, sizeof(char), birimAdiUzunluk, dosya);
        fread(&(*birimler)[i].birimKodu, sizeof(unsigned short int), 1, dosya);
        fread(&(*calisanSayilari)[i], sizeof(int), 1, dosya);
        (*birimler)[i].birimCalisanlar = malloc((*calisanSayilari)[i] * sizeof(Calisan));
        for (int j = 0; j < (*calisanSayilari)[i]; j++) {
            Calisan *calisan = &(*birimler)[i].birimCalisanlar[j];
            int adUzunluk, soyadUzunluk;
            fread(&adUzunluk, sizeof(int), 1, dosya);
            calisan->calisanAdi = malloc(adUzunluk);
            fread(calisan->calisanAdi, sizeof(char), adUzunluk, dosya);
            fread(&soyadUzunluk, sizeof(int), 1, dosya);
            calisan->calisanSoyadi = malloc(soyadUzunluk);
            fread(calisan->calisanSoyadi, sizeof(char), soyadUzunluk, dosya);
            fread(&calisan->birimKodu, sizeof(unsigned short int), 1, dosya);
            fread(&calisan->maas, sizeof(float), 1, dosya);
            fread(&calisan->girisYili, sizeof(int), 1, dosya);
        }
    }

    fclose(dosya);
}

