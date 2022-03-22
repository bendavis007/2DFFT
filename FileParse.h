//    <Header file for FileParse.cpp>
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
Code names: FileParse.h

Language: C++

Code tested under the following compilers/operating systems: gcc versions 4.0.1, 4.1.1, 4.2.1

Additional comments: Header file for FileParse.cpp.

================================================================================*/
#ifndef file_parse_h
#define file_parse_h

int ParseInt(int Start, int Stop, char* parseline);
double ParseDbl(int Start, int Stop, char* parseline);
char ParseChar(int Start, int Stop, char* parseline);
char* ParseDel(int Inst, int Character, char* parseline);



#endif
