#include <iostream>
#include <string>
#include <conio.h> 

std::string getPassword() {
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') {  
        if (ch == '\b') {  // �����˸��
            if (!password.empty()) {
                std::cout << "\b \b";  // ɾ���Ǻ�
                password.pop_back();   // ɾ�������е�һ���ַ�
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}
