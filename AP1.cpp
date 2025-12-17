#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls"); // windows
    #else
        system("clear"); // linux/macOS
    #endif
};

void tambahHistori(vector<string>& hist, const string& entry) {
    hist.push_back(entry);
}

void tampilanHistori(const vector<string>& hist) {
    if (hist.empty()) {
        cout << "\n=== History Konversi ===" << endl;
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

bool parseInput(const string& input, string& angka, int& basis) {
    size_t buka = input.find('(');
    size_t tutup = input.find(')');

    if (buka == string::npos || tutup == string::npos || tutup <= buka)
        return false;

    angka = input.substr(0, buka);
    string basisStr = input.substr(buka + 1, tutup - buka - 1);

    try {
        basis = stoi(basisStr);
    } catch (...) {
        return false;
    }

    if (!(basis == 2 || basis == 8 || basis == 10 || basis == 16))
        return false;

    if (angka.empty())
        return false;

    return true;
}

bool validasi(const string& angka, int basis) {
    for (char c : angka) {
        int nilai;

        if (c >= '0' && c <= '9')
            nilai = c - '0';
        else if (c >= 'A' && c <= 'F')
            nilai = 10 + (c - 'A');
        else if (c >= 'a' && c <= 'f')
            nilai = 10 + (c - 'a');
        else
            return false;

        if (nilai >= basis)
            return false;
    }
    return true;
}

void inputNilai(string& angka, int& basis) {
    string input;

    while (true) {
        cout << "Masukkan nilai beserta basisnya: ";
        cin >> input;

        if (!parseInput(input, angka, basis)) {
            cout << "\nFormat input salah!\n";
            continue;
        }

        if (!validasi(angka, basis)) {
            cout << "\nDigit tidak sesuai dengan basis!\n";
            continue;
        }

        return; // input valid
    }
}

int getTujuan(){
    string input;
    
    while(true) {
        cout << "Masukkan basis tujuan: ";
        cin >> input;

        for (char & c : input) {
            c = tolower(c); // biar input ga case sensitive
        }
        //validasi input
        if (input == "2" || input == "biner" || input == "bin") {
            return 2;
        } else if (input == "8" || input == "oktal" || input == "oct") {
            return 8;
        } else if (input == "10" || input == "desimal" || input == "dec") {
            return 10;
        } else if (input == "16" || input == "heksadesimal" || input == "hex") {
            return 16;
        } else {
            cout << "Basis tujuan tidak valid!\n\n";
        }
    }
}

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
    string check;
    //Kutambahin do While biar bisa ulang lagi sesuai keinginan usr
    do {
        clearScreen(); // biar di console/terminal bersih pas mulai program
        string angka;
        int pilihan, basis;
        cout << "=== Program Konversi Bilangan ===\n";
        cout << "Pilihan Menu:\n";
        cout << "[1] Konversi Bilangan\n";
        cout << "[2] Lihat History Konversi\n";
        cout << "[3] Keluar Program\n";
        
        while(true) {
            cout << "Masukkan pilihan (1/2/3): ";
            cin >> pilihan;
            if(pilihan == 1 || pilihan == 2 || pilihan == 3) {
                break;
            } else {
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
                cin.clear(); // untuk membersihkan flag error pada cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // untuk mengabaikan input yang salah
            }
        }

        if(pilihan == 1) {
            clearScreen();
            cout << "=== Konversi Bilangan ===\n";
            cout << "Format input nilai (abaikan kurung siku): \n";
            cout << "Desimal\t\t[...(10)]\n";
            cout << "Biner\t\t[...(2)]\n";
            cout << "Oktal\t\t[...(8)]\n";
            cout << "Heksadesimal\t[...(16)]\n";
            inputNilai(angka, basis);

            cout << "\nFormat Basis Tujuan: \n";
            cout << "Biner\t\t[2/biner/bin]\n";
            cout << "Oktal\t\t[8/oktal/oct]\n";
            cout << "Desimal\t\t[10/desimal/dec]\n";
            cout << "Heksadesimal\t[16/heksadesimal/hex]\n";
            int tujuan = getTujuan();

            int desimal = 0;
            
            if (basis == 10) desimal = stoi(angka);
            else if (basis == 2) desimal = binerKeDesimal(angka);
            else if (basis == 8) desimal = oktalKeDesimal(angka);
            else if (basis == 16) desimal = heksaKeDesimal(angka);


            if (tujuan == 10)
                cout << "\nHasil: " << desimal << endl;
            else if (tujuan == 2)
                cout << "\nHasil: " << desimalKe(desimal, 2) << endl;
            else if (tujuan == 8)
                cout << "\nHasil: " << desimalKe(desimal, 8) << endl;
            else if (tujuan == 16)
                cout << "\nHasil: " << desimalKe(desimal, 16) << endl;

            string historiEntry = angka + " dari " + (basis == 10 ? "desimal" : (basis == 2 ? "biner" : (basis == 8 ? "oktal" : "heksadesimal"))) + " ke " + (tujuan == 10 ? "desimal" : (tujuan == 2 ? "biner" : (tujuan == 8 ? "oktal" : "heksadesimal"))) + " = " + (tujuan == 10 ? to_string(desimal) : desimalKe(desimal, tujuan));
            tambahHistori(histori, historiEntry);

        } else if(pilihan == 2) {
            clearScreen();
            tampilanHistori(histori);
        }
        else if(pilihan == 3) {
            break;
        }

        cout << "\nApakah anda ingin kembali ke menu utama?:\n";
        cout << "[y] Kembali ke menu utama\n";
        cout << "[masukkan apa saja] Keluar dari program\n";
        cout << "Pilihan: ";
        cin >> check;
    } while (check == "y" || check == "Y");
    if (check != "y" && check != "Y") {
        cout << "Terima kasih telah menggunakan program ini!" << endl;
    }
}
