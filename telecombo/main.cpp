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

// �ļ�������
const std::string USERS_FILE = "users.dll";
const std::string PACKAGES_FILE = "packages.dll";

// ��ʼ���ļ�
void initializeFiles() {
    // ��鲢���� users.dll
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

    // ��鲢���� packages.dll
    std::ifstream packagesFile(PACKAGES_FILE);
    if (!packagesFile.is_open()) {
        // �ļ��������򴴽��ļ���д���ʼ����
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
        // ����ļ����ڣ�����ļ��Ƿ�Ϊ��
        packagesFile.seekg(0, std::ios::end); // �Ƶ��ļ�ĩβ
        if (packagesFile.tellg() == 0) { // ����ļ���С
            packagesFile.close(); // �رն�ȡ�ļ���
            std::ofstream createPackagesFile(PACKAGES_FILE);
            if (createPackagesFile.is_open()) {
                // ��ӳ�ʼ�ײ�����
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

// ���ļ������û�
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

// �����û����ļ�
void saveUsers(const std::vector<User>& users) {
    std::ofstream file(USERS_FILE);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.getUsername() << " " << user.getPassword() << std::endl;
        }
        file.close();
    }
}

// ���ļ������ײ�
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

// ע�����û�
void registerUser(std::vector<User>& users) {
    std::string username, password;
    system("cls");
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "-------------------------------------\n";
    std::cout << "Enter password: ";
    password = getPassword();  // ʹ�� getPassword ������ȡ����


    // ����û����Ƿ��Ѿ�����
    if (std::any_of(users.begin(), users.end(), [&username](const User& user) { return user.getUsername() == username; })) {
        std::cout << "Username already exists. Please choose another one.\n";
    }
    else {
        users.emplace_back(username, password);
        saveUsers(users);
        std::cout << "User registered successfully.\n";
    }
}

// �����ײ͵��ļ�
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

            // ����Ƿ���ھ�����ͬ ID ���ײ�
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

// ������
void adminFunctions(Admin& admin, std::vector<User>& users);
void registerUser(std::vector<User>& users);
void saveUsers(const std::vector<User>& users);

int main() {
    // ��ʼ���ļ�
    initializeFiles();
    Admin admin("admin", "adminpass");

    // �����û����ײ�����
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
            password = getPassword();  // ʹ���Զ��庯����ȡ����
            
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

                                // ����û�����
                                if (unsubscribeChoice == "yes" || unsubscribeChoice == "y") {
                                    // ִ���˶��߼�
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
                            // �����޸�������߼�
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
