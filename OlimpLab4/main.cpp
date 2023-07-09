
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string s;
    ifstream f("../input");
    getline(f, s);
    if (s == "")
        return 0;
    int n = s.size();
    vector<vector<string>> best(n, vector<string>(n)); //мои left и right

    for (int len = 1; len <= n; len++) {
        for (int left = 0; left + len - 1 < n; left++) {
            int right = left + len - 1;

            if (len == 1) {
                if ((s[left] == '(') || (s[left] == ')')) {
                    best[left][right] = "()";
                } else if ((s[left] == '[') || (s[left] == ']')) {
                    best[left][right] = "[]";
                }
                //else throw 1; Можно выкинуть исключение, если в файле может быть что-то кроме скобок, т.е. если данные не коррекны, но С.Н не одобряет throw
            } else if (len == 2) {
                if ((s[left] == '(') && (s[right] == ')')) {
                    best[left][right] = "()";
                } else if ((s[left] == '[') && (s[right] == ']')) {
                    best[left][right] = "[]";
                } else { // скобки друг другу не равны, поэтому мы лучшим образом просто их дополняем
                    best[left][right] = best[left][left] + best[right][right];
                }
            } else {
                string min(201, ' '); //просто заполняю на столько столько символов, сколько точно будет больше чем во входном файле
                for (int right1 = left; right1 < right; right1++) {
                    int left2 = right1 + 1;
                    string t = best[left][right1] + best[left2][right];

                    if (t.size() < min.size()) {
                        min = t;
                    }
                }
                if (((s[left] == '(') && (s[right] == ')')) || ((s[left] == '[') && (s[right] == ']'))) {
                    string t = s[left] + best[left + 1][right - 1] +
                               s[right]; // дополняем внутренности, если наружности нормальные

                    if (t.size() < min.size()) {
                        min = t;
                    }
                }
                best[left][right] = min;
            }
        }
    }
    ofstream f2 ("../output");
    //printf("%s", best[0][n-1].c_str());
    f2 << best[0][n - 1].c_str();
    f.close();
    f2.close();
    return 0;
}