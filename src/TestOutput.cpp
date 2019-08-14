/*
EZ2 I/O Replacement Project
Copyright (C) 2019 Ignacio Conde

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#define WINVER 0x410
#define _WIN32_WINDOWS 0x0410
#define _WIN32_IE 0x0500
#define _WIN32_IE_IE50 0x0500

//Hacky stuff stolen from stackoverflow for printing in binary.
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#include <iostream>
#include <string>
#include <iostream.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Functions
void outPortASM(int portid, char value);

int main(){
	printf("EZ2 I/O Replacement Project  Copyright (C) 2019  Ignacio Conde\n");
	printf("This program comes with ABSOLUTELY NO WARRANTY; for details type 'w'.\n");
	printf("This is free software, and you are welcome to redistribute it under certain conditions; type 'c' for details.\n\n");
	printf("Enter 'r' to run the software.\n\n");
	string s;
	cin >> s;

	while(s != "r"){
		if(s == "w"){
		printf("\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;\nwithout even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n\n");
		}
		else if(s == "c"){
			printf("\nThis program is free software:\nyou can redistribute it and/or modify it under the terms of the GNU General Public License\nas published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n");
		}
		else
			printf("\nUnexpected command. Please try again.\n\n");

		cin >> s;
	}

	while(s != "n"){
		int port;
		printf("\nPlease insert port 256~259: \n\n");
		cin >> port;

		int value;
		printf("\nPlease insert value (128/64/32/16/8/4/2/1): \n\n");
		cin >> value;

		outPortASM(port, value);

		printf("\nDo you want to keep testing? (Y/N): \n\n");
		cin >> s;
	}

	printf("\n\nPress any key to exit the software.\n");
	getch();
	return 0;
}

void outPortASM(int portid, char value){
	__asm mov edx,portid
	__asm mov al,value
	__asm out dx,al
}