#include "User.h"
#include <cmath> 
#include <iostream>
#include "PasswordInput.h"

// 构造函数
User::User(const std::string& username, const std::string& password)
    : username(username), password(password), currentPackage(0, 0.0, 0, 0.0, 0.0) {}

// 登录功能
bool User::login(const std::string& enteredPassword) const {
    return password == enteredPassword;
}

// 选择套餐功能
void User::choosePackage(const Package& package) {
    currentPackage = package;
}

// 设置当前套餐
void User::setCurrentPackage(const Package& package) {
    currentPackage = package;
}

// 查看当前套餐
Package User::getCurrentPackage() const {
    return currentPackage;
}

// 返回用户名
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

// 查找符合要求的套餐
Package User::findSuitablePackage(const std::vector<Package>& packages, double fee, int callMinutes, double data, double bandwidth) const {
    for (const auto& pkg : packages) {
        if (pkg.getFee() <= fee && pkg.getCallMinutes() >= callMinutes && pkg.getData() >= data && pkg.getBandwidth() >= bandwidth) {
            return pkg;
        }
    }
    return Package(0, 0.0, 0, 0.0, 0.0); // 返回一个默认无效套餐
}

// 查找最接近要求的套餐
Package User::recommendClosestPackage(const std::vector<Package>& packages, double fee, int callMinutes, double data, double bandwidth) const {
    Package closestPackage = packages.front();
    double closestDifference = std::numeric_limits<double>::max();

    for (const auto& pkg : packages) {
        double difference = std::abs(pkg.getFee() - fee) + std::abs(pkg.getCallMinutes() - callMinutes) +
            std::abs(pkg.getData() - data) + std::abs(pkg.getBandwidth() - bandwidth);
        if (difference < closestDifference) {
            closestDifference = difference;
            closestPackage = pkg;
        }
    }
    return closestPackage;
}

// 修改密码功能
void User::changePassword(const std::string& newPassword) {
    password = newPassword;
}