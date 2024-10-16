#include "User.h"
#include <cmath> 
#include <iostream>
#include "PasswordInput.h"

// ���캯��
User::User(const std::string& username, const std::string& password)
    : username(username), password(password), currentPackage(0, 0.0, 0, 0.0, 0.0) {}

// ��¼����
bool User::login(const std::string& enteredPassword) const {
    return password == enteredPassword;
}

// ѡ���ײ͹���
void User::choosePackage(const Package& package) {
    currentPackage = package;
}

// ���õ�ǰ�ײ�
void User::setCurrentPackage(const Package& package) {
    currentPackage = package;
}

// �鿴��ǰ�ײ�
Package User::getCurrentPackage() const {
    return currentPackage;
}

// �����û���
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

// ���ҷ���Ҫ����ײ�
Package User::findSuitablePackage(const std::vector<Package>& packages, double fee, int callMinutes, double data, double bandwidth) const {
    for (const auto& pkg : packages) {
        if (pkg.getFee() <= fee && pkg.getCallMinutes() >= callMinutes && pkg.getData() >= data && pkg.getBandwidth() >= bandwidth) {
            return pkg;
        }
    }
    return Package(0, 0.0, 0, 0.0, 0.0); // ����һ��Ĭ����Ч�ײ�
}

// ������ӽ�Ҫ����ײ�
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

// �޸����빦��
void User::changePassword(const std::string& newPassword) {
    password = newPassword;
}