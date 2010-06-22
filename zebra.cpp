#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

void printTable(vector<int> t[5][5])
{
    int d,e,f;
    for(d = 0; d < 5; d++)
    {
        for(e=0; e<5; e++)
        {
            for(f=0; f < t[d][e].size(); f++)
            {
                printf("%d", t[d][e][f]);
            }
            printf(" | ");
        }
        printf("\n");
    }
}

int main()
{
    //instantiate the table w all possibilities
    vector<int> table[5][5];
    /* Legend:
    1  2  3  4  5
    Y  B  R  I  G
    N  U  E  S  J
    W  T  M  O  C
    K  C  O  L  P
    F  H  S  D  Z
    */
    int a,b,c;
    for(int a = 0; a <5; a++)
    {
        for(int b=0; b<5; b++)
        {
            for(int c=1; c<6; c++)
            {
                table[a][b].push_back(c);
            }
        }
    }

    printTable(table);

    return 0;
}

