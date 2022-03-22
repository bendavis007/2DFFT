//    <Header file for FileClass.cpp.>
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
Code names: FileClass.h

Language: C++

Code tested under the following compilers/operating systems: gcc versions 4.0.1, 4.1.1, 4.2.1

Additional comments: Header file for FileClass.cpp.

================================================================================*/
#ifndef file_class_h
#define file_class_h

#define SIZE 150

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class FileClass
{
    public: 
        FileClass() { };                     //Class Constructor
        ~FileClass() { };                    //Class Destructor
        char mode[10];
        ifstream myfileread;                 //For Reading data
        ofstream myfilewrite;                //For Writeing Data
        
        char File_Name[30];                  //String Array for File_Name Variable
        
        void GetFileName();                  //Class Function get have user enter the FileName
        void AssignFileName(char AssnFileName[]); // Assign File Name
	void AppendFileName(char extended[]); // Append to main File name
        
        void Open_File_Read();               //Class Function to Open a File for Reading
        void Open_File_Write();              //Class Function to Open a File for Reading     

        void Read_Data (char line[]);        //Class Function to Read data from a file
        
        void Write_Data(char character);     //Class Function to Write a character to a data file  
        void Write_Data(char line[]);        //Class Function to Write String Charachter data to a file
        void Write_Data(int number, int width, int precision);         //Class Function to Write Interger numeric data to a file        
        void Write_Data(long int number, int width, int precision);    //Class Function to Write Interger numeric data to a file        
        void Write_Data(double number, int width, int precision);      //Class Function to Write Double numberic data to a file                
        void Write_Data(long double number, int width, int precision); //Class Function to Write Double numberic data to a file                        

        void Write_Data(float number, int width, int precision);       //Class Function to Write Double numberic data to a file                

        void Close_Read_File();              //Class Function to Close a file that was opened for Reading
        void Close_Write_File();             //Class Function to Close a file that was opened for Writing

        int EndOfReadFile();                 //Class Function to Detect End of File for Reading Functions
        int EndOfWriteFile();                //Class Function to Detect End of File for Writing Functions  
};        

#endif
