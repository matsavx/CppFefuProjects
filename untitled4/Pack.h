#pragma once

#include "MassageType.h"
#include <iostream>
#include <cstring>


using namespace std;
//------------------------------DATA---------------------------------
// ������� ����� ��� ������ � ������� � ���������
class CContent
{
public:

    virtual int marshall(unsigned char* content) { return 0; }
    virtual void unmarshall(unsigned char* content, int len) {}
    virtual char* toString() { return NULL; }
    //virtual void toStringStream(std::ostream& stream) {};
    //virtual CContent* getCopy() const { return new CContent(); }

};


class CPointsMove : public CContent
{
public:

    SPoints points;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &points, sizeof(SPoints));
        return sizeof(SPoints);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&points, content, sizeof(len));
    }

};

class AddPoints : public CContent
{
public:
    SPointsAdd points;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &points, sizeof(SPoints));
        return sizeof(SPoints);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&points, content, sizeof(len));
    }
};

class CSetSignal : public CContent
{
public:
    SSetSignal data;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(SPoints));
        return sizeof(SPoints);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};

class CSetVelocity : public CContent
{
public:
    SSetVelocity velocity;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &velocity, sizeof(SSetVelocity));
        return sizeof(SSetVelocity);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&velocity, content, sizeof(len));
    }
};

class CSetControl : public CContent
{
public:
    SSetControl control;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &control, sizeof(SSetControl));
        return sizeof(SSetControl);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&control, content, sizeof(len));
    }
};

class CGetSensorData : public CContent
{
public:
    SSensorData data;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(SSensorData));
        return sizeof(SSensorData);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};

class CGetNavigation : public CContent
{
public:
    unsigned char data;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(unsigned char));
        return sizeof(unsigned char);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};

class CCurrentCMD : public CContent
{
public:

    unsigned char data; // ��� �� ��� ������������
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(unsigned char));
        return sizeof(unsigned char);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};

class CAlive : public CContent
{
public:
    unsigned char data;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(unsigned char));
        return sizeof(unsigned char);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};

class CSensorData : public CContent
{
public:
    SSensorData data;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(SSensorData));
        return sizeof(SSensorData);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};

class CSensorList : public CContent
{
public:
    SSensorsList list;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &list, sizeof(SSensorsList));
        return sizeof(SSensorsList);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&list, content, sizeof(len));
    }
};

class CError : public CContent
{
public:
    unsigned char error;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &error, sizeof(SSensorsList));
        return sizeof(SSensorsList);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&error, content, sizeof(len));
    }
};

class CSetParamControl : public CContent
{
public:
    float data;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(float));
        return sizeof(float);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};

class CSetTIME : public CContent
{
public:
    SSetTime time;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &time, sizeof(SSetTime));
        return sizeof(SSetTime);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&time, content, sizeof(len));
    }
};

class CSetMode : public CContent
{
public:
    SSetMode mode;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &mode, sizeof(SSetMode));
        return sizeof(SSetMode);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&mode, content, sizeof(len));
    }
};

class CSet_settime : public CContent
{
public:
    float data;
    virtual int marshall(unsigned char* content)
    {
        memcpy(content, &data, sizeof(float));
        return sizeof(float);

    }
    virtual void unmarshall(unsigned char* content, int len)
    {
        memcpy(&data, content, sizeof(len));
    }
};