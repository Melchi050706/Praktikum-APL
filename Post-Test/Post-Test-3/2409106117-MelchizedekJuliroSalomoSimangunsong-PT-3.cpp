#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Character {
    string name;
    string element;
    int rarity;
};

struct User {
    string username;
    string password;
};

const int MAX_USERS = 10;
const int MAX_CHARACTERS = 100;
User users[MAX_USERS];
Character characters[MAX_CHARACTERS];
int totalUsers = 0;
int totalCharacters = 3;

int main() {
    // Data awal karakter
    characters[0] = {"Silver Wolf", "Quantum", 5};
    characters[1] = {"Kafka", "Lightning", 5};
    characters[2] = {"Dan Heng", "Wind", 4};

    // Registrasi Akun
    cout << "===== Registrasi Akun =====\n";
    if (totalUsers < MAX_USERS) {
        cout << "Masukkan Username: ";
        getline(cin, users[totalUsers].username);
        cout << "Masukkan Password: ";
        getline(cin, users[totalUsers].password);
        totalUsers++;
        cout << "Akun berhasil didaftarkan!\n";
    }

    int loginAttempts;
    bool loggedIn;
    User currentUser;

    while (true) {
        loginAttempts = 0;
        loggedIn = false;
        
        while (!loggedIn && loginAttempts < 3) {
            cout << "\n===== Login =====\n";
            cout << "Masukkan Username: ";
            getline(cin, currentUser.username);
            cout << "Masukkan Password: ";
            getline(cin, currentUser.password);

            bool validUser = false;
            for (int i = 0; i < totalUsers; i++) {
                if (users[i].username == currentUser.username && users[i].password == currentUser.password) {
                    validUser = true;
                    break;
                }
            }

            if (validUser) {
                loggedIn = true;
                cout << "Berhasil login!\n";
            } else {
                cout << "Login gagal le coba lagi.\n";
                loginAttempts++;
            }
        }
        
        if (!loggedIn) {
            cout << "Anda telah gagal login 3 kali, makanya masukin yang bener!.\n";
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
            cin.ignore();
            
            if (pilihan == 1) {
                cout << "\nDaftar Karakter:\n";
                cout << left << setw(8) << "Indeks" << setw(20) << "Nama" << setw(15) << "Elemen" << setw(10) << "Rarity" << endl;
                cout << "--------------------------------------------------------\n";
                for (int i = 0; i < totalCharacters; i++) {
                    cout << left << setw(8) << (i + 1) << setw(20) << characters[i].name << setw(15) << characters[i].element << setw(10) << characters[i].rarity << endl;
                }
            }
            else if (pilihan == 2) {
                if (totalCharacters < MAX_CHARACTERS) {
                    cout << "Masukkan Nama Karakter: ";
                    getline(cin, characters[totalCharacters].name);
                    cout << "Masukkan Elemen Karakter: ";
                    getline(cin, characters[totalCharacters].element);
                    cout << "Masukkan Rarity Karakter: ";
                    cin >> characters[totalCharacters].rarity;
                    cin.ignore();
                    totalCharacters++;
                    cout << "Karakter berhasil ditambahkan!\n";
                } else {
                    cout << "Database sudah penuh le kebanyakan karakter kering juga material kalian nanti.\n";
                }
            }
            else if (pilihan == 3) {
                cout << "\nDaftar Karakter:\n";
                cout << left << setw(8) << "Indeks" << setw(20) << "Nama" << setw(15) << "Elemen" << setw(10) << "Rarity" << endl;
                cout << "--------------------------------------------------------\n";
                for (int i = 0; i < totalCharacters; i++) {
                    cout << left << setw(8) << (i + 1) << setw(20) << characters[i].name << setw(15) << characters[i].element << setw(10) << characters[i].rarity << endl;
                }
                int index;
                cout << "Masukkan indeks karakter yang ingin diedit (1 - " << totalCharacters << "): ";
                cin >> index;
                cin.ignore();
                index--;
                if (index >= 0 && index < totalCharacters) {
                    cout << "Masukkan Nama Baru: ";
                    getline(cin, characters[index].name);
                    cout << "Masukkan Elemen Baru: ";
                    getline(cin, characters[index].element);
                    cout << "Masukkan Rarity Baru: ";
                    cin >> characters[index].rarity;
                    cin.ignore();
                    cout << "Karakter berhasil diperbarui!\n";
                } else {
                    cout << "pilih yang bener ya sayang!\n";
                }
            }
            else if (pilihan == 4) {
                cout << "\nDaftar Karakter:\n";
                cout << left << setw(8) << "Indeks" << setw(20) << "Nama" << setw(15) << "Elemen" << setw(10) << "Rarity" << endl;
                cout << "--------------------------------------------------------\n";
                for (int i = 0; i < totalCharacters; i++) {
                    cout << left << setw(8) << (i + 1) << setw(20) << characters[i].name << setw(15) << characters[i].element << setw(10) << characters[i].rarity << endl;
                }
                int index;
                cout << "Masukkan indeks karakter yang ingin dihapus (1 - " << totalCharacters << "): ";
                cin >> index;
                index--;
                if (index >= 0 && index < totalCharacters) {
                    for (int i = index; i < totalCharacters - 1; i++) {
                        characters[i] = characters[i + 1];
                    }
                    totalCharacters--;
                    cout << "Karakter berhasil dihapus!\n";
                } else {
                    cout << "pilih yang bener!\n";
                }
            }
            else if (pilihan == 5) {
                cout << "Terima kasih sudah mau melihat program ini, nextim kita buat program Wuthering Waves kalo di bolehkan Bang Ade!\n";
                return 0;
            }
            else {
                cout << "Pilih yang bener ya wir kan di situ ada tulisan piliahn dari no 1-5 pengen di tempeleng nih!\n";
            }
        } while (pilihan != 5);
    }
    return 0;
}
