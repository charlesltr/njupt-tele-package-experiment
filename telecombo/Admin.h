#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "Package.h"  // 包含Package类的声明
#include "User.h"

// 管理员类
class Admin {
public:
    // 构造函数
    Admin(const std::string& username, const std::string& password);

    // 登录功能
    bool login(const std::string& enteredPassword) const;

    // 管理套餐功能
    void addPackage(const Package& package);
    void removePackage(int packageId);
    void updatePackage(int packageId, const Package& newPackage);

    // 查看所有套餐
    const std::vector<Package>& getAllPackages() const;

    // 记录用户订阅
    void recordSubscription(const User& user);


    // 用户管理功能
    void deleteUser(std::vector<User>& users, const std::string& username);
    void viewUsersAndPackages(const std::vector<User>& users) const;

private:
    std::string username; // 用户名
    std::string password; // 密码
    std::vector<Package> packages; // 所有套餐列表
    static std::vector<Admin> admins; // 声明静态成员admins
};

#endif

