#include "Package.h"

// 构造函数
Package::Package(int id, double fee, int callMinutes, double data, double bandwidth)
    : id(id), fee(fee), callMinutes(callMinutes), data(data), bandwidth(bandwidth) {}

// 获取套餐信息
int Package::getId() const { return id; } // 返回套餐的唯一标识符
double Package::getFee() const { return fee; } // 返回每月的费用
int Package::getCallMinutes() const { return callMinutes; } // 返回套餐中包含的通话分钟数
double Package::getData() const { return data; } // 返回套餐中包含的数据流量（可以GB为单位）
double Package::getBandwidth() const { return bandwidth; } // 返回套餐中提供的带宽（可以Mbps为单位）

// 设置套餐信息
void Package::setFee(double fee) { this->fee = fee; } // 设置每月的费用
void Package::setCallMinutes(int minutes) { callMinutes = minutes; } // 设置通话分钟数
void Package::setData(double data) { this->data = data; } // 设置数据流量
void Package::setBandwidth(double bandwidth) { this->bandwidth = bandwidth; } // 设置带宽

