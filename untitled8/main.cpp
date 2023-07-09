#include <iostream>
using namespace std;

template <class T>
class TNode {
private:
    TNode *prev, *next;
public:
    T data;
    TNode(const T& item, TNode<T> *ptrprev = NULL, TNode<T> *ptrnext = NULL):data(item), prev(ptrprev), next(ptrnext) {
        if (prev)
            prev->next = this;
        if (next)
            next->prev = this;
    }
    void InsertOrder(TNode<T> *&head, T item);
};

template<class T>
void TNode<T>::InsertOrder(TNode<T> *&head, T item) {

}

int main() {
    Node *head;

}
