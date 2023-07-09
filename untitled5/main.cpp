#include <iostream>

using namespace std;

struct TNode {
    string name = "";
    int value = 0;
};

class Graph {
private:
    int N = 0;
    int** matrix = nullptr;
public:
    Graph() {
        N = 0;
        matrix = nullptr;
    }
    ~Graph() {
        delete[] matrix;
    }

    void AddVertex(int column, const string vertexName) {
        if (column <= 0)
            cout << "Ошибка! Место вставки указано неверно. Место вставки не может быть меньше или равно нулю." << endl;
        else if (column > N+1)
            cout << "Ошибка! Место вставки не может быть больше количества вершин+1." << endl;
        else if (N == 0) {
            N++;
            matrix = new int*[N];
        }
        else if (N > 0) {
            int max = N;
            int** temporaryArray = new int *[max];
            for (int i = 0; i < max; i++) {
                for (int j = 0; j < max; j++)
                    temporaryArray[i][j] = matrix[i][j];
            }
            delete [] matrix;
            N++;
            matrix = new int*[N];
            for (int i = 0; i < max; i++) {
                for (int j = 0; j < max; j++)
                    matrix[i][j] = temporaryArray[i][j];
            }
            
            for (int j = N-1; j <= column-1; j++) {
                for (int i = 0; i < N; i++)
                    matrix[i][j] = matrix[i][j-1];
            }
//            for (int i = 0; i < N; i++) {
//                matrix[i][column - 1].name = vertexName;
//                matrix[column - 1][i].name = vertexName;
//            }
        }
    }

    void print() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << matrix[i][j];
            cout << endl;
        }
    }
};

int main() {
    Graph graph;
    graph.AddVertex(1,"x1");
    graph.AddVertex(2,"x2");
    graph.AddVertex(3,"x3");
    graph.print();
}
