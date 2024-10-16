#include "Admin.h"
#include <fstream>
#include <iostream>

// ��ʼ����̬��Ա����
std::vector<Admin> Admin::admins;

// ���캯��
Admin::Admin(const std::string& username, const std::string& password)
    : username(username), password(password) {
    admins.push_back(*this); // ��������ӵ�����Ա�б���
}

// ��¼����
bool Admin::login(const std::string& enteredPassword) const {
    return password == enteredPassword;
}

// ����ײ�
void Admin::addPackage(const Package& package) {
    packages.push_back(package);
}

// �Ƴ��ײ�
void Admin::removePackage(int packageId) {
    packages.erase(std::remove_if(packages.begin(), packages.end(),
        [packageId](const Package& pkg) { return pkg.getId() == packageId; }),
        packages.end());
}

// �����ײ�
void Admin::updatePackage(int packageId, const Package& newPackage) {
    for (auto& pkg : packages) {
        if (pkg.getId() == packageId) {
            pkg = newPackage;
            break;
        }
    }
}

// ��ȡ�����ײ�
const std::vector<Package>& Admin::getAllPackages() const {
    return packages;
}

// ��¼�û�����
void Admin::recordSubscription(const User& user) {
    std::ofstream outFile("users.dll", std::ios::app);
    if (outFile.is_open()) {
        const Package& package = user.getCurrentPackage();
        outFile << user.getUsername() << " " << package.getId() << " "
            << package.getFee() << " " << package.getCallMinutes() << " "
            << package.getData() << " " << package.getBandwidth() << std::endl;
        outFile.close();
    }
}

// ɾ���û�
void Admin::deleteUser(std::vector<User>& users, const std::string& username) {
    users.erase(std::remove_if(users.begin(), users.end(),
        [&username](const User& user) { return user.getUsername() == username; }),
        users.end());
}

// �鿴�û������ײ�
void Admin::viewUsersAndPackages(const std::vector<User>& users) const {
    for (const auto& user : users) {
        std::cout << "Username: " << user.getUsername()
            << ", Package ID: " << user.getCurrentPackage().getId() << '\n';
    }
}
