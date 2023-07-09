//TODO:: 11-15тиричная система в 10тичную
// Описать ошибки.
// Перевод из 10 в другие.
// Интерфейс

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

void toTen(string number, int first_system, bool &sign, bool &is_double, int &ten_before_point, double &ten_after_point) {
    //Знак (отрицательный - true)
    if (number[0] == '-') { //проверка первого элемента строки на наличие минуса
        sign = true; //флаг знака
        number.erase(0,1); //удалить 1 символ начиная с позиции 0
    }
    string str_before_point;

    int runner = 0;
    int count_before_point = 0;
    int count_after_point = 0;
    string str_after_point;



    while (runner < number.length()) {
        if (number[runner] == '.') {
            is_double = true;
            runner = number.length();
            number.erase(0, count_before_point+1);
            str_after_point = number;
            count_after_point = str_after_point.length();
        } else {
            str_before_point = str_before_point + number[runner]; //Записываем в новую строку символы начальной строки слева направо
            count_before_point++; //Количество символов в str_before_point
            runner++; //бегунок по циклу
        }
    }

    char char_before_point[count_before_point];
    for (int i = 0; i < count_before_point; i++) {
        char_before_point[i] = str_before_point[i];
    }
    for (int power = count_before_point - 1; power >= 0; power--) {
        if (isdigit(char_before_point[count_before_point - power - 1])) {
            ten_before_point = ten_before_point + ((int(char_before_point[count_before_point - power - 1] - 48)) *
                                                   pow(first_system,
                                                       power)); //прибавляем получившееся в уже посчитанное
        } else {
            int letter_to_number = 0;
            if (char_before_point[count_before_point - power - 1] == 'A')
                letter_to_number = 10;
            if (char_before_point[count_before_point - power - 1] == 'B')
                letter_to_number = 11;
            if (char_before_point[count_before_point - power - 1] == 'C')
                letter_to_number = 12;
            if (char_before_point[count_before_point - power - 1] == 'D')
                letter_to_number = 13;
            if (char_before_point[count_before_point - power - 1] == 'E')
                letter_to_number = 14;
            if (char_before_point[count_before_point - power - 1] == 'F')
                letter_to_number = 15;
            ten_before_point = ten_before_point + (letter_to_number * pow(first_system, power));
        }
    }
    if (is_double == true) {
        ten_after_point = 0;
        char char_after_point[count_after_point];
        for (int i = 0; i < count_after_point; i++) {
            char_after_point[i] = str_after_point[i];
        }
        for (int power = 1; power <= count_after_point; power++) {
            if (isdigit(char_after_point[power-1])) {
                ten_after_point = ten_after_point + ((int(char_after_point[power - 1] - 48)) / pow(first_system, power));
            } else {
                int letter_to_number = 0;
                if (char_before_point[power - 1] == 'A')
                    letter_to_number = 10;
                if (char_before_point[power - 1] == 'B')
                    letter_to_number = 11;
                if (char_before_point[power - 1] == 'C')
                    letter_to_number = 12;
                if (char_before_point[power - 1] == 'D')
                    letter_to_number = 13;
                if (char_before_point[power - 1] == 'E')
                    letter_to_number = 14;
                if (char_before_point[power - 1] == 'F')
                    letter_to_number = 15;
                ten_after_point = ten_after_point + (letter_to_number / pow(first_system, power));
            }
        }

    }
}

void from_Ten(int second_system, bool &sign, bool &is_double, int &ten_before_point, double &ten_after_point) {
    string result_number_before_point;
    string result_number_after_point;
    int count_ten_after_point = 0;
    int temporary_number = ten_before_point;

    while (ten_before_point >= second_system) {
        if (second_system > 10) {
            if (ten_before_point % second_system == 10)
                result_number_before_point = result_number_before_point + "A";
            else if (ten_before_point % second_system == 11)
                result_number_before_point = result_number_before_point + "B";
            else if (ten_before_point % second_system == 12)
                result_number_before_point = result_number_before_point + "C";
            else if (ten_before_point % second_system == 13)
                result_number_before_point = result_number_before_point + "D";
            else if (ten_before_point % second_system == 14)
                result_number_before_point = result_number_before_point + "E";
            else if (ten_before_point % second_system == 15)
                result_number_before_point = result_number_before_point + "F";
            else result_number_before_point = result_number_before_point + to_string(ten_before_point % second_system);
        } else {
            result_number_before_point = result_number_before_point + to_string(ten_before_point % second_system);
        }
        ten_before_point = ten_before_point / second_system;
    }
    if (second_system > 10) {
        if (ten_before_point== 10)
            result_number_before_point = result_number_before_point + "A";
        else if (ten_before_point == 11)
            result_number_before_point = result_number_before_point + "B";
        else if (ten_before_point == 12)
            result_number_before_point = result_number_before_point + "C";
        else if (ten_before_point == 13)
            result_number_before_point = result_number_before_point + "D";
        else if (ten_before_point == 14)
            result_number_before_point = result_number_before_point + "E";
        else if (ten_before_point == 15)
            result_number_before_point = result_number_before_point + "F";
        else result_number_before_point = result_number_before_point + to_string(ten_before_point);
    } else {
        result_number_before_point = result_number_before_point + to_string(ten_before_point);
    }
    reverse(result_number_before_point.begin(), result_number_before_point.end());

    if (is_double == true) {
        temporary_number = ten_after_point;
        while (temporary_number != 0) { //Считаем количество цифр в числе после точки
            count_ten_after_point++;
            temporary_number = temporary_number / 10;
        }
        ten_after_point = ten_after_point / pow(10, count_ten_after_point);
        int i = 1;

        while (i <= count_ten_after_point + 3) {
            ten_after_point = ten_after_point * second_system;
            int x = ten_after_point;
            if (second_system > 10) {
                if (x== 10)
                    result_number_after_point = result_number_after_point + "A";
                else if (x == 11)
                    result_number_after_point = result_number_after_point + "B";
                else if (x == 12)
                    result_number_after_point = result_number_after_point + "C";
                else if (x == 13)
                    result_number_after_point = result_number_after_point + "D";
                else if (x == 14)
                    result_number_after_point = result_number_after_point + "E";
                else if (x == 15)
                    result_number_after_point = result_number_after_point + "F";
                else result_number_after_point = result_number_after_point + to_string(x);
            } else {
                result_number_after_point = result_number_after_point + to_string(x);
            }
            ten_after_point -= x;
            i++;
        }
    }
    if (is_double == true) {
        if (sign == true) {
            cout << "Наше число = " << "-" << result_number_before_point + "." + result_number_after_point << endl;
        } else {
            cout << "Наше число = " << result_number_before_point + "." + result_number_after_point <<endl;
        }
    } else {
        if (sign == true) {
            cout << "Наше число = " << "-" << result_number_before_point <<endl;
        } else {
            cout << "Наше число = " << result_number_before_point << endl;
        }
    }
}

