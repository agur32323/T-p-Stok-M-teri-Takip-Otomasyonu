#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cstdlib> 

#define MAX_MUSTERI 100 

using namespace std;

struct Musteri {
    int hesapNo;
    string isim;
    double bakiye;
};

Musteri musteriler[MAX_MUSTERI];
int musteriSayisi = 0;

void musteriKaydet(const Musteri& musteri) {
    ofstream dosya("musteriler.txt", ios::app);
    if (dosya.is_open()) {
        dosya << musteri.hesapNo << ";" << musteri.isim << ";" << musteri.bakiye << endl;
        dosya.close();
        cout << "Müþteri kaydedildi.\n";
    } else {
        cerr << "Dosya açýlamadý!\n";
    }
}

int stringToInt(const string& str) {
    return atoi(str.c_str());
}

double stringToDouble(const string& str) {
    return atof(str.c_str());
}

void musterileriOku() {
    musteriSayisi = 0;
    ifstream dosya("musteriler.txt");
    string satir;

    if (dosya.is_open()) {
        while (getline(dosya, satir) && musteriSayisi < MAX_MUSTERI) {
            stringstream ss(satir);
            string token;

            getline(ss, token, ';');
            musteriler[musteriSayisi].hesapNo = stringToInt(token);  
            getline(ss, musteriler[musteriSayisi].isim, ';');       
            getline(ss, token, ';');
            musteriler[musteriSayisi].bakiye = stringToDouble(token); 

            musteriSayisi++;
        }
        dosya.close();
    } else {
        cerr << "Dosya açýlamadý!\n";
    }
}

void musterileriGoster() {
    for (int i = 0; i < musteriSayisi; i++) {
        cout << "Hesap No: " << musteriler[i].hesapNo
             << ", Ýsim: " << musteriler[i].isim
             << ", Bakiye: " << musteriler[i].bakiye << endl;
    }
}

void yeniMusteriEkle() {
    if (musteriSayisi >= MAX_MUSTERI) {
        cerr << "Müþteri kapasitesine ulaþýldý!\n";
        return;
    }

    Musteri musteri;
    cout << "Yeni müþteri hesap numarasý: ";
    cin >> musteri.hesapNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Yeni müþteri ismi: ";
    getline(cin, musteri.isim);
    cout << "Baþlangýç bakiyesi: ";
    cin >> musteri.bakiye;

    musteriler[musteriSayisi++] = musteri; 
    musteriKaydet(musteri); 
}

void musteriAra() {
    int hesapNo;
    cout << "Aranacak hesap numarasý: ";
    cin >> hesapNo;

    for (int i = 0; i < musteriSayisi; i++) {
        if (musteriler[i].hesapNo == hesapNo) {
            cout << "Bulundu: Hesap No: " << musteriler[i].hesapNo
                 << ", Ýsim: " << musteriler[i].isim
                 << ", Bakiye: " << musteriler[i].bakiye << endl;
            return;
        }
    }
    cout << "Müþteri bulunamadý!\n";
}

void musteriSil() {
    int hesapNo;
    cout << "Silinecek hesap numarasý: ";
    cin >> hesapNo;

    for (int i = 0; i < musteriSayisi; i++) {
        if (musteriler[i].hesapNo == hesapNo) {
            for (int j = i; j < musteriSayisi - 1; j++) {
                musteriler[j] = musteriler[j + 1];
            }
            musteriSayisi--;
            cout << "Müþteri silindi.\n";
            return;
        }
    }
    cout << "Müþteri bulunamadý!\n";
}

void musteriGuncelle() {
    int hesapNo;
    cout << "Güncellenecek hesap numarasý: ";
    cin >> hesapNo;

    for (int i = 0; i < musteriSayisi; i++) {
        if (musteriler[i].hesapNo == hesapNo) {
            cout << "Yeni isim: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, musteriler[i].isim);
            cout << "Yeni bakiye: ";
            cin >> musteriler[i].bakiye;
            cout << "Müþteri güncellendi.\n";
            return;
        }
    }
    cout << "Müþteri bulunamadý!\n";
}

int main() {
    setlocale(LC_ALL, "Turkish");
    musterileriOku();

    int secim;
    do {
        cout << "\nTüpçü Stok Müþteri Takip Otomasyonu\n";
        cout << "1. Yeni Müþteri Ekle\n";
        cout << "2. Müþteri Listesini Göster\n";
        cout << "3. Müþteri Ara\n";
        cout << "4. Müþteri Sil\n";
        cout << "5. Müþteri Güncelle\n";
        cout << "6. Çýkýþ\n";
        cout << "Seçiminizi yapýnýz: ";
        cin >> secim;

        switch (secim) {
            case 1: yeniMusteriEkle(); break;
            case 2: musterileriGoster(); break;
            case 3: musteriAra(); break;
            case 4: musteriSil(); break;
            case 5: musteriGuncelle(); break;
            case 6: cout << "Programdan çýkýlýyor.\n"; break;
            default: cout << "Geçersiz seçim!\n"; break;
        }
    } while (secim != 6);

    return 0;
}

