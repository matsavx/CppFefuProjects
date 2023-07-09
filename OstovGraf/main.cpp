//TODO::Неориентированный граф
//TODO::Матрица смежности array[N] of array[N]
//TODO::Добавление, удаление, поиск вершины/дуги, печать
//TODO::Алгоритм - Дейкстра
//TODO::Обход вершин графа в глубину (99-100)

#include <iostream>

using namespace std;

struct NodeArray {
    int name = 0;
    int *ptr = nullptr;
};

class Graph {
private:
    int N = 0;
    NodeArray *array = nullptr;
public:
    Graph() {
        N = 0;
        array = nullptr;
    }
    ~Graph(){
        delete [] array;
    }
    void AddVertex(int vertexName);
    void RemoveVertex(int vertexName);
    string SearchVertex(int vertexName);
    void AddArc(int firstName, int secondName, int weight);
    void RemoveArc(int firstName, int secondName);
    int SearchArc(int firstName, int secondName);
    void print();
    void Dijkstra(int st);
};

void Graph::AddVertex(int vertexName) {
    bool nameFlag = true;
    for (int i = 0; i < N; i++) {
        if (vertexName == array[i].name)
            nameFlag = false;
    }
    if (vertexName < 1)
        cout << "Ошибка. Имя вершины должно быть больше 0" << endl;
    else if (N == 0) {
        N++;
        array = new NodeArray[N];
        array[0].ptr = new int[N];
        array[0].name = vertexName;
    } else if (!nameFlag)
        cout << "Ошибка! Вершина с таким именем уже существует." << endl;
        else {
            int max = N;
            auto *temporaryArray = new NodeArray[max];
            for (int k = 0; k < max; k++)
                temporaryArray[k].ptr = new int[max];
            for (int i = 0; i < max; i++) {
                temporaryArray[i].name = array[i].name;
                for (int j = 0; j < max; j++)
                    temporaryArray[i].ptr[j] = array[i].ptr[j];
            }
            N++;
            array = new NodeArray[N];
            for (int k = 0; k < N; k++)
                array[k].ptr = new int[N];
            for (int i = 0; i < N-1; i++) {
                array[i].name = temporaryArray[i].name;
                for (int j = 0; j < N-1; j++)
                    array[i].ptr[j] = temporaryArray[i].ptr[j];
            }
            for (int i = 0; i < N; i++) {
                array[N-1].ptr[i] = 0;
                array[i].ptr[N-1] = 0;
            }
            delete [] temporaryArray;

            if (vertexName > array[N-2].name)
                array[N-1].name = vertexName;
            else {
                int column = 0;
                bool colFlag = false;
                while ((column != N) && (!colFlag)) {
                    if (vertexName > array[column].name) column++;
                    else colFlag = true;
                }
                for (int i = N - 1; i > column; i--) {
                    for (int j = N - 1; j > column; j--) {
                        array[i].ptr[j] = array[i].ptr[j - 1];
                    }
                }
                for (int i = 0; i <= column; i++) {
                    for (int j = N - 1; j > column; j--) {
                        array[i].ptr[j] = array[i].ptr[j - 1];
                    }
                }
                if (column == 0) {
                    for (int i = N - 1; i > column; i--) {
                        for (int j = 0; j < N; j++) {
                            array[i].ptr[j] = array[i - 1].ptr[j];
                        }
                        array[i].name = array[i - 1].name;
                    }
                    for (int i = 0; i < N; i++) {
                        array[column].ptr[i] = 0;
                        array[i].ptr[column] = 0;
                    }
                    array[column].name = vertexName;
                } else {
                    for (int i = N - 1; i > column - 1; i--) {
                        for (int j = 0; j < N; j++) {
                            array[i].ptr[j] = array[i - 1].ptr[j];
                        }
                        array[i].name = array[i - 1].name;
                    }
                    array[column].name = vertexName;
                    for (int i = 0; i < N; i++)
                        array[column].ptr[i] = 0;
                    for (int i = 0; i < N; i++) {
                        array[column].ptr[i] = 0;
                        array[i].ptr[column] = 0;
                    }
                }
            }
        }

}

