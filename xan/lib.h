#ifndef XAN_LIB_H
#define XAN_LIB_H

using namespace std;

const int N = 20;

struct table {
    string group[N];
    string day[N];
    string subject[N];
    string time[N];
};
/*
struct time_name {
    int hour;
    int min;
};
*/

string comparison(table s, table t, int count, string str);

int reading (int count, string str, table g, table d, table s, table t, string myday, string mygroup);

#endif //XAN_LIB_H
