#include <iostream>
#include <string>
#include <fstream>
#include "lib.h"

using namespace std;

int main() {

    //time_name t1;
    table g, d, s, t;
    string str;
    int count, de;

    string mygroup, myday;

    ifstream f ("C:\\myfiles\\MyClionProjects\\xan\\timetable");


    cout << "Введите номер группы: ";
    cin >> mygroup;
    cout << endl << "Введите день недели: ";
    cin >> myday;
    cout << endl;


    while (getline(f, str)) {

        reading (count, str, g, d, s, t, myday, mygroup);

    }

    f.close();

}
