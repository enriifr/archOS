//enrico fracasso
//archos system updater 2.0

#include <iostream>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
int globCentroY,globCentroX;
bool fileismoved = false;

void dialogBox(const char messagechar[], short appendedLines=0){
	COORD coord;
	coord.X = (globCentroX-(strlen(messagechar)/2));    // X position
	coord.Y = globCentroY+5+appendedLines;    // Y position
	string message;
	for(int loop=0;messagechar[loop]!='\0';loop++){
		message=message+messagechar[loop];
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout<<message<<endl;
}

void SetColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Reset to default console color
void ResetColor() {
    SetColor(7, 0); // Light Gray on Black
}

void bootupIMG(int xcentro,int ycentro, bool isUpdating=false){
	int numRighe=0;
	const char riga1[]="   @@@@@@@@@    @@@@@@@@@  @@@@@@@@@    @@    @@     @@@@@@@@     @@@@@@@@@";
	const char riga2[]="  @@@    @@@   @@@    @@@ @@@    @@@   @@@    @@@   @@@    @@@   @@@    @@@";
	const char riga3[]="  @@@    @@@   @@@    @@@ @@@    @@    @@@    @@@   @@@    @@@   @@@    @@ ";
	const char riga4[]="  @@@    @@@  @@@@@@@@@@@ @@@         @@@@@@@@@@@@@ @@@    @@@   @@@       ";
	const char riga5[]="@@@@@@@@@@@@ @@@@@@@@@@   @@@        @@@@@@@@@@@@@  @@@    @@@ @@@@@@@@@@@@";
	const char riga6[]="  @@@    @@@ @@@@@@@@@@@@ @@@    @@    @@@    @@@   @@@    @@@          @@@";
	const char riga7[]="  @@@    @@@   @@@    @@@ @@@    @@@   @@@    @@@   @@@    @@@    @@    @@@";
	const char riga8[]="  @@@    @@    @@@    @@@ @@@@@@@@@    @@@    @@     @@@@@@@@   @@@@@@@@@@ ";
	const char riga9[]="               @@@    @@@                                                  ";
	const char riga10[]="[ Installing Update... ]";
	COORD coord;    // Coordinate structure
	coord.X = (xcentro-(strlen(riga1)/2));    // X position
	coord.Y = ycentro-5;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga1[loop]!='\0';loop++){
		if(riga1[loop]==' '){
			SetColor(15,0);
			cout<<riga1[loop];
		}
		if(riga1[loop]=='@'){
			SetColor(4,4);
			cout<<riga1[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga2)/2));    // X position
	coord.Y = ycentro-4;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga2[loop]!='\0';loop++){
		if(riga2[loop]==' '){
			SetColor(15,0);
			cout<<riga2[loop];
		}
		if(riga2[loop]=='@'){
			SetColor(4,4);
			cout<<riga2[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga3)/2));    // X position
	coord.Y = ycentro-3;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga3[loop]!='\0';loop++){
		if(riga3[loop]==' '){
			SetColor(15,0);
			cout<<riga3[loop];
		}
		if(riga3[loop]=='@'){
			SetColor(4,4);
			cout<<riga3[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga4)/2));    // X position
	coord.Y = ycentro-2;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga4[loop]!='\0';loop++){
		if(riga4[loop]==' '){
			SetColor(15,0);
			cout<<riga4[loop];
		}
		if(riga4[loop]=='@'){
			SetColor(4,4);
			cout<<riga4[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga5)/2));    // X position
	coord.Y = ycentro-1;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga5[loop]!='\0';loop++){
		if(riga5[loop]==' '){
			SetColor(15,0);
			cout<<riga5[loop];
		}
		if(riga5[loop]=='@'){
			SetColor(4,4);
			cout<<riga5[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga6)/2));    // X position
	coord.Y = ycentro;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga6[loop]!='\0';loop++){
		if(riga6[loop]==' '){
			SetColor(15,0);
			cout<<riga6[loop];
		}
		if(riga6[loop]=='@'){
			SetColor(4,4);
			cout<<riga6[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga7)/2));    // X position
	coord.Y = ycentro+1;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga7[loop]!='\0';loop++){
		if(riga7[loop]==' '){
			SetColor(15,0);
			cout<<riga7[loop];
		}
		if(riga7[loop]=='@'){
			SetColor(4,4);
			cout<<riga7[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga8)/2));    // X position
	coord.Y = ycentro+2;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga8[loop]!='\0';loop++){
		if(riga8[loop]==' '){
			SetColor(15,0);
			cout<<riga8[loop];
		}
		if(riga8[loop]=='@'){
			SetColor(4,4);
			cout<<riga8[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga9)/2));    // X position
	coord.Y = ycentro+3;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga9[loop]!='\0';loop++){
		if(riga9[loop]==' '){
			SetColor(15,0);
			cout<<riga9[loop];
		}
		if(riga9[loop]=='@'){
			SetColor(4,4);
			cout<<riga9[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga10)/2));    // X position
	coord.Y = ycentro+5;    // Y position
	cout<<endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetColor(15,0);
	cout<<"[ Installing Update... ]"<<endl;
	ResetColor();
	if(isUpdating){
		coord.X = (xcentro-(strlen(riga10)/2));    // X position
		coord.Y = ycentro+5;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		
		srand(time(NULL));
		int randomSleep;
		for(int loop=0;loop<23;loop++){
			randomSleep= rand() % 1000 + 1;
			Sleep(randomSleep);
			SetColor(0,10);
			if(loop!=0){
				cout<<riga10[loop];
			}else{
				SetColor(15,0);
				cout<<"[";
				ResetColor();
			}
		}
		cout<<endl;
		ResetColor();
	}
}


