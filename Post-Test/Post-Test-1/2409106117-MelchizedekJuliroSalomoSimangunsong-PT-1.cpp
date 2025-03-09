#include <iostream>
using namespace std;

int main() {
    string username, password;
    while (true) {
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;
        
        if (username == "Melchizedek" && password == "2409106117") {
            cout << "Berhasil login\n";
            break;
        } else {
            cout << "Gagal login. Password atau username yang Anda masukkan salah. Silakan coba lagi.\n";
        }
    }
    
    int kodeSandi;
    do {
        cout << "Masukkan kode sandi (harus lebih dari 100 dan tidak lebih dari 99999): ";
        cin >> kodeSandi;
        if (kodeSandi <= 100 || kodeSandi > 99999) {
            cout << "Kata sandi tidak boleh kurang dari 100 dan tidak boleh lebih dari 99999.\n";
        }
    } while (kodeSandi <= 100 || kodeSandi > 99999);
    
    int pilihan;
    do {
        cout << "\n=== MENU ===\n1. Cek bilangan prima\n2. Cek habis dibagi 2 & 3, tidak 5\n3. Cek palindrome\n4. Keluar\nPilihan: ";
        cin >> pilihan;
        
        if (pilihan == 1) {
            bool prima = true;
            if (kodeSandi < 2) prima = false;
            for (int i = 2; i * i <= kodeSandi; i++) {
                if (kodeSandi % i == 0) {
                    prima = false;
                    break;
                }
            }
            cout << (prima ? "Kode sandi adalah bilangan prima.\n" : "Bukan bilangan prima.\n");
        } 
        else if (pilihan == 2) {
            if (kodeSandi % 2 == 0 && kodeSandi % 3 == 0 && kodeSandi % 5 != 0) {
                cout << "Kode sandi memenuhi syarat.\n";
            } else {
                cout << "Kode sandi tidak memenuhi syarat.\n";
            }
        } 
        else if (pilihan == 3) {
            int originalNum = kodeSandi, reversedNum = 0;
            while (originalNum > 0) {
                reversedNum = reversedNum * 10 + (originalNum % 10);
                originalNum /= 10;
            }
            cout << (reversedNum == kodeSandi ? "Kode sandi adalah palindrome.\n" : "Bukan palindrome.\n");
        } 
        else if (pilihan != 4) {
            cout << "Pilihan cuma ada nomor 1-4.\n";
        }
    } while (pilihan != 4);
    
    cout << "Terima kasih!";
    return 0;
}
