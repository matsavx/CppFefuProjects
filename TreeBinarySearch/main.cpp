//Бинарный Поиск/ Добро пожаловать в мою фигню!
#include <iostream>

using namespace std;
struct TNode{
    TNode *left;
    TNode *right;
    int value;
};
class BinaryTree {
private:
    TNode  *head;
public:
    BinaryTree() {
        head = nullptr;
    }
    ~BinaryTree() {
        head = nullptr;
    }
    void Add(int key); //Возможно тут будет проблема, так как я исправил предупреждение о разных названиях переменных (вместо value поставил key) 16.12 1:55
    bool Remove(int key);
    bool Search(int key);
    void AddTo(TNode *node, int key);
    void print();
    TNode* FindWithParent(int key, TNode* &parent);

private:
    void printNode(TNode *node, int level);
};

void BinaryTree::Add(int key) {
    //Если дерево пустое - создаем корень
    if(head == nullptr) {
        head = new TNode;
        head->value = key;
    }
    else { //Иначе, ищем место для вставки
        AddTo(head, key);
    }
}
//Рекурсивная вставка для метода Add
void BinaryTree::AddTo(TNode *node, int key) {
    //1.Вставляемое значение меньше значения узла
    if(key <= node->value) {
        //Если нет левого поддерева - добавиляем значение в левого ребенка
        if(node->left == nullptr) {
            node->left = new TNode;
            node->left->value = key;
        }
        //Иначе - повторяем для левого поддерева
        else
            AddTo(node->left, key);
    }
    //2.Вставляемое значение больше или равно значению узла
    else {
        //Если нет правого поддерева - добавляем значение в правого ребенка
        if(node->right == nullptr) {
            node->right = new TNode;
            node->right->value = key;
        }
        //Иначе - повторяем для правго поддерева
        else
            AddTo(node->right, key);
    }
}

bool BinaryTree::Remove(int key) {
    TNode *current = nullptr;
    TNode* parent = nullptr;
    //Поиск удаляемого узла
    current = FindWithParent(key, parent);   // Возможно тут будет ошибка, Я мог легко напутать с указателями 16.12 0:20
    if(current == nullptr) {
        return false;
    }
    //Случай 1: Если нет детей справа, левый ребенок встает на место удаляемого
    if(current->right == nullptr){
        cout << "Случай 1. Нет детей справа" << endl;
        if(parent == nullptr) {
            head = current->left;
            cout << "Родителя нет. Левый встает на место удаляемого" << endl;
        }
        else {
            if(parent->value >= current->value) {
                parent->left = current->left;
                cout << "Значение родителя больше текущего, левый ребенок текущего узла становится левым ребенком родителя" << endl;
            }

            else if(parent->value < current->value) {
                parent->right = current->left;
                cout << "Значение родителя меньше текущего, левый ребеное ттекущего узла становится правым ребенком родителя" << endl;
            }
        }
    } // Случай 2: Если у правого ребенка нет детей слева, то он занимает место удаляемого узла
    else if(current->right->left == nullptr) {
        cout << "Случай 2. У правого ребенка нет детей слева." << endl;
        current->right->left = current->left;
        if (parent == nullptr) {
            cout << "Родителя нет. Он занимает место удаляемого" << endl;
            head = current->right;
        }
        else if (parent->value > current->value) {
            parent->left = current->right;
            cout << "Значение родителя больше текущего. Правый ребенок текущего узла становится левым ребенком родителя" << endl;
        }
        else if (parent->value < current->value) {
            parent->right = current->right;
            cout << "Значение родителя меньше текущего. Правый ребенок текущего узла становится правым ребенком родителя" << endl;
        }
    } // Случай 3: Если у правого ребенка есть дети слева, крайний левый ребенок
    // из правого поддерева заменяет удаляемый узел
    else {
        cout << "Случай 3. У правого ребенка есть дети слева, крайний левый ребенок из правого поддерева заменяет удаляемый узел" << endl;
        //Поиск крайнего левого узла
        TNode *leftmost = current->right->left;
        TNode *leftmostParent = current->right;
        while(leftmost->left != nullptr) {
            leftmostParent = leftmost;
            leftmost = leftmost->left;
        }
        cout << "Левое поддерево родителя становится правым поддеревом крайнего левого узла" << endl;
        leftmostParent->left = leftmost->right;
        cout << "Левый и правый ребенок текущего узла становится левым и правым ребенком крайнего левого" << endl;
        leftmost->left = current->left;
        leftmost->right = current->right;
        if(parent == nullptr)
            head = leftmost;

        else if(parent->value > current->value) {
            parent->left = leftmost;
            cout << "Значение родителя больше текущего. Крайний левый узел становится левым ребенком родителя" << endl;
        }

        else if (parent->value < current->value) {
            parent->right = leftmost;
            cout << "Значение родителя меньше текущего. Крайний левый узел становится правым ребенком родителя" << endl;
        }
    }
    return true;
}

//Возвращает родителя найденного узла (или null) для метода Remove
TNode* BinaryTree::FindWithParent(int key, TNode *&parent) {
    //Поиск значения в дереве до тех пор пока не нашли
    TNode* current = head;
//    parent = nullptr;
    bool flag = false;
    while((current != nullptr) && !flag) {
        if(current->value > key) {
            //Если текущее значение меньше - идем налево
            parent = current;
            current = current->left;
        }
        else if(current->value < key) {
            //Если искомое значение больше - идем направо
            parent = current;
            current = current->right;
        } else
            //Если равно - выходим
            flag = true;
    }
    return current;
}

// Должно находить и возвращать первый узел с заданным значением. Если значение не найдено - возвращать null
bool BinaryTree::Search(int key) {
    TNode* parent;
    return (FindWithParent(key, parent) != nullptr);
}

void BinaryTree::printNode(TNode *node,int level = 0) {
    if(node != nullptr) {
        printNode(node->right, level+1);
        for(int i = 0; i<level; i++) {
            cout << "     ";
        }
        cout << (node->value)<<"\n";
        printNode(node->left, level+1);
    }
}
void BinaryTree::print(){
    cout << "--------------------------------------------------------" << endl;
    if (head == nullptr){
        cout << "Empty" << endl;
    } else {
        printNode(head, 0);
    }
    cout << "--------------------------------------------------------" << endl;
}

int main() {
    BinaryTree T;
//    T.Add(10);
//    T.Add(11);
//    T.Add(2);
//    T.Add(11);
    T.Add(3);
    T.Add(5);
    T.Add(4);
    T.Add(6);
    T.Add(8);
    T.Add(6);
    T.Add(9);
    T.Add(7);
    T.Add(6);
    T.Add(2);
    T.Add(1);
    T.Add(3);
    T.Add(4);
    T.print();
    T.Add(2);
    T.print();

//    T.Remove(8);
//    T.print();
//    T.Remove(5);
//    T.print();
//    T.Remove(9);
//    T.print();
//    T.Remove(1);
//    T.print();

}