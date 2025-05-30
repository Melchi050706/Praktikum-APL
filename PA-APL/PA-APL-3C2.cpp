#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h> // Untuk getch()
#include <cctype>  // Untuk tolower(), isprint(), isspace(), isalnum()
#include <limits>  // Untuk numeric_limits (digunakan dengan cin.ignore)
#include <algorithm> // Untuk std::any_of (digunakan di containsSpace)

using namespace std;

const int MAX_TIKET = 100;
const int MAX_USER = 20;
const int MAX_PESANAN = 100;

// --- Variabel global untuk status tampilan password (opsional, bisa juga parameter) ---
// bool tampilkanPasswordSaatInput = false; // Defaultnya tersembunyi

// Fungsi untuk konversi string ke lowercase
string toLower(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

// Fungsi untuk mengecek apakah string mengandung spasi
bool containsSpace(const string& str) {
    return std::any_of(str.begin(), str.end(), ::isspace);
}

// Fungsi untuk mengecek apakah string hanya berisi whitespace
bool isStringOnlyWhitespace(const string& str) {
    if (str.empty()) {
        return true; // Anggap string kosong juga sebagai "hanya whitespace" untuk validasi input
    }
    for (char c : str) {
        if (!isspace(c)) {
            return false;
        }
    }
    return true;
}

// Fungsi untuk mengecek apakah string mengandung simbol (selain huruf, angka, dan spasi)
bool containsSymbol(const string& str) {
    for (char c : str) {
        if (!isalnum(c) && c != ' ') { // Jika bukan alfanumerik dan bukan spasi
            return true;
        }
    }
    return false;
}


// Struktur data
struct Tiket {
    int id;
    string namaKonser;
    string tanggal;
    int harga;
};

struct User {
    string username;
    string password;
};

struct Pesanan {
    string konser;
    int harga;
};

// Data global
Tiket tiket[MAX_TIKET] = {
    {1, "Rock Fest", "10/05/2025", 250000},
    {2, "Jazz Night", "15/05/2025", 200000},
    {3, "Pop Party", "20/05/2025", 300000}
};
int jumlahTiket = 3;

User users[MAX_USER];
int jumlahUser = 0;

Pesanan riwayat[MAX_PESANAN];
int jumlahPesanan = 0;

// --- FUNGSI SORTING ---
void bubbleSortHarga(bool ascending = true) {
    for (int i = 0; i < jumlahTiket - 1; i++) {
        for (int j = 0; j < jumlahTiket - i - 1; j++) {
            bool kondisi = ascending ? (tiket[j].harga > tiket[j + 1].harga) : (tiket[j].harga < tiket[j + 1].harga);
            if (kondisi) {
                swap(tiket[j], tiket[j + 1]);
            }
        }
    }
}

void insertionSortNama(bool ascending = true) {
    for (int i = 1; i < jumlahTiket; i++) {
        Tiket key = tiket[i];
        int j = i - 1;
        while (j >= 0 && (ascending ? (toLower(tiket[j].namaKonser) > toLower(key.namaKonser)) : (toLower(tiket[j].namaKonser) < toLower(key.namaKonser)))) {
            tiket[j + 1] = tiket[j];
            j--;
        }
        tiket[j + 1] = key;
    }
}

// --- FUNGSI TAMPILAN ---
void tampilkanTiketBox() {
    cout << "+-----+----------------------+---------------+------------+\n";
    cout << "| ID  | Nama Konser          | Tanggal       | Harga (Rp) |\n";
    cout << "+-----+----------------------+---------------+------------+\n";
    if (jumlahTiket == 0) {
        cout << "|                     TIDAK ADA TIKET TERSEDIA                     |\n";
    } else {
        for (int i = 0; i < jumlahTiket; i++) {
            cout << "| " << setw(3) << tiket[i].id << " | "
                 << setw(20) << left << tiket[i].namaKonser << right << " | "
                 << setw(13) << tiket[i].tanggal << " | "
                 << setw(10) << tiket[i].harga << " |\n";
        }
    }
    cout << "+-----+----------------------+---------------+------------+\n";
}

void tampilkanTiketDenganPilihanUrutan() {
    if (jumlahTiket == 0) {
        cout << "\nBelum ada tiket yang tersedia.\n";
        tampilkanTiketBox();
        return;
    }

    string input;
    int pilihan;

    cout << "\n=== LIHAT TIKET ===\n";
    cout << "1. Tampilkan Langsung (Sesuai ID awal)\n";
    cout << "2. Urutkan Berdasarkan Harga\n";
    cout << "3. Urutkan Berdasarkan Nama\n";
    cout << "Pilihan: ";

    // Validasi input utama
    while (true) {
        getline(cin, input);

        if (input.empty()) {
            cout << "Input tidak boleh kosong. Masukkan angka 1-3: ";
        } else {
            bool isNumber = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            if (!isNumber) {
                cout << "Input harus berupa angka. Masukkan angka 1-3: ";
            } else {
                pilihan = stoi(input);
                if (pilihan >= 1 && pilihan <= 3) {
                    break; // Input valid, keluar dari loop
                } else {
                    cout << "Pilihan tidak valid. Masukkan angka 1-3: ";
                }
            }
        }
    }

    char arah;
    switch (pilihan) {
        case 1:
            cout << "Menampilkan tiket sesuai urutan saat ini (default atau setelah operasi terakhir).\n";
            break;

        case 2:
            do {
                cout << "Urutkan harga (a untuk Ascending / d untuk Descending): ";
                getline(cin, input);

                if (input.empty()) {
                    cout << "Input tidak boleh kosong. Masukkan 'a' atau 'd': ";
                } else if (input.length() > 1 || (tolower(input[0]) != 'a' && tolower(input[0]) != 'd')) {
                    cout << "Pilihan tidak valid. Masukkan 'a' atau 'd': ";
                } else {
                    arah = tolower(input[0]);
                }
            } while (arah != 'a' && arah != 'd');

            bubbleSortHarga(arah == 'a');
            cout << "Tiket diurutkan berdasarkan harga.\n";
            break;

        case 3:
            do {
                cout << "Urutkan nama (a untuk Ascending / d untuk Descending): ";
                getline(cin, input);

                if (input.empty()) {
                    cout << "Input tidak boleh kosong. Masukkan 'a' atau 'd': ";
                } else if (input.length() > 1 || (tolower(input[0]) != 'a' && tolower(input[0]) != 'd')) {
                    cout << "Pilihan tidak valid. Masukkan 'a' atau 'd': ";
                } else {
                    arah = tolower(input[0]);
                }
            } while (arah != 'a' && arah != 'd');

            insertionSortNama(arah == 'a');
            cout << "Tiket diurutkan berdasarkan nama.\n";
            break;
    }

    tampilkanTiketBox();
}

// --- FUNGSI PENCARIAN ---
int linearSearchID(int id) {
    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].id == id) return i;
    }
    return -1;
}

