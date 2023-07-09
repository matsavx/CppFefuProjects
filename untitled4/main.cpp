#include <iostream>
#include <bitset>
#include "Pack.h"


#define SOH '*'
#define MARKER 10 // 1010

//using namespace std;
struct SAddress
{
	unsigned char node;
	unsigned char component;
	unsigned char instance;

};
//приоритет
enum EPriority
{
	LOW,     // 00 // низкий
	MIDDLE,  // 01 // средний
	HIGH,    // 10 // высокий
	CRITICAL // 11 // критичный
};

// подтверждение
enum EConfirm
{
	without_confirm_not_confirm, // не подтверждение | не требует подтверждением
	without_confirm_confirm,     // не подтверждение | требует подтверждение
	with_confirm_not_confirm,    // подтверждение    | не требует подтверждение
};

enum ETypeMSG // типы сообщений
{
	//Commands:
	cmd_start,       //0x0
	cmd_stop,        //0x1
	cmd_pause,       //0x2
	cmd_points_move, //0x3
	cmd_add_points,  //0x4
	cmd_set_signal,  //0x5
	cmd_set_velocity,//0x6
	cmd_set_control, //0x7
	//Requests:
	req_navig,       //0x8
	req_current_cmd, //0x9
	req_is_alive,    //0xA
	req_sensor_data, //0xB
	req_sensor_list, //0xC
	//Answers:
	ans_Navigation,  //0xD
	ans_current_cmd, //0xE
	ans_alive,       //0xF
	ans_sensor_data, //0x10
	ans_sensor_list, //0x11
	ans_sensor_type, //0x12
	//Events:
	ev_mission_completed, //0x13
	ev_error,             //0x14
	//Service:
	srv_set_param_control, //0x15
	srv_set_TIME,          //0x16
	srv_set_MODE,          //0x17
	srv_set_settime        //0x18
};


const unsigned short Crc16Table[256] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
	0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
	0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
	0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
	0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
	0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
	0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
	0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
	0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
	0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
	0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
	0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
	0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
	0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
	0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
	0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
	0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
	0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
	0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
	0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
	0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
	0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
	0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

unsigned short Crc16(unsigned char *pcBlock, unsigned short len)
{
	unsigned short crc = 0xFFFF;

	while (len--)
		crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++];

	return crc;
}

unsigned short CRC16(unsigned char* buff, int len)
{

	return 0;
}

/*
//------------------------------DATA---------------------------------
// базовый класс для работы с данными в сообщении

class CContent
{
public:

	virtual int marshall(unsigned char* buff) { return 0; }
	virtual void unmarshall(unsigned char* buff) {}
	virtual char* toString() { return NULL; }
	virtual void toStringStream(std::ostream& stream) {};
	//virtual CContent* getCopy() const { return new CContent(); }

};
*/

class CMessage
{
public:


	unsigned char buffer[1033]; // сам массив для всего что есть

	uint16_t len_data;          // lдлина данных
	uint16_t len_msg;           // длина сообщения

	SAddress address_to;        // сообщение откуда
	SAddress address_from;      // сообщение куда

	EPriority msg_priority;     // приоритет
	EConfirm  msg_confirm;      // подтверждение
	ETypeMSG  msg_type;         // тип сообщения
	CContent *msg_data;

	CMessage() {}; // конструктор по умолчанию

	//конструктор передачи данных
	CMessage(SAddress addr_from, SAddress addr_to, EPriority priority, ETypeMSG msg, EConfirm confirm, CContent *data = NULL):
		address_from(addr_from), address_to(addr_to), msg_priority(priority), msg_confirm(confirm), msg_type(msg), msg_data(data)
	{
		len_data = msg_data->marshall(buffer + 7);       // длина данных
		len_msg = len_data + 7 + 2;                      // длина данных + длина заголовка + длина CRC16
		header_pack();                                   // пакуем
		unsigned short Crc = Crc16(buffer, len_msg - 2); // расчет контрольной суммы

	}