void Graph::RemoveVertex(int vertexName) {
    bool removeVertex = false;
    int column = 0;
    if (N == 0)
        cout << "Ошибка! Граф не имеет ни одной вершины. Удаление невозможно." << endl;
    else {
        while ((column != N) && (!removeVertex)) {
            if (array[column].name != vertexName)
                column++;
            else removeVertex = true;
        }
    }
    if (!removeVertex)
        cout << "Ошибка! Такой вершины нет." << endl;
    else { //удаляем и перемещаем
        array[column].name = 0;
        for (int i = column; i < N; i++) {
            for (int j = column; j < N - 1; j++)
                array[i].ptr[j] = array[i].ptr[j + 1];
            array[i].ptr = array[i + 1].ptr;
            array[i].name = array[i + 1].name;
        }
        for (int i = 0; i < column; i++) {
            for (int j = column; j < N - 1; j++)
                array[i].ptr[j] = array[i].ptr[j + 1];
        }
//        array[column].ptr[column] = 0;

        array[N - 1].ptr = nullptr;

        //Уменьшаем размер массива
        int max = N - 1;
        auto *temporaryArray = new NodeArray[max];
        for (int i = 0; i < max; i++) {
            temporaryArray[i].ptr = new int[max];
//            temporaryArray[i].ptr = array[i].ptr;
            temporaryArray[i].name = array[i].name;
            for (int j = 0; j < max; j++)
                temporaryArray[i].ptr[j] = array[i].ptr[j];
        }
        N--;
        array = new NodeArray[N];
        for (int k = 0; k < N; k++)
            array[k].ptr = new int[N];
        for (int i = 0; i < N; i++) {
//            array[i].ptr = temporaryArray[i].ptr;
            array[i].name = temporaryArray[i].name;
            for (int j = 0; j < N; j++)
                array[i].ptr[j] = temporaryArray[i].ptr[j];
        }
        delete[] temporaryArray;
    }
}

string Graph::SearchVertex(int vertexName) {
    cout << "Результат поиска вершины ( " << vertexName << " ): ";
    if (N == 0)
        cout << "Ошибка! Граф не существует. Поиск невозможен." << endl;
    else {
        for (int i = 0; i < N; i++) {
            if (array[i].name == vertexName)
                return "Вершина с таким именем существует. Ее индекс в таблице: " + to_string(i+1);
        }
        return "Вершины с таким именем не существует.";
    }
}

void Graph::AddArc(int firstName, int secondName, int weight) {
    int nameFirstArc = 0;
    int nameSecondArc = 0;
    bool arcFirstName = false;
    bool arcSecondName = false;
    while ((nameFirstArc != N) && (!arcFirstName))
        if (array[nameFirstArc].name != firstName) nameFirstArc++;
        else arcFirstName = true;
    while ((nameSecondArc != N) && (!arcSecondName))
        if (array[nameSecondArc].name != secondName) nameSecondArc++;
        else arcSecondName = true;
    if (!arcFirstName && !arcSecondName)
        cout << "Ошибка! (Добавление дуги) Вершины с таким названием не существует." << endl;
    else if (weight < 0)
        cout << "Ошибка! (Добавление дуги) Вес дуги введен неверно. Дуга не может иметь отрицательный вес." << endl;
    else if (weight == 0)
        cout << "Предупреждение! (Добавление дуги) Дуга не добавлена, так как введенный вес равен нулю." << endl;
    else if (firstName == secondName)
        cout << "Ошибка! (Добавление дуги) Дуга не добавлена, так как цепных дуг быть не может." << endl;
    else {
        array[nameFirstArc].ptr[nameSecondArc] = weight;
        array[nameSecondArc].ptr[nameFirstArc] = weight;
    }
}

void Graph::RemoveArc(int firstName, int secondName) {
    int nameFirstArc = 0;
    int nameSecondArc = 0;
    bool arcFirstName = false;
    bool arcSecondName = false;
    while ((nameFirstArc != N) && (!arcFirstName))
        if (array[nameFirstArc].name != firstName) nameFirstArc++;
        else arcFirstName = true;
    while ((nameSecondArc != N) && (!arcSecondName))
        if (array[nameSecondArc].name != secondName) nameSecondArc++;
        else arcSecondName = true;
    if (!arcFirstName && !arcSecondName)
        cout << "Ошибка! (Удаление дуги) Вершины с таким названием не существует." << endl;
    else {
        array[nameFirstArc].ptr[nameSecondArc] = 0;
        array[nameSecondArc].ptr[nameFirstArc] = 0;
    }
}

