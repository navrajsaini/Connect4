/*
 * By: Navraj Saini
 * 001175967
 */


#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef struct
{
   string name;
   bool max_pl;
}player;

char Grid[6][7]; // make a 7 X 6 grid for the game
//0000000 : 1(0) location
//0000000
//0000000
//0000000
//0000000
//0000000 : 6(5) location
// so the bottom is Grid[5][*]
string win;
void create_board(); // function to initialize the board
void print(); // function to print the board
bool check(); // check if a player won, passes the grid and the location
              // x/o is dropped at
bool validmove(int);// check if the move is valid based on the location the
                    // x/o is dropped at
bool Drop(player, int);// drop the correct disc based on the player
int alphaB(int, int, int, int, bool);

int main()
{
   create_board();// ini the board

   player p1; char m;
   cout << "please enter your name: ";
   cin >> p1.name;
   player p2;
   p2.name = "Comp";
   
   char ex = true;
   while (ex)
   {
      cout << "Are you the maximizing player? y or n ";
      cin >> m;
      
      if (m == 'y')
      {
	 p1.max_pl = true;
	 p2.max_pl = false;
	 ex = false;
      }
      else if (m == 'n')
      {
	 p2.max_pl = true;
	 p1.max_pl = false;
	 ex = false;
      }
      else
      {
	 cout << "please enter y or n: ";
	 cin >> m;
	 if (m == 'y')
	 {
	    p1.max_pl = true;
	    p2.max_pl = false;
	    ex = false;
	 }
	 if (m == 'n')
	 {
	    p1.max_pl = false;
	    p2.max_pl = true;
	    ex = false;
	 }
      }
   }
   int loc = 0;
   // get the player to drop x/o to a location
   int person = 0;
   if (p1.max_pl == true)
      person = 0;
   else
      person = 1;
   
   bool winner = check();
   bool cont = true;
   while (winner == false)
   {
      cout << "which location would you like to drop your? 1 to 7 " << endl;
      print();
      
      if(person % 2 == 0 && cont)
      {
	 cin >> loc;
	 cont = Drop(p1, loc);
	 while(!cont)
	 {
	    cout << "Please input a valid move: ";
	    cin >> loc;
	    cont = Drop(p1, loc);
	 }
	 person++;
      }
      else if (person % 2 == 1)
      {
	 // minimax func to find the loc
	 cout << endl << "This is when Minimax is implemented... " << endl;
	 int alp = INT_MIN;
	 int bet = INT_MAX;
	 int i = 0;
	 loc = alphaB(i, 8, alp, bet, p2.max_pl);
	 Drop(p2, loc+1);
	 person++;
      }
      winner = check();
      
   }
   if (winner == true)
   {
      print();
      cout << endl;
      cout << "The winner is: ";
      if (win == "max")
      {
	 if (p1.max_pl == true)
	    cout << p1.name << endl;
	 else
	    cout << p2.name << endl;
      }
      else
      {
	 if (p1.max_pl == false)
	    cout << p1.name << endl;
	 else
	    cout << p2.name << endl;
      }
      return 0;
   }
}
void create_board()
{
   for (int i = 0; i < 6; i++)
   {
      for (int j = 0; j < 7; j++)
	 Grid[i][j] = 'e';
   }
}

void print()
{
   for (int i = 0; i < 6; i++)
   {
      for (int j = 0; j < 7; j++)
      {
	 if (j == 0)
	    cout << " | ";
	 else
	 {}
	 cout << Grid[i][j] << " | ";
      }
      cout << endl;
   }
}
//I'M SORRYYYYYYYYYYYYYYYYYYYYYYY :'(
bool check()
{
   for (int i = 0; i < 6; i++)
   {
      for (int j = 0; j < 7; j++)
      {
	 if ((Grid[i][j] == 'x' && Grid[i+1][j+1] == 'x' && Grid[i+2][j+2] == 'x' && Grid[i+3][j+3] == 'x')or // diagonal to the right
	     (Grid[i][j] == 'x' && Grid[i-1][j+1] == 'x' && Grid[i-2][j+2] == 'x' && Grid[i-3][j+3] == 'x')or //  "        "  "   right down
	     (Grid[i][j] == 'x' && Grid[i+1][j-1] == 'x' && Grid[i+2][j-2] == 'x' && Grid[i+3][j-3] == 'x')or //  "        "  "   left
	     (Grid[i][j] == 'x' && Grid[i-1][j-1] == 'x' && Grid[i-2][j-2] == 'x' && Grid[i-3][j-3] == 'x')or //  "        "  "    "   down
	     (Grid[i][j] == 'x' && Grid[i][j+1] == 'x' && Grid[i][j+2] == 'x' && Grid[i][j+3] == 'x')or //horizontal
	     (Grid[i][j] == 'x' && Grid[i+1][j] == 'x' && Grid[i+2][j] == 'x' && Grid[i+3][j] == 'x')) // vertical
	 {
	    win = "max";
	    return true;
	    
	 }
	 else if ((Grid[i][j] == 'o' && Grid[i+1][j+1] == 'o' && Grid[i+2][j+2] == 'o' && Grid[i+3][j+3] == 'o')or
		  (Grid[i][j] == 'o' && Grid[i-1][j+1] == 'o' && Grid[i-2][j+2] == 'o' && Grid[i-3][j+3] == 'o')or
		  (Grid[i][j] == 'o' && Grid[i+1][j-1] == 'o' && Grid[i+2][j-2] == 'o' && Grid[i+3][j-3] == 'o')or
		  (Grid[i][j] == 'o' && Grid[i-1][j-1] == 'o' && Grid[i-2][j-2] == 'o' && Grid[i-3][j-3] == 'o')or
		  (Grid[i][j] == 'o' && Grid[i][j+1] == 'o' && Grid[i][j+2] == 'o' && Grid[i][j+3] == 'o')or
		  (Grid[i][j] == 'o' && Grid[i+1][j] == 'o' && Grid[i+2][j] == 'o' && Grid[i+3][j] == 'o'))
	 {
	    win = "min";
	    return true;
	    
	 }	 
      }
   }
   return false;
}

bool Drop(player pl, int loc)
{
   loc--;
   if (validmove(loc))
   {
      for (int i = 5; i >= 0; i--)
      {
	 if (Grid[i][loc] == 'e')
	 {
	    if (pl.max_pl == true)
	    {
	       Grid[i][loc] = 'x';
	       return true;
	    }
	    else
	    {
	       Grid[i][loc] = 'o';
	       return true;
	    }
	 }
      }
   }
   else
      cout << "INVALID" << endl;
   return false;

   print();
}

bool validmove(int loc)
{
      if (Grid[5][loc] == 'e' or Grid[0][loc]== 'e')
	 return true;
      else
	 return false;
}

int alphaB(int j, int d, int alp, int bet, bool maxpl)
{
   int v;
   if (d == 0)
      return 4;
   if (maxpl)// maximizing player
   {
      v = INT_MIN;
      for (int i = 0; i < 7; i++)
      {
	
      }
   }
   else
   {

   }
}
