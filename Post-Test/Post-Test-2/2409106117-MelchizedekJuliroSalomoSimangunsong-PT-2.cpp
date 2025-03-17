#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    const int MAX_CHARACTERS = 100;
    string characters[MAX_CHARACTERS][3] = {
        {"Silver Wolf", "Quantum", "5"},
        {"Kafka", "Lightning", "5"},
        {"Dan Heng", "Wind", "4"}
    }; 
    int totalCharacters = 3;
    string username, password;
    int loginAttempts = 0;
    bool loggedIn = false;
    
    while (true) { 
        loginAttempts = 0;
        loggedIn = false;
        

        while (!loggedIn && loginAttempts < 3) {
            cout << "Masukkan Username: ";
            getline(cin, username);
            cout << "Masukkan Password: ";
            getline(cin, password);
            
            if (username == "Melchizedek" && password == "2409106117") {
                cout << "Berhasil login!\n";
                loggedIn = true;
            } else {
                cout << "Login gagal! Username atau password salah.\n";
                loginAttempts++;
            }
        }
        
        if (!loggedIn) {
            cout << "Anda telah gagal login 3 kali. Program berhenti.\n";
            return 0;
        }
        
        int pilihan;
        do {
            cout << "\n===== Sistem Manajemen Karakter Honkai: Star Rail =====\n";
            cout << "1. Tampilkan Karakter\n";
            cout << "2. Tambah Karakter\n";
            cout << "3. Edit Karakter\n";
            cout << "4. Hapus Karakter\n";
            cout << "5. Keluar\n";
            cout << "Pilihan: ";
            cin >> pilihan;
            cin.clear();
            cin.ignore();
            
            if (pilihan == 1) {
                cout << "\nDaftar Karakter:\n";
                cout << left << setw(8) << "Indeks" << setw(20) << "Nama" << setw(15) << "Elemen" << setw(10) << "Rarity" << endl;
                cout << "--------------------------------------------------------\n";
                for (int i = 0; i < totalCharacters; i++) {
                    cout << left << setw(8) << (i + 1) << setw(20) << characters[i][0] << setw(15) << characters[i][1] << setw(10) << characters[i][2] << endl;
                }
            }
            else if (pilihan == 2) {
                if (totalCharacters < MAX_CHARACTERS) {
                    cout << "Masukkan Nama Karakter: ";
                    getline(cin, characters[totalCharacters][0]);
                    cout << "Masukkan Elemen Karakter: ";
                    getline(cin, characters[totalCharacters][1]);
                    cout << "Masukkan Rarity Karakter: ";
                    getline(cin, characters[totalCharacters][2]);
                    totalCharacters++;
                    cout << "Karakter berhasil ditambahkan!\n";
                } else {
                    cout << "Database penuh! Tidak bisa menambahkan karakter lagi.\n";
                }
            }
            else if (pilihan == 3) {
                int index;
                cout << "\nDaftar Karakter:\n";
                cout << left << setw(8) << "Indeks" << setw(20) << "Nama" << setw(15) << "Elemen" << setw(10) << "Rarity" << endl;
                cout << "--------------------------------------------------------\n";
                for (int i = 0; i < totalCharacters; i++) {
                    cout << left << setw(8) << (i + 1) << setw(20) << characters[i][0] << setw(15) << characters[i][1] << setw(10) << characters[i][2] << endl;
                }
                cout << "Masukkan indeks karakter yang ingin diedit (1 - " << totalCharacters << "): ";
                cin >> index;
                cin.ignore();
                index--;
                if (index >= 0 && index < totalCharacters) {
                    cout << "Masukkan Nama Baru: ";
                    getline(cin, characters[index][0]);
                    cout << "Masukkan Elemen Baru: ";
                    getline(cin, characters[index][1]);
                    cout << "Masukkan Rarity Baru: ";
                    getline(cin, characters[index][2]);
                    cout << "Karakter berhasil diperbarui!\n";
                } else {
                    cout << "Indeks tidak valid!\n";
                }
            }
            else if (pilihan == 4) {
                int index;
                cout << "\nDaftar Karakter:\n";
                cout << left << setw(8) << "Indeks" << setw(20) << "Nama" << setw(15) << "Elemen" << setw(10) << "Rarity" << endl;
                cout << "--------------------------------------------------------\n";
                for (int i = 0; i < totalCharacters; i++) {
                    cout << left << setw(8) << (i + 1) << setw(20) << characters[i][0] << setw(15) << characters[i][1] << setw(10) << characters[i][2] << endl;
                }
                cout << "Masukkan indeks karakter yang ingin dihapus (1 - " << totalCharacters << "): ";
                cin >> index;
                index--;
                if (index >= 0 && index < totalCharacters) {
                    for (int i = index; i < totalCharacters - 1; i++) {
                        characters[i][0] = characters[i + 1][0];
                        characters[i][1] = characters[i + 1][1];
                        characters[i][2] = characters[i + 1][2];
                    }
                    totalCharacters--;
                    cout << "Karakter berhasil dihapus!\n";
                } else {
                    cout << "Indeks tidak valid!\n";
                }
            }
            else if (pilihan == 5) {
                cout << "Terima kasih sudah mau memakai program gw next main Honkai Star Rail aja\n";
                return 0;
            }
            else {
                cout << "Pilihan tidak valid!\n";
            }
        } while (pilihan != 5);
    }
    return 0;
}