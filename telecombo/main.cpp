#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <conio.h>
#include <iomanip>
#include "User.h"
#include "Admin.h"
#include "Package.h"
#include "PasswordInput.h"
#include "Menu.h"

// 文件名常量
const std::string USERS_FILE = "users.dll";
const std::string PACKAGES_FILE = "packages.dll";

// 初始化文件
void initializeFiles() {
    // 检查并创建 users.dll
    std::ifstream usersFile(USERS_FILE);
    if (!usersFile.is_open()) {
        std::ofstream createUsersFile(USERS_FILE);
        if (createUsersFile.is_open()) {
            std::cout << "Created file: " << USERS_FILE << std::endl;
            createUsersFile.close();
        }
        else {
            std::cerr << "Failed to create file: " << USERS_FILE << std::endl;
        }
    }
    usersFile.close();

    // 检查并创建 packages.dll
    std::ifstream packagesFile(PACKAGES_FILE);
    if (!packagesFile.is_open()) {
        // 文件不存在则创建文件并写入初始数据
        std::ofstream createPackagesFile(PACKAGES_FILE);
        if (createPackagesFile.is_open()) {
            std::cout << "Created file: " << PACKAGES_FILE << std::endl;
            createPackagesFile << "10 30.0 60 15.0 100" << std::endl;
            createPackagesFile << "11 19.9 10 120.0 100" << std::endl;
            std::cout << "Added initial packages to new file: " << PACKAGES_FILE << std::endl;
            createPackagesFile.close();
        }
        else {
            std::cerr << "Failed to create file: " << PACKAGES_FILE << std::endl;
        }
    }
    else {
        // 如果文件存在，检查文件是否为空
        packagesFile.seekg(0, std::ios::end); // 移到文件末尾
        if (packagesFile.tellg() == 0) { // 检查文件大小
            packagesFile.close(); // 关闭读取文件流
            std::ofstream createPackagesFile(PACKAGES_FILE);
            if (createPackagesFile.is_open()) {
                // 添加初始套餐数据
                createPackagesFile << "10 30.0 60 15.0 100" << std::endl;
                createPackagesFile << "11 19.9 10 120.0 100" << std::endl;
                std::cout << "Added initial packages to empty file: " << PACKAGES_FILE << std::endl;
                createPackagesFile.close();
            }
        }
        else {
            std::cout << "Packages file already has data. Skipping initial package addition." << std::endl;
        }
    }
    packagesFile.close();

}

// 从文件加载用户
std::vector<User> loadUsers() {
    std::vector<User> users;
    std::ifstream file(USERS_FILE);
    if (file.is_open()) {
        std::string username, password;
        while (file >> username >> password) {
            users.emplace_back(username, password);
        }
        file.close();
    }
    return users;
}

// 保存用户到文件
void saveUsers(const std::vector<User>& users) {
    std::ofstream file(USERS_FILE);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.getUsername() << " " << user.getPassword() << std::endl;
        }
        file.close();
    }
}

// 从文件加载套餐
std::vector<Package> loadPackages() {
    std::vector<Package> packages;
    std::ifstream file(PACKAGES_FILE);
    if (file.is_open()) {
        int id, callMinutes;
        double fee, data, bandwidth;
        while (file >> id >> fee >> callMinutes >> data >> bandwidth) {
            packages.emplace_back(id, fee, callMinutes, data, bandwidth);
        }
        file.close();
    }
    return packages;
}

// 注册新用户
void registerUser(std::vector<User>& users) {
    std::string username, password;
    system("cls");
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "-------------------------------------\n";
    std::cout << "Enter password: ";
    password = getPassword();  // 使用 getPassword 函数获取密码


    // 检查用户名是否已经存在
    if (std::any_of(users.begin(), users.end(), [&username](const User& user) { return user.getUsername() == username; })) {
        std::cout << "Username already exists. Please choose another one.\n";
    }
    else {
        users.emplace_back(username, password);
        saveUsers(users);
        std::cout << "User registered successfully.\n";
    }
}

