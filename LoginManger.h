#pragma once
#include <iostream>
#include <string>

using namespace std;

class LoginManger
{
public:
  
    string userNameAttempt;
    string passWordAttempt;

    LoginManger();
    void login();

private:
    string passWord = "masuk123";
    string userName = "user@email.com";
    bool accessGranted;
};


