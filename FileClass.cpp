//    <Program handles data I/O.>
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
Code names: FileClass.cpp

Language: C++

Code tested under the following compilers/operating systems: gcc versions 4.0.1, 4.1.1, 4.2.1

Additional comments: Program handles data I/O.

================================================================================*/

#include "FileClass.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;

void FileClass::GetFileName()
{
    // Note: This function has no error checking
    cout << "Enter File Name: ";
    cin >> File_Name;
}

void FileClass::AssignFileName(char AssnFileName[])
{
    strcpy(File_Name, AssnFileName);
    cout << File_Name << endl;
}

void FileClass::AppendFileName(char extended[])
{
}    

void FileClass::Open_File_Read()
{
    myfileread.open(File_Name,ios::in);
    if (!myfileread)
     {  
         cerr << "\nInput file: " << File_Name << " cannot be opened\n";
         exit(1);     
     }  
}

void FileClass::Open_File_Write()
{
    myfilewrite.open(File_Name,ios::out);
    if (!myfilewrite)
     {  
         cerr << "\nOutput file: " << File_Name << " cannot be opened\n";
         exit(1);     
     }  
}

void FileClass::Read_Data(char line[])
{   
    myfileread.getline(line,700);  
}

void FileClass::Write_Data(char character)
{
    myfilewrite << character;
}

void FileClass::Write_Data(char line[])
{
    //strcat(line,"\n");
    myfilewrite << line; //<< endl;
}

void FileClass::Write_Data(int number, int width, int precision)
{
    cout.fill(' ');
   myfilewrite << setw(width) << setprecision(precision) << fixed << number; // << "\n";
}

void FileClass::Write_Data(long int number, int width, int precision)
{
//   cout << fixed; 
   cout.fill(' '); 
   myfilewrite << setw(width) << setprecision(precision) << fixed << number; // << "\n";
}

void FileClass::Write_Data(double number, int width, int precision)
{
    cout.fill(' ');
   myfilewrite << setw(width) << setprecision(precision) << fixed << number; // << "\n";
}

void FileClass::Write_Data(long double number, int width, int precision)
{
    cout.fill(' ');
    myfilewrite << setw(width) << setprecision(precision) << number; // << "\n";
}

void FileClass::Write_Data(float number, int width, int precision)
{
    cout.fill(' ');
    myfilewrite << setw(width) << setprecision(precision) << number; // << "\n";
}

void FileClass::Close_Read_File()
{
    myfileread.close();
}

void FileClass::Close_Write_File()
{
    myfilewrite.close();
}

int FileClass::EndOfReadFile()
{
    return(myfileread.eof());
}

int FileClass::EndOfWriteFile()
{
    return(myfilewrite.eof());
}


