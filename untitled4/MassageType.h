#pragma once
#include <iostream>
using namespace std;

#pragma pack(push, 1) // ��������� ������������ �������� �� 1 �����

enum ECommandType
{
    POINTS_MOVE,
    POINTS_ADD,
    POINTS_CLEAR, 	// �������� ���� ����� ����� �������
    SIGNAL_SET,
    VELOCITY_SET,
    CONTROL_SET 	// ������������ ����� ��������: ����������/��������������
};

enum EMovementMode
{
    POINTS, // ��������� ������ �����
    LINEAR, // �������� �� �������
    SPLINE  // �������� �� �������
};

struct SPoint3D
{
    float x, y, z;
    float a, b, c;
};

struct SPoints
{
    SPoint3D pts[20];
    unsigned char count;
    float velocity;
    EMovementMode mode;
};

struct SPointsMove
{
    SPoint3D pts[20]; // ���-�� �����
    uint8_t ptsNum;
    unsigned char count; // ���-�� ������. ����� (��� � ������� ��������)
    float velocity; // ��������
    EMovementMode mode;
};

struct SPointsAdd
{
    SPoint3D pts[20];
    uint8_t ptsNum;
    unsigned char count;

};

struct SSetSignal
{
    uint8_t outputIndex;
    bool val;
};

struct SSetVelocity
{
    float velocity;
};

struct SSetControl
{
    uint8_t control; // 0 == auto
};

#pragma pack(pop)
#pragma pack(push, 1) // ��������� ������������ �������� �� 1 �����

enum ERequestType
{
    NAVIG_GET,
    CUR_CMD_GET,
    IS_ALIVE,
    SENSOR_DATA_GET,
    SENSOR_LIST_GET
};

struct SSensorData
{

    unsigned char sensorId;
    unsigned char count_butes;
    char butes[1020];

    //uint8_t sensorId;
    //uint16_t dataSize;
    //uint8_t data[1020];
};

struct SSensor
{
    uint8_t id;
    uint8_t type;
};

struct SSensorsList
{
    uint8_t sensorNum;
    SSensor sensors[255];
};

#pragma pack(pop)

#pragma pack(push, 1) // ��������� ������������ �������� �� 1 �����

enum EServiceType
{
    PID_SET,
    STEP_SET,
    TIME_SET,
    MODE_SET,
};

struct SSetPid
{
    float p, i, d;
};

struct SSetStep
{
    float step;
};

struct SSetTime
{
    uint64_t time; // millis
};

struct SSetMode
{
    uint8_t mode;
};

#pragma pack(pop)

#pragma pack(push, 1) // ��������� ������������ �������� �� 1 �����

enum EEventType
{
    MISSION_COMPLETE,
    ERROR
};

#pragma pack(pop)