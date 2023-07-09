#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 10;

//TODO:: Сделать что-то с эти константами 22:12 10.05
struct Raz_Matr {
    int index_vector[MAX];
    int column_vector[MAX];
    int elem_vector[MAX];
    int matrix[MAX][MAX];
};

class MatrixClass {
private:
    Raz_Matr A;
    int n, m, k, I, J;

public:
    void Read_Matr(/*ifstream f,*/Raz_Matr A);
    int Element(Raz_Matr A, int I, int J);
    void Print(Raz_Matr A);
};


void MatrixClass::Read_Matr(/*ifstream f1,*/ Raz_Matr A1) {
    string str,vrem;
    int eraser = 0;

    ifstream f ("C:\\myfiles\\MyClionProjects\\RazMatrix\\file"); // хз почему, скорее всего неправильно передаю параметры

    getline(f,str);

    for (int i = 0; str[i]!=' '; i++) {
        vrem += str[i];
        eraser = i;
    }
    n = stoi(vrem);
    str.erase(1,(eraser+1));

    for (int i = 0; str[i]!=' '; i++) {
        vrem += str[i];
        eraser = i;
    }
    m = stoi(vrem);
    str.erase(1,(eraser+1));

    for (int i = 0; str[i]!=' '; i++) {
        vrem += str[i];
    }
    k = stoi(vrem);

    getline(f,str); //Тут может быть проблема с считыванием 23:07 10.05

    int runner = 0;
    while (runner < k){
        for (int i = 0; str[i]!=' '; i++) {
            vrem += str[i];
            eraser = i;
        }
        str.erase(1,(eraser+1));
        runner++;
        A1.elem_vector[runner] = stoi(vrem);
    }

    getline(f,str);

    runner = 0;

    while (runner < k){
        for (int i = 0; str[i]!=' '; i++) {
            vrem += str[i];
            eraser = i;
        }
        str.erase(1,(eraser+1));
        runner++;
        A1.column_vector[runner] = stoi(vrem);
    }

    getline(f,str);

    runner = 0;

    while (runner < n){
        for (int i = 0; str[i]!=' '; i++) {
            vrem += str[i];
            eraser = i;
        }
        str.erase(1,(eraser+1));
        runner++;
        A1.index_vector[runner] = stoi(vrem);
    }

    f.close();
}

int MatrixClass::Element(Raz_Matr A1, int I1, int J1) {

    if ((A1.index_vector[I1] == A1.index_vector[I1 + 1]) || (A1.index_vector[I1] = 0)) //Сломается ли это в последней строчке
        A1.matrix[I1][J1] = 0;
    else {
        A1.matrix[I1][J1] = 0;
        for(int i = A1.index_vector[I1]; i < A1.index_vector[I1+1]; i++){
            if (J1 == A1.column_vector[i])
                A1.matrix[I1][J1] = A1.elem_vector[i];
        }
    }

    return A1.matrix[I1][J1];
}

void MatrixClass::Print(Raz_Matr A1) {

    for (I = 1; I < n; I++){
        for (J = 1; J < m; J++){
            cout << Element(A,I,J) << " ";
        }
        cout << endl;
    }
}

int main() {

}


