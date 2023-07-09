#include <iostream>
#include <fstream>

using namespace std;

struct Raz_Matr {
    int *index_vector;
    int *column_vector;
    int *elem_vector;
    int n, k, m;
};

Raz_Matr A;
int I, J;

/*void readFirstString(ifstream &f1, int &n, int&m, int &k){
    string str,vrem;
    int eraser = 0;

    getline(f1,str);

    for (int i = 0; str[i]!=' '; i++) {
        vrem += str[i];
        eraser = i;
    }
    n = stoi(vrem);
    str.erase(0,(eraser+2));

    vrem = "";
    for (int i = 0; str[i]!=' '; i++) {
        vrem += str[i];
        eraser = i;
    }
    m = stoi(vrem);
    str.erase(0,(eraser+2));

    vrem = "";
    for (int i = 0; str[i]!='\r'; i++) {
        vrem += str[i];
    }
    k = stoi(vrem);
}*/


void Read_Matr(ifstream &f1, Raz_Matr &A1) {
    string str =  " ";
    string vrem;
    int eraser = 0;

    getline(f1,str);

    for (int i = 0; str[i]!=' '; i++) {
        vrem += str[i];
        eraser = i;
    }
    A1.n = stoi(vrem);
    str.erase(0,(eraser+2));

    vrem = "";
    for (int i = 0; str[i]!=' '; i++) {
        vrem += str[i];
        eraser = i;
    }
    A1.m = stoi(vrem);
    str.erase(0,(eraser+2));

    vrem = "";
    for (int i = 0; str[i]!='\r'; i++) {
        vrem += str[i];
    }
    A1.k = stoi(vrem);
    vrem = "";

    A1.index_vector = new int[A1.n];
    A1.column_vector = new int[A1.k];
    A1.elem_vector = new int[A1.k];

    getline(f1, str);

    int runner = 0;
    while (runner < A1.k) {
        for (int i = 0; (str[i] != ' ') && (str[i] != '\r'); i++) {
            vrem += str[i];
            eraser = i;
        }
        str.erase(0, (eraser + 2));
        A1.elem_vector[runner] = stoi(vrem);
        vrem = "";
        runner++;
    }

    getline(f1, str);

    runner = 0;

    while (runner < A1.k) {
        for (int i = 0; (str[i] != ' ') && (str[i] != '\r'); i++) {
            vrem += str[i];
            eraser = i;
        }
        str.erase(0, (eraser + 2));
        A1.column_vector[runner] = stoi(vrem);
        vrem = "";
        runner++;
    }

    getline(f1, str);

    for (int run = 0; run < A1.n; run++) {
        for (int i = 0; (str[i] != ' ') && (str[i] != '\0'); i++) {
            vrem += str[i];
            eraser = i;
        }
        str.erase(0, (eraser + 2));
        A1.index_vector[run] = stoi(vrem);
        vrem = "";
    }
}

int Element(Raz_Matr &A1, int &I1, int &J1) {
    if ((A1.index_vector[I1] == A1.index_vector[I1 + 1]) || (A1.index_vector[I1] == 0))
        return 0;
    else {
        for(int i = A1.index_vector[I1]-1; i < A1.index_vector[I1+1]-1; i++){
            if (J1 == A1.column_vector[i]-1)
                return A1.elem_vector[i];
        }
        if (I1 == (A1.n-1)) {
            for(int i = A1.index_vector[I1]-1; i < A1.k; i++){
                if (J1 == A1.column_vector[i]-1)
                    return A1.elem_vector[i];
            }
        }
    }
    return 0;
}

void Print(Raz_Matr &A1) {
    for (I = 0; I < A1.n; I++){
        for (J = 0; J < A1.m; J++){
            cout << Element(A1,I,J) << " ";
        }
        cout << endl;
    }
}

int main() {
    ifstream f("../file");
    Raz_Matr mymatrix;
    //readFirstString(f, n, m, k);
    //mymatrix.index_vector = new int[n];
    //mymatrix.column_vector = new int[k];
    //mymatrix.elem_vector = new int[k];
    Read_Matr(f, mymatrix);
    f.close();
    Print(mymatrix);
}