	// конструктор для прияма
	CMessage(unsigned char* buff, int len)
	{
		for (int i = 0; i < len; i++)
		{
			if (buff[i] == SOH && ((buff[i + 6] & 0xF) == MARKER)) // можно еще с 15 сравнивать, ибо 15 = 0b1111 || 0xF = 0b1111 = 1111
			{
				len_data = uint16_t(buffer[i + 5] << 2) | (buffer[i + 6] >> 6);   // получение длинны данных (размер данных)
				len_msg = len_data + 7 + 2;                                       // длина / размер всего сообщения включая заголовка
				memcpy(buffer, buff + i, len_msg - 1);                            // копируем данный в свой буфер (buff + i) - это сдвигание сылки на начало масива на i ячеек

				if (true)//Crc16(buffer, len_msg - 1) == (unsigned char)buff[i + len_msg - 1]) // при условии что контрольные суммы совпадают
				{
					memcpy(buffer, buff + i, len_msg);
					header_unpack();

					switch (msg_type)
					{
					case ETypeMSG::cmd_points_move:
						msg_data = new CPointsMove;
						break;
					case ETypeMSG::cmd_add_points:
						msg_data = new AddPoints;
						break;
					case ETypeMSG::cmd_set_signal:
						msg_data = new CSetSignal;
						break;
					case ETypeMSG::cmd_set_velocity:
						msg_data = new CSetVelocity;
						break;
					case ETypeMSG::cmd_set_control:
						msg_data = new CSetControl;
						break;
					case ETypeMSG::req_sensor_data:
						msg_data = new CGetSensorData;
						break;
					case ETypeMSG::ans_Navigation:
						msg_data = new CGetNavigation;
						break;
					case ETypeMSG::ans_current_cmd:
						msg_data = new CCurrentCMD;
						break;
					case ETypeMSG::ans_alive:
						msg_data = new CAlive;
						break;
					case ETypeMSG::ans_sensor_data:
						msg_data = new CSensorData;
						break;
					case ETypeMSG::ans_sensor_list:
						msg_data = new CSensorList;
						break;
					case ETypeMSG::ev_error:
						msg_data = new CError;
						break;
					case ETypeMSG::srv_set_param_control:
						msg_data = new CSetParamControl;
						break;
					case ETypeMSG::srv_set_TIME:
						msg_data = new CSetTIME;
						break;
					case ETypeMSG::srv_set_MODE:
						msg_data = new CSetMode;
						break;
					case ETypeMSG::srv_set_settime:
						msg_data = new CSet_settime;
						break;
					default:
						msg_data = new CContent;
						break;
                        case cmd_start:
                            break;
                        case cmd_stop:
                            break;
                        case cmd_pause:
                            break;
                        case req_navig:
                            break;
                        case req_current_cmd:
                            break;
                        case req_is_alive:
                            break;
                        case req_sensor_list:
                            break;
                        case ans_sensor_type:
                            break;
                        case ev_mission_completed:
                            break;
                    }

					msg_data->unmarshall(buffer, len_data); // получение данных с масива со всей хренью
					break;
				}

			}
		}
	}

	unsigned char *get_msg()
	{
		return buffer;
	}

	uint16_t get_msg_size()
	{
		return len_data + 7 + 2;
	}

	// запаковка заголовка
	void header_pack()
	{
		buffer[0] = SOH;
		buffer[1] = (address_from.node << 4) | (address_from.component);
		buffer[2] = (address_from.instance << 4) | (address_to.node);
		buffer[3] = (address_to.component << 4) | (address_to.instance);
		buffer[4] = (msg_type << 2) | (msg_priority);
		buffer[5] = (len_data >> 2);
		buffer[6] = (len_data << 6) | (msg_confirm << 4) | (MARKER);


		std::cout << "#---------------------------- Pack ----------------------------#" << std::endl;
		std::cout << " 0. : " << std::bitset<8>(buffer[0]) << std::endl;
		std::cout << " 1. : " << std::bitset<8>(buffer[1]) << std::endl;
		std::cout << " 2. : " << std::bitset<8>(buffer[2]) << std::endl;
		std::cout << " 3. : " << std::bitset<8>(buffer[3]) << std::endl;
		std::cout << " 4. : " << std::bitset<8>(buffer[4]) << std::endl;
		std::cout << " 5. : " << std::bitset<8>(buffer[5]) << std::endl;
		std::cout << " 6. : " << std::bitset<8>(buffer[6]) << std::endl;
		std::cout << "#--------------------------- Packed ---------------------------#" << std::endl;


		std::cout << "Pack massage" << std::endl;
	}

