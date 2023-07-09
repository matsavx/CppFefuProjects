#include <iostream>

using namespace std;

/*
struct Queue {
    short size;
    short data;
};
 */

class ochered{
    short new_elem; //элемент, который вводит пользователь или элемент,
    // который просто стоит следующим в очереди на добавление в нашу приоритетную очередь
    short size;

private:
    short data;
    int tail;
    int head;
    enum{max_size = 7};
    int arr[max_size];

public:
    ochered(int max_size){
        tail = 0;
        head = 0;
    }

    // Проверяет заполнена ли данная очередь на максимум
    bool IsFull();

    //Заполнение очереди с увеличением tail, если функция isFull == false
    void Fill();

    //ввод нового элемента
    short Add();
    // Получение размера очереди
    short getsize();

    //Проверят данную очередь на пустоту
    bool isEmpty;

    // добавление элемента
    void push (short data);

    //удаление элемента
    void pop(short data);

    //вывода очереди с приоритетом на экран
    void PrintWithPriority();

};

short ochered::getsize(){
    return size;
}

short ochered::Add (){
    return new_elem;
}

void ochered::push(short data){
    if (isFull == false) {

        for (int i = 0; i <= size; i++) {
            if ((arr[i] >= new_elem) && (arr[i + 1] < new_elem)) {
                tail++;
                for (int k = tail; k > i+1; k--){
                    arr[k] = arr[k-1];
                }
                arr[i+1] = new_elem;
            }
        }
    }
    else cout << endl << "извините, очередь уже заполнена на максимум" << endl;
}

