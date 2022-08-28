#include "LoginManger.h"

LoginManger::LoginManger() {
        accessGranted = 0;
}

void LoginManger::login() {
    cout << "Masukkan username dan password .\nUsername & Password\n";
    cin >> userNameAttempt;
    cin >> passWordAttempt;
    if (userNameAttempt == userName && passWordAttempt == passWord) {
        cout << "Benar Mantap!!!!.";
    }
    else
    {
        cout << "Coba Lagi!";
    }
}