	// распаковка заголовка
	void header_unpack()
	{
		if (buffer[0] == SOH)
		{
			unsigned char addres_marker = 0xF;// 0b00001111; // маска для адреса
			unsigned char marker_for_PC = 0b00000011; // маска для приоритета и для подтверждения

			address_from.node = (buffer[1] >> 4);
			address_from.component = (buffer[1] & addres_marker);

			address_from.instance = (buffer[2] >> 4);
			address_to.node = (buffer[2] & addres_marker);

			address_to.component = (buffer[3] >> 4);
			address_to.instance = (buffer[3] & addres_marker);

			msg_type = ETypeMSG(buffer[4] >> 2);
			msg_priority = EPriority(buffer[4] & marker_for_PC);
			len_data = uint16_t(buffer[5] << 2) | (buffer[6] >> 6);
			msg_confirm = EConfirm((buffer[6] >> 4) & marker_for_PC);


			std::cout << "#---------------------------- Unpack ----------------------------#\n" << std::endl;
			std::cout << " Address from node      : " << std::bitset<4>(address_from.node)      << std::endl;
			std::cout << " Address from component : " << std::bitset<4>(address_from.component) << std::endl;
			std::cout << " Address from instance  : " << std::bitset<4>(address_from.instance)  << std::endl;
			std::cout << " Address to node        : " << std::bitset<4>(address_to.node)        << std::endl;
			std::cout << " Address to component   : " << std::bitset<4>(address_to.component)   << std::endl;
			std::cout << " Address to instance    : " << std::bitset<4>(address_to.instance)    << std::endl;
			std::cout << " Massage Type           : " << std::bitset<6>(msg_type)               << std::endl;
			std::cout << " Massage Priority       : " << std::bitset<2>(msg_confirm)			<< std::endl;
			std::cout << " Massage Confirm        : " << std::bitset<2>(msg_confirm)			<< std::endl;
			std::cout << "#----------------------- Unpacked massage -----------------------#"	<< std::endl;


		}


	}

	~CMessage() //деструктор
	{
		delete msg_data;
		msg_data = nullptr;
		std::cout << "Destructing CMessage" << '\n';
	};

};


int main() {
	setlocale(LC_ALL, "rus");

	//для проверки запаковки
	/*
	SAddress address_to;        // сообщение откуда
	SAddress address_from;
	ETypeMSG msg_type; // 0
	EPriority msg_priority(CRITICAL);     // прио
ритет
	EConfirm  msg_confirm(without_confirm_confirm);      // подтверждение
	uint16_t len_date = 0;      // lдлина данных
	uint16_t len_msg;       // длина сообщения

	address_from.node = 15;     // 1111
	address_from.component = 9; // 1001
	// 0110 1111
	address_from.instance = 6;  // 0110
	address_to.node = 15;       // 1111
	// 1001 0110
	address_to.component = 9;   // 1001
	address_to.instance = 6;    // 0110
	msg_type = cmd_start;
	CContent* data;
	//data->marshall('asdf');

	//адрес куда, адрес откуда, приоритет, тип , подтверждение, данные

	CMessage Massage = CMessage(address_from, address_to, msg_priority, msg_type, msg_confirm);
	Massage.header_unpack();
	*/

	const int size = 19;
	unsigned char buffer[size] = {3,1,1,1,1,1,1,1,3,5,1,3,'*',0b11111001,0b01101111,0b10010110,0b10101010,0b11111111,0b11011010};
	CMessage Massage = CMessage(buffer, size);

	int crc = Crc16(buffer, size);
	std::cout << "Вывод crc :=: "<<crc << std::endl;
	system("pause");
	return 0;

}

/*
Указатель на функцию
тип функции (*имя функции)(спецификация параметров)

*/