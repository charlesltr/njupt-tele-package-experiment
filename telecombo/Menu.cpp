#include <iostream>
#include "Menu.h"

// 打印管理员菜单
void printAdminMenu() {
    std::cout << "-------------------------------------\n";
    std::cout << "Admin Menu:\n";
    std::cout << "-------------------------------------\n";
    std::cout << "1. Add Package\n";
    std::cout << "2. Remove Package\n";
    std::cout << "3. Update Package\n";
    std::cout << "4. View All Packages\n";
    std::cout << "5. View Users and Packages\n";
    std::cout << "6. Delete User Account\n";
    std::cout << "0. Logout\n";
    std::cout << "-------------------------------------\n";
}

// 打印主菜单
void printMainMenu() {
    system("cls");
    std::cout << "Welcome to package system!\n" ;
    std::cout << "-------------------------------------\n";
    std::cout << "Main Menu:\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register as User\n";
    std::cout << "0. Exit\n";
    std::cout << "-------------------------------------\n";
    std::cout << "Enter your choice:\n ";

}

// 打印用户菜单
void printUserMenu() {
    std::cout << "-------------------------------------\n";
    std::cout << "User Menu:\n";
    std::cout << "-------------------------------------\n";
    std::cout << "1. Find Package by Requirements\n";
    std::cout << "2. View Package by ID\n";
    std::cout << "3. View Current Subscription\n";
    std::cout << "4. Change Password\n";
    std::cout << "0. Logout\n";
    std::cout << "Enter your choice: \n";
    std::cout << "-------------------------------------\n";
}
