#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int binerkedesimal(string biner) {
    int des = 0;
    int panjang = biner.length();
    for (int i = 0; i < panjang; i++) {
        if (biner[panjang - 1 - i] == '1') {
            des += pow(2, i);
        }
    }
    return des;
}

int oktalkedesimal(string oktal) {
    int des = 0;
    int panjang = oktal.length();
    for (int i = 0; i < panjang; i++) {
        des += (oktal[panjang - 1 - i] - '0') * pow(8, i);
    }
    return des;
}

int heksakedesimal(string heksa) {
    int des = 0;
    int panjang = heksa.length();
    for (int i = 0; i < panjang; i++) {
        char c = toupper(heksa[panjang - 1 - i]);
        int nilai;
        if (c >= '0' && c <= '9')
            nilai = c - '0';
        else
            nilai = 10 + (c - 'A');
        des += nilai * pow(16, i);
    }
    return des;
}

string desimalke(int des, int basis) {
    string simbol = "0123456789ABCDEF";
    string hasil = "";
    if (des == 0) return "0";
    while (des > 0) {
        hasil = simbol[des % basis] + hasil;
        des /= basis;
    }
    return hasil;
}

int main() {
    string dari, ke, angka;
    cout << "=== Program Konversi Bilangan ===\n";
    cout << "Masukkan asal bilangan (desimal/biner/oktal/heksa): ";
    cin >> dari;
    cout << "Masukkan tujuan bilangan (desimal/biner/oktal/heksa): ";
    cin >> ke;
    cout << "Masukkan angkanya: ";
    cin >> angka;

    int desimal = 0;

    if (dari == "desimal") desimal = stoi(angka);
    else if (dari == "biner") desimal = binerkedesimal(angka);
    else if (dari == "oktal") desimal = oktalkedesimal(angka);
    else if (dari == "heksa") desimal = heksakedesimal(angka);
    else {
        cout << "Jenis bilangan asal tidak dikenali!\n";
        return 0;
    }

    if (ke == "desimal")
        cout << "Hasil: " << desimal << endl;
    else if (ke == "biner")
        cout << "Hasil: " << desimalke(desimal, 2) << endl;
    else if (ke == "oktal")
        cout << "Hasil: " << desimalke(desimal, 8) << endl;
    else if (ke == "heksa")
        cout << "Hasil: " << desimalke(desimal, 16) << endl;
    else
        cout << "Jenis bilangan tujuan tidak dikenali!\n";
}
