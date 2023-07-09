#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct CrossRoad
{
    int top, left, bot, right, num;
};

class Labirint
{
private:
    char buff[20];
    CrossRoad M[16];
    int Check[16] ={-1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1},
            Way[16]={-1, -1, -1, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1}, w=0, r=0, s=0, e=0;

public:
//======================================//
    Labirint(void)
    {
        ifstream fin("C:\\myfiles\\MyClionProjects\\LabirintAMGU\\CR.txt");
        if(!fin)
        {
            cerr<<"Can't find CR file in workfolder\n";
            system ("pause");
            exit(0);
        }

        int u=0;
        while(!fin. eof())
        {
            fin >>buff;
            M[u].top=CharNum2Int();
            fin >>buff;
            M[u].left=CharNum2Int();
            fin >>buff;
            M[u].bot=CharNum2Int();
            fin >>buff;
            M[u].right=CharNum2Int();
            M[u].num=u;
            u++;
        }
    }
    //======================================//
    int CharNum2Int(void);
    void Step(int next);
};

//======================================//
int Labirint:: CharNum2Int(void)
{
    int m=1, res, k=0, i;
    i=strlen(buff);
    if(buff[k]=='-')
    {
        m=(-1);
        i--;
        k++;
    }
    if(i==1) return m*(buff[k]-'0');
    if(i==2)
    {
        res=10*(buff[k]-'0');
        k++;
        res=m*(res+(buff[k]-'0'));
        return res;
    }
    else
    {
        cerr<<"Invalid parameter in CR.txt";
        system("pause");
        exit(1);
    }
};
//======================================//

void Labirint:: Step(int next)
{
    int i=0;
    while(next!=Check[i])
    {
        i++;
        if (i==16) break;
    }
    if(next!=Check[i])
    {
        Check[s]=next;
        s++;
    }
    if(s==1) Way[w] =next;
    cout<<"I'm now on the "<<Way[ w] <<"CR:\n";
    if (Way[w]!=15)
    {
        cout<<"check Top;";
        if(M[Way[w]].top!=-2)
        {
            int i=0;
            while(Check[i]!=M[Way[w]].top)
            {
                i++;
                if (i==16) break;
            }

            if(Check[i]!=M[Way[w]].top)
            {
                Way[w+1]=M[Way[w]].top;
                cout<<"\n...go to the "<<M[Way[w]].top<<"CR...\n";
                w++;
                Step(M[Way[w-1]].top);
            }
        }
        if(e) return;
        cout<<"check Left; ";
        if(M[Way[w]].left!=-2)
        {
            int i=0;
            while(Check[i]!=M[Way[w]].left)
            {
                i++;
                if (i==16) break;
            };
            if(Check[i]!=M[Way[w]].left)
            {
                Way[w+1]=M[Way[w]].left;
                cout<<"\n...go to the "<<M[Way[w]].left<<"CR...\n";
                w++;
                Step(M[Way[w-1]].left);
            };
        };
        if(e) return;
        cout<<"check Bot; ";
        if(M[Way[w]].bot!=-2)
        {
            int i=0;
            while(Check[i]!=M[Way[w]].bot)
            {
                i++;
                if (i==16) break;
            }
            if(Check[i]!=M[Way[w]].bot)
            {
                Way[w+1]=M[Way[w]].bot;
                cout<<"\n...go to the "<<M[Way[w]].bot<<"CR...\n";
                w++;
                Step(M[Way[w-1]].bot);
            }
        }
        if(e) return ;
        cout<<"check Right; ";

        if(M[Way[w]].right!=-2)
        {
            int i=0;
            while(Check[i]!=M[Way[w]].right)
            {
                i++;
                if (i==16) break;
            };
            if(Check[i] !=M[Way[w]].right)
            {
                Way[w+1]=M[Way[w]].right;
                cout<<"...go to the "<<M[Way[w]].right<<"CR...\n";
                w++;
                Step(M[Way[w-1]].right);
            };
        };
        if(e) return ;
        if(Way[w]==15)
        {
            cout<<"\n**********************\n Exit is found!\n**********************\n the way is: ";
            for(int i=0;i<=w;i++)
                cout<<Way[i]<<' ';
            cout<<'\n';
            e=1;
            return;
        };
        Way[w]=-1;
        w--;
        cout<<"!go back to the "<<Way[w] <<"\n ";
        return;
    };
};

int main(int argc, char** argv)
{
    Labirint C;
    C.Step(0);
    system("pause");
    return 0;
}