int main() {
    string number;
    int first_system = 0;
    int second_system = 0;
    bool point_counter = false;
    bool error = false;
    int i = -1;
    cout << "Введите число, которое хотите перевести в другую систему счисления: ";
    cin >> number;
    cout << "Введите систему счисления,  которой это число определено" << endl;
    cin >> first_system;
//    if ((first_system >= 2) && (first_system <= 16)) {
//
//    while ((i < number.length()) && (error == false)) {
//        i++;
//        if (number[0] != '.') {
//            if ((number[i] == '.') && (point_counter == false)) {
//                point_counter = true;
//
//                if ((number[i] != '-') && (i != 0)) {
//                    error = true;
//                    cout << "Ошибка! Минус должен находиться только в начале числа." << endl;
//                } else {
//
//                    if (first_system == 16) {
//                        if (((number[i] >= 'A') && (number[i] <= 'F')) || ((number[i] >= '0') && (number[i] <= '9'))) {
//                            cout << "Начинаем вычисление!" << endl;
//                        } else {
//                            error = true;
//                            cout << "Ошибка. Цифры в числе не могут быть больше заданной СС" << endl;
//                        }
//                    } else if (first_system == 15) {
//                        if (((number[i] >= 'A') && (number[i] <= 'E')) || ((number[i] >= '0') && (number[i] <= '9'))) {
//                            cout << "Начинаем вычисление!" << endl;
//                        } else {
//                            error = true;
//                            cout << "Ошибка. Цифры в числе не могут быть больше заданной СС" << endl;
//                        }
//                    } else if (first_system == 14) {
//                        if (((number[i] >= 'A') && (number[i] <= 'D')) || ((number[i] >= '0') && (number[i] <= '9'))) {
//                            cout << "Начинаем вычисление!" << endl;
//                        } else {
//                            error = true;
//                            cout << "Ошибка. Цифры в числе не могут быть больше заданной СС" << endl;
//                        }
//                    } else if (first_system == 13) {
//                        if (((number[i] >= 'A') && (number[i] <= 'C')) || ((number[i] >= '0') && (number[i] <= '9'))) {
//                            cout << "Начинаем вычисление!" << endl;
//                        } else {
//                            error = true;
//                            cout << "Ошибка. Цифры в числе не могут быть больше заданной СС" << endl;
//                        }
//                    } else if (first_system == 12) {
//                        if (((number[i] >= 'A') && (number[i] <= 'B')) || ((number[i] >= '0') && (number[i] <= '9'))) {
//                            cout << "Начинаем вычисление!" << endl;
//                        } else  {
//                            error = true;
//                            cout << "Ошибка. Цифры в числе не могут быть больше заданной СС" << endl;
//                        }
//                    } else if (first_system == 11) {
//                        if (((number[i] == 'A')) || ((number[i] >= '0') && (number[i] <= '9'))) {
//                            cout << "Начинаем вычисление!" << endl;
//                        } else {
//                            error = true;
//                            cout << "Ошибка. Цифры в числе не могут быть больше заданной СС" << endl;
//                        }
//                    } else {
//                        char a = number[i];
//                        if (int(a - 48) <= first_system) {
//                            cout << "Начинаем вычисление!" << endl;
//                        } else  {
//                            error = true;
//                            cout << "Ошибка. Цифры в числе не могут быть больше заданной СС" << endl;
//                        }
//                    }
//                }
//            } else  {
//                error = true;
//                cout << "В числе может быть максимум одна точка" << endl;
//            }
//        } else {
//            error = true;
//            cout << "Ошибка. Число не может начинаться с точки" << endl;
//        }
//    }
//
//    } else cout << "Ошибка. СС может быть только в диапазоне от 2 до 16" << endl;
    bool sign = false;
    bool is_double = false;
    int ten_before_point = 0;
    double ten_after_point = 0;
    cout << "Введите систему счисления, в которую Вы хотите перевести данное число" << endl;
    cin >> second_system;
    toTen(number,first_system, sign, is_double, ten_before_point, ten_after_point);

    from_Ten(second_system, sign, is_double, ten_before_point, ten_after_point);

//reverse(str.begin(), str.end());
}
