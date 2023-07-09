#include <iostream>

using namespace std;

class Queue {
private:
    unsigned short head;
    unsigned short tail;
    unsigned short max_size;
    int *data;
public:
    Queue(unsigned short max_size) {
        head = 0;
        tail = 0;

        // if (max_size < 10)
        //   max_size = 10;

        this->max_size = max_size;

        data = new int[max_size+1];
    }

    Queue(const Queue &queue) {
        max_size = queue.max_size;
        data = new int[max_size+1];
        if (!data) {
            cout << "memory allocation error";
            exit(1);
        }
        head = queue.head;
        tail = queue.tail;
        /*if (tail > head) {
            for (int i = head; i < tail; i++)
                data[i] = queue.data[i];
        }
        else {
            for (int i = 0; i <= tail; i++)
                data[i] = queue.data[i];
            for (int i = head; i < max_size; i ++)
                data[i] = queue.data[i];
        }*/
        for (int i = 0; i <= max_size; i ++)
            data[i] = queue.data[i];
    }

    ~Queue(){
        delete[](data);
    }


    bool add(int element) {
        if ((head == tail) && (tail != max_size)) {
            data[tail] = element;
            tail++;
            return true;
        }
        //if ((tail == 0) && (tail !=head)) {
            //data[max_size] = element;
            //tail++;
           // return true;
        //}
        if (tail == max_size) {
            data[tail] = element;
            tail = 0;
            data[tail] = 0;
            head++;
            return true;
        }
        if (tail < head) {
            data[tail] = element;
            tail++;
            data[tail] = 0;
            head++;
            return true;
        }
        if ((tail < head) && (head == max_size)) {
            data[tail] = element;
            tail++;
            data[tail] = 0;
            head = 0;
        }
        if ((tail != 0) && (tail != max_size) && (tail != head)){
            data[tail] = element;
            tail++;
            return true;
        }
        return false;
    }

    bool del() {
        if (head == tail)
            return false;
        if (tail == 0)
            tail = max_size;
        int maxElemIndex = head;
        for (int i = head; i < max_size; i++) {
            if (data[i+1] > data[i])
                maxElemIndex = i+1;
        }
        if (tail < head) {
            for (int i = 0; i < tail; i++) {
                if ((data[i+1] > data[i]) && (data[i+1] > data[maxElemIndex]))
                    maxElemIndex = i+1;
            }
        }
        if ((tail == 1) && (data[0] > data[maxElemIndex]))
            maxElemIndex = 0;

        if (tail < head) {
            if (maxElemIndex > tail) {
                for (int i = head; i < max_size; i++) {
                    data[i+1] = data[i];
                }
                data[head] = 0;
                head++;
            }
            if ((maxElemIndex < tail) && (maxElemIndex == tail-1)) {
                tail--;
                data[tail] = 0;
            }
            if ((maxElemIndex < tail) && (maxElemIndex != tail-1)) {
                for (int i = maxElemIndex; i < tail; i++) {
                    data[i] = data[i+1];
                }
                tail--;
            }
        }
        else {
            for (int i = maxElemIndex; i < tail; i++)
                data[i] = data[i + 1];
            tail--;
        }
    }

    int length() {
        int run = 0;
        if (head == tail)
            return 0;
        if (tail < head) {
            for (int i = 0; i < max_size; i++) {
                if (data[i] != 0)
                    run++;
            }
            run++;
            return run;
        }
        return tail;
    }

    friend istream &operator >> (istream &stream, Queue &queue) { //перегрузка ввода по Шилдту
        int element;
        stream >> element;
        queue.add(element);
        return stream;
    }

    friend ostream &operator << (ostream &stream, Queue &queue) { //перегрузка вывода по Шилдту
        if (queue.length() == 0)
            stream << "Пусто" << endl;
        else {
            if (queue.tail > queue.head) {
                for (int i = queue.head; i < queue.length(); i++)
                    stream << queue.data[i] << " ";
            }
            else {
                for (int i = queue.head; i <= queue.max_size; i++)
                    stream << queue.data[i] << " ";
                for (int i = 0; i < queue.tail; i++)
                    stream << queue.data[i] << " ";
            }
            /*if (queue.tail < queue.head) {
                for (int i = 0; i <= queue.max_size; i++)
                    stream << queue.data[i] << " ";
            }
            else {
                for (int i = 0; i < queue.length(); i++)
                    stream << queue.data[i] << " ";
            }*/
        }
        stream << "\nГолова указывает на ячейку номер " << queue.head << endl;
        stream << "\nХвост указывает на ячейку номер " << queue.tail << endl;
        return stream;
    }

    Queue operator = (Queue queue) { //перегрузка присваивания по Шилдту
        max_size = queue.max_size;
        int runner = 0;
        head = queue.head;
        tail = queue.tail;
        /*runner = queue.head;
        if (data == queue.data)
            return *this;
        if (tail > head) {
            for (int i = head; i < tail; i++) {
                data[i] = queue.data[runner];
                runner++;
            }
        }
        else {
            runner = 0;
            for (int i = 0; i <= tail; i++) {
                data[i] = queue.data[runner];
                runner++;
            }
            runner = queue.head;
            for (int i = head; i < max_size; i++) {
                data[i] = queue.data[runner];
                runner++;
            }
        }*/
        for (int i = 0; i <= max_size; i++) {
            data[i] = queue.data[runner];
            runner++;
        }
        return *this;
    }
};

int main() {
    Queue QUEUE(10);
    cout <<"Очередь перед заполнением\n" << QUEUE << "\nДлина = " << QUEUE.length() <<"\n--------------------" << endl;

    for (int i = 1; i <= 8; i++)
        QUEUE.add(i);
    cout <<"Очередь после заполнения\n" << QUEUE << "\nДлина = " << QUEUE.length() <<"\n--------------------" << endl;

    for (int i = 0; i < 1; i++)
        QUEUE.del();
    cout <<"Очередь после удаления\n" << QUEUE << "\nДлина = " << QUEUE.length() <<"\n--------------------" << endl;

    Queue firstQUEUE(QUEUE);
    cout <<"1 Очередь после копирования\n" << firstQUEUE << "\nДлина = " << firstQUEUE.length() <<"\n--------------------" << endl;

    Queue secondQUEUE(12);
    for (int i = 1; i <= 15; i++)
        secondQUEUE.add(i);
    cout <<"2 Очередь после заполнения\n" << secondQUEUE << "\nДлина = " << secondQUEUE.length() <<"\n--------------------" << endl;

    firstQUEUE = secondQUEUE;

    cout <<"1 Очередь после присваивания\n" << firstQUEUE << "\nДлина = " << firstQUEUE.length() <<"\n--------------------" << endl;
}