
#include <iostream>

#include <vector>
using namespace std;

int pow(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}
void MsdIntSorting(vector<int>& vec, int from, int to, int d, int max_digit) {
    auto Char_At = [max_digit](int number, int pos) {
        return (number % pow(10, max_digit - pos)) / pow(10, max_digit - pos - 1);
    };
    if ((to - from <= 1) || (d == max_digit)) {
        return;
    }

    vector<int> pockets[10];

    for (int j = from; j < to; j++) {
        int digit = Char_At(vec[j], d);
        pockets[digit].push_back(vec[j]);
    }

    int idx = 0;
    for (int k = 0; k < 10; k++) {
        for (int l = 0; l < pockets[k].size(); l++) {
            vec[from + idx] = (pockets[k][l]);
            idx++;
        }
        pockets[k].clear();
    }
    vector<pair<int, int>> indexes;
    indexes.clear();
    pair<int, int> p;
    p.first = p.second = from;

    while (p.second != to) {
        p.second++;
        if (p.second == to || Char_At(vec[p.second], d) != Char_At(vec[p.first], d)) {
            pair<int, int> toBePushed = p;
            indexes.push_back(toBePushed);
            p.first = p.second;
        }
    }

    int new_d = d + 1;
    for (int i = 0; i < indexes.size(); i++) {
        MsdIntSorting(vec, indexes[i].first, indexes[i].second, new_d, max_digit);
    }
}

void MsdIntSort() {
    vector <int> vec;
    int size = 200;
    for (int i = 0; i < size; i++) {
        vec.push_back(size-i);
    }

    MsdIntSorting(vec, 0, size, 0, 4);

    for (int i = 0; i < size; i++) {
        cout << vec[i] << endl;
    }
}

int main() {
    MsdIntSort();
}