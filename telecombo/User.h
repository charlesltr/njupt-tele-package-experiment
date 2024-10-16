#ifndef USER_H
#define USER_H

#include <string>
#include "Package.h"
#include <vector>

// ��ͨ�û���
class User {
public:
    // ���캯��
    User(const std::string& username, const std::string& password);

    // ��¼����
    bool login(const std::string& enteredPassword) const;

    // ѡ���ײ͹���
    void choosePackage(const Package& package);

    // ���õ�ǰ�ײ�
    void setCurrentPackage(const Package& package);

    // �鿴��ǰ�ײ�
    Package getCurrentPackage() const;

    // �����û���
    std::string getUsername() const;

    // ��������
    std::string getPassword() const;

    // �޸����빦��
    void changePassword(const std::string& newPassword);

    // ���ҷ���Ҫ����ײ�
    Package findSuitablePackage(const std::vector<Package>& packages, double fee, int callMinutes, double data, double bandwidth) const;

    // ������ӽ�Ҫ����ײ�
    Package recommendClosestPackage(const std::vector<Package>& packages, double fee, int callMinutes, double data, double bandwidth) const;

private:
    std::string username; // �û���
    std::string password; // ����
    Package currentPackage; // ��ǰѡ����ײ�
};

#endif
