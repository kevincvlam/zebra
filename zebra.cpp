#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

void printTbl(vector<int> t[5][5]) //print the table with all the possibilities
{

    printf("-1-|-2-|-3-|-4-|-5-|\n");
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

int cellContains(vector<int> t[5][5], int r, int c, int opt) //if cell contains a possibility, return 1
{
    int a;
    for(a=0; a<t[r][c].size(); a++)
    {
        if(t[r][c][a] == opt)
        return 1;
    }
    return 0;
}

int cellContainsOnly(vector<int> t[5][5], int r, int c, int opt) //if cell contains a possibility, return 1
{
    if( t[r][c].size() == 1 && t[r][c][0] == opt)
        return 1;
    return 0;
}

void removeOpt(vector<int> t[5][5], int r, int c, int opt) //remove a possibility from the given cell
{
  int a; int index;
  if(cellContains(t, r, c, opt))
  {
  for(a=0; a< t[r][c].size(); a++)
  {
      if(t[r][c][a] == opt)
      index = a;
  }
  t[r][c].erase(t[r][c].begin()+index);
  }
}

void chooseOpt(vector<int> t[5][5], int r, int c, int opt)
{
    if(cellContains(t, r, c, opt))
    {
    int i;
    int size = t[r][c].size();
    for(i=0; i<size; i++)
    {
        t[r][c].pop_back();
    }
    t[r][c].push_back(opt);

    //remove option from all other cells
    int a; int b;
    for(a=0; a<5; a++)
    {
        for(b=0; b<5; b++)
        {
            if(a != r && b!= c)
            {
                removeOpt(t, a, b, opt);
            }
        }
    }

    }

}

void forceOpt(vector<int> t[5][5], int r, int c, int opt)
{
    int i;
    int size = t[r][c].size();
    for(i=0; i<size; i++)
    {
        t[r][c].pop_back();
    }
    t[r][c].push_back(opt);

    //remove option from all other cells
    int a; int b;
    for(a=0; a<5; a++)
    {
        for(b=0; b<5; b++)
        {
            if(a != r && b!= c)
            {
                removeOpt(t, a, b, opt);
            }
        }
    }
}

void reduceSpot(vector<int> t[5][5], int r, int c) //use the axioms to reduce the possibilites in a spot, based on the given state
{
    //code the contrapositives
  //color row
  if(r == 0)
  {
    //if the house is not red, the nationality cannot be english
    if(!cellContains(t, r, c, 3))
    {
        removeOpt(t, 1, c, 3);
    }

    //not green, not coffee
    if(!cellContains(t, r, c, 5))
    {
        removeOpt(t, 2, c, 5);
    }

    //not yellow, no kools
    if(!cellContains(t, r, c, 1))
    {
        removeOpt(t, 3, c, 1);
    }
  }

  //nationality row
  if(r == 1)
  {
      //if the nationality is not english, the house cannot be red
      if(!cellContains(t, r, c, 3))
      {
          removeOpt(t, 0, c, 3);
      }

      //if not spaniard, no dog
      if(!cellContains(t, r, c, 4))
      {
          removeOpt(t, 4, c, 4);
      }

      //not ukrainian, not tea
      if(!cellContains(t, r, c, 2))
      {
          removeOpt(t, 2, c, 2);
      }

      //norwegian lives in the first house
      if(c != 0)
      {
          removeOpt(t, r, c, 1);
      }

      //not japanese, not parliaments
      if(!cellContains(t,r,c, 5))
      {
          removeOpt(t, 3, c, 5);
      }
  }

  //drink row
  if(r==2)
  {
    //not green, not coffee
    if(!cellContains(t, r, c, 5))
    {
        removeOpt(t, 0, c, 5);
    }

    //not tea, not ukrainian
    if(!cellContains(t,r,c,2))
    {
        removeOpt(t, 1, c, 2);
    }

    //if not the middle house, no milk
    if(c != 2)
    {
        removeOpt(t, r, c, 3);
    }

    //not oj, not lucky strike
    if(!cellContains(t, r, c, 4))
    {
        removeOpt(t, 3, c, 4);
    }
  }

  //smoke row
  if(r==3)
  {
      //not old gold, not snails
      if(!cellContains(t, r, c, 3))
      {
          removeOpt(t, 4,  c, 3);
      }

      //not kools not yellow
      if(!cellContains(t, r, c, 1))
      {
          removeOpt(t, 0, c, 1);
      }

      //not lucky strike, not oj
      if(!cellContains(t, r, c, 4))
      {
          removeOpt(t, 2, c, 4);
      }

      //not parliaments not japanese
      if(!cellContains(t, r, c, 5))
      {
          removeOpt(t, 1, c, 5);
      }
  }

  //pet row
  if(r==4)
  {
      //if not dog, not spaniard
      if(!cellContains(t, r, c, 4))
      {
          removeOpt(t, 1, c, 4);
      }

      //not snails, not old gold
      if(!cellContains(t, r, c, 3))
      {
          removeOpt(t, 3, c, 3);
      }
  }

  //if col is in a certain range, check neighbour nonsense on borders do proper things
  //neighbour axioms

  //boundaries
  if(c == 0)
  {

      if(r == 1 && c == 0)
      {
          chooseOpt(t, 1, 0, 1);
      }
      //since no house is left of the first house, it cannot be to the right of the ivory
      if(r == 0)
      {
          removeOpt(t, r, c, 5);
      }


      //if the house to the right isn't blue, not norwegian
      if(r==1)
      {
          if(!cellContains(t, 0, c+1, 2))
          {
              removeOpt(t, r, c, 1);
          }
      }

      //if the house to the right isn't norwegian, not blue
      if(r==0)
      {
          if(!cellContains(t, 1, c+1, 1))
          {
              removeOpt(t, r, c, 2);
          }
      }


      //if the house to the right does not have fox no chesterfields
      if(r == 3)
      {
          if(!cellContains(t, 4, c+1, 1))
          {
              removeOpt(t, r, c, 2);
          }
      }


      //if the house to the right does not have chesterfields, no fox
      if(r == 4)
      {
          if(!cellContains(t, 3, c+1, 2))
          {
              removeOpt(t, r, c, 1);
          }
      }

      //if the house to the right has no horse no kools
      if(r == 3)
      {
          if(!cellContains(t, 4, c+1, 2))
          {
              removeOpt(t, r, c, 1);
          }
      }

      //if the house to the right has no kools, no horse
      if(r == 4)
      {
          if(!cellContains(t, 3, c+1, 1))
          {
              removeOpt(t, r, c, 2);
          }
      }
  }

  if(c == 4)
  {
      //the rightmost house cannot be ivory
      if(r == 0)
      {
          removeOpt(t, r, c, 4);
      }

      //if the house left has no fox, no chesterfields
      if(r == 3)
      {
          if(!cellContains(t, 4, c-1, 1))
          {
              removeOpt(t, r, c, 2);
          }
      }

      //if the house left has no chesterfields, no fox
      if(r == 4)
      {
          if(!cellContains(t, 3, c-1, 2))
          {
              removeOpt(t, r, c, 1);
          }
      }

      //if the house to the left has no horse no kools
      if(r == 3)
      {
          if(!cellContains(t, 4, c-1, 2))
          {
              removeOpt(t, r, c, 1);
          }
      }

      //if the house to the left has no kools, no horse
      if(r == 4)
      {
          if(!cellContains(t, 3, c-1, 1))
          {
              removeOpt(t, r, c, 2);
          }
      }

            //if the house to the left isn't blue, not norwegian
      if(r==1)
      {
          if(!cellContains(t, 0, c-1, 2))
          {
              removeOpt(t, r, c, 1);
          }
      }

      //if the house to the left isn't norwegian, not blue
      if(r==0)
      {
          if(!cellContains(t, 1, c-1, 1))
          {
              removeOpt(t, r, c, 2);
          }
      }
  }

  //non boundaries
  if(c < 4 && c > 0)
  {
      if(r == 0) //color
      {
          //if house to left isnt ivory, not green
          if(!cellContains(t, r, c-1, 4))
          {
              removeOpt(t, r, c, 5);
          }
          //if the house to the right isn't green, not ivory
          if(!cellContains(t, r, c+1, 5))
          {
              removeOpt(t, r, c, 4);
          }

          //if the next house isn't norwegian, not blue
          if(!cellContains(t, 1, c-1, 1) && !cellContains(t, 1, c+1, 1))
          {
              removeOpt(t, r, c, 2);
          }

      }

      if(r==1)
      {
          //if the next house isnt blue, not norwegian
          if(!cellContains(t, 0, c-1, 2) && !cellContains(t, 2, c+1, 1))
          {
              removeOpt(t, r, c, 1);
          }
      }



      if(r==3) // smokes
      {
          //if the house next has no fox, no chesterfields
          if(!cellContains(t, 4, c-1, 1) && !cellContains(t, 4, c+1, 1))
          {
              removeOpt(t, r, c, 2);
          }

                    //if the house next has no horse, no kools
          if(!cellContains(t, 4, c-1, 2) && !cellContains(t, 4, c+1, 2))
          {
              removeOpt(t, r, c, 1);
          }
      }

      if(r==4) //pet
      {
          //if the house next has no chester, no fox
          if(!cellContains(t, 3, c-1, 2) && !cellContains(t, 3, c+1, 2))
          {
              removeOpt(t, r, c, 1);
          }

          //if the house next has no kools no horse
          if(!cellContains(t, 3, c-1, 1) && !cellContains(t, 3, c+1, 1))
          {
              removeOpt(t, r, c, 2);
          }
      }
  }

//code the logical positives, ie. chooosing



  if(r==0) //color
  {
      //if house is red choose eng
      if(cellContainsOnly(t, r, c,3))
      {
          chooseOpt(t, 1, c, 3);
      }

      //if green, coffee
      if(cellContainsOnly(t, r, c, 5))
      {
          chooseOpt(t, 2, c, 5);
      }

      //if yellow, kools
      if(cellContainsOnly(t, r, c, 1))
      {
          chooseOpt(t, 3, c, 1);
      }


  }

  if(r==1) //nat
  {
      //if eng, red
      if(cellContainsOnly(t, r, c,3))
      {
          chooseOpt(t, 0, c, 3);
      }

      //if span, dog
      if(cellContainsOnly(t, r, c, 4))
      {
          chooseOpt(t, 4, c, 4);
      }

      //if u, then tea
      if(cellContainsOnly(t, r, c, 2))
      {
          chooseOpt(t, 2, c, 2);
      }
      //jap then parliaments
      if(cellContainsOnly(t, r, c, 5))
      {
          chooseOpt(t, 3, c, 5);
      }
  }

  if(r==2) //drink
  {
      //if coffee, green
      if(cellContainsOnly(t, r, c, 5))
      {
          chooseOpt(t,0, c, 5);
      }
      //if t, then u
      if(cellContainsOnly(t, r, c, 2))
      {
          chooseOpt(t, 1, c, 2);
      }
      //oj then lucky strike
      if(cellContainsOnly(t, r, c, 4))
      {
          chooseOpt(t, 3, c, 4);
      }
  }

  if(r==3) //smoke
  {
      //if old gold, snails
      if(cellContainsOnly(t, r, c,3))
      {
          chooseOpt(t, 4, c, 3);
      }
      //if kools, yellow
      if(cellContainsOnly(t, r, c, 1))
      {
          chooseOpt(t, 0, c, 1);
      }

      //lucky ten oj
      if(cellContainsOnly(t, r, c, 4))
      {
          chooseOpt(t, 2, c, 4);
      }

      //parliaments then japanese
      if(cellContainsOnly(t, r, c, 5))
      {
          chooseOpt(t, 1, c, 5);
      }
  }

  if(r==4) //pet
  {
      //if dog, span
      if(cellContainsOnly(t, r, c, 4))
      {
          chooseOpt(t, 1, c, 4);
      }
      //if snails, old gold
      if(cellContainsOnly(t, r, c,3))
      {
          chooseOpt(t, 3, c, 3);
      }
  }

  //neighbour axioms

  //left
  if(c == 0)
  {
      //if the house to the right is green, ivory
      if(r==0)
      {
        if(cellContainsOnly(t, 0, c+1, 5))
        {
            chooseOpt(t, 0, c, 4);
        }

      }
      //if right fox, chester
      if(r==3)
      {
          if(cellContainsOnly(t, 4, c+1, 1))
          {
              chooseOpt(t, r, c, 2);
          }
          //right horse, kools
          if(cellContainsOnly(t, 4, c+1, 2))
          {
              chooseOpt(t, r, c, 1);
          }
      }

      //if right chester, fox
      if(r==4)
      {
          if(cellContainsOnly(t, 3, c+1, 2))
          {
              chooseOpt(t, r, c, 1);
          }

          //right kools, horse
          if(cellContainsOnly(t, 3, c+1, 1))
          {
              chooseOpt(t, r, c, 2);
          }
      }
  }

  //right
  if(c == 4)
  {
      //if the house to the left is ivory, green
      if(r==0)
      {
          if(cellContainsOnly(t, 0, c-1, 4))
          {
              chooseOpt(t, 0, c, 5);
          }
      }

      //if left fox, chester
      if(r==3)
      {
          if(cellContainsOnly(t, 4, c-1, 1))
          {
              chooseOpt(t, r, c, 2);
          }

          //left horse, kools
          if(cellContainsOnly(t, 4, c-1, 2))
          {
              chooseOpt(t, r, c, 1);
          }
      }

      //if left chester, fox
      if(r==4)
      {
          if(cellContainsOnly(t, 3, c-1, 2))
          {
              chooseOpt(t, r, c, 1);
          }


      //left kools, horse
          if(cellContainsOnly(t, 3, c-1, 1))
          {
              chooseOpt(t, r, c, 2);
          }
      }
  }

  //non boundary
  if(c>0 && c<4)
  {

      if(r==0)
      {   //green ivory
          if(cellContainsOnly(t, 0, c-1, 4))
          {
              chooseOpt(t, 0, c, 5);
          }
          if(cellContainsOnly(t, 0, c+1, 5))
          {
            chooseOpt(t, 0, c, 4);
          }
      }

      if(r==3)
      {   //fox then chester
          if(cellContainsOnly(t, 4, c-1, 1) || cellContainsOnly(t, 4, c+1, 1))
          {
              chooseOpt(t, r, c, 2);
          }
          //horse then kools
          if(cellContainsOnly(t, 4, c-1, 2) || cellContainsOnly(t, 4, c+1, 2))
          {
              chooseOpt(t, r, c, 1);
          }
      }

      if(r==4)
      {
          //chester then fox
          if(cellContainsOnly(t, 3, c-1, 2) || cellContainsOnly(t, 3, c+1, 2))
          {
              chooseOpt(t, r, c, 1);
          }

          //kools then horse
          if(cellContainsOnly(t, 3, c-1, 1) || cellContainsOnly(t, 3, c+1, 1))
          {
              chooseOpt(t, r, c, 12);
          }
      }
  }


}

void reduceTbl(vector<int> t[5][5])
{
    //use axioms to reduce possibilities in table, keep track of boundaries, prevent segfaults
    int a, b;
    for(a=0; a<5; a++)
    {
        for(b=0; b<5; b++)
        {
            reduceSpot(t, a, b);
        }
    }
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
           if(t[d][e].size() < min && t[d][e].size() > 1)
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
           if(t[d][e].size() < min && t[d][e].size() > 1)
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
                return 1;
            }
        }
    }
    return 0;
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



