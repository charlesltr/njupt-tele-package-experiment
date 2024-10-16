#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

// �����ʾ�Ż��ײ�
class Package {
public:
    // ���캯��
    Package(int id, double fee, int callMinutes, double data, double bandwidth);

    // ��ȡ�ײ���Ϣ
    int getId() const;
    double getFee() const;
    int getCallMinutes() const;
    double getData() const;
    double getBandwidth() const;

    // �����ײ���Ϣ
    void setFee(double fee);
    void setCallMinutes(int minutes);
    void setData(double data);
    void setBandwidth(double bandwidth);

private:
    int id; // �ײͱ��
    double fee; // ���ʷ�
    int callMinutes; // ͨ��ʱ��
    double data; // 4G����
    double bandwidth; // �������
};

#endif