int Graph::SearchArc(int firstName, int secondName) {
    cout << "Результат поиска дуги ( " << firstName << " " << secondName << " ): ";
    int nameFirstArc = 0;
    int nameSecondArc = 0;
    bool arcFirstName = false;
    bool arcSecondName = false;
    while ((nameFirstArc != N) && (!arcFirstName))
        if (array[nameFirstArc].name != firstName) nameFirstArc++;
        else arcFirstName = true;
    while ((nameSecondArc != N) && (!arcSecondName))
        if (array[nameSecondArc].name != secondName) nameSecondArc++;
        else arcSecondName = true;
    if (!arcFirstName && !arcSecondName) {
        cout << "Ошибка! (Поиск дуги) Вершины с таким названием не существует. ";
        return -1;
    }
    else
        return array[nameFirstArc].ptr[nameSecondArc];
}

void Graph::print() {
    if (N==0)
        cout << "Вершин нет. Печатать нечего" << endl;
    else {
        cout << "\t";
        for (int i = 0; i < N; i++)
            cout << array[i].name << "\t";
        cout << endl;
        for (int i = 0; i < N; i++) {
            cout << array[i].name << "\t";
            for (int j = 0; j < N; j++)
                cout << array[j].ptr[i] << "\t";
            cout << endl;
        }
    }
    cout << "--------------------------------------------------" << endl;
}

void Graph::Dijkstra(int vertexName) { //На вход порядковый номер вершины в таблице, от которой нужно найти кратчайший путь до остальных вершин.
    int column = 0;
    bool dFlag = false;
    while ((column != N) && (!dFlag)) {
        if (array[column].name != vertexName)
            column++;
        else dFlag = true;
    }
    if (!dFlag)
        cout << "Ошибка! (Алгоритм Дейкстры) Начальная вершина указана неверно. Вершины с таким именем не существует." << endl;
    else {
        int distance[N];
        int st = column + 1;
        int index = 0, u = 0, m = st;
        bool visited[N];

        for (int i = 0; i < N; i++) {
            distance[i] = 2147483647;
            visited[i] = false;
        }
        distance[st - 1] = 0;
        for (int count = 0; count < N - 1; count++) {
            int min = 2147483647;
            for (int i = 0; i < N; i++)
                if (!visited[i] && distance[i] <= min) {
                    min = distance[i];
                    index = i;
                }
            u = index;
            visited[u] = true;
            for (int i = 0; i < N; i++)
                if (!visited[i] && array[i].ptr[u] && distance[u] != 2147483647 &&
                    distance[u] + array[i].ptr[u] < distance[i])
                    distance[i] = distance[u] + array[i].ptr[u];
        }
        cout << "Стоимость пути из начальной вершины до остальных:\t\n";
        for (int i = 0; i < N; i++) {
            if (distance[i] != 2147483647) {
                cout << array[m - 1].name << " > " << array[i].name << " = " << distance[i] << endl;
            } else cout << array[m - 1].name << " > " << array[i].name << " = " << "маршрут недоступен" << endl;
        }
    }
}

int main() {
    Graph graph;

    for (int i=10;i<16;i++){
        graph.AddVertex(26-i);
        graph.AddVertex(i);
    }
    graph.print();

    for (int i=10;i<16;i++){
        for (int j=10;j<16;j++){
            graph.AddArc(i,26-j,(i+j)%5);
        }
    }
    graph.print();

    cout << graph.SearchArc(10,11) << endl;
    cout << graph.SearchArc(10,12) << endl;
    cout << graph.SearchVertex(11) << endl;
    cout << graph.SearchVertex(1) << endl;



//    graph.AddVertex(2);
//
//    graph.AddVertex(4);
//   graph.AddArc(2,4,20);
//    graph.print();
//    graph.AddVertex(3);
//    graph.AddArc(2,3,10);
//    graph.AddArc(3,4,5);
//    graph.print();
//
//    graph.AddVertex(1);
//    graph.AddArc(1,2,8);
//    graph.AddArc(3,1,15);
//    graph.AddArc(4,1,18);
//    graph.print();
//    graph.RemoveVertex(3);
//    graph.print();
//
//    graph.RemoveArc(4,2);
//    graph.print();
//
//    cout << graph.SearchVertex(3) << endl;
//    cout << graph.SearchVertex(5) << endl;
//    cout << graph.SearchArc(1,3) << endl;
//    cout << graph.SearchArc(2,4) << endl;


    graph.Dijkstra(10); //На вход порядковый номер вершины в таблице, от которой нужно найти кратчайший путь до остальных вершин.
}