bool cekIDUnik(int id) {
    return linearSearchID(id) == -1;
}

// --- FUNGSI CRUD TIKET ---
void tambahTiket() {
    if (jumlahTiket >= MAX_TIKET) {
        cout << "Kapasitas tiket penuh! Tidak bisa menambah tiket lagi.\n";
        return;
    }

    Tiket &t = tiket[jumlahTiket];
    string input;

    cout << "\n=== TAMBAH TIKET BARU ===\n";

    // Input ID Tiket dengan validasi
    do {
        cout << "ID Tiket: ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input ID tidak boleh kosong. Harus angka positif. Coba lagi: ";
        } else {
            bool isNumber = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            if (!isNumber) {
                cout << "Input ID harus berupa angka. Coba lagi: ";
            } else {
                t.id = stoi(input);
                if (t.id <= 0) {
                    cout << "ID harus lebih besar dari 0. Coba lagi: ";
                } else if (!cekIDUnik(t.id)) {
                    cout << "ID Tiket " << t.id << " sudah ada. Masukkan ID unik: ";
                } else {
                    break; // Validasi berhasil
                }
            }
        }
    } while (true);

    // Input Nama Konser dengan validasi
    do {
        cout << "Nama Konser (tanpa simbol): ";
        getline(cin, t.namaKonser);

        if (t.namaKonser.empty()) {
            cout << "Nama konser tidak boleh kosong. Masukkan Nama Konser (tanpa simbol): ";
        } else if (isStringOnlyWhitespace(t.namaKonser)) {
            cout << "Nama konser tidak boleh hanya spasi. Masukkan Nama Konser (tanpa simbol): ";
        } else if (containsSymbol(t.namaKonser)) {
            cout << "Nama konser tidak boleh mengandung simbol. Masukkan Nama Konser (tanpa simbol): ";
        }
    } while (t.namaKonser.empty() || isStringOnlyWhitespace(t.namaKonser) || containsSymbol(t.namaKonser));

    int d, m, y;

    // Input Hari
    do {
        cout << "Tanggal Konser:\n";
        cout << "  Hari (1-31): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input hari tidak boleh kosong. Masukkan angka 1-31: ";
            continue;
        }

        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Input hari harus berupa angka. Masukkan angka 1-31: ";
        } else {
            d = stoi(input);
            if (d < 1 || d > 31) {
                cout << "Hari harus antara 1-31. Masukkan ulang: ";
            } else {
                break;
            }
        }
    } while (true);

    // Input Bulan
    do {
        cout << "  Bulan (1-12): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input bulan tidak boleh kosong. Masukkan angka 1-12: ";
            continue;
        }

        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Input bulan harus berupa angka. Masukkan angka 1-12: ";
        } else {
            m = stoi(input);
            if (m < 1 || m > 12) {
                cout << "Bulan harus antara 1-12. Masukkan ulang: ";
            } else {
                break;
            }
        }
    } while (true);

    const int TAHUN_MIN = 2024;
    const int TAHUN_MAX = 2050;

    // Input Tahun
    do {
        cout << "  Tahun (" << TAHUN_MIN << "-" << TAHUN_MAX << "): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input tahun tidak boleh kosong. Masukkan antara " << TAHUN_MIN << "-" << TAHUN_MAX << ": ";
            continue;
        }

        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Input tahun harus berupa angka. Masukkan antara " << TAHUN_MIN << "-" << TAHUN_MAX << ": ";
        } else {
            y = stoi(input);
            if (y < TAHUN_MIN || y > TAHUN_MAX) {
                cout << "Tahun harus antara " << TAHUN_MIN << "-" << TAHUN_MAX << ". Masukkan ulang: ";
            } else {
                break;
            }
        }
    } while (true);

    // Format tanggal
    t.tanggal = (d < 10 ? "0" : "") + to_string(d) + "/" +
                (m < 10 ? "0" : "") + to_string(m) + "/" +
                to_string(y);

    // Input Harga Tiket
    do {
        cout << "Harga Tiket (Rp): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input harga tidak boleh kosong. Harus angka positif lebih dari 0: Rp ";
        } else {
            bool isNumber = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            if (!isNumber) {
                cout << "Input harga harus berupa angka. Harus lebih dari 0: Rp ";
            } else {
                t.harga = stoi(input);
                if (t.harga <= 0) {
                    cout << "Harga harus lebih besar dari 0. Harus lebih dari 0: Rp ";
                } else {
                    break;
                }
            }
        }
    } while (true);

    jumlahTiket++;
    cout << "Tiket \"" << t.namaKonser << "\" berhasil ditambahkan.\n";
}