int solve(vector<int> t[5][5], int r, int c) //solve the puzzle
{
    if(noSolution(t)) {return 0;} //break if no solution or if the board has not changed

    if(solution(t)) {return 1;}

    int a;
    for(a = 0; a< t[r][c].size(); a++)
       {
        //problem is here, the other options get removed..and the options are available
        chooseOpt(t, r, c, t[r][c][a]);

        //need to store possible values, and iterate through them...(choose opt should do it automatically)
        reduceTbl(t);
        if(solve(t, constrainedRow(t), constrainedCol(t)))
        {
        printTbl(t);
        return 1;
        }
       }
    return 0;
}

void printNat(vector<int> t[5][5], int b)
{
    if(t[1][b][0] == 1)
    {
        printf("Norwegian");
    }
    else if(t[1][b][0] == 2)
    {
        printf("Ukranian");
    }
    else if(t[1][b][0] == 3)
    {
        printf("English");
    }
    else if(t[1][b][0] == 4)
    {
        printf("Spanish");
    }
    else if(t[1][b][0] == 5)
    {
        printf("Japanese");
    }

}

void printSol(vector<int> t[5][5])
{
    int a; int b;
    int z; int w;
    for(a=0; a<5; a++)
    {
        for(b=0; b<5; b++)
        {
            if(t[4][b][0] == 5)
            {
               z = b;
            }
            if(t[2][b][0] == 2)
            {
                w =b;
            }
        }
    }
    printf("The owner of the zebra is: ");
    printNat(t, z);
    printf("\nThe man who drinks the water is: ");
    printNat(t, w);
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
    chooseOpt(table, 2, 2, 3);
    chooseOpt(table, 0, 1, 2);
    chooseOpt(table, 1, 0, 1);

    printf("Initial Table");
    printTbl(table);
    printf("\n");

    solve(table, constrainedRow(table), constrainedCol(table));
    printf("\n");

    printSol(table);

    return 0;
}

