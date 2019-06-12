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

#include <iostream.h>
#include <conio.h>

using namespace std;

//Functions
char inPortASM(int);
void readPorts();

//Constants
const int CONSTANT = 156;

int main() {
	for (int value = 0 ; value <= 4 ; value++)
	{
		readPorts();
	}
   getch();
   return 0;
}

//Reads ports 100~108 and prints its values on binary or 0~255 for the turntables.
void readPorts()
{
	int portid = 101;
	unsigned char show;

	//While not finished
	while (portid != 999)
	{
		//Stores read value from current port [PORT VALUE IS HARDCODED, NOTICE '+CONSTANT'].
		show = inPortASM(portid+CONSTANT);

		//Shifts values to start in decimal 0 for presentation.
		if(portid == 103 || portid == 104)
			show += 128;

		//Prints the value obtained from the port in binary, or in decimal in the case of turntables. (Binary printing stolen from stackoverflow)
		switch (portid)
		{
			case 101:
				{
					printf("TEST, SVC, E4~1 & P2~1 = "BYTE_TO_BINARY_PATTERN"\r\n", BYTE_TO_BINARY(show));
					portid = 103;
				}
				break;

			case 103:
				{
					printf("P1 TT = %d\r\n", show);
					portid = 102;
				}
				break;

			case 102:
				{
					printf("PDL1, 2xQE, B5~1  = "BYTE_TO_BINARY_PATTERN"\r\n", BYTE_TO_BINARY(show));
					portid = 104;
				}
				break;

			case 104:
				{
					printf("P2 TT = %d\r\n", show);
					portid = 106;
				}
				break;

			case 106:
				{
					printf("PDL2, 2xQE, B10~6 = "BYTE_TO_BINARY_PATTERN"\r\n", BYTE_TO_BINARY(show));
					portid = 999;
				}
				break;
		}
	}
}

//Reads and returns the value of the specified input port. (Stolen from UserPort 2.0 PDF)
char inPortASM (int portid)
{
	char value;
	__asm mov edx,portid
	__asm in al,dx
	__asm mov value,al
	return value;
}