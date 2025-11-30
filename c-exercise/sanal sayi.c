#include <stdio.h>

typedef struct {
    float gercek;  
    float sanal;   
} KarmaþýkSayý;

// Toplama iþlemi
KarmaþýkSayý toplama(KarmaþýkSayý sayý1, KarmaþýkSayý sayý2) {
    KarmaþýkSayý sonuç;
    sonuç.gercek = sayý1.gercek + sayý2.gercek;
    sonuç.sanal = sayý1.sanal + sayý2.sanal;
    return sonuç;
}

// Çýkarma iþlemi
KarmaþýkSayý çýkarma(KarmaþýkSayý sayý1, KarmaþýkSayý sayý2) {
    KarmaþýkSayý sonuç;
    sonuç.gercek = sayý1.gercek - sayý2.gercek;
    sonuç.sanal = sayý1.sanal - sayý2.sanal;
    return sonuç;
}

// Karmaþýk sayýyý ekrana yazdýrma fonksiyonu
void karmaþýkSayýyýYazdýr(KarmaþýkSayý sayý) {
    if (sayý.sanal < 0)
        printf("%.2f - %.2fi\n", sayý.gercek, sayý.sanal);
    else
        printf("%.2f + %.2fi\n", sayý.gercek, sayý.sanal);
}

int main() {
    KarmaþýkSayý sayý1 = { 3, 4 }; // 3 + 4i
    KarmaþýkSayý sayý2 = { 1, -2 }; // 1 - 2i

    printf("Sayý 1: ");
    karmaþýkSayýyýYazdýr(sayý1);

    printf("Sayý 2: ");
    karmaþýkSayýyýYazdýr(sayý2);

    KarmaþýkSayý toplam = toplama(sayý1, sayý2);
    printf("Toplam: ");
    karmaþýkSayýyýYazdýr(toplam);

    KarmaþýkSayý fark = çýkarma(sayý1, sayý2);
    printf("Fark: ");
    karmaþýkSayýyýYazdýr(fark);

    return 0;
}
