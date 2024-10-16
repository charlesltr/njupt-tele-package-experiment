#include "Admin.h"
#include <fstream>
#include <iostream>

// 初始化静态成员变量
std::vector<Admin> Admin::admins;

// 构造函数
Admin::Admin(const std::string& username, const std::string& password)
    : username(username), password(password) {
    admins.push_back(*this); // 将自身添加到管理员列表中
}

// 登录功能
bool Admin::login(const std::string& enteredPassword) const {
    return password == enteredPassword;
}

// 添加套餐
void Admin::addPackage(const Package& package) {
    packages.push_back(package);
}

// 移除套餐
void Admin::removePackage(int packageId) {
    packages.erase(std::remove_if(packages.begin(), packages.end(),
        [packageId](const Package& pkg) { return pkg.getId() == packageId; }),
        packages.end());
}

// 更新套餐
void Admin::updatePackage(int packageId, const Package& newPackage) {
    for (auto& pkg : packages) {
        if (pkg.getId() == packageId) {
            pkg = newPackage;
            break;
        }
    }
}

// 获取所有套餐
const std::vector<Package>& Admin::getAllPackages() const {
    return packages;
}

// 记录用户订阅
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

// 删除用户
void Admin::deleteUser(std::vector<User>& users, const std::string& username) {
    users.erase(std::remove_if(users.begin(), users.end(),
        [&username](const User& user) { return user.getUsername() == username; }),
        users.end());
}

// 查看用户及其套餐
void Admin::viewUsersAndPackages(const std::vector<User>& users) const {
    for (const auto& user : users) {
        std::cout << "Username: " << user.getUsername()
            << ", Package ID: " << user.getCurrentPackage().getId() << '\n';
    }
}