void updateTiket() {
    if (jumlahTiket == 0) {
        cout << "Belum ada tiket untuk diupdate.\n";
        return;
    }

    tampilkanTiketBox(); // Tampilkan daftar tiket
    string input;
    int id = -1;

    // Validasi input ID Tiket
    do {
        cout << "Masukkan ID tiket yang akan diupdate: ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input tidak boleh kosong. Masukkan ID tiket: ";
        } else {
            bool isNumber = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            if (!isNumber) {
                cout << "Input harus berupa angka. Masukkan ID tiket: ";
            } else {
                id = stoi(input);
                int index = linearSearchID(id);
                if (index == -1) {
                    cout << "ID tiket tidak ditemukan. Silakan coba lagi.\n";
                    id = -1; // Reset agar loop tetap jalan
                }
            }
        }
    } while (id == -1);

    int index = linearSearchID(id); // Cari ulang setelah validasi selesai

    // Tampilkan data lama
    cout << "\n--- Data Tiket Lama (ID: " << tiket[index].id << ") ---\n";
    cout << "Nama Konser: " << tiket[index].namaKonser << endl;
    cout << "Tanggal    : " << tiket[index].tanggal << endl;
    cout << "Harga (Rp) : " << tiket[index].harga << endl;
    cout << "\n--- Masukkan Data Baru (kosongkan jika tidak ingin diubah) ---\n";

    // Input Nama Konser Baru (tidak boleh kosong)
    do {
        cout << "Nama Konser baru (tanpa simbol): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Nama konser tidak boleh kosong. Silakan masukkan nama konser.\n";
        } else if (isStringOnlyWhitespace(input)) {
            cout << "Nama konser tidak boleh hanya spasi. Silakan masukkan nama konser yang valid.\n";
        } else if (containsSymbol(input)) {
            cout << "Nama konser tidak boleh mengandung simbol. Silakan masukkan nama konser yang valid.\n";
        } else {
            tiket[index].namaKonser = input;
            break;
        }
    } while (true); // Loop hingga input valid

    // Input Update Tanggal (tidak boleh kosong)
    char gantiTanggal;
    do {
        cout << "Update tanggal? (y/n): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input tidak boleh kosong. Masukkan 'y' atau 'n'.\n";
        } else if (input.length() > 1 || (tolower(input[0]) != 'y' && tolower(input[0]) != 'n')) {
            cout << "Pilihan tidak valid. Masukkan 'y' atau 'n'.\n";
        } else {
            gantiTanggal = tolower(input[0]);
        }
    } while (gantiTanggal != 'y' && gantiTanggal != 'n');

    if (gantiTanggal == 'y') {
        int d, m, y;
        const int TAHUN_MIN = 2024;
        const int TAHUN_MAX = 2050;

        // Input Hari
        do {
            cout << "  Tanggal baru (hari, 1-31): ";
            getline(cin, input);

            if (input.empty()) {
                cout << "Input hari tidak boleh kosong. Masukkan angka 1-31: ";
            } else {
                bool isNumber = true;
                for (char c : input) {
                    if (!isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }

                if (!isNumber) {
                    cout << "Input hari harus berupa angka. Masukkan angka 1-31: ";
                } else {
                    d = stoi(input);
                    if (d < 1 || d > 31) {
                        cout << "Hari harus antara 1-31. Masukkan ulang: ";
                    } else {
                        break;
                    }
                }
            }
        } while (true);

        // Input Bulan
        do {
            cout << "  Bulan baru (1-12): ";
            getline(cin, input);

            if (input.empty()) {
                cout << "Input bulan tidak boleh kosong. Masukkan angka 1-12: ";
            } else {
                bool isNumber = true;
                for (char c : input) {
                    if (!isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }

                if (!isNumber) {
                    cout << "Input bulan harus berupa angka. Masukkan angka 1-12: ";
                } else {
                    m = stoi(input);
                    if (m < 1 || m > 12) {
                        cout << "Bulan harus antara 1-12. Masukkan ulang: ";
                    } else {
                        break;
                    }
                }
            }
        } while (true);

        // Input Tahun
        do {
            cout << "  Tahun baru (" << TAHUN_MIN << "-" << TAHUN_MAX << "): ";
            getline(cin, input);

            if (input.empty()) {
                cout << "Input tahun tidak boleh kosong. Masukkan antara " << TAHUN_MIN << "-" << TAHUN_MAX << ": ";
            } else {
                bool isNumber = true;
                for (char c : input) {
                    if (!isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }

                if (!isNumber) {
                    cout << "Input tahun harus berupa angka. Masukkan antara " << TAHUN_MIN << "-" << TAHUN_MAX << ": ";
                } else {
                    y = stoi(input);
                    if (y < TAHUN_MIN || y > TAHUN_MAX) {
                        cout << "Tahun harus antara " << TAHUN_MIN << "-" << TAHUN_MAX << ". Masukkan ulang: ";
                    } else {
                        break;
                    }
                }
            }
        } while (true);

        // Update tanggal
        tiket[index].tanggal = (d < 10 ? "0" : "") + to_string(d) + "/" +
                               (m < 10 ? "0" : "") + to_string(m) + "/" +
                               to_string(y);
    }

    // Input Harga Baru (boleh kosong, tapi jika ada, harus valid)
    cout << "Harga baru (Rp) (masukkan angka positif atau biarkan kosong jika tidak ingin diubah): ";
    string hargaStr;
    getline(cin, hargaStr);

    if (!hargaStr.empty()) {
        try {
            int inputInt = stoi(hargaStr);
            if (inputInt > 0) {
                tiket[index].harga = inputInt;
            } else {
                cout << "Harga baru tidak valid (harus > 0), harga tidak diubah.\n";
            }
        } catch (...) {
            cout << "Input harga tidak valid (bukan angka), harga tidak diubah.\n";
        }
    }

    cout << "Tiket ID " << id << " berhasil diperbarui.\n";
}


void hapusTiket() {
    if (jumlahTiket == 0) {
        cout << "Belum ada tiket untuk dihapus.\n";
        return;
    }

    tampilkanTiketBox(); // Tampilkan daftar tiket

    string input;
    int id = -1;

    // Validasi input ID Tiket
    do {
        cout << "Masukkan ID tiket yang akan dihapus: ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input tidak boleh kosong. Masukkan ID tiket: ";
        } else {
            bool isNumber = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            if (!isNumber) {
                cout << "Input harus berupa angka. Masukkan ID tiket: ";
            } else {
                id = stoi(input);
                int index = linearSearchID(id);
                if (index == -1) {
                    cout << "ID tiket tidak ditemukan. Silakan coba lagi.\n";
                    id = -1; // Reset agar loop tetap jalan
                }
            }
        }
    } while (id == -1);

    int index = linearSearchID(id); // Cari ulang setelah validasi selesai

    char konfirmasi;
    do {
        cout << "Anda yakin ingin menghapus tiket \"" << tiket[index].namaKonser << "\"? (y/n): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input tidak boleh kosong. Masukkan 'y' atau 'n'.\n";
        } else if (input.length() > 1 || (tolower(input[0]) != 'y' && tolower(input[0]) != 'n')) {
            cout << "Pilihan tidak valid. Masukkan 'y' atau 'n'.\n";
        } else {
            konfirmasi = tolower(input[0]);
        }
    } while (konfirmasi != 'y' && konfirmasi != 'n');

    if (konfirmasi == 'y') {
        for (int j = index; j < jumlahTiket - 1; j++) {
            tiket[j] = tiket[j + 1];
        }
        jumlahTiket--;
        cout << "Tiket berhasil dihapus.\n";
    } else {
        cout << "Penghapusan tiket dibatalkan.\n";
    }
}

