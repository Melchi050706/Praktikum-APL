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

// Prototipe Fungsi dan Prosedur
void registrasi();
bool login(User &currentUser);
void menu();
void tampilKarakter(int index = 0); // rekursif
void tambahKarakter();
void editKarakter();
void hapusKarakter();
void keluar(); // overloading
void keluar(string username); // overloading
void ubahRarity(int* rarity); // dereference
void hitungKarakter(int &total); // address-of

// Prototipe sorting
void sortNamaAscending();
void sortRarityDescending();
void sortElemenAscending();

int main() {
    // Data awal
    characters[0] = {"Silver Wolf", "Quantum", 5};
    characters[1] = {"Kafka", "Lightning", 5};
    characters[2] = {"Dan Heng", "Wind", 4};

    registrasi();

    User currentUser;
    if (!login(currentUser)) {
        cout << "Anda telah gagal login 3 kali.\n";
        return 0;
    }

    menu();
    keluar(currentUser.username); // contoh overloading
    return 0;
}

// ======================= SUBPROGRAM ========================

void registrasi() {
    cout << "===== Registrasi Akun =====\n";
    if (totalUsers < MAX_USERS) {
        cout << "Masukkan Username: ";
        getline(cin, users[totalUsers].username);
        cout << "Masukkan Password: ";
        getline(cin, users[totalUsers].password);
        totalUsers++;
        cout << "Akun berhasil didaftarkan!\n";
    }
}

bool login(User &currentUser) {
    int loginAttempts = 0;
    bool loggedIn = false;

    while (!loggedIn && loginAttempts < 3) {
        cout << "\n===== Login =====\n";
        cout << "Masukkan Username: ";
        getline(cin, currentUser.username);
        cout << "Masukkan Password: ";
        getline(cin, currentUser.password);

        for (int i = 0; i < totalUsers; i++) {
            if (users[i].username == currentUser.username &&
                users[i].password == currentUser.password) {
                loggedIn = true;
                cout << "Berhasil login!\n";
                break;
            }
        }

        if (!loggedIn) {
            cout << "Login gagal, coba lagi.\n";
            loginAttempts++;
        }
    }

    return loggedIn;
}

void menu() {
    int pilihan;
    do {
        cout << "\n===== Menu Karakter Honkai: Star Rail =====\n";
        cout << "1. Tampilkan Karakter\n";
        cout << "2. Tambah Karakter\n";
        cout << "3. Edit Karakter\n";
        cout << "4. Hapus Karakter\n";
        cout << "5. Keluar\n";
        cout << "6. Sorting Nama Ascending\n";
        cout << "7. Sorting Rarity Descending\n";
        cout << "8. Sorting Elemen Ascending\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: tampilKarakter(); break;
            case 2: tambahKarakter(); break;
            case 3: editKarakter(); break;
            case 4: hapusKarakter(); break;
            case 5: break;
            case 6: sortNamaAscending(); break;
            case 7: sortRarityDescending(); break;
            case 8: sortElemenAscending(); break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);
}

// REKURSIF untuk menampilkan data karakter
void tampilKarakter(int index) {
    if (index == 0) {
        cout << "\nDaftar Karakter:\n";
        cout << left << setw(8) << "Indeks" << setw(20) << "Nama"
             << setw(15) << "Elemen" << setw(10) << "Rarity" << endl;
        cout << "--------------------------------------------------------\n";
    }

    if (index < totalCharacters) {
        cout << left << setw(8) << (index + 1)
             << setw(20) << characters[index].name
             << setw(15) << characters[index].element
             << setw(10) << characters[index].rarity << endl;
        tampilKarakter(index + 1); // rekursif lanjut
    }
}

void tambahKarakter() {
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

        // Fungsi dengan parameter address-of
        hitungKarakter(totalCharacters);
    } else {
        cout << "Database karakter penuh!\n";
    }
}

void editKarakter() {
    tampilKarakter();
    int index;
    cout << "Masukkan indeks karakter yang ingin diedit: ";
    cin >> index; cin.ignore();
    index--;

    if (index >= 0 && index < totalCharacters) {
        cout << "Masukkan Nama Baru: ";
        getline(cin, characters[index].name);
        cout << "Masukkan Elemen Baru: ";
        getline(cin, characters[index].element);

        // Fungsi dengan parameter dereference
        ubahRarity(&characters[index].rarity);

        cout << "Karakter berhasil diperbarui!\n";
    } else {
        cout << "Indeks tidak valid!\n";
    }
}

void hapusKarakter() {
    tampilKarakter();
    int index;
    cout << "Masukkan indeks karakter yang ingin dihapus: ";
    cin >> index; cin.ignore();
    index--;

    if (index >= 0 && index < totalCharacters) {
        for (int i = index; i < totalCharacters - 1; i++) {
            characters[i] = characters[i + 1];
        }
        totalCharacters--;
        cout << "Karakter berhasil dihapus!\n";

        // Tampilkan jumlah karakter sekarang
        hitungKarakter(totalCharacters);
    } else {
        cout << "Indeks tidak valid!\n";
    }
}

// Fungsi Overloading
void keluar() {
    cout << "Terima kasih sudah menggunakan program ini!\n";
}

void keluar(string username) {
    cout << "Sampai jumpa lagi, " << username << "! Terima kasih sudah login.\n";
}

// Fungsi dengan parameter dereference (*)
void ubahRarity(int* rarity) {
    cout << "Masukkan Rarity Baru (via pointer): ";
    cin >> *rarity;
    cin.ignore();
}

// Fungsi dengan parameter address-of (&)
void hitungKarakter(int &total) {
    cout << "Total karakter saat ini: " << total << endl;
}

// ================= SORTING ==================

// Sorting nama secara ascending (A-Z)
void sortNamaAscending() {
    for (int i = 0; i < totalCharacters - 1; i++) {
        for (int j = 0; j < totalCharacters - i - 1; j++) {
            if (characters[j].name > characters[j + 1].name) {
                swap(characters[j], characters[j + 1]);
            }
        }
    }
    cout << "Data berhasil disorting berdasarkan Nama (A-Z).\n";
    tampilKarakter();
}

// Sorting rarity secara descending (tinggi ke rendah)
void sortRarityDescending() {
    for (int i = 0; i < totalCharacters - 1; i++) {
        for (int j = 0; j < totalCharacters - i - 1; j++) {
            if (characters[j].rarity < characters[j + 1].rarity) {
                swap(characters[j], characters[j + 1]);
            }
        }
    }
    cout << "Data berhasil disorting berdasarkan Rarity (tinggi ke rendah).\n";
    tampilKarakter();
}

// Sorting elemen secara ascending (bebas)
void sortElemenAscending() {
    for (int i = 0; i < totalCharacters - 1; i++) {
        for (int j = 0; j < totalCharacters - i - 1; j++) {
            if (characters[j].element > characters[j + 1].element) {
                swap(characters[j], characters[j + 1]);
            }
        }
    }
    cout << "Data berhasil disorting berdasarkan Elemen (A-Z).\n";
    tampilKarakter();
}