// 保存套餐到文件
void savePackages(const std::vector<Package>& packages) {
    std::ofstream file(PACKAGES_FILE);
    if (file.is_open()) {
        for (const auto& pkg : packages) {
            file << pkg.getId() << " " << pkg.getFee() << " "
                << pkg.getCallMinutes() << " " << pkg.getData() << " "
                << pkg.getBandwidth() << std::endl;
        }
        file.close();
    }
}



void adminFunctions(Admin& admin, std::vector<User>& users) {
    int choice;
    do {
        printAdminMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            double fee;
            int callMinutes;
            double data;
            double bandwidth;
            std::cout << "-------------------------------------\n";
            std::cout << "Enter package details \n(id fee callMinutes data bandwidth\n): ";
            std::cin >> id >> fee >> callMinutes >> data >> bandwidth;

            // 检查是否存在具有相同 ID 的套餐
            const auto& packages = admin.getAllPackages();
            auto it = std::find_if(packages.begin(), packages.end(), [id](const Package& pkg) {
                return pkg.getId() == id;
                });

            if (it != packages.end()) {
                std::cout << "-------------------------------------\n";
                std::cout << "Package with ID " << id << " already exists.\n";
                std::cout << "Returning to previous menu.\n";
            }
            else {
                admin.addPackage(Package(id, fee, callMinutes, data, bandwidth));
                savePackages(admin.getAllPackages());
                std::cout << "-------------------------------------\n";
                std::cout << "Package added successfully.\n";
            }
            break;
        }
        case 2: {
            int id;
            std::cout << "-------------------------------------\n";
            std::cout << "Enter package id to remove: ";
            std::cin >> id;
            admin.removePackage(id);
            savePackages(admin.getAllPackages());
            std::cout << "-------------------------------------\n";
            std::cout << "Package removed successfully.\n";
            break;
        }
        case 3: {
            int id;
            double fee;
            int callMinutes;
            double data;
            double bandwidth;
            std::cout << "-------------------------------------\n";
            std::cout << "Enter updated package details (id fee callMinutes data bandwidth): ";
            std::cout << "-------------------------------------\n";
            std::cin >> id >> fee >> callMinutes >> data >> bandwidth;
            admin.updatePackage(id, Package(id, fee, callMinutes, data, bandwidth));
            savePackages(admin.getAllPackages());
            std::cout << "-------------------------------------\n";
            std::cout << "Package updated successfully.\n";
            std::cout << "-------------------------------------\n";
            break;
        }
        case 4: {
            std::cout << "All Packages:\n";
            std::cout << "-------------------------------------\n";
            for (const auto& pkg : admin.getAllPackages()) {
                std::cout << "ID: " << pkg.getId()
                    << ", Fee: " << pkg.getFee()
                    << ", Call Minutes: " << pkg.getCallMinutes()
                    << ", Data: " << pkg.getData()
                    << ", Bandwidth: " << pkg.getBandwidth() << '\n';
                std::cout << "-------------------------------------\n";
            }
            break;
        }
        case 5: {
            std::cout << "-------------------------------------\n";
            std::cout << "Users' Package Data:\n";
            std::cout << "-------------------------------------\n";
            for (const auto& user : users) {
                std::cout << "Username: " << user.getUsername()
                    << ", Package ID: " << user.getCurrentPackage().getId() << '\n';
            }
            std::cout << "-------------------------------------\n";
            break;
        }
        case 6: {
            std::string username;
            std::cout << "-------------------------------------\n";
            std::cout << "Enter username to delete: ";
            std::cin >> username;
            admin.deleteUser(users, username);
            std::cout << "-------------------------------------\n";
            std::cout << "User deleted successfully.\n";
            break;
        }
        case 0:
            system("cls");
            std::cout << "Logging out...\n";   
            std::cout << "-------------------------------------\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cout << "-------------------------------------\n";
        }
    } while (choice != 0);
}

// 主函数
void adminFunctions(Admin& admin, std::vector<User>& users);
void registerUser(std::vector<User>& users);
void saveUsers(const std::vector<User>& users);

