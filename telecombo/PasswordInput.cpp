#include <iostream>
#include <string>
#include <conio.h> 

std::string getPassword() {
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') {  
        if (ch == '\b') {  // 处理退格键
            if (!password.empty()) {
                std::cout << "\b \b";  // 删除星号
                password.pop_back();   // 删除密码中的一个字符
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
