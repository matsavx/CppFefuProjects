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

    while (runner < number.length()) { //Бегаем, присваиваем
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
    for (int power = count_before_point - 1; power >= 0; power--) { //делаем весь стаф с умножением на СС в степени
        if (isdigit(char_before_point[count_before_point - power - 1])) {
            ten_before_point = ten_before_point + ((int(char_before_point[count_before_point - power - 1] - 48)) *
                                                   pow(first_system,
                                                       power)); //прибавляем получившееся в уже посчитанное
        } else { //Хуета для ебучих СС > 10
            int letter_to_number = 0;
            if (char_before_point[count_before_point - power - 1] == 'A' || char_before_point[power - 1] == 'a')
                letter_to_number = 10;
            if (char_before_point[count_before_point - power - 1] == 'B' || char_before_point[power - 1] == 'b')
                letter_to_number = 11;
            if (char_before_point[count_before_point - power - 1] == 'C' || char_before_point[power - 1] == 'c')
                letter_to_number = 12;
            if (char_before_point[count_before_point - power - 1] == 'D' || char_before_point[power - 1] == 'd')
                letter_to_number = 13;
            if (char_before_point[count_before_point - power - 1] == 'E' || char_before_point[power - 1] == 'e')
                letter_to_number = 14;
            if (char_before_point[count_before_point - power - 1] == 'F' || char_before_point[power - 1] == 'f')
                letter_to_number = 15;
            ten_before_point = ten_before_point + (letter_to_number * pow(first_system, power));
        }
    }
    if (is_double == true) { //Если десятичное то тоже самое только с делением (тк степень отричательная)
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
                if (char_before_point[power - 1] == 'A' || char_before_point[power - 1] == 'a')
                    letter_to_number = 10;
                if (char_before_point[power - 1] == 'B' || char_before_point[power - 1] == 'b')
                    letter_to_number = 11;
                if (char_before_point[power - 1] == 'C' || char_before_point[power - 1] == 'c')
                    letter_to_number = 12;
                if (char_before_point[power - 1] == 'D' || char_before_point[power - 1] == 'd')
                    letter_to_number = 13;
                if (char_before_point[power - 1] == 'E' || char_before_point[power - 1] == 'e')
                    letter_to_number = 14;
                if (char_before_point[power - 1] == 'F' || char_before_point[power - 1] == 'f')
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

    while (ten_before_point >= second_system) { //заходим пока делимое больше СС
        if (second_system > 10) { //Хуета для СС > 10
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
            result_number_before_point = result_number_before_point + to_string(ten_before_point % second_system); //Записываем в строку остаток от деления. Выше та же хуета
        }
        ten_before_point = ten_before_point / second_system; //Когда вышли из цикла - последнее оставшееся делимое тоже надо записать (оно меньше чем СС)
    }
    if (second_system > 10) { // Эта хуета то же самое что и выше, только для этого последнего делимого, которое мы еще не записали. Поэтому его записываем
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
    reverse(result_number_before_point.begin(), result_number_before_point.end()); //Тут переворачиваем строку, тк это нужно по алгоритму перевода

    if (is_double == true) { //Для ебаных десятичных
        int temporary_number = ten_after_point; //в функции перевода в 10тичную мы умножали ten_after_point на 10 в степени, чтобы вывести его, то есть в ten_after_point сейчас целое число, но оно - это наша часть после запятой
        while (temporary_number != 0) { //Считаем количество цифр в числе после точки
            count_ten_after_point++;
            temporary_number = temporary_number / 10;
        }
        ten_after_point = ten_after_point / pow(10, count_ten_after_point); //Смотрим на предыдущий длинный как мой хуй комментарий и возвращаем всё обратно - делим ten_after_point на 10 в степени количества цифр в числе, чтоб было десятичное число (0. и это число)

        int i = 1; //бегунок - бегать по следующему циклу while

        while (i <= count_ten_after_point + 3) {
            ten_after_point = ten_after_point * second_system; //умножаем как в алгоритме
            int x = ten_after_point; //Вот эта хуйня работает так: int - целое число а double - десятичное. Если в int записать double, то вся часть после точки нахуй записываться не будет в этот x
            if (second_system > 10) { //Ебучая проверка для ебучих СС > 10
                if (x== 10)
                    result_number_after_point = result_number_after_point + "A"; //записываем букву в строку (эта строка - наше итоговое число)
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
                else result_number_after_point = result_number_after_point + to_string(x); //Если не > 10, то число (от 0 до 9) переводим в строку
            } else {
                result_number_after_point = result_number_after_point + to_string(x); //Если СС < 11 то в предыдущую хуету не заходим
            }
            ten_after_point = ten_after_point - x; //в ten_after_point щас либо 0. (например 0.123) либо какое-то число с точкой (например 1.123). Мы отнимаем от него х (целая часть которую я писал в ебучем длинном комментарии, чтобы послучить опять число вида 0.123)
            i++; //прибавляем бегунок
        }
    }
    if (is_double == true) { //вывод перенес из функции перевода в 10тичную
        if (sign == true) {
            cout << "Результат перевода: " << "-" << result_number_before_point + "." + result_number_after_point << endl;
        } else {
            cout << "Результат перевода:Наше число = " << result_number_before_point + "." + result_number_after_point <<endl;
        }
    } else {
        if (sign == true) {
            cout << "Результат перевода: " << "-" << result_number_before_point <<endl;
        } else {
            cout << "Результат перевода: " << result_number_before_point << endl;
        }
    }
}

int main() {
    string number;
    int first_system = 0;
    int second_system = 0;
    bool point_counter = false;
    int systemValue = 0;
    bool arrayError = true;
    bool error = false;
    int i = 0;
    cout << "Введите число, которое хотите перевести в другую систему счисления: ";
    cin >> number;
    cout << "Введите систему счисления,  которой это число определено" << endl;
    cin >> first_system;
    char array[] = {'-','.','0','1','2','3','4','5','6','7','8','9','A','a','B','b','C','c','D','d','E','e','F','f'};

    while (i < number.length() && error == false) {
        arrayError = true;
        if (first_system >= 2 || first_system <= 16) {
            if (first_system == 2)
                systemValue = 4;
            if (first_system == 3)
                systemValue = 5;
            if (first_system == 4)
                systemValue = 6;
            if (first_system == 5)
                systemValue = 7;
            if (first_system == 6)
                systemValue = 8;
            if (first_system == 7)
                systemValue = 9;
            if (first_system == 8)
                systemValue = 10;
            if (first_system == 9)
                systemValue = 11;
            if (first_system == 10)
                systemValue = 12;
            if (first_system == 11)
                systemValue = 14;
            if (first_system == 12)
                systemValue = 16;
            if (first_system == 13)
                systemValue = 18;
            if (first_system == 14)
                systemValue = 20;
            if (first_system == 15)
                systemValue = 22;
            if (first_system == 16)
                systemValue = 24;
            for (int j = 0; j < systemValue; j++) {
                if (number[i] == array[j])
                    arrayError = false;
            }

            if (arrayError == false) {
                if ((number[i] == '-' && i == 0) || (number[i] != '-')) {
                    if (number[0] != '.') {
                        if (number[number.length()-1] != '.') {
                            if ((number[i] == '.' && point_counter == false) || (number[i] != '.')) {
                                if (number[i] == '.')
                                    point_counter = true;
                            } else {
                                error = true;
                                cout << "Ошибка. Точка может быть только одна" << endl;
                            }
                        } else {
                            error = true;
                            cout << "Ошибка. Точка не может быть в конце числа" << endl;
                        }
                    } else {
                        cout << "Ошибка. Число не может начинаться с точки" << endl;
                        error = true;
                    }
                } else {
                    error = true;
                    cout << "Ошибка. Минус может стоять только в начале" << endl;
                }
            } else {
                error = true;
                cout << "Ошибка. Недопустимый символ в числе" << endl;
            }
        } else {
            error = true;
            cout << "Ошибка. Система счисления должна быть в диапазоне от 2 до 16" << endl;
        }
        i++;
    }

    if (error != true) {
        bool sign = false;
        bool is_double = false;
        int ten_before_point = 0;
        double ten_after_point = 0;
        cout << "Введите систему счисления, в которую Вы хотите перевести данное число" << endl;
        cin >> second_system;
        if (second_system >= 2 && second_system <= 16) {
            toTen(number, first_system, sign, is_double, ten_before_point, ten_after_point);

            from_Ten(second_system, sign, is_double, ten_before_point, ten_after_point);
        } else
            cout << "Ошибка. Система исчисления должна быть в диапазоне от 2 до 16" << endl;
    } else
        cout << "Программа завершена. Запустите её заново с корректно введенными значениями" << endl;
}
