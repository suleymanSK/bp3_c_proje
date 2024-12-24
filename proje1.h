/*
* @file proje.h
* @description benim kendi kütüphanem. Kullandığımız fonksiyonların prototipi buradadır. 1.PROJE
* @date 23.12.2024
* @author Suleyman salih kuloglu suleyman.kuloglu@stu.fsm.edu.tr
*/
#ifndef PROJE1_H
#define PROJE1_H


typedef struct{
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

typedef struct{
    char *birimAdi;
    unsigned short int birimKodu;
    Calisan *birimCalisanlar;
} Birim;

// 1. İlgili değerleri alıp bir Birim struct döndüren fonksiyon
Birim birimOlustur(const char *birimAdi, unsigned short int birimKodu);

// 2. İlgili değerleri alıp bir Calisan struct döndüren fonksiyon
Calisan calisanOlustur(const char *calisanAdi, const char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);

// 3. Oluşturulan yeni struct yapılarını diziye ekleyen fonksiyon
void birimeCalisanEkle(Birim *birim, Calisan calisan, int *calisanSayisi);

// 4. Parametre olarak Calisan türünden değişken alıp bilgilerini yazdıran bir fonksiyon
void calisanBilgileriYazdir(const Calisan *calisan);

// 5. Parametre olarak Birim türünden değişken alıp bilgilerini yazdıran bir fonksiyon
void birimBilgileriYazdir(const Birim *birim);

// 6. Parametre olarak Birim türünden dinamik bir dizi alıp bilgilerini yazdıran bir fonksiyon
void tumBirimBilgileriYazdir(const Birim *birimler, int birimSayisi);

// 7. Parametre olarak aldığı birimin çalışanlarının maaş ortalamasını hesaplayan bir fonksiyon
float birimMaasOrtalamasi(const Birim *birim, int calisanSayisi);

// 8. Parametre olarak aldığı birimde ortalama maaş üzerinde maaş alan çalışanları listeleyen bir fonksiyon
void ortalamaUstuMaasCalisanlar(const Birim *birim, int calisanSayisi);

// 9. Her birimin ayrı ayrı en yüksek maaş alan çalışanını yazdıran fonksiyon
void enYuksekMaasCalisanlari(const Birim *birimler, int birimSayisi, int *calisanSayilari);

// 10. Parametre olarak bir maaş değeri alıp, 10 yıldan fazla çalışanlar bu maaştan az alıyor ise maaşlarını parametre olarak verilen maaşa eşitleyen fonksiyon
void maasGuncelle(Calisan *calisanlar, int calisanSayisi, float yeniMaas,float ortalama);

// 11. Tüm Birim ve Calisan bilgilerini bir dosyaya yazan bir fonksiyon
void dosyayaYaz(const Birim *birimler, int birimSayisi, int *calisanSayilari, const char *dosyaAdi);

// 12. Tüm Birim ve Calisan bilgilerini dosyadan diziye aktaran bir fonksiyon
void dosyadanOku(Birim **birimler, int *birimSayisi, int **calisanSayilari, const char *dosyaAdi);

#endif // PROJE1_H
