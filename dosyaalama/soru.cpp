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
        cout << "M��teri kaydedildi.\n";
    } else {
        cerr << "Dosya a��lamad�!\n";
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
        cerr << "Dosya a��lamad�!\n";
    }
}

void musterileriGoster() {
    for (int i = 0; i < musteriSayisi; i++) {
        cout << "Hesap No: " << musteriler[i].hesapNo
             << ", �sim: " << musteriler[i].isim
             << ", Bakiye: " << musteriler[i].bakiye << endl;
    }
}

void yeniMusteriEkle() {
    if (musteriSayisi >= MAX_MUSTERI) {
        cerr << "M��teri kapasitesine ula��ld�!\n";
        return;
    }

    Musteri musteri;
    cout << "Yeni m��teri hesap numaras�: ";
    cin >> musteri.hesapNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Yeni m��teri ismi: ";
    getline(cin, musteri.isim);
    cout << "Ba�lang�� bakiyesi: ";
    cin >> musteri.bakiye;

    musteriler[musteriSayisi++] = musteri; 
    musteriKaydet(musteri); 
}

void musteriAra() {
    int hesapNo;
    cout << "Aranacak hesap numaras�: ";
    cin >> hesapNo;

    for (int i = 0; i < musteriSayisi; i++) {
        if (musteriler[i].hesapNo == hesapNo) {
            cout << "Bulundu: Hesap No: " << musteriler[i].hesapNo
                 << ", �sim: " << musteriler[i].isim
                 << ", Bakiye: " << musteriler[i].bakiye << endl;
            return;
        }
    }
    cout << "M��teri bulunamad�!\n";
}

void musteriSil() {
    int hesapNo;
    cout << "Silinecek hesap numaras�: ";
    cin >> hesapNo;

    for (int i = 0; i < musteriSayisi; i++) {
        if (musteriler[i].hesapNo == hesapNo) {
            for (int j = i; j < musteriSayisi - 1; j++) {
                musteriler[j] = musteriler[j + 1];
            }
            musteriSayisi--;
            cout << "M��teri silindi.\n";
            return;
        }
    }
    cout << "M��teri bulunamad�!\n";
}

void musteriGuncelle() {
    int hesapNo;
    cout << "G�ncellenecek hesap numaras�: ";
    cin >> hesapNo;

    for (int i = 0; i < musteriSayisi; i++) {
        if (musteriler[i].hesapNo == hesapNo) {
            cout << "Yeni isim: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, musteriler[i].isim);
            cout << "Yeni bakiye: ";
            cin >> musteriler[i].bakiye;
            cout << "M��teri g�ncellendi.\n";
            return;
        }
    }
    cout << "M��teri bulunamad�!\n";
}

int main() {
    setlocale(LC_ALL, "Turkish");
    musterileriOku();

    int secim;
    do {
        cout << "\nT�p�� Stok M��teri Takip Otomasyonu\n";
        cout << "1. Yeni M��teri Ekle\n";
        cout << "2. M��teri Listesini G�ster\n";
        cout << "3. M��teri Ara\n";
        cout << "4. M��teri Sil\n";
        cout << "5. M��teri G�ncelle\n";
        cout << "6. ��k��\n";
        cout << "Se�iminizi yap�n�z: ";
        cin >> secim;

        switch (secim) {
            case 1: yeniMusteriEkle(); break;
            case 2: musterileriGoster(); break;
            case 3: musteriAra(); break;
            case 4: musteriSil(); break;
            case 5: musteriGuncelle(); break;
            case 6: cout << "Programdan ��k�l�yor.\n"; break;
            default: cout << "Ge�ersiz se�im!\n"; break;
        }
    } while (secim != 6);

    return 0;
}

