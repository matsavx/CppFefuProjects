#include <iostream>
#include <iostream>
#include <math.h>

using namespace std;

const int n = 4;

void Displaying_Matrix(bool **matrix, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < pow(2, n); j++) {

            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}

int NumberOfMass(char mass[n], char *mas) {

    int sizeMass = (int) pow(2, n);
    int result = 0;

    for (int i = 0; i < n; i++) {
        if (mass[i] == mas[i]) {
            result += ((int) pow(2, n - i)) / 2;
        }
    }
    return result;
}

int main() {

    ifstream f ("C:\\myfiles\\MyClionProjects\\стргенслав\\main.cpp");

    getline (f, str);

    char mas[n];

    for (int op = 1; op <= n; op++){
        mas[op] = str[op];
    }


    int lines = (int) pow(2, n);

    bool matrix[n][lines];

    for (int i = 0; i < n; i++) {

        int repeat = (int) pow(2, i);

        int limiter = 0;

        int helper = repeat;

        bool repeter = true;

        while (limiter < lines) {

            if (helper > 0 && repeter) {

                matrix[i][limiter] = false;
                helper--;

            } else {

                matrix[i][limiter] = true;
                repeter = false;
                helper++;

                if (helper == repeat * 2) {

                    repeter = true;
                }
            }
            limiter++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < lines; j++) {

            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;

    bool podmn[n];

    for (int i = 0; i < n; i++) {

        cout << "Введите " << i+11 << " символ подмножества: ";
        cin >> podmn[i];
        cout << endl;
    }

    int chet = 0;
    int result;

    for (int i = 0; i<lines; i++){
        for(int j = 0; j<n; j++){

            if(matrix[j][i] == podmn[j]){
                chet++;
            }
            if(chet == n){
                result = i;
            }

        }
        chet = 0;
    }

    cout<<"Номер вашего подмножества в кодах Грея: "<<result+1;

    return 0;
}