void laporanPenjualan() {
    if (jumlahPesanan == 0) {
        cout << "Belum ada transaksi penjualan.\n";
        return;
    }

    string namaKonserUnik[MAX_TIKET];
    int jumlahTerjual[MAX_TIKET] = {0};
    int uniqueCount = 0;

    for (int i = 0; i < jumlahPesanan; i++) {
        bool found = false;
        for (int j = 0; j < uniqueCount; j++) {
            if (riwayat[i].konser == namaKonserUnik[j]) {
                jumlahTerjual[j]++;
                found = true;
                break;
            }
        }
        if (!found && uniqueCount < MAX_TIKET) {
            namaKonserUnik[uniqueCount] = riwayat[i].konser;
            jumlahTerjual[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    char arahSort;
    cout << "Urutkan laporan berdasarkan jumlah tiket terjual (a untuk Ascending / d untuk Descending): ";
    cin >> arahSort;
    arahSort = tolower(arahSort);
    while (arahSort != 'a' && arahSort != 'd') {
        cout << "Pilihan tidak valid. Masukkan 'a' atau 'd': ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> arahSort;
        arahSort = tolower(arahSort);
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < uniqueCount - 1; i++) {
        for (int j = 0; j < uniqueCount - i - 1; j++) {
            bool kondisiSort = (arahSort == 'a') ? (jumlahTerjual[j] > jumlahTerjual[j + 1]) : (jumlahTerjual[j] < jumlahTerjual[j + 1]);
            if (kondisiSort) {
                swap(jumlahTerjual[j], jumlahTerjual[j + 1]);
                swap(namaKonserUnik[j], namaKonserUnik[j + 1]);
            }
        }
    }

    cout << "\n=== LAPORAN PENJUALAN TIKET ===\n";
    cout << "+----------------------+----------------+\n";
    cout << "| Nama Konser          | Tiket Terjual  |\n";
    cout << "+----------------------+----------------+\n";
    for (int i = 0; i < uniqueCount; i++) {
        cout << "| " << setw(20) << left << namaKonserUnik[i] << right
             << " | " << setw(14) << jumlahTerjual[i] << " |\n";
    }
    cout << "+----------------------+----------------+\n";
}

// --- MENU ADMIN ---
void menuAdmin() {
    string input;
    int pilihan;
    do {
        system("cls");
        cout << "\n====== MENU ADMIN ======\n";
        cout << "1. Lihat Tiket\n";
        cout << "2. Tambah Tiket\n";
        cout << "3. Update Tiket\n";
        cout << "4. Hapus Tiket\n";
        cout << "5. Laporan Penjualan\n";
        cout << "0. Logout\n";
        cout << "------------------------\n";
        cout << "Pilihan Anda: ";
        
        getline(cin, input); // Baca input sebagai string

        if (input.empty()) {
            cout << "Input tidak boleh kosong. Silakan masukkan pilihan Anda (0-5).\n";
            cout << "Tekan tombol apapun untuk coba lagi...";
            getch();
            continue;
        }

        // Cek apakah input adalah angka
        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Input harus berupa angka. Silakan coba lagi.\n";
            cout << "Tekan tombol apapun untuk coba lagi...";
            getch();
            continue;
        }

        pilihan = stoi(input);

        if (pilihan < 0 || pilihan > 5) {
            cout << "Pilihan tidak valid. Masukkan angka antara 0 hingga 5.\n";
            cout << "Tekan tombol apapun untuk coba lagi...";
            getch();
            continue;
        }

        system("cls");

        switch (pilihan) {
            case 1: tampilkanTiketDenganPilihanUrutan(); break;
            case 2: tambahTiket(); break;
            case 3: updateTiket(); break;
            case 4: hapusTiket(); break;
            case 5: laporanPenjualan(); break;
            case 0: cout << "Logout dari akun Admin berhasil.\n"; break;
            default: cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

        if (pilihan != 0) {
            cout << "\nTekan tombol apapun untuk kembali ke Menu Admin...";
            getch();
        }

    } while (pilihan != 0);
}
void pesanTiket();
void lihatRiwayat();

// --- MENU USER ---
void menuUser() {
    int pilih;
    do {
        system("cls");
        cout << "\n====== MENU USER ======\n";
        cout << "1. Lihat Tiket\n";
        cout << "2. Cari & Pesan Tiket\n";
        cout << "3. Riwayat Pemesanan\n";
        cout << "0. Logout\n";
        cout << "-----------------------\n";
        cout << "Pilihan Anda: ";
        cin >> pilih;
        while(cin.fail()) {
            cout << "Pilihan tidak valid. Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> pilih;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");
        switch (pilih) {
            case 1: tampilkanTiketDenganPilihanUrutan(); break;
            case 2: pesanTiket(); break;
            case 3: lihatRiwayat(); break;
            case 0: cout << "Logout dari akun User berhasil.\n"; break;
            default: cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
        if (pilih != 0) {
            cout << "\nTekan tombol apapun untuk kembali ke Menu User...";
            getch();
        }
    } while (pilih != 0);
}

// --- FUNGSI PESAN TIKET (USER) ---
void pesanTiket() {
    if (jumlahTiket == 0) {
        cout << "\nMaaf, tidak ada tiket yang tersedia saat ini.\n";
        return;
    }

    insertionSortNama(true);
    string keyword = "";
    char ch;

    do {
        system("cls");
        cout << "=== CARI & PESAN TIKET ===\n";
        cout << "Ketik nama konser (Live Search, ESC = batal/kembali): " << keyword;
        cout << " " << "\b"; // Untuk memastikan kursor terlihat setelah teks

        int hasilIndex[MAX_TIKET];
        int jumlahHasil = 0;

        cout << "\n+-----+----------------------+---------------+------------+\n";
        cout << "| ID  | Nama Konser          | Tanggal       | Harga (Rp) |\n";
        cout << "+-----+----------------------+---------------+------------+\n";

        string lowerKeyword = toLower(keyword);

        if (keyword.empty()) {
            for (int i = 0; i < jumlahTiket; i++) {
                cout << "| " << setw(3) << tiket[i].id << " | "
                     << setw(20) << left << tiket[i].namaKonser << right << " | "
                     << setw(13) << tiket[i].tanggal << " | "
                     << setw(10) << tiket[i].harga << " |\n";
                hasilIndex[jumlahHasil++] = i;
            }
        } else {
            for (int i = 0; i < jumlahTiket; i++) {
                string lowerNama = toLower(tiket[i].namaKonser);
                if (lowerNama.find(lowerKeyword) != string::npos) {
                    cout << "| " << setw(3) << tiket[i].id << " | "
                         << setw(20) << left << tiket[i].namaKonser << right << " | "
                         << setw(13) << tiket[i].tanggal << " | "
                         << setw(10) << tiket[i].harga << " |\n";
                    hasilIndex[jumlahHasil++] = i;
                }
            }
        }

        cout << "+-----+----------------------+---------------+------------+\n";

        if (jumlahHasil == 0 && !keyword.empty()) {
            cout << "Tidak ada tiket yang cocok dengan \"" << keyword << "\".\n";
        } else if (jumlahHasil == 0 && keyword.empty() && jumlahTiket > 0) {
            cout << "Ketikkan nama konser untuk mencari...\n";
        } else if (jumlahTiket == 0 && jumlahHasil == 0) {
            cout << "|                     TIDAK ADA TIKET TERSEDIA                     |\n";
            cout << "+-----+----------------------+---------------+------------+\n";
        }

        cout << "\nKetik untuk mencari, ENTER untuk memilih ID dari daftar di atas, atau ESC untuk kembali.\n";

        ch = getch();
        if ((int)ch == 27) { // ESC
            cout << "\nPencarian dan pemesanan dibatalkan/kembali ke menu.\n";
            return;
        } else if (ch == '\b') { // Backspace
            if (!keyword.empty()) {
                keyword.resize(keyword.length() - 1);
            }
        } else if (ch == '\r') { // Enter
            if (jumlahHasil > 0) {
                string input;
                int idPilih;
                bool valid = false;

                // Input ID Tiket dengan validasi
                while (!valid) {
                    cout << "Masukkan ID tiket yang ingin dipesan dari daftar di atas: ";
                    getline(cin, input);

                    if (input.empty()) {
                        cout << "Input tidak boleh kosong. Silakan masukkan ID tiket.\n";
                    } else {
                        bool isNumber = true;
                        for (char c : input) {
                            if (!isdigit(c)) {
                                isNumber = false;
                                break;
                            }
                        }

                        if (!isNumber) {
                            cout << "Input harus berupa angka. Silakan coba lagi.\n";
                        } else {
                            idPilih = stoi(input);
                            valid = true;
                        }
                    }
                }

                int indexTiketDiArray = -1;
                for (int i = 0; i < jumlahHasil; ++i) {
                    if (tiket[hasilIndex[i]].id == idPilih) {
                        indexTiketDiArray = hasilIndex[i];
                        break;
                    }
                }

                if (indexTiketDiArray != -1) {
                    char konfirmasi;
                    string jawaban;

                    // Validasi konfirmasi y/n
                    do {
                        cout << "\nPesan tiket \"" << tiket[indexTiketDiArray].namaKonser
                             << "\" seharga Rp " << tiket[indexTiketDiArray].harga << "? (y/n): ";
                        getline(cin, jawaban);

                        if (jawaban.empty()) {
                            cout << "Input tidak boleh kosong. Masukkan 'y' atau 'n'.\n";
                        } else if (jawaban.length() > 1 || (tolower(jawaban[0]) != 'y' && tolower(jawaban[0]) != 'n')) {
                            cout << "Pilihan tidak valid. Masukkan 'y' atau 'n'.\n";
                        } else {
                            konfirmasi = tolower(jawaban[0]);
                        }
                    } while (konfirmasi != 'y' && konfirmasi != 'n');

                    if (konfirmasi == 'y') {
                        if (jumlahPesanan < MAX_PESANAN) {
                            riwayat[jumlahPesanan].konser = tiket[indexTiketDiArray].namaKonser;
                            riwayat[jumlahPesanan].harga = tiket[indexTiketDiArray].harga;
                            jumlahPesanan++;
                            cout << "Tiket \"" << tiket[indexTiketDiArray].namaKonser << "\" berhasil dipesan!\n";
                        } else {
                            cout << "Riwayat pesanan penuh, tidak bisa memesan lagi.\n";
                        }
                    } else {
                        cout << "Pesanan dibatalkan.\n";
                    }
                } else {
                    cout << "ID tiket " << idPilih << " tidak valid atau tidak ada dalam daftar hasil pencarian.\n";
                }

                cout << "Tekan tombol apapun untuk melanjutkan...";
                getch();
                return;

            } else {
                cout << "Tidak ada tiket untuk dipilih.\n";
                if (jumlahTiket == 0) {
                    cout << "Tekan tombol apapun untuk kembali..."; getch();
                    return;
                }
                cout << "Tekan tombol apapun untuk mencoba lagi..."; getch();
            }
        } else if (isprint(ch)) {
            if (keyword.length() < 50) {
                keyword += ch;
            }
        }
    } while (true);
}

// --- FUNGSI LIHAT RIWAYAT (USER) ---
void lihatRiwayat() {
    cout << "\n=== RIWAYAT PEMESANAN ANDA ===\n";
    if (jumlahPesanan == 0) {
        cout << "Anda belum memiliki riwayat pemesanan.\n";
        return;
    }
    cout << "+----+----------------------+------------+\n";
    cout << "| No | Nama Konser          | Harga (Rp) |\n";
    cout << "+----+----------------------+------------+\n";
    long long totalPembelian = 0;
    for (int i = 0; i < jumlahPesanan; i++) {
        cout << "| " << setw(2) << i + 1 << " | "
             << setw(20) << left << riwayat[i].konser << right << " | "
             << setw(10) << riwayat[i].harga << " |\n";
        totalPembelian += riwayat[i].harga;
    }
    cout << "+----+----------------------+------------+\n";
    cout << "|    | Total Pembelian Anda | " << setw(10) << totalPembelian << " |\n";
    cout << "+----+----------------------+------------+\n";
}

// --- FUNGSI AUTHENTIKASI & REGISTRASI ---

// Fungsi input password yang dimodifikasi
// defaultMasked: true jika password awalnya disembunyikan, false jika awalnya terlihat
string inputPassword(bool defaultMasked = true) {
    string pass = "";
    char ch;
    bool maskPassword = defaultMasked; // Status masking saat ini

    while (true) {
        ch = getch();

        if (ch == '\r') { // Tombol Enter
            break;
        }
        if (ch == 0 || ch == -32) { // Tombol panah atau fungsi khusus (biasanya dua karakter)
            getch(); // Baca karakter kedua dari special key dan abaikan
            continue;
        }
        if (ch == '\t') { // Tombol TAB untuk toggle visibilitas
            maskPassword = !maskPassword;
            // Hapus password yang sudah tertampil dan tampilkan ulang sesuai mode baru
            for (int i = 0; i < pass.length(); ++i) {
                cout << "\b \b"; // Mundur, spasi (hapus), mundur lagi
            }
            for (char c_pass : pass) {
                cout << (maskPassword ? '*' : c_pass);
            }
            continue; // Lanjutkan loop tanpa memproses TAB sebagai bagian password
        }

        if (ch == '\b') { // Tombol Backspace
            if (!pass.empty()) {
                pass.resize(pass.length() - 1);
                cout << "\b \b"; // Hapus karakter dari layar
            }
        } else if (isprint(ch) && ch != ' ') { // Hanya proses karakter cetak dan BUKAN SPASI
            if (pass.length() < 50) { // Batasi panjang password
                pass += ch;
                cout << (maskPassword ? '*' : ch); // Tampilkan '*' atau karakter asli
            }
        } else if (ch == ' ') {
            // Abaikan spasi, jangan tambahkan ke password
        }
    }
    cout << endl;
    return pass;
}


bool loginUser() {
    string user, pass;
    int loginAttempts = 0;
    const int MAX_LOGIN_ATTEMPTS = 3;
    const string ADMIN_USER = "admin";
    const string ADMIN_PASS = "admin123";

    while (loginAttempts < MAX_LOGIN_ATTEMPTS) {
        system("cls");
        cout << "\n--- LOGIN PENGGUNA ---\n";

        // Input Username
        cout << "Username: ";
        getline(cin, user); // Tanpa ws, baca langsung

        if (user.empty()) {
            cout << "Username tidak boleh kosong.\n";
        } else if (isStringOnlyWhitespace(user)) {
            cout << "Username tidak boleh hanya terdiri dari spasi.\n";
        } else if (containsSpace(user)) {
            cout << "Username tidak boleh mengandung spasi.\n";
        } else {
            // Input Password
            cout << "Password (tanpa spasi, TAB untuk tampilkan/sembunyikan): ";
            pass = inputPassword(true); // Password disembunyikan secara default

            if (pass.empty()) {
                cout << "Password tidak boleh kosong.\n";
            } else if (user == ADMIN_USER && pass == ADMIN_PASS) {
                cout << "\nLogin sebagai Admin berhasil!\n";
                cout << "Selamat datang, " << ADMIN_USER << ".\n";
                cout << "Tekan tombol apapun untuk masuk ke Menu Admin...";
                getch();
                menuAdmin();
                return true;
            } else {
                bool userFound = false;
                for (int i = 0; i < jumlahUser; i++) {
                    if (users[i].username == user && users[i].password == pass) {
                        cout << "\nLogin berhasil!\n";
                        cout << "Selamat datang, " << users[i].username << ".\n";
                        cout << "Tekan tombol apapun untuk masuk ke Menu User...";
                        getch();
                        menuUser();
                        return true;
                    }
                }
                cout << "\nLogin gagal. Username atau password salah.\n";
            }
        }

        // Hitung percobaan login
        loginAttempts++;
        if (loginAttempts < MAX_LOGIN_ATTEMPTS) {
            cout << "Sisa percobaan: " << MAX_LOGIN_ATTEMPTS - loginAttempts << ".\n";
            cout << "Tekan tombol apapun untuk mencoba lagi...";
            getch();
        } else {
            cout << "Anda telah gagal login sebanyak " << MAX_LOGIN_ATTEMPTS << " kali.\n";
            cout << "Kembali ke menu utama.\n";
            cout << "Tekan tombol apapun...";
            getch();
        }
    }

    return false;
}
void registerUser() {
    if (jumlahUser >= MAX_USER) {
        cout << "Kapasitas slot user penuh! Tidak bisa mendaftar lagi.\n";
        return;
    }

    string newUser, newPass, confirmPass;

    system("cls");
    cout << "\n--- REGISTRASI USER BARU ---\n";
    cout << "Ketentuan:\n";
    cout << " - Username: min 3 karakter, tanpa spasi, tidak boleh hanya spasi.\n";
    cout << " - Password: min 5 karakter, tanpa spasi, tidak boleh kosong.\n\n";

    // Input Username dengan validasi
    do {
        cout << "Buat Username: ";
        getline(cin, newUser); // Menggunakan getline agar bisa baca input kosong

        if (newUser.empty()) {
            cout << "Username tidak boleh kosong. Silakan coba lagi.\n";
        } else if (isStringOnlyWhitespace(newUser)) {
            cout << "Username tidak boleh hanya terdiri dari spasi. Silakan coba lagi.\n";
        } else if (containsSpace(newUser)) {
            cout << "Username tidak boleh mengandung spasi. Silakan coba lagi.\n";
        } else if (newUser.length() < 3) {
            cout << "Username terlalu pendek. Minimal 3 karakter. Silakan coba lagi.\n";
        } else if (toLower(newUser) == "admin") {
            cout << "Username 'admin' tidak diizinkan. Silakan coba lagi.\n";
        } else {
            bool duplikat = false;
            for (int i = 0; i < jumlahUser; i++) {
                if (toLower(users[i].username) == toLower(newUser)) {
                    duplikat = true;
                    break;
                }
            }
            if (duplikat) {
                cout << "Username \"" << newUser << "\" sudah digunakan. Silakan coba lagi.\n";
            } else {
                break; // Keluar dari loop jika semua valid
            }
        }
    } while (true);

    // Input Password dengan validasi
    do {
        cout << "Buat Password (TAB untuk tampilkan/sembunyikan): ";
        newPass = inputPassword(true); // Defaultnya password disembunyikan

        if (newPass.empty()) {
            cout << "Password tidak boleh kosong. Silakan coba lagi.\n";
        } else if (newPass.length() < 5) {
            cout << "Password terlalu pendek. Minimal 5 karakter. Silakan coba lagi.\n";
        } else {
            break; // Keluar dari loop jika valid
        }
    } while (true);

    // Konfirmasi Password
    do {
        cout << "Konfirmasi Password (TAB untuk tampilkan/sembunyikan): ";
        confirmPass = inputPassword(true); // Defaultnya password disembunyikan

        if (confirmPass.empty()) {
            cout << "Password konfirmasi tidak boleh kosong. Silakan coba lagi.\n";
        } else if (newPass != confirmPass) {
            cout << "Password tidak cocok. Silakan coba lagi.\n";
        } else {
            break; // Keluar dari loop jika valid
        }
    } while (true);

    // Simpan user baru
    users[jumlahUser].username = newUser;
    users[jumlahUser].password = newPass;
    jumlahUser++;

    cout << "\nRegistrasi berhasil! Selamat datang, " << newUser << ".\n";
    cout << "Silakan login untuk melanjutkan.\n";
}

// --- FUNGSI UTAMA (MAIN) ---
int main() {
    string input;
    int pilih;

    do {
        system("cls");
        cout << "\n====== SISTEM BOOKING TIKET KONSER ======";
        cout << "\n                 SELAMAT DATANG             ";
        cout << "\n===========================================";
        cout << "\n1. Login";
        cout << "\n2. Register";
        cout << "\n0. Keluar";
        cout << "\n-------------------------------------------";
        cout << "\nPilih Menu: ";

        getline(cin, input);

        if (input.empty()) {
            cout << "Input tidak boleh kosong. Silakan masukkan pilihan Anda (0/1/2).";
            cout << "\nTekan tombol apapun untuk coba lagi...";
            getch();
            continue; // Ulangi loop jika input kosong
        }

        // Cek apakah input adalah angka
        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Input harus berupa angka. Silakan coba lagi.";
            cout << "\nTekan tombol apapun untuk coba lagi...";
            getch();
            continue; // Ulangi loop jika input bukan angka
        }

        pilih = stoi(input);

        switch (pilih) {
            case 1:
                loginUser();
                break;
            case 2:
                registerUser();
                cout << "\nTekan tombol apapun untuk kembali ke Menu Utama...";
                getch();
                break;
            case 0:
                system("cls");
                cout << "Terima kasih telah menggunakan sistem ini!\n";
                cout << "Program akan keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                cout << "Tekan tombol apapun untuk kembali ke Menu Utama...";
                getch();
        }
    } while (pilih != 0);

    return 0;
}