int main() {
    // 初始化文件
    initializeFiles();
    Admin admin("admin", "adminpass");

    // 加载用户和套餐数据
    std::vector<User> users = loadUsers();
    std::vector<Package> packages = loadPackages();


    for (const auto& pkg : packages) {
        admin.addPackage(pkg);
    }

    int mainChoice;
    do {
        printMainMenu();
        std::cin >> mainChoice;

        if (mainChoice == 1) {
            system("cls");
            std::string username, password;
            std::cout << "-------------------------------------\n";
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "\n-------------------------------------\n";
            std::cout << "Enter password: ";
            password = getPassword();  // 使用自定义函数获取密码
            
            if (username == "admin" && admin.login(password)) {
                system("cls");
                std::cout << "Logged in as Admin\n";
                adminFunctions(admin, users);
            }
            else {
                auto it = std::find_if(users.begin(), users.end(), [&username](const User& user) {
                    return user.getUsername() == username;
                    });

                if (it != users.end() && it->login(password)) {
                    system("cls");
                    int userChoice;
                    do {
                        std::cout << "-------------------------------------\n";
                        std::cout << "Logged in as " << it->getUsername() << "\n";
                        printUserMenu();
                        std::cin >> userChoice;

                        if (userChoice == 1) {
                            double fee, data, bandwidth;
                            int callMinutes;
                            std::cout << "-------------------------------------\n";
                            std::cout << "Enter your requirements (fee, call minutes, data, bandwidth): ";
                            std::cin >> fee >> callMinutes >> data >> bandwidth;

                            Package suitablePackage = it->findSuitablePackage(packages, fee, callMinutes, data, bandwidth);
                            if (suitablePackage.getId() != 0) {
                                std::cout << "Found suitable package: ID " << suitablePackage.getId() << "\n";
                                std::cout << "Monthly Fee" << suitablePackage.getFee() << "\n"
                                     << "Call Minutes: " << suitablePackage.getCallMinutes() << "\n"
                                     << "4G Data: " << suitablePackage.getData() << " GB\n"
                                     << "Bandwidth: " << suitablePackage.getBandwidth() << " Mbps\n";
                                std::cout << "Do you want to subscribe? (y/n):\n ";
                                std::cout << "-------------------------------------\n";
                                char subscribe;
                                std::cin >> subscribe;
                                if (subscribe == 'y' || subscribe == 'Y') {
                                    it->choosePackage(suitablePackage);
                                    saveUsers(users);
                                    std::cout << "-------------------------------------\n";
                                    std::cout << "Subscribed successfully.\n";
                                }
                            }
                            else {
                                std::cout << "No exact match found. Recommending closest package.\n";
                                Package closestPackage = it->recommendClosestPackage(packages, fee, callMinutes, data, bandwidth);
                                std::cout << "Recommended package: ID " << closestPackage.getId() << "\n";
                                std::cout << "Do you want to subscribe? (y/n): ";
                                char subscribe;
                                std::cin >> subscribe;
                                if (subscribe == 'y' || subscribe == 'Y') {
                                    it->choosePackage(closestPackage);
                                    saveUsers(users);
                                    std::cout << "-------------------------------------\n";
                                    std::cout << "Subscribed successfully.\n";
                                }
                            }
                        }
                        else if (userChoice == 2) {
                            int packageId;
                            std::cout << "-------------------------------------\n";
                            std::cout << "Enter package ID: ";
                            std::cin >> packageId;

                            auto pkgIt = std::find_if(packages.begin(), packages.end(), [packageId](const Package& pkg) {
                                return pkg.getId() == packageId;
                                });

                            if (pkgIt != packages.end()) {
                                std::cout << "-------------------------------------\n";
                                std::cout << "Package ID: " << pkgIt->getId() << " Details:\n";
                                std::cout << "Monthly Fee: " << pkgIt->getFee() << "\n"
                                    << "Call Minutes: " << pkgIt->getCallMinutes() << "\n"
                                    << "4G Data: " << pkgIt->getData() << " GB\n"
                                    << "Bandwidth: " << pkgIt->getBandwidth() << " Mbps\n";
                                std::cout << "-------------------------------------\n";
                                std::cout << "Do you want to subscribe? (y/n): ";
                                char subscribe;
                                std::cin >> subscribe;
                                if (subscribe == 'y' || subscribe == 'Y') {
                                    it->choosePackage(*pkgIt);
                                    saveUsers(users);
                                    std::cout << "-------------------------------------\n";
                                    std::cout << "Subscribed successfully.\n";
                                }
                            }
                            else {
                                std::cout << "-------------------------------------\n";
                                std::cout << "Package not found.\n";
                            }
                        }
                        else if (userChoice == 3) {
                            Package currentPackage = it->getCurrentPackage();
                            if (currentPackage.getId() != 0) {
                                std::cout << "Current Subscription: Package ID " << currentPackage.getId() 
                                    << "Monthly Fee " << currentPackage.getFee() << "\n"
                                    << "Call Minutes " << currentPackage.getCallMinutes() << "\n"
                                    << "4G Data " << currentPackage.getData() << " GB\n" 
                                    << "Bandwidth " << currentPackage.getBandwidth() << " Mbps\n" 
                                    <<  "\n";

                                std::cout << "-------------------------------------\n";
                                std::cout << "Are you sure to unsubscribe your Current Subscription? (yes/no): ";
                                std::string unsubscribeChoice;
                                std::cin >> unsubscribeChoice;

                                // 检查用户输入
                                if (unsubscribeChoice == "yes" || unsubscribeChoice == "y") {
                                    // 执行退订逻辑
                                    it->setCurrentPackage(Package(0, 0.0, 0, 0.0, 0.0)); 
                                    std::cout << "-------------------------------------\n";
                                    std::cout << "Unsubscribed successfully.\n";
                                }
                                else {
                                    std::cout << "-------------------------------------\n";
                                    std::cout << "Operation cancelled.\n";
                                }
                            }
                            else {
                                std::cout << "-------------------------------------\n";
                                std::cout << "No current subscription.\n";
                            }
                        }
                        else if (userChoice == 4) {
                            // 处理修改密码的逻辑
                            std::cout << "Enter current password: ";
                            std::string currentPassword = getPassword();

                            if (it->login(currentPassword)) {
                                std::cout << "-------------------------------------\n";
                                std::cout << "Enter new password: ";
                                std::string newPassword = getPassword();

                                std::cout << "-------------------------------------\n";
                                std::cout << "Confirm new password:\n ";
                                std::string confirmPassword = getPassword();


                                if (newPassword == confirmPassword) {
                                    it->changePassword(newPassword);
                                    saveUsers(users);
                                    std::cout << "-------------------------------------\n";
                                    std::cout << "Password changed successfully.\n";
                                    std::cout << "-------------------------------------\n";
                                }
                                else {
                                    std::cout << "-------------------------------------\n";
                                    std::cout << "Passwords do not match. Please try again.\n";
                                    std::cout << "-------------------------------------\n";
                                }
                            }
                            else {
                                std::cout << "-------------------------------------\n";
                                std::cout << "Incorrect current password.\n";
                                std::cout << "-------------------------------------\n";
                            }
                        }
                        else if (userChoice != 0) {
                            std::cout << "-------------------------------------\n";
                            std::cout << "Invalid choice. Please try again.\n";
                            std::cout << "-------------------------------------\n";
                        }
                    } while (userChoice != 0);
                }
                else {
                    std::cout << "-------------------------------------\n";
                    std::cout << "Invalid login\n";
                    std::cout << "-------------------------------------\n";
                }
            }
        }
        else if (mainChoice == 2) {
            system("cls");
            std::cout << "-------------------------------------\n";
            registerUser(users);
            saveUsers(users);
            std::cout << "-------------------------------------\n";
        }
        else if (mainChoice != 0) {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (mainChoice != 0);

    return 0;
}
