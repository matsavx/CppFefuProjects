#include "lib.h";
int Fibanachy(int i)

{
    int schetchik = 1;
    if (i < 1) return 0;
    if (i == 1) return 1;
    return Fibanachy(i - 1) + Fibanachy(i - 2);
}