#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

// 用类表示优惠套餐
class Package {
public:
    // 构造函数
    Package(int id, double fee, int callMinutes, double data, double bandwidth);

    // 获取套餐信息
    int getId() const;
    double getFee() const;
    int getCallMinutes() const;
    double getData() const;
    double getBandwidth() const;

    // 设置套餐信息
    void setFee(double fee);
    void setCallMinutes(int minutes);
    void setData(double data);
    void setBandwidth(double bandwidth);

private:
    int id; // 套餐编号
    double fee; // 月资费
    int callMinutes; // 通话时长
    double data; // 4G流量
    double bandwidth; // 宽带带宽
};

#endif

