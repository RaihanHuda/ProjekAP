
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

void tambahHistori(vector<string>& hist, const string& entry) {
    hist.push_back(entry);
}

void tanpilanHistori(const vector<string>& hist) {
    if (hist.empty()) {
        cout << "Anda belum melakukan konversi." << endl;
        return;
    }
    cout << "=== History Konversi ===" << endl;
    for (size_t i = 0; i < hist.size(); i++) {
        cout << i + 1 << ". " << hist[i] << endl;
    }
}

void hapusHistori(vector<string>& hist) {
    hist.clear();
    cout << "History konversi telah dihapus." << endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls"); // windows
    #else
        system("clear"); // linux/macOS
    #endif
};

int binerKeDesimal(string biner) {
    int des = 0;
    int panjang = biner.length();
    for (int i = 0; i < panjang; i++) {
        if (biner[panjang - 1 - i] == '1') {
            des += pow(2, i);
        }
    }
    return des;
}

int oktalKeDesimal(string oktal) {
    int des = 0;
    int panjang = oktal.length();
    for (int i = 0; i < panjang; i++) {
        des += (oktal[panjang - 1 - i] - '0') * pow(8, i);
    }
    return des;
}

int heksaKeDesimal(string heksa) {
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

string desimalKe(int des, int basis) {
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
    
    vector<string> histori;
    char check;
    //Kutambahin do While biar bisa ulang lagi sesuai keinginan usr
    do {
        
        clearScreen(); // biar di console/terminal bersih pas mulai program
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
    else if (dari == "biner") desimal = binerKeDesimal(angka);
    else if (dari == "oktal") desimal = oktalKeDesimal(angka);
    else if (dari == "heksa") desimal = heksaKeDesimal(angka);
    else {
        cout << "Jenis bilangan asal tidak dikenali!\n";
        return 0;
    }

    if (ke == "desimal")
        cout << "\nHasil: " << desimal << endl;
    else if (ke == "biner")
        cout << "\nHasil: " << desimalKe(desimal, 2) << endl;
    else if (ke == "oktal")
        cout << "\nHasil: " << desimalKe(desimal, 8) << endl;
        else if (ke == "heksa")
        cout << "\nHasil: " << desimalKe(desimal, 16) << endl;
        else
        cout << "Jenis bilangan tujuan tidak dikenali!\n";

        cout << "\nApakah Anda ingin melakukan konversi lagi? (y/n): ";
        cin >> check;
    } while (check == 'y' || check == 'Y');
}
