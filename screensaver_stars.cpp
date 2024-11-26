//enrico fracasso, 2024
//screensaver (stars)

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

short width,height;

void SetColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Reset the color to default
void ResetColor() {
    SetColor(7, 0);  // Light Gray text on black background
}

bool isCursorOnCharacter(char characterToCheck) {
    // Get handle to the console screen buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        cerr << "Error: Invalid console handle!" << endl;
        return false;
    }

    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        cerr << "Error: Unable to retrieve console buffer info!" << endl;
        return false;
    }
    COORD cursorPos = csbi.dwCursorPosition;

    // Read the character at the cursor position
    char readChar;
    DWORD charsRead;
    if (!ReadConsoleOutputCharacterA(hConsole, &readChar, 1, cursorPos, &charsRead)) {
        cerr << "Error: Unable to read console output!" << endl;
        return false;
    }

    // Check if the read character matches the target character
    return (charsRead > 0 && readChar == characterToCheck);
}

int GetConsoleWindowSize(void) {
    // Get handle to the active console screen buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        //std::cerr << "Error: Unable to get console handle." << std::endl;
        return 1;
    }

    // Get console screen buffer information
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        //std::cerr << "Error: Unable to get console screen buffer info." << std::endl;
        return 2;
    }

    // Calculate the console window size
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int main(void){
	system("cls");
	GetConsoleWindowSize();
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	COORD coord;
	short color;
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		while(true){
			color=0 + rand() % (15 - 0 + 1);
			coord.X = 0 + rand() % (width - 0 + 1);    // X position
			coord.Y = 0 + rand() % (height - 0 + 1);    // Y position
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			if(isCursorOnCharacter('@')){
				SetColor(15,0);
				cout<<" ";
			}else{
				SetColor(15,15);
				cout<<"@";
			}
			Sleep(150);
		}
	}
	SetColor(7,0);
	system("cls");
	return 0;
}

