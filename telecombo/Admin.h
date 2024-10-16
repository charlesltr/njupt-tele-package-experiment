#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "Package.h"  // ����Package�������
#include "User.h"

// ����Ա��
class Admin {
public:
    // ���캯��
    Admin(const std::string& username, const std::string& password);

    // ��¼����
    bool login(const std::string& enteredPassword) const;

    // �����ײ͹���
    void addPackage(const Package& package);
    void removePackage(int packageId);
    void updatePackage(int packageId, const Package& newPackage);

    // �鿴�����ײ�
    const std::vector<Package>& getAllPackages() const;

    // ��¼�û�����
    void recordSubscription(const User& user);


    // �û�������
    void deleteUser(std::vector<User>& users, const std::string& username);
    void viewUsersAndPackages(const std::vector<User>& users) const;

private:
    std::string username; // �û���
    std::string password; // ����
    std::vector<Package> packages; // �����ײ��б�
    static std::vector<Admin> admins; // ������̬��Աadmins
};

#endif

