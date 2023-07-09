#include <iostream>

using namespace std;

void changeVariables(int a, int b) {
    a = a + b;
    b = a - b;
    a = a - b;
    cout << a << " " << b << endl;
}

bool intersection (int *a, int *b, int s) {
    if ((a[0] <= b[0]) && (a[s-1] >= b[0]))
        return true;
    else return (b[0] <= a[0]) && (b[s-1] >= a[0]);
}

void quick (int* arr, int left, int right) {
    int l = left;
    int r = right;
    int p = arr[left];

    while (left < right) {
        while ((arr[right] >= p) && (left < right))
            right--;
        if (left != right) {
            arr[left] = arr[right];
            left++;
        }

        while ((arr[left] <= p) && (left < right))
            left++;
        if (left != right) {
            arr[right] = arr[left];
            right--;
        }
    }

    arr[left] = p;
    p = left;
    left = l;
    right = r;

    if (left < p)
        quick(arr, left, p-1);
    if (right > p)
        quick(arr, p+1, right);
}

void quickSort(int* arr, int left, int right) {
    int l = left;
    int r = right;
    int p = arr[left];

    while (left < right) {
        while ((arr[right] >= p) && (left < right))
            right--;
        if (right != left) {
            arr[left] = arr[right];
            left++;
        }
        while ((arr[left] <= p) && (left < right))
            left++;
        if (left != right) {
            arr[right] = arr[left];
            right--;
        }
    }
        arr[left] = p;
        p = left;
        left = l;
        right = r;
        if (left < p)
            quickSort(arr, left, p-1);
        if (right > p)
            quickSort(arr, p+1, right);
}

void change(int* arr, int size) {
    for (int i = 0; i < size/2; i++) {
        arr[i] = arr[i] + arr[size-i-1];
        arr[size-i-1] = arr[i] - arr[size-i-1];
        arr[i] = arr[i] - arr[size-i-1];
    }
}

int main() {
//    changeVariables(10,20);
//    int a[] = {-2,-1,0,1};
//    int b[] = {0,1,2,3};
//    cout << intersection(a,b, 4);
    int a[20];
    // Заполнение массива случайными числами
    for (int i = 0; i<20; i++)
        a[i] = rand() % 201 - 100;
    // Вывод элементов массива до сортировки
    for (int i = 0; i<20; i++)
        cout << " " << a[i];
    cout << endl;
    quick(a, 0, 20-1); // вызов функции сортировки
    // Вывод элементов массива после сортировки
    for (int i = 0; i<20; i++)
        cout << " " << a[i];
    cout << endl;

    change(a, 20);
    for (int i = 0; i<20; i++)
        cout << " " << a[i];
    cout << endl;

    return 0;
}
