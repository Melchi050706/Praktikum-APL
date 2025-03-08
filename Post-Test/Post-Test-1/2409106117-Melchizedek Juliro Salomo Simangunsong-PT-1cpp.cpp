#include <iostream>
#include <cmath>
#include <string>

using namespace std;

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

bool isValidCode(int num) {
    return (num % 2 == 0 && num % 3 == 0 && num % 5 != 0);
}

bool isPalindrome(int num) {
    int originalNum = num;
    int reversedNum = 0;
    
    while (num > 0) {
        int digit = num % 10;
        reversedNum = reversedNum * 10 + digit;
        num /= 10;
    }
    
    return originalNum == reversedNum;
}

bool login() {
    string username, password;
    while (true) {
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;
        
        if (username == "1" && password == "1") {
            cout << "Berhasil login\n";
            return true;
        } else {
            cout << "Gagal login. Password atau username yang Anda masukkan salah. Silakan coba lagi.\n";
        }
    }
}

int main() {
    if (!login()) return 0;
    
    int kodeSandi;
    do {
        cout << "Masukkan kode sandi (harus lebih dari 100 dan tidak lebih dari 99999): ";
        cin >> kodeSandi;
    } while (kodeSandi <= 100 || kodeSandi > 99999);
    
    int pilihan;
    do {
        cout << "\n=== MENU ===\n1. Cek bilangan prima\n2. Cek habis dibagi 2 & 3, tidak 5\n3. Cek palindrome\n4. Keluar\nPilihan: ";
        cin >> pilihan;
        
        if (pilihan == 1) cout << (isPrime(kodeSandi) ? "Kode sandi adalah bilangan prima.\n" : "Bukan bilangan prima.\n");
        else if (pilihan == 2) cout << (isValidCode(kodeSandi) ? "Kode sandi memenuhi syarat.\n" : "Tidak memenuhi syarat.\n");
        else if (pilihan == 3) cout << (isPalindrome(kodeSandi) ? "Kode sandi adalah palindrome.\n" : "Bukan palindrome.\n");
        else if (pilihan != 4) cout << "Pilihan tidak valid.\n";
    } while (pilihan != 4);
    
    cout << "Terima kasih!";
    return 0;
}

// test