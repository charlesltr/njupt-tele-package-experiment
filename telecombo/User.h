#ifndef USER_H
#define USER_H

#include <string>
#include "Package.h"
#include <vector>

// 普通用户类
class User {
public:
    // 构造函数
    User(const std::string& username, const std::string& password);

    // 登录功能
    bool login(const std::string& enteredPassword) const;

    // 选择套餐功能
    void choosePackage(const Package& package);

    // 设置当前套餐
    void setCurrentPackage(const Package& package);

    // 查看当前套餐
    Package getCurrentPackage() const;

    // 返回用户名
    std::string getUsername() const;

    // 返回密码
    std::string getPassword() const;

    // 修改密码功能
    void changePassword(const std::string& newPassword);

    // 查找符合要求的套餐
    Package findSuitablePackage(const std::vector<Package>& packages, double fee, int callMinutes, double data, double bandwidth) const;

    // 查找最接近要求的套餐
    Package recommendClosestPackage(const std::vector<Package>& packages, double fee, int callMinutes, double data, double bandwidth) const;

private:
    std::string username; // 用户名
    std::string password; // 密码
    Package currentPackage; // 当前选择的套餐
};

#endif
