#include <iostream>
#include "lib.h"
using namespace std;


int main() {
int i = 1;
int n;
cin >> n;
int sum = 0;
while (i<=n)
{
    sum = sum + Fibbanachy(i);
    i++;
}
    cout << sum  <<endl;
}
