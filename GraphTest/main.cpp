//TODO::Неориентированный граф
//TODO::Матрица смежности array[N] of array[N]
//TODO::Добавление, удаление, поиск вершины/дуги, печать
//TODO::Алгоритм - Дейкстра
//TODO::Обход вершин графа в глубину (99-100)

#include <iostream>

using namespace std;

struct NodeArray {
    int name = 0;
    //int visit = 0;
    int *ptr = nullptr;
};

class Graph {
private:
    int N = 0;
    NodeArray *array = nullptr;
public:
    Graph(int N) {
        this->N = N;
        array = new NodeArray[N];
    }
    ~Graph(){
//        for (int i = 0; i < N; i++) {
//            for(int j = 0; j < N; j++) {
//                array[i].ptr[j].visit = 0;
//            }
//            delete [] array[i].ptr;
//        }
//        N = 0;
        delete [] array;
    }
    void AddVertex(unsigned short column, int vertexName);
    void RemoveVertex(unsigned short column);
    string SearchVertex(int vertexName);
    void AddArc(unsigned short line, unsigned short column, int weight);
    void RemoveArc(unsigned short line, unsigned short column);
    int SearchArc(unsigned short line, unsigned short column);
    void print();
    void Dijkstra(int st);
};

void Graph::AddVertex(unsigned short column, const int vertexName) {

    if (column <= 0)
        cout << "Ошибка! Место вставки указано неверно. Место вставки не может быть меньше или равно нулю." << endl;
    else if (column > N+1)
        cout << "Ошибка! Место вставки не может быть больше количества вершин+1." << endl;
    else if (N != 0) {
        //Добавление новой ячейки массиву через копирование
        int max = N;
        auto *temporaryArray = new NodeArray[max];
        for (int k = 0; k < max; k++)
            temporaryArray[k].ptr = new int[max];
        for (int i = 0; i < max; i++) {
            temporaryArray[i].ptr = array[i].ptr;
            temporaryArray[i].name = array[i].name;
            for (int j = 0; j < max; j++)
                temporaryArray[i].ptr[j] = array[i].ptr[j];
        }
        N++;
        array = new NodeArray[N];
        for (int k = 0; k < N; k++)
            array[k].ptr = new int[N];
        for (int i = 0; i < N-1; i++) {
            array[i].ptr = temporaryArray[i].ptr;
            array[i].name = temporaryArray[i].name;
            for (int j = 0; j < N-1; j++)
                array[i].ptr[j] = temporaryArray[i].ptr[j];
        }
        delete [] temporaryArray;

        //Вставка новой вершины в указанное место в массиве
        for (int i = N-1; i >= column-1; i--) {
            for (int j = N-1; j >= column; j++)
                array[i].ptr[j] = array[i].ptr[j-1];
            array[i].ptr = array[i-1].ptr;
        }
        array[column-1].name = vertexName;
    } else {
        N++;
        array = new NodeArray[N];
        array[0].ptr = new int[N];
        array[0].name = vertexName;
    }
}

void Graph::RemoveVertex(unsigned short column) {
    if (N == 0)
        cout << "Ошибка! Граф не имеет ни одной вершины. Удаление невозможно." << endl;
    else if ((column <= 0) || (column > N))
        cout << "Ошибка! Столбцы нумерованы от 1 до значения количества вершин." << endl;
    else //удаляем и перемещаем
        array[column-1].name = 0;
    for (int i = column-1; i < N-1; i++) {
        for (int j = column-1; j < N-1; j++)
            array[i].ptr[j] = array[i].ptr[j+1];
        array[i].ptr = array[i+1].ptr;
        array[i].name = array[i+1].name;
    }
    array[N-1].ptr = nullptr;

    //Уменьшаем размер массива
    int max = N-1;
    auto *temporaryArray = new NodeArray[max];
    for (int i = 0; i < max; i++) {
        temporaryArray[i].ptr = new int[max];
        temporaryArray[i].ptr = array[i].ptr;
        temporaryArray[i].name = array[i].name;
        for (int j = 0; j < max; j++)
            temporaryArray[i].ptr[j] = array[i].ptr[j];
    }
    N--;
    array = new NodeArray[N];
    for (int k = 0; k < N; k++)
        array[k].ptr = new int[N];
    for (int i = 0; i < N; i++) {
        array[i].ptr = temporaryArray[i].ptr;
        array[i].name = temporaryArray[i].name;
        for (int j = 0; j < N; j++)
            array[i].ptr[j] = temporaryArray[i].ptr[j];
    }
    delete [] temporaryArray;
}

string Graph::SearchVertex(int vertexName) {
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

void Graph::AddArc(unsigned short line, unsigned short column, int weight) {
    if ((line < 1) || (line > N))
        cout << "Ошибка! Номер строки введен неверно. Значение должно быть от 1 до значения количества существующих вершин" << endl;
    else if ((column < 1) || (column > N))
        cout << "Ошибка! Номер столбца введен неверно. Значение должно быть от 1 до значения количества существующих вершин" << endl;
    else if (weight < 0)
        cout << "Ошибка! Вес дуги введен неверно. Дуга не может иметь отрицательный вес." << endl;
    else if (weight == 0)
        cout << "Предупреждение! Дуга не добавлена, так как введенный вес равен нулю." << endl;
    else if (line == column)
        cout << "Ошибка! Дуга не добавлена, так как цепных дуг быть не может." << endl;
    else
        array[column - 1].ptr[line - 1] = weight;
}

void Graph::RemoveArc(unsigned short line, unsigned short column) {
    if ((line < 1) || (line > N))
        cout << "Ошибка! Номер строки введен неверно. Значение должно быть от 1 до значения количества существующих вершин" << endl;
    else if ((column < 1) || (column > N))
        cout << "Ошибка! Номер столбца введен неверно. Значение должно быть от 1 до значения количества существующих вершин" << endl;
    else if (array[column-1].ptr[line-1] == 0)
        cout << "Предупреждение! Вы пытаетесь удалить несуществующую дугу." << endl;
    else {
        array[column-1].ptr[line-1] = 0;
        array[line-1].ptr[column-1] = 0;
    }
}

int Graph::SearchArc(unsigned short line, unsigned short column) {
    if ((line < 1) || (line > N))
        cout << "Ошибка! Номер строки введен неверно. Значение должно быть от 1 до значения количества существующих вершин" << endl;
    else if ((column < 1) || (column > N))
        cout << "Ошибка! Номер столбца введен неверно. Значение должно быть от 1 до значения количества существующих вершин" << endl;
    else {
        cout << "Результат поиска: ";
        return array[column - 1].ptr[line - 1];
    }
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
}

void Graph::Dijkstra(int st) {
    int distance[N];
    int index = 0, u = 0, m = st;
    bool visited[N];
//    for (int j = 0; j < N; j++) { //строки
//        distance[j] = array[j].ptr[j].visit;
//        for (int i = 0; i < N; i++) { //столбцы
//            if (distance[j] > array[i].ptr[j].visit)
//                distance[j] = array[i].ptr[j].visit;
//        }
//        visited[j] = false;
//    }
    for (int i=0; i < N; i++)
    {
        distance[i] = 2147483647;
        visited[i] = false;
    }
    distance[st-1]=0;
    for (int count = 0; count < N-1; count++) {
        int min = 2147483647;
        for (int i = 0; i < N; i++)
            if (!visited[i] && distance[i]<=min)
            {
                min = distance[i];
                index = i;
            }
        u = index;
        visited[u]=true;
        for (int i = 0; i < N; i++)
            if (!visited[i] && array[i].ptr[u] && distance[u]!=2147483647 && distance[u]+array[i].ptr[u] < distance[i])
                distance[i]=distance[u]+array[i].ptr[u];
    }
    cout<<"Стоимость пути из начальной вершины до остальных:\t\n";
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (distance[i] != 2147483647) {
            cout << m << " > " << i + 1 << " = " << distance[i] << endl;
            sum += distance[i];
        } else cout << m << " > " << i + 1 << " = " << "маршрут недоступен" << endl;
    }
    cout << "Сумма пути: " << sum << endl;
}

int main() {
    Graph graph(4);
    graph.AddVertex(1,1);
    graph.AddVertex(2,2);
    graph.AddVertex(3,3);
    graph.AddVertex(4,4);
    graph.AddArc(1,2,20);
    graph.AddArc(1,3,10);
    graph.AddArc(1,4,8);
    graph.AddArc(2,3,5);
    graph.AddArc(2,4,15);
    graph.AddArc(3,4,18);

    graph.print();

//    cout << graph.SearchArc(1,2) << endl;
//    cout << graph.SearchArc(2,3) << endl;
//    cout << graph.SearchArc(1,1) << endl;

//    cout << graph.SearchVertex("x3") << endl;
//    cout << graph.SearchVertex("x4") << endl;
//    graph.RemoveVertex(3);
//    cout << graph.SearchVertex("x3") << endl;
//    cout << graph.SearchVertex("x4") << endl;

    //graph.Dijkstra(1);
}