// Set console text color

void changelog_print(const string& fileName, const string& version) {
    ifstream inputFile(fileName); // Open the file for reading

    if (!inputFile) {
    	SetColor(12,0);
        cerr << "Error: Unable to open file: " << fileName << endl;
        ResetColor();
		return; // Exit the function on error
    }
	cout<<"\nWhat's new in version "<<version<<"\n"<<endl;
    string line;
    while (getline(inputFile, line)) {
        // Print each line to the console
        cout << line << endl;
    }
	cout<<endl;
    inputFile.close(); // Close the file
}

// Get first line from a file
string getFirstLine(const string& filename) {
    ifstream file(filename); // Open file for reading
    if (file.is_open()) {
        string firstLine;
        if (getline(file, firstLine)) { // Read the first line
            file.close();
            return firstLine; // Return the first line
        } else {
            file.close();
            return "Version Unknown";
        }
    } else {
        return "Version Unknown";
    }
}

// Rename a file
void renameFile(const string& oldName, const string& newName) {
    if (MoveFile(oldName.c_str(), newName.c_str())) {
        // File successfully renamed
    } else {
        // Error handling if rename fails
    }
}

// Check if USB is present
bool is_usb_present(const string& usb_path) {
    DWORD ftyp = GetFileAttributes(usb_path.c_str());
    return (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY));
}

// Check if file is system or hidden
bool is_system_or_hidden(const string& file_path) {
    DWORD file_attributes = GetFileAttributes(file_path.c_str());
    if (file_attributes == INVALID_FILE_ATTRIBUTES) {
        return true; // Invalid file attributes (not accessible)
    }
    return (file_attributes & FILE_ATTRIBUTE_SYSTEM) || (file_attributes & FILE_ATTRIBUTE_HIDDEN);
}

// Move file from source to destination
void move_file(const string& source, const string& destination) {
    if (rename(source.c_str(), destination.c_str()) != 0) {
        SetColor(12, 0);  // Red text
        dialogBox("Error installing the new system image.");
        ResetColor();
    } else {
        fileismoved = true;
    }
}

