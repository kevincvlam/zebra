#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

void printTbl(vector<int> t[5][5]) //print the table with all the possibilities
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

void reduceSpot(vector<int> t[5][5], int r, int c) //use the axioms to reduce the possibilites in a spot, based on the given state
{
    //code the contrapositives

}

void reduceTbl(vector<int> t[5][5])
{
    //use axioms to reduce possibilities in table
}

int constrainedRow(vector<int> t[5][5]) //return the row of the most constrained cell
{
    int d,e;
    int min = t[0][0].size();
    int row = 0;
    for(d = 0; d < 5; d++)
    {
        for(e=0; e<5; e++)
        {
           if(t[d][e].size() < min)
            {
                min = t[d][e].size();
                row = d;
            }
        }
    }
    return row;
}

int constrainedCol(vector<int> t[5][5]) //return the col of the most constrained cell
{
    int d,e;
    int min = t[0][0].size();
    int col = 0;
    for(d = 0; d < 5; d++)
    {
        for(e=0; e<5; e++)
        {
           if(t[d][e].size() < min)
            {
                min = t[d][e].size();
                col = e;
            }
        }
    }
    return col;
}

int noSolution(vector<int> t[5][5]) //returns 0 if there is a cell with 0 possibilities, 1 otherwise
{
    int d,e;
    for(d = 0; d < 5; d++)
    {
        for(e=0; e<5; e++)
        {
           if(t[d][e].size() == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int solution(vector<int> t[5][5]) // returns 1 if the solution is found, ie all the cells have one option
{
    int d,e;
    for(d = 0; d < 5; d++)
    {
        for(e=0; e<5; e++)
        {
           if(t[d][e].size() != 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

void chooseOpt(vector<int> t[5][5], int r, int c, int opt)
{
    int i;
    int size = t[r][c].size();
    for(i=0; i<size; i++)
    {
        t[r][c].pop_back();
    }
    t[r][c].push_back(opt);
}

int solve(vector<int> t[5][5], int r, int c) //solve the puzzle
{
    if(noSolution(t)) {return 0;}

    if(solution(t)) {return 1;}

    /*
    for all possibilties of each cell

        erase all but that option
        reducetbl();

        if(solve(reducedtbl), constrainedRow(table), constrainedCol(table))
        {
        print tbl;
        return 1;
        }
    end for

    return 0;

    */
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
    printTbl(table);


    return 0;
}

