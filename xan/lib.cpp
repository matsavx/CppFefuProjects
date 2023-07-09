#include <iostream>
#include <string>
#include "lib.h"

using namespace std;

string comparison(table s, table t, int count, string str) {

    if (s.subject[count] == "-")
        throw "В этот день нет пары";

    int len,er;
   // string hstr, mstr;
    len = str.length();

    for (int i = 1; i < len; i++){

        t.time[count] += str[i];

    }

    return t.time[count];

    /*
       for (int i = 1; str[i] != ':'; i++) {

           hstr += str[i];
           er++;
       }
       t1.hour = stoi(hstr);
       str.erase(1, er);

       for (int i = 1; i < len; i++) {

           mstr += str[i];
       }
       t1.min = stoi(mstr);

       cout << t1.hour << ":" << t1.min << endl;

       return 0;
    */

}

int reading (int count, string str, table g, table d, table s, table t, string myday, string mygroup) {

        int eraser,de;
        count++;

        for ( int i = 0; str[i] != ' '; i++) {

            g.group[count] += str[i];
            eraser = i;
        }

        str.erase(1, (eraser + 1));

        for ( int i = 1; str[i] != ' '; i++) {

            d.day[count] += str[i];
            eraser = i;
        }

        str.erase(1, (eraser + 1));

        if (str[1] == '-') {

            s.subject[count] += str[1];
        }
        else {

            for (int i = 1; str[i] != ' '; i++) {

                s.subject[count] += str[i];
                eraser = i;

            }

            str.erase(1, (eraser + 1));

        }
        if ((mygroup == g.group[count]) && (myday == d.day[count])) {

            try {
                cout << comparison(s, t, count, str);
            }
            catch (char const *err) {
                cout << err;
            }
        }
    cin >> de;
}