// Move files from USB to destination folder
void move_files(const string& usb_path, const string& destination) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    string search_path = usb_path + "\\*";  // Wildcard to search all files in the directory
    hFind = FindFirstFile(search_path.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        SetColor(12, 0);  // Red text
        dialogBox("Error opening USB directory.");
        ResetColor();
        return;
    }

    do {
        string file_name = findFileData.cFileName;
        if (file_name != "." && file_name != "..") {
            string source_path = usb_path + "\\" + file_name;
            string destination_path = destination + "\\" + file_name;

            // Skip system and hidden files
            if (is_system_or_hidden(source_path)) {
                continue;
            }

            // Move the file to the destination folder
            move_file(source_path, destination_path);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

// Get the current directory
string getCurrentDirectory() {
    char buffer[MAX_PATH];
    DWORD length = GetCurrentDirectoryA(MAX_PATH, buffer);
    if (length == 0) {
        SetColor(12, 0);  // Red text
        dialogBox("Failed to get current directory.");
        ResetColor();
        return "";
    }
    return string(buffer);
}

// Main function for moving files
int main_filemover() {
    string currentDir = getCurrentDirectory();
    // Path to your USB drive and destination folder (replace these with your actual paths)
    string usb_path = "E:\\";  // Example: "E:\" (update this to your USB path or letter)
    string destination_folder = currentDir; // Destination folder

    SetColor(10, 0);  // Green text
    dialogBox("Waiting for USB drive to be inserted...");

    // Continuously check for USB drive
    while (true) {
        // Check if the USB is present
        if (is_usb_present(usb_path)) {
            SetColor(10, 0);  // Green text
            //cout << "USB stick detected!\nSystem update in progress..." << endl;
            ResetColor();
            Sleep(300);

            // Move files from USB to destination folder
            move_files(usb_path, destination_folder);
            break;  // Exit loop after moving files
        }

        // Wait for a short time before checking again
        Sleep(2000);
    }

    if (fileismoved == false) {
        SetColor(14, 0);  // Yellow text
        dialogBox("Something went wrong. Aborting System Update...");
        Sleep(700);
        dialogBox("                                                     ");
        Sleep(700);
        dialogBox("Something went wrong. Aborting System Update...");
        Sleep(700);
        dialogBox("                                                     ");
        Sleep(700);
        dialogBox("Something went wrong. Aborting System Update...");
        Sleep(1500);
        ResetColor();
        return 404;
    }

    //system("pause");
    return 0;
}

void getCenter(void) {
	
    // Get the console screen buffer information
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // Calculate the center position
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        globCentroX = consoleWidth / 2;
        globCentroY = consoleHeight / 2;

        // Set the cursor position to the center
        COORD centerCoord = {static_cast<SHORT>(globCentroX), static_cast<SHORT>(globCentroY)};
        SetConsoleCursorPosition(hConsole, centerCoord);
    } else {
        //crashScreen("GETCONSOLECENTER","CONSOLE_SCREEN_BUFFER_INFO_UNAVAIL");
    }
}

int main() {
	system("cls"),
	getCenter();
	bootupIMG(globCentroX,globCentroY);
    string oldFileName = "SYSTEM.MAIN.exe"; // Replace with your file's current name
    string newFileName = "old.system.main.exe"; // Replace with the desired new name
    renameFile("changelog.txt", "changelog.OLD.txt");
    renameFile(oldFileName, newFileName);
    
    //main_filemover();

    switch (main_filemover()) {
        case 0:
        	system("cls");
			getCenter();
			bootupIMG(globCentroX,globCentroY,true);
			system("cls");
            SetColor(10, 0);  // Green text
            cout << "System updated successfully to version " << getFirstLine("changelog.txt") << "." << endl;
            ResetColor();
            system("pause");
            changelog_print("changelog.txt", getFirstLine("changelog.txt"));
            system("pause");
            system("del changelog.OLD.txt");
            system("SYSTEM.MAIN.exe");
            break;
        case 404:
            string newFileName = "SYSTEM.MAIN.exe"; // Replace with your file's current name
            string oldFileName = "old.system.main.exe"; // Replace with the desired new name
        
            renameFile(oldFileName, newFileName);
            SetColor(12, 0);  // Red text
            dialogBox("Unable to update system. Verify installation files in USB drive and try again.");
            ResetColor();
            cout<<endl;
            system("PAUSE");
            break;
    }

    exit(0);
}

