#include "Package.h"

// ���캯��
Package::Package(int id, double fee, int callMinutes, double data, double bandwidth)
    : id(id), fee(fee), callMinutes(callMinutes), data(data), bandwidth(bandwidth) {}

// ��ȡ�ײ���Ϣ
int Package::getId() const { return id; } // �����ײ͵�Ψһ��ʶ��
double Package::getFee() const { return fee; } // ����ÿ�µķ���
int Package::getCallMinutes() const { return callMinutes; } // �����ײ��а�����ͨ��������
double Package::getData() const { return data; } // �����ײ��а�������������������GBΪ��λ��
double Package::getBandwidth() const { return bandwidth; } // �����ײ����ṩ�Ĵ�������MbpsΪ��λ��

// �����ײ���Ϣ
void Package::setFee(double fee) { this->fee = fee; } // ����ÿ�µķ���
void Package::setCallMinutes(int minutes) { callMinutes = minutes; } // ����ͨ��������
void Package::setData(double data) { this->data = data; } // ������������
void Package::setBandwidth(double bandwidth) { this->bandwidth = bandwidth; } // ���ô���

