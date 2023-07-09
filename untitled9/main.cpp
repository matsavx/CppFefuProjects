#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    // указатель на адрес следующего узла
    Node<T> *next;
public:
    T data;
    //конструктор
    Node(const T& item, Node<T> *ptrnext = NULL):
            data(item), next(ptrnext) {return;}
    // Вставка следующим
    void InsertAfter(Node<T> *p)
    {
        p->next = next;
        next = p;
    }
    void InsertFront(Node<T> *p, T item) {
        p = next;
        p->next = next;
        p->data = item;

    }
    Node<T>*GetNode(const T& item)
    {
        Node<T> *p;
        p = new Node<T>(item,p);
        return p;
    }
// Удаление следующего
    Node<T> *DeleteAfter(void);
    // Получение адреса следующего
    Node<T> *NextNode(void) const {return next;}
};

template <class T>
void InsertOrder(Node<int> *head, T item) { //Функция добавления элемента по возрастанию значению
    Node<T> *currPtr, *prevPtr, *newNode; //Создаем указатели: текущего узла, предыдущего, и на новый создаваемый узел с введенным элементом
    prevPtr = NULL; //Предыдущий перед первым, поэтому он 0
    currPtr = head; //Голова - первый элемент
    while (currPtr != NULL) //Пока текущий узел не 0 (то есть пока не пройдем все)
    {
        if (item < currPtr->data) //Если нашли место вставки, то выйдем из цикла while
            break;
        prevPtr = currPtr; //Иначе, пока двигаемся до места вставки предыдущему указателю присваиваем текущий узел
        currPtr = currPtr->NextNode(); //А текущему - следующий. То есть переписываем, пока двигаемся
    }
    if (prevPtr == NULL) //Если указатель на предыдущий узел это 0, то есть если текущий узел - первый, значит мы не сдвинулись с места и надо добавить вводимый элемент в самое начало
        prevPtr->InsertFront(head, item); //Добавление этого элемента в начало
    else //А иначе
    {
        newNode = prevPtr->GetNode(item); //Создаем новый узел и в него запихиваем введенное значение
        prevPtr->InsertAfter(newNode); //указатель на предыдущий переписывается. Теперь этот указатель указывает на вставленный новый узел (связываем текущий с новым (новую 4ку с 5кой))
    }
}

template <class T>
Node<T>* Node<T>::DeleteAfter(void)
{
    // если нет следующего возвратить NULL
    if (next==NULL) return NULL;
    // сохранить адрес удаляемого узла
    Node<T> *tempPtr = next;
    // текущий указывает на узел, следующий за удаляемым
    next = tempPtr->next;
    // возвратить указатель на удаляемый узел
    return tempPtr;
}

template <class T>
void PrintNodeList(Node<T> * head)
{
    if (!head) {cout <<"\nList empty"; return;}
    cout << '\n';
    while (head)
    {
        cout << head->data << '\t';
        head = head->NextNode();
    }
}

template <class T>
Node<T> *BuildNodeList(T M[], int n)
{
    Node<T> *head=NULL;
    for (int i = n-1; i>=0; i--)
        head= new Node<T>(M[i],head);
    return head;
}

int main(int argc, char** argv)
{
    int M[]={1,2,3,5};
    Node <int> *p=BuildNodeList(M,4); //Создали список длинной 4
    InsertOrder(p,4); //Добавляем в список р элемент 4
    PrintNodeList(p); //Печать
    return 0;
}
