//    <Routine for reading in data.>
//    Copyright (C) <2012>  <Darrell Berrier>

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

/*================================================================================
Title:
Authors:
================================================================================
Code names: FileParse.cpp

Language: C++

Code tested under the following compilers/operating systems: gcc versions 4.0.1, 4.1.1, 4.2.1

Additional comments: Routine for reading in data.

================================================================================*/
#include "FileParse.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>

using namespace std;

char chartemp [500];

char ParseChar(int Start, int Stop, char* parseline)
{
    char temp[2];
    int Sp = Stop;
    int i = 0;
        
    for (int St = Start; St <= Sp; St++)
    {
      temp[i] = parseline[St];
      temp[i+1] = '\0';
      i++;
    };

    char Answer[0];
    Answer[0] = temp[0];
    return(Answer[0]);
    };

int ParseInt(int Start, int Stop, char* parseline)
{
    char temp[15];
    int Answer = 0;
    int Sp = Stop;
    int tp = 0;
    int i = 0;
        
    for (int St = Start; St <= Sp; St++)
    {
        temp[i] = parseline[St];
        temp[i+1] = '\0';
        i++;
    };
    Answer = atoi(temp);
    return(Answer);
};

double ParseDbl(int Start, int Stop, char* parseline)
{
    char temp[35];
    double Answer = 0.0;
    int Sp = Stop;
    int tp = 0;
    int i = 0;
    for (int x=0; x<=35; x++)
    {temp[x] = '\0';};
        
    for (int St = Start; St-1 < Sp; St++)
    {
        temp[i] = parseline[St];
        temp[i+1] = '\0';
        i++;
    };
//    cout << "Temp: " << temp << endl;
    Answer = atof(temp);
    return(Answer);
};

char* ParseDel(int Inst, int Character, char* parseline){
      int x = 0;
      int Instance = Inst;
      int instcount = 0;
      char Deliminator = Character;
      int length = 0;
      for (int x=0; x<=500; x++){chartemp[x] = '\0';};
      
      length = strlen(parseline);
      
      for (int i = 0; i <= length; i++)
          {                
               if (parseline[i] == Deliminator || parseline[i] =='\0'){instcount ++; i++;}
               if( instcount == (Instance - 1)){
                   chartemp[x] = parseline[i];
                   x++;
                   }
           }
return (chartemp);                  
}

