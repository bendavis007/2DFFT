//    <Program reads in a set of csv formatted input then generates a shell script to call 2dfft.>
//    Copyright (C) <2012>  <Joel Berrier>

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
Code names: scripter.cpp

Language: C++

Code tested under the following compilers/operating systems: gcc versions 4.0.1, 4.1.1, 4.2.1

Description of input data:

> [blank line]
> image_textfile_1,keyword_1,outer_radius_1
> image_textfile_2,keyword_2,outer_radius_2
> image_textfile_3,keyword_3,outer_radius_3
> image_textfile_etc,keyword_etc,outer_radius_etc
> [blank line]

may run this on as many image_textfiles as desired.
Units are in pixels.

Description of output data: Creates shell script for calling 2dfft.

Additional comments: Program  reads in a set of csv formatted input then generates a shell script to call 2dfft.

================================================================================*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "FileClass.h"
#include "FileParse.h"

using namespace std;

int dummy = 0;
char buffer[21];

int main(int argc, char *argv[])
{
  struct Master
  {
    char filename[40];
    char keyword[40];
    char radius[40];
    int max;
  };
 
  cout << "Creating Array" << endl;
  Master *ReadArray = new Master[1200];
    
  cout << "Creating Variables" << endl;
  int Number = 0;
  char NLine[150];

  cout << "Creating File Class Objects" << endl;
  FileClass ReadArrayRead;
  FileClass ScriptWrite;
  
  cout << "Collecting File Information" << endl;
  cout << "Enter Input File Name\n";
  ReadArrayRead.GetFileName();
  ReadArrayRead.Open_File_Read();
  cout << endl;
  
  cout << "Enter Output File Name\n";
  ScriptWrite.GetFileName();
  ScriptWrite.Open_File_Write();
  cout << endl;

  while(! ReadArrayRead.EndOfReadFile())
   {
     ReadArrayRead.Read_Data(NLine);
     strcpy(ReadArray[Number].filename,ParseDel(1, ',',NLine));
     strcpy(ReadArray[Number].keyword,ParseDel(2, ',',NLine));
     strcpy(ReadArray[Number].radius,ParseDel(3, ',',NLine));
     ReadArray[Number].max = atoi(ReadArray[Number].radius);
     Number++;
   }    
 
  cout << "Closing File Class for Input to Array" << endl;
  ReadArrayRead.Close_Read_File();
  
  // Start Processing according to specifications
  cout << "Writing Scripts.  Please wait.." << endl;

  int dummy = 0;

  for (int i = 1; i < Number-1 ;i++)
    {
      cout << Number - i - 1 << endl;

      dummy = ReadArray[i].max;
      
      ScriptWrite.Write_Data((char*)"rm");
      ScriptWrite.Write_Data(' ');
      ScriptWrite.Write_Data(ReadArray[i].keyword);
      ScriptWrite.Write_Data((char*)"_m*");
      ScriptWrite.Write_Data('\n');
      ScriptWrite.Write_Data('\n');
      
      for(int j = 1; j < dummy; j++)
	{
	  ScriptWrite.Write_Data((char*)"./2dfft << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data(ReadArray[i].filename);
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data(' ');
	  ScriptWrite.Write_Data(ReadArray[i].max,0,0);
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');
	  
	  /*	  ScriptWrite.Write_Data("./smu_fft << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data("out");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data("outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data("_");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data("END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');  */

	  ScriptWrite.Write_Data((char*)"./give_maximum_pitch_phase << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_m0");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"cat temp_pitch_data >> ");
	  ScriptWrite.Write_Data(ReadArray[i].keyword);
	  ScriptWrite.Write_Data((char*)"_m0");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"./give_maximum_pitch_phase << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_m1");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"cat temp_pitch_data >> ");
	  ScriptWrite.Write_Data(ReadArray[i].keyword);
	  ScriptWrite.Write_Data((char*)"_m1");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"./give_maximum_pitch_phase << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_m2");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"cat temp_pitch_data >> ");
	  ScriptWrite.Write_Data(ReadArray[i].keyword);
	  ScriptWrite.Write_Data((char*)"_m2");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"./give_maximum_pitch_phase << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_m3");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"cat temp_pitch_data >> ");
	  ScriptWrite.Write_Data(ReadArray[i].keyword);
	  ScriptWrite.Write_Data((char*)"_m3");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"./give_maximum_pitch_phase << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_m4");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"cat temp_pitch_data >> ");
	  ScriptWrite.Write_Data(ReadArray[i].keyword);
	  ScriptWrite.Write_Data((char*)"_m4");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"./give_maximum_pitch_phase << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_m5");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"cat temp_pitch_data >> ");
	  ScriptWrite.Write_Data(ReadArray[i].keyword);
	  ScriptWrite.Write_Data((char*)"_m5");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"./give_maximum_pitch_phase << END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"outi");
	  ScriptWrite.Write_Data(j,0,0);
	  ScriptWrite.Write_Data((char*)"_m6");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"END");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"cat temp_pitch_data >> ");
	  ScriptWrite.Write_Data(ReadArray[i].keyword);
	  ScriptWrite.Write_Data((char*)"_m6");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');

	  ScriptWrite.Write_Data((char*)"rm temp_pitch_data*");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"rm out*");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data((char*)"rm gal.parmout*");
	  ScriptWrite.Write_Data('\n');
	  ScriptWrite.Write_Data('\n');
	};
      
    };

  cout << "Closing remaining File Class" << endl;
  ScriptWrite.Close_Write_File();

  cout << "Ending Results" << endl;
  
  cout << "Clearing Arrays from Memory" << endl;
  
  delete [] ReadArray;
  
  cout << "Application Run is done!" << endl;
  
  return 0;
};
