#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <limits>
#include <vector>
#include <chrono>

#define OS_VER "ArchOS 0.8.119 "

using namespace std;
using namespace chrono;
steady_clock::time_point lastKeyPressTime = steady_clock::now();

// SETTINGS GLOBALS
int globScreensaverTime;
bool globScreensaverEnabled;
////////////////////

int main(void);
void mainmenu(const string& username = "User");
void statusbar(const string& status, const string& username);
void SetColor(int textColor, int bgColor);
void ResetColor();

const DWORD MAX_BUFFER_SIZE = 10000;
short globTIMEH,globTIMEM,globReminderHours,globReminderMins,globUSERCOORDY,globUSERCOORDX;
string globSTATUS,globUSER;
string globIsUserAdmin;
char globReminderText[20]="";
bool sysupdated=false,globHasBooted=false;
int globCentroX,globCentroY;

void crashScreen(const string& errprocess,const string& errorcode);

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
        crashScreen("GETCONSOLECENTER","CONSOLE_SCREEN_BUFFER_INFO_UNAVAIL");
    }
}

void bootupIMG(int xcentro,int ycentro){
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
	const char riga10[]="Booting Up...";
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
	SetColor(14,0);
	cout<<"Booting Up..."<<endl;
	ResetColor();
}

void crashScreen(const string& errprocess,const string& errorcode){
	sysupdated=true;
	system("cls");
	system("color f7");
	SetColor(0,15);
	cout<<"One or more System's processes returned an unexpected error."<<endl;
	cout<<"To prevent further damage to Your Computer, the session was terminated."<<endl;
	cout<<"All unsaved data will be lost."<<endl;
	cout<<endl<<"Error occurred in process: "<<errprocess<<endl;
	cout<<"Error: "<<errorcode<<endl;
	cout<<endl<<endl<<"Press any key to quit."<<endl;
	
	
	//sad smiley
	COORD coord;    // Coordinate structure
	coord.X = 50;    // X position
	coord.Y = 10;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetColor(15,8);
	cout<<"  ";
	coord.X = 54;    // X position
	coord.Y = 10;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetColor(15,8);
	cout<<"  ";
	coord.X = 48;    // X position
	coord.Y = 12;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetColor(15,8);
	cout<<"          ";
	coord.X = 46;    // X position
	coord.Y = 13;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetColor(15,8);
	cout<<"  ";
	coord.X = 58;    // X position
	coord.Y = 13;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetColor(15,8);
	cout<<"  ";
	SetColor(0,15);
	cout<<endl<<endl;
	getchar();
	exit(0);
}

DWORD WINAPI clock(LPVOID lpParam) {
    string* message = static_cast<string*>(lpParam);
    while(sysupdated==false){
		// Save the current cursor position
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
		if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		    SHORT originalX = csbi.dwCursorPosition.X;
		    SHORT originalY = csbi.dwCursorPosition.Y;
			COORD coord;    // Coordinate structure
			coord.X = 0;    // X position
			coord.Y = 0;    // Y position
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			//statusbar(globSTATUS,globUSER);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			SYSTEMTIME localTime;
			GetLocalTime(&localTime);
			int oldTime=localTime.wMinute;
			SetColor(15,0);
			cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute;
			ResetColor();
			coord.X=originalX;
			coord.Y=originalY;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			while(oldTime==localTime.wMinute){ 
				globUSERCOORDX=coord.X=originalX;
				globUSERCOORDY=coord.Y=originalY;
				GetLocalTime(&localTime);
				globTIMEH=localTime.wHour;
				globTIMEM=localTime.wMinute;
				//globTIMES=localTime.wSecond;
				Sleep(500);
			}
		}else{
			crashScreen("SYSCLOCK","CONSOLE_SCREEN_BUFFER_INFO_UNAVAIL");
		}
	}
    return 0;
}

void createSettingsDB(const string& username){
	string filename;
	filename=username+"_settings.txt";
	ofstream outFile(filename);
	if(outFile.is_open()){
		outFile<<"SCREENSAVER N"<<endl;
	}else{
		SetColor(14,0);
		cout<<"Unable to create User Settings DB File"<<endl;
	}
	outFile.close();
}

void updateSettingsDB(const string& username,const string& screensaverSettings){
	string filename;
	filename=username+"_settings.txt";
	ofstream outFile(filename);
	if(outFile.is_open()){
		outFile<<screensaverSettings<<endl;
	}else{
		SetColor(14,0);
		cout<<"\nUnable to overwrite User Settings DB File"<<endl;
		system("pause");
	}
	outFile.close();
}

void loadSettings(const string& username){
	string filename;
	filename=username+"_settings.txt";
	ifstream inputFile(filename);

    if (!inputFile) {
        //crashScreen("READ_USERDATA_SETTINGS","USERSETTINGS_FILE_UNAVAIL");
    	SetColor(12,0);
		cout<<endl<<"WARNING: USER SETTINGS DB IS UNAVAIL. DEFAULT SETTINGS APPLIED."<<endl;
		system("pause");
		globScreensaverEnabled=true;
		globScreensaverTime=10;
		return;
	}

    string line, setting="SCREENSAVER";

    string value1,value2;
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        if (lineStream>>setting>>value1>>value2) {
            if (setting == "SCREENSAVER") {
                if(value1=="T"){
                	globScreensaverEnabled=true;
				}else{
					globScreensaverEnabled=false;
				}
				globScreensaverTime=stoi(value2);
				inputFile.close();
                return; 
            }/*
            if(fileUsername==username){
            	return 1;
			}*/
        }
    }
}

int user_exists(const string& fileName="users.txt", const string& username=NULL) {
    ifstream inputFile(fileName);

    if (!inputFile) {
        crashScreen("READ_USERDATA_USRNM_CHCKR","USER_DB_FILE_UNAVAIL");
    }

    string line, fileUsername;

    string filePassword;
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        if (lineStream>>fileUsername>>filePassword>>globIsUserAdmin) {
            if (fileUsername == username && filePassword == "NULL") {
                inputFile.close();
                return 2; 
            }
            if(fileUsername==username){
            	return 1;
			}
        }
    }

	
    /*while (getline(inputFile, line)) {
        istringstream lineStream(line);
        if (lineStream >> fileUsername) {
            if (fileUsername == username) {
            	
				inputFile.close();
                return 1; 
            }
        }
    }*/
    return 0; 
}

bool validate_password(const string& fileName="users.txt", const string& username=NULL, const string& password=NULL) {
    ifstream inputFile(fileName);

    if (!inputFile) {
    	crashScreen("READ_USERDATA_PSSWD_CHCKR","USER_DB_FILE_UNAVAIL");
    }

    string line, fileUsername, filePassword;
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        if (lineStream >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                inputFile.close();
                return true; 
            }
        }
    }

    inputFile.close();
    return false; 
}

bool save_user(const string& fileName, const string& username, const string& password, const string& isAdmin) {
    if (user_exists(fileName, username)) {
        cout << "Error: Username already exists." << endl;
        return false; // Cannot save duplicate usernames
    }

    ofstream outputFile(fileName, ios::app); // Open file in append mode
    if (!outputFile) {
        crashScreen("SAVE_USERDATA","USER_DB_FILE_UNAVAIL");
        return false;
    }

    outputFile <<"\n"<< username << " " << password <<" "<<isAdmin<< endl;
    outputFile.close();
    return true; // User saved successfully
}

// Set the console text color
void SetColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Reset the color to default
void ResetColor() {
    SetColor(7, 0);  // Light Gray text on black background
}

void addUser(const string& theUser) {
    char passwordSetup;
    string userName;
    system("cls");
    //statusbar("newuser",theUser);
    SetColor(15,0);
    cout << "This process will help you set up a new User Account for this PC." << endl;
    cout << "\nPlease choose the username for the new User of This PC:\n" << theUser << "> ";
    ResetColor();
    cin >> userName;
    SetColor(15,0);
    string adminYN;
    cout<<"Grant this user admin privileges? (Y/N)"<<endl;
    ResetColor();
    cout<<theUser<<"> ";
    while(adminYN!="n"&&adminYN!="N"&&adminYN!="y"&&adminYN!="Y"){
		adminYN=getch();
		if(adminYN!="n"&&adminYN!="N"&&adminYN!="y"&&adminYN!="Y"){
			SetColor(12,0);
			cout<<"\r Invalid choice.                ";
			Sleep(420);
			cout<<"\r                                  ";
			SetColor(15,0);
			cout<<"\r"<<theUser<<"> ";
			ResetColor();
		}	
	}
	SetColor(15,0);
    cout << "\nWould you like to set up a password for your user account? (Y/N)" <<endl;
    cout<<theUser<<"> ";
    ResetColor();
	while(passwordSetup!='n'&&passwordSetup!='N'&&passwordSetup!='y'&&passwordSetup!='Y'){
		cin >> passwordSetup;
		if(passwordSetup!='n'&&passwordSetup!='N'&&passwordSetup!='y'&&passwordSetup!='Y'){
			SetColor(12,0);
			cout<<"\r Invalid choice.                ";
			Sleep(420);
			cout<<"\r                                  ";
			SetColor(15,0);
			cout<<"\r"<<userName<<"> ";
			ResetColor();
		}	
	}
	string password;
	char getch_buffer;
    if (passwordSetup == 'n' || passwordSetup == 'N') {
        SetColor(15, 1);  
        cout << "It is recommended to set up a password for additional security. You may always add one in the System's settings." << endl;
        save_user("users.txt",userName,"NULL",adminYN);
        system("pause");
    }else if(passwordSetup == 'y' || passwordSetup == 'Y'){
    	SetColor(15,0);
    	cout<<"\nType your new password for user "<<userName<<": ";
    	ResetColor();
		int loop=0;
		while(1){
				getch_buffer=getch();
				if(getch_buffer=='\r'){
					break;
				}else if(getch_buffer=='\b'){
					if(password.size()>0){
					cout<<'\b';
					cout<<" ";
					cout<<'\b';
					password.pop_back();					
					}
				}else{
					cout<<"*";
					password+=getch_buffer;
				}
			}
		//password[loop]='\0';
		save_user("users.txt",userName,password,adminYN);
	}
    SetColor(14, 0);  // Yellow text
    cout << "\nUser added to Accounts List successfully.\n" << endl;
    ResetColor();
}

void newSystem() {  // NON FINITO
    string userName = "User";
    char passwordSetup;
    SetColor(14, 0);  // Yellow text
    cout << "Thank you for choosing "<<OS_VER<< endl;
    SetColor(15,0);
    cout << "This setup will guide you through all the steps necessary to set up Your PC." << endl;
    cout << "\nPlease choose the username for the main user of This PC:\n" << userName << "> ";
    ResetColor();
    cin >> userName;
    SetColor(15,0);
    cout << "Welcome, " << userName << ". You will be the main user on This PC." << endl;
    cout << "\nWould you like to set up a password for your user account? (Y/N)" <<endl;
    cout<<userName<<"> ";
    ResetColor();
	while(passwordSetup!='n'&&passwordSetup!='N'&&passwordSetup!='y'&&passwordSetup!='Y'){
		cin >> passwordSetup;
		if(passwordSetup!='n'&&passwordSetup!='N'&&passwordSetup!='y'&&passwordSetup!='Y'){
			SetColor(12,0);
			cout<<"\r Invalid choice.                ";
			Sleep(420);
			cout<<"\r                                  ";
			SetColor(15,0);
			cout<<"\r"<<userName<<"> ";
			ResetColor();
		}	
	}
	string password;
	char getch_buffer;
    if (passwordSetup == 'n' || passwordSetup == 'N') {
        SetColor(15, 1);  
        cout << "It is recommended to set up a password for additional security. You may always add one in the System's settings." << endl;
        save_user("users.txt",userName,"NULL","Y");
    }else if(passwordSetup == 'y' || passwordSetup == 'Y'){
    	SetColor(15,0);
    	cout<<"\nType your new password for user "<<userName<<": ";
    	ResetColor();
		int loop=0;
		while(1){
				getch_buffer=getch();
				if(getch_buffer=='\r'){
					break;
				}else if(getch_buffer=='\b'){
					if(password.size()>0){
					cout<<'\b';
					cout<<" ";
					cout<<'\b';
					password.pop_back();					
					}
				}else{
					cout<<"*";
					password+=getch_buffer;
				}
			}
		//password[loop]='\0';
		save_user("users.txt",userName,password,"Y");
	}
	createSettingsDB(userName);
    SetColor(14, 0);  // Yellow text
    cout << "\nAll done!\nEnjoy your ArchOS experience.\n" << endl;
    ResetColor();
}

void statusbar(const string& status, const string& username = "User") {		//NEEDS UPDATE!!!
	globSTATUS=status;
	globUSER=username;
	SYSTEMTIME localTime;
	GetLocalTime(&localTime);
    
	if (status == "startup") {
    	SetColor(15,0);
    	cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| Starting...\n"<<endl;
    }
    else if(status=="settings"){
    	SetColor(15,0);
    	cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| System Preferences\n"<<endl;
	}
    else if(status=="newuser"){
    	SetColor(15,0);
    	cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| Add User Account\n"<<endl;
	}
    else if (status == "setup") {
        SetColor(15,0);
    	cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
		SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| Setup\n"<<endl;
    }
    else if (status == "sysupdate") {
    	SetColor(15,0);
    	cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| System Update\n"<<endl;
	}
    else if (status == "mainmenu") {
    	SetColor(15,0);
		cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| Welcome, " << username << "\n" << endl;
    }
    else if (status == "apps") {
    	SetColor(15,0);
    	cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| This PC/" << username << "/Programs\n" << endl;
    }
    else if (status == "installUSB") {
    	SetColor(15,0);
    	cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Yellow text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| File Transfer (USB)\n" << endl;
    }
    else {
    	SetColor(15,0);
		cout<<setfill('0')<<setw(2)<<localTime.wHour<<":"<<setfill('0')<<setw(2)<<localTime.wMinute<<" | ";
        SetColor(14, 0);  // Red text
        cout << OS_VER;
        SetColor(15,0);
        cout<<"| ";
    	SetColor(9,0);
    	cout<<"Running "<<status<<endl;
	}
    ResetColor();
}

void appsfolder(const string& username = "User") {
	string runProgram;
	
	while(runProgram!="!back"){
	    system("cls");
	    statusbar("apps", username);
	    SetColor(10, 0);  // Green text
	    cout << "Programs list:\n" << endl;
	    WIN32_FIND_DATA findFileData;
	    HANDLE hFind = FindFirstFile("apps\\*", &findFileData);  // opens directory
	    if (hFind == INVALID_HANDLE_VALUE) {
	    	SetColor(12,0);
	        cerr << "Error opening directory" << endl;
	        ResetColor();
	        return;
	    }
	
	    do {
	        string name = findFileData.cFileName;
	        if (name != "." && name != "..") {
	            SetColor(11, 0);  // Light Blue text
	            cout << name << endl;
	        }
	    } while (FindNextFile(hFind, &findFileData));  // reads directory and prints
	
	    FindClose(hFind);  // closes directory
	    ResetColor();
	    cout<<"\nType !back to go back to the main menu.\n/Programs/RUN: ";
	    cin>>runProgram;
	    if(runProgram=="!back")
	    	break;
	    string programCMD="apps\\"+runProgram;
	    statusbar(runProgram,username);
		system(programCMD.c_str());
	    int returnCode = system(programCMD.c_str());
	    if(returnCode!=0){
	    	SetColor(12,0);
	    	cout<<"Program not found."<<endl;
	    	ResetColor();
	    	system("pause");	
		}
	}
}

void settings(const string&username){
	//bool mainmenubool=true;
	//bool usermenubool=true;
	//bool elsematched=false;
	string settingsmenuchoice,usermenuchoice;
	while(settingsmenuchoice!="!back"){
		system("cls");
		statusbar("settings",username);
		//cout<<elsematched<<endl;
		SetColor(10,0);
		cout<<"\nSYSTEM PREFERENCES\n"<<endl;
		SetColor(15,0);
		cout<<"\nI. About PC\n\n1. User settings\n2. System Update"<<endl;
		ResetColor();
		cout<<"\nType '!back' to go back to the main menu.\n"<<endl;
		cout<<username<<"> ";
		cin>>settingsmenuchoice;
		if(settingsmenuchoice=="1"&&globIsUserAdmin=="Y"){
			//elsematched=true;
			while(usermenuchoice!="!back"){
				system("cls");
				SetColor(10,0);
				statusbar("USER SETTINGS\n");
				SetColor(15,0);
				cout<<"\n1. Add User Account\n2. Edit User Account\n3. Delete User Account"<<endl;
				ResetColor();
				cout<<"\nType '!back' to go back to the main menu.\n"<<endl;
				cout<<username<<"> ";
				cin>>usermenuchoice;
				if(usermenuchoice=="1"){
					statusbar("newuser");
					addUser(username);
				}else if(usermenuchoice=="!back"){
					//usermenubool=false;
					break;
				}else if(usermenuchoice=="2"){
					cout<<"\nWork In Progress...";
					system("pause");
				}else if(usermenuchoice=="3"){
					cout<<"\nWork In Progress...";
					system("pause");
				}else{
					SetColor(12,0);
					cout<<"Invalid choice."<<endl;
					ResetColor();
					system("pause");
				}
			}
		}else if(settingsmenuchoice=="!back"){
			//mainmenubool=false;
			//elsematched=true;
			mainmenu(username);
		}else if(settingsmenuchoice=="1"&&globIsUserAdmin=="N"){
			//elsematched=true;
			SetColor(12,0);
			cout<<"Your User Account does not have permission to execute this action."<<endl;
			ResetColor();
			system("pause");
		}else if(settingsmenuchoice=="2"&&globIsUserAdmin=="Y"){
			//elsematched=true;
			system("cls");
			statusbar("sysupdate");
			sysupdated=true;
			system("system.updater.exe");
			exit(0);
		}else if(settingsmenuchoice=="2"&&globIsUserAdmin=="N"){
			//elsematched=true;
			SetColor(12,0);
			cout<<"Your User Account does not have permission to execute this action."<<endl;
			ResetColor();
			system("pause");
		}else if(settingsmenuchoice=="I"||settingsmenuchoice=="i"){
			system("cls");
			statusbar("aboutpc");
			cout<<endl;
			cout<<"System Info:"<<endl;
			cout<<endl<<"ArchOS version: "<<OS_VER<<endl;
			cout<<"User: "<<username;
			if(globIsUserAdmin=="Y"){
				SetColor(9,0);
				cout<<" [Administrator]"<<endl;
				ResetColor();
			}
			else{
				cout<<endl;
			}
			cout<<"Installed programs: WIP"<<endl;
			cout<<"Installed programs: WIP"<<endl;
			cout<<"Installed programs: WIP"<<endl;
			cout<<endl<<endl;
			getch();
		}else{
			SetColor(12,0);
			cout<<"Invalid choice."<<endl;
			ResetColor();
			system("pause");
		}
	}
	//cout<<elsematched<<endl;
}

std::vector<CHAR_INFO> copiedBuffer;

void CopyConsoleBuffer(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        crashScreen("BUFFERCOPY", "CANNOT_COPY_SCR");
        return;
    }

    // Get current console screen buffer information
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        DWORD dwError = GetLastError();
        crashScreen("BUFFERCOPY", "BUFFER_INFO_UNAVAIL, Code: " + std::to_string(dwError));
        return;
    }

    // Get the actual console screen size (width and height)
    SHORT consoleWidth = csbi.dwSize.X; // Width (columns)
    SHORT consoleHeight = csbi.dwSize.Y; // Height (rows)

    // Resize the copiedBuffer to fit the entire console screen size
    DWORD bufferSizeTotal = consoleWidth * consoleHeight;
    copiedBuffer.resize(bufferSizeTotal, CHAR_INFO{});

    // Set the starting point for reading the console screen output
    COORD bufferCoord = { 0, 0 };

    // Process the console in chunks of 15 lines
    const SHORT linesPerRead = 15;
    SHORT startY = 0;
    
    while (startY < consoleHeight) {
        SHORT endY = startY + linesPerRead - 1;
        if (endY >= consoleHeight) {
            endY = consoleHeight - 1;  // Ensure we don't exceed console height
        }

        // Define the region to read (startY to endY)
        SMALL_RECT readRegion;
        readRegion.Left = 0;
        readRegion.Top = startY;
        readRegion.Right = consoleWidth - 1;  // Right bound (0-indexed)
        readRegion.Bottom = endY; // Bottom bound (0-indexed)

        // Read the portion of the console screen buffer
        if (!ReadConsoleOutput(hConsole, copiedBuffer.data() + (startY * consoleWidth), { consoleWidth, static_cast<SHORT>(endY - startY + 1) }, bufferCoord, &readRegion)) {
            DWORD dwError = GetLastError();
            crashScreen("BUFFERCOPY", "BUFFER_READ_ERROR, Code: " + std::to_string(dwError));
            return;
        }

        // Move to the next set of lines (15 lines ahead)
        startY += linesPerRead;
    }
}

// Function to paste (reprint) the copied buffer content back to the console
void PasteConsoleBuffer(void) {
    system("cls");
    
    if (copiedBuffer.empty()) {
        crashScreen("BUFFERPASTE", "COPY_FAILED");
        return;
    }

    // Get handle to the active console screen buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        crashScreen("BUFFERCOPY", "SCR_HANDLE_UNAVAIL");
        return;
    }

    // Get console screen buffer information to determine the position to paste the content
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        crashScreen("BUFFERCOPY", "BUFFER_INFO_UNAVAIL");
        return;
    }

    // Get the actual console screen size (width and height)
    SHORT consoleWidth = csbi.dwSize.X; // Width (columns)
    SHORT consoleHeight = csbi.dwSize.Y; // Height (rows)

    // Split the buffer into chunks, like we did in CopyConsoleBuffer
    const SHORT linesPerWrite = 15;  // Number of lines to write in each chunk (for example, 15)
    SHORT startY = 0;

    // Iterate through the buffer and paste it in chunks of lines
    while (startY < consoleHeight) {
        SHORT endY = startY + linesPerWrite - 1;
        if (endY >= consoleHeight) {
            endY = consoleHeight - 1;  // Ensure we don't exceed console height
        }

        // Define the region to write (startY to endY)
        SMALL_RECT writeRegion;
        writeRegion.Left = 0;
        writeRegion.Top = startY;
        writeRegion.Right = consoleWidth - 1;  // Right bound (0-indexed)
        writeRegion.Bottom = endY; // Bottom bound (0-indexed)

        // Set the starting point for writing the console screen output
        COORD bufferCoord = { 0, 0 };

        // Write the portion of the console screen buffer
        if (!WriteConsoleOutput(hConsole, copiedBuffer.data() + (startY * consoleWidth), { consoleWidth, static_cast<SHORT>(endY - startY + 1) }, bufferCoord, &writeRegion)) {
            DWORD dwError = GetLastError();
            crashScreen("BUFFERCOPY", "PASTE_FAILED, Error Code: " + std::to_string(dwError));
            return;
        }

        // Move to the next set of lines (15 lines ahead)
        startY += linesPerWrite;
    }

    // std::cout << "Console content pasted!" << std::endl;
}

DWORD WINAPI reminerAppActive(LPVOID lpParam){
	const char riga1[]="+-------REMINDER-------+";
	const char riga2[]="|                      |";
	const char riga3[]="|                      |";
	const char riga4[]="+----------------------+";
	const char riga5[]="--Press any key to dismiss--";
	short originalX,originalY;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
	    SHORT originalX = csbi.dwCursorPosition.X;
	    SHORT originalY = csbi.dwCursorPosition.Y;
	} else {
	    crashScreen("ACTIVEREMINDER","CONSOLE_INFO_UNAVAIL");
	}
	SYSTEMTIME localTime;
	GetLocalTime(&localTime);
	while(globReminderHours!=globTIMEH||globReminderMins!=globTIMEM){
		COORD coord;
		coord.X=originalX;
		coord.Y=originalY;
		//globTIMES=localTime.wSecond;
		Sleep(2000);
	}
	CopyConsoleBuffer();
	COORD coord;
	coord.X = (globCentroX-(strlen(riga1)/2));    // X position
	coord.Y = globCentroY-3;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga1[loop]!='\0';loop++){
		if(riga1[loop]=='+'||riga1[loop]=='-'||riga1[loop]=='|'){
			SetColor(15,0);
			cout<<riga1[loop];
		}else{
			SetColor(14,0);
			cout<<riga1[loop];
		}
	}
	coord.X = (globCentroX-(strlen(riga2)/2));    // X position
	coord.Y = globCentroY-2;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga2[loop]!='\0';loop++){
		if(riga2[loop]=='+'||riga2[loop]=='-'||riga2[loop]=='|'){
			SetColor(15,0);
			cout<<riga2[loop];
		}else{
			SetColor(14,0);
			cout<<riga2[loop];
		}
	}
	coord.X = (globCentroX-(strlen(riga3)/2));    // X position
	coord.Y = globCentroY-1;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga3[loop]!='\0';loop++){
		if(riga3[loop]=='+'||riga3[loop]=='-'||riga3[loop]=='|'){
			SetColor(15,0);
			cout<<riga3[loop];
		}else{
			SetColor(14,0);
			cout<<riga3[loop];
		}
	}
	coord.X = (globCentroX-(strlen(riga4)/2));    // X position
	coord.Y = globCentroY;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga4[loop]!='\0';loop++){
		if(riga4[loop]=='+'||riga4[loop]=='-'||riga4[loop]=='|'){
			SetColor(15,0);
			cout<<riga4[loop];
		}else{
			SetColor(14,0);
			cout<<riga4[loop];
		}
	}
	coord.X = (globCentroX-(strlen(riga5)/2));    // X position
	coord.Y = globCentroY+2;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga5[loop]!='\0';loop++){
		SetColor(15,0);
		cout<<riga5[loop];
	}
	coord.X = (globCentroX-(strlen(globReminderText)/2));    // X position
	coord.Y = globCentroY-2;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;globReminderText[loop]!='\0';loop++){
		SetColor(15,0);
		cout<<globReminderText[loop];
	}
	while(true){
		int getch_buffer=getch();
		if(getch_buffer=='\r'){
			break;
		}
	}
	PasteConsoleBuffer();
	coord.X = globUSERCOORDX;    // X position
	coord.Y = globUSERCOORDY;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return 0;
}

void reminderApp(const string& username){
	HANDLE hThread;
    DWORD threadId;
	short hour1, hour2, min1, min2;
	char getch_buffer;
	short action;
	while(true){
		system("cls");
		statusbar("reminder",globUSER);
		SetColor(14,0);
		cout<<endl<<"a";
		SetColor(12,0);
		cout<<"REMINDER";
		SetColor(15,0);
		cout<<"        Version 1.15"<<endl<<endl;
		cout<<"1. Set Reminder"<<endl<<endl<<"0. Quit"<<endl<<endl<<globUSER<<"> ";
		ResetColor();
		cin>>action;
		switch(action){
			case 1:
				SetColor(15,0);
				cout<<endl<<"Set Reminder time (HH-MM)"<<endl;
				SetColor(0,15);
				cout<<"  ";
				SetColor(15,0);
				cout<<":";
				SetColor(0,15);
				cout<<"  ";
				cout<<"\b\b\b\b\b";
			while (true) {
        getch_buffer = getch();
        if (getch_buffer >= '0' && getch_buffer <= '2') {
            cout << getch_buffer;
            hour1 = getch_buffer - '0';
            hour1=hour1*10;
            break;
        } else {
            NULL;
        }
    }

    while (true) {
        getch_buffer = getch();
        if (getch_buffer >= '0' && getch_buffer <= '9') {
            cout << getch_buffer;
            hour2 = getch_buffer - '0';
            break;
        } else {
            NULL;
        }
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD coord;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    coord.X = csbi.dwCursorPosition.X + 1;
    coord.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    while (true) {
        getch_buffer = getch();
        if (getch_buffer >= '0' && getch_buffer <= '5') {
            cout << getch_buffer;
            min1 = getch_buffer - '0';
            min1=min1*10;
            break;
        } else {
            NULL;
        }
    }

    while (true) {
        getch_buffer = getch();
        if (getch_buffer >= '0' && getch_buffer <= '9') {
            cout << getch_buffer;
            min2 = getch_buffer - '0';
            break;
        } else {
            NULL;
        }
    }
				globReminderHours=hour1+hour2;
				globReminderMins=min1+min2;
				SetColor(15,0);
				cout<<endl<<"Set Reminder Text: ";
				char reminderText[20];
				ResetColor();
				cin>>reminderText;
				for(int loop=0; loop<20; loop++){
					globReminderText[loop]=reminderText[loop];
				}
				SetColor(14,0);
				
				hThread = CreateThread(
		        NULL,                     // Default security attributes
		        0,                        // Default stack size
		        reminerAppActive,         // Thread function
		        NULL,                 // Parameter to pass to the thread function
		        0,                        // Default creation flags
		        NULL                      // Thread ID (not used)
		    );
		    
				cout<<endl<<endl<<"Reminder set! You will recive a notification at "<<globReminderHours<<":"<<globReminderMins<<endl;
				ResetColor();
				system("pause");
				break;
			case 0:
				return;
			default:
				SetColor(12,0);
				cout<<"Invalid choice."<<endl;
		}
	}
}

void sysprograms(const string& username){
	int runcode;
	while(true){
		system("cls");
		statusbar("sysprog",username);
		cout<<endl;
		SetColor(12,0);
		cout<<"SYSTEM APPS"<<endl;
		SetColor(9,0);
		cout<<endl<<"1. aReminder [APP]"<<endl<<endl;
		ResetColor();
		cout<<username<<"> ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin>>runcode;
		switch(runcode){
			case 1:
				reminderApp(username);
				return;
			case 0:
				return;
			default:
				SetColor(14,0);
				cout<<"Invalid choice"<<endl;
				system("pause");
		}
	}
}

void shutdown(int xcentro,int ycentro);

void mainmenu(const string& username) {
    char menuchoice;
    bool menubool = true;
    globUSER=username;
    while (menubool) {
        system("cls");
        statusbar("mainmenu", username);
        SetColor(15, 0);  // White text
        cout << "\n1. Installed Programs [Folder]\n2. File Transfer\n3. System Programs\n\nP. Preferences" << endl;
        SetColor(14, 0);  // Yellow text
        cout << "L. Log Out" << endl;
        SetColor(12,0);
		cout<<"Q. Shut Down\n"<<endl;
		ResetColor();
        cout << "\n" << username << "> ";
        cin >> menuchoice;

        switch (menuchoice) {
        case '1':  // 1
            appsfolder(username);
            break;
        case 'Q':  // sS
        case 'q':
            shutdown(globCentroX,globCentroY);
            break;
        case 'L':  // lL
        case 'l':
            main(); // Recursively call main function to reset system
            break;
        case '2':
            system("cls");
            statusbar("installUSB");
            system("filetransfer.exe");  // Assuming you have a filetransfer.exe to run
            break;
        case '3':
        	sysprograms(username);
            break;
        case 'P':
        case 'p':
        	system("cls");
        	//statusbar("sysupdate");
        	//system("system.updater.exe");
        	//statusbar("settings",username);
			settings(username);
	
			//exit(0);
        default:
            SetColor(12, 0);  // Red text
            cout << "Invalid choice" << endl;
            ResetColor();
            fflush(stdin);
            system("pause");
        }
    }
}

DWORD WINAPI screensaverTimer(LPVOID lpParam) {
    short originalX, originalY;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (true) {
		start:
        // Calculate elapsed time since the last key press
        for (int key = 0; key <= 0xFF; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) { // Check if key is pressed
                lastKeyPressTime = steady_clock::now();
            }
    	}
        auto elapsedTime = duration_cast<seconds>(steady_clock::now() - lastKeyPressTime).count();

        if (elapsedTime > globScreensaverTime&&globScreensaverEnabled) {
            if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
                originalX = csbi.dwCursorPosition.X;
                originalY = csbi.dwCursorPosition.Y;
            } else {
                crashScreen("SCREENSAVERTIMER", "CONSOLE_INFO_UNAVAIL");
                return 0;
            }

            CopyConsoleBuffer();

            // Screensaver process creation
            STARTUPINFO si = { sizeof(si) };
            PROCESS_INFORMATION pi;
            if (CreateProcess(
                NULL,                           // Application name
                (LPSTR)"screensaver_stars.exe",  // Command line
                NULL,                           // Process security attributes
                NULL,                           // Thread security attributes
                FALSE,                          // Inherit handles
                0,                              // Creation flags
                NULL,                           // Environment
                NULL,                           // Current directory
                &si,                            // Startup info
                &pi                             // Process information
            )) {

                bool screensaverDismissed = false;
                while (!screensaverDismissed) {
                    // Check for key press using GetAsyncKeyState
                    for (int key = 0; key <= 0xFF; ++key) {
                        if (GetAsyncKeyState(key) & 0x8000) { // Check if key is pressed
                        	//_getch();
                            lastKeyPressTime = steady_clock::now();

                            // Attempt to terminate the screensaver process
                            BOOL result = TerminateProcess(pi.hProcess, 0);  // Stop the screensaver
                            
                            if (!result) {
                                DWORD dwError = GetLastError();
                                SetColor(12,0);
                                std::cerr << "TerminateProcess failed with error code: " << dwError << std::endl;
                            } else {
                                SetColor(12, 0);
                                std::cout << "Screensaver process terminated successfully." << std::endl;
                            }

                            CloseHandle(pi.hProcess);
                            CloseHandle(pi.hThread);

                            ResetColor();
                            system("cls");
                            PasteConsoleBuffer();

                            // Reset cursor position to original
                            COORD coord = { originalX, originalY };
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                            // Flush cin buffer to avoid leftover input
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            screensaverDismissed = true;  // Exit loop after key press
                            goto start;
                        }
                    }

                    // Add a small delay to prevent high CPU usage
                    this_thread::sleep_for(milliseconds(1));
                }
            }
            lastKeyPressTime = steady_clock::now();
        }

        // Add a small delay to check the elapsed time periodically
        this_thread::sleep_for(milliseconds(1));
    }
}

void debugscrsize(void){
	system("cls");
	cout<<"123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"<<endl;
	cout<<"2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0";
	Sleep(12000);
}

void shutdown(int xcentro,int ycentro){
	const char riga1[]="+------SHUTDOWN------+";
	const char riga2[]="|  Switching Off...  |";
	const char riga3[]="+--------------------+";
	
	COORD coord;    // Coordinate structure
	coord.X = (xcentro-(strlen(riga1)/2));    // X position
	coord.Y = ycentro-1;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga1[loop]!='\0';loop++){
		if(riga1[loop]=='+'||riga1[loop]=='|'||riga1[loop]=='-'){
			SetColor(15,0);
			cout<<riga1[loop];
		}
		else{
			SetColor(12,0);
			cout<<riga1[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga2)/2));    // X position
	coord.Y = ycentro;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga2[loop]!='\0';loop++){
		if(riga2[loop]=='+'||riga2[loop]=='|'){
			SetColor(15,0);
			cout<<riga2[loop];
		}
		else{
			SetColor(15,0);
			cout<<riga2[loop];
		}
	}
	coord.X = (xcentro-(strlen(riga3)/2));    // X position
	coord.Y = ycentro+1;    // Y position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for(int loop=0;riga3[loop]!='\0';loop++){
		if(riga3[loop]=='+'||riga3[loop]=='|'||riga3[loop]=='-'){
			SetColor(15,0);
			cout<<riga3[loop];
		}
		else{
			SetColor(12,0);
			cout<<riga3[loop];
		}
	}
	Sleep(2000);
	system("cls");
	Sleep(500);
	exit (0);
}

int main(void) {
	SetConsoleOutputCP(437);
	system("cls");
	system("color 0f");
	if(globHasBooted==false){
		getCenter();
		bootupIMG(globCentroX,globCentroY);
	    Sleep(3000);
		system("cls");
		globHasBooted=true;
	}
	
    string firstStart;
    string username;
    string password;
    statusbar("startup");
    ifstream inFile("firststart.txt");
    if (inFile) {
        system("cls");
        statusbar("setup");
        newSystem();
        inFile.close();
		system("pause");
        system("del firststart.txt");
    	system("cls");
    	statusbar("startup");
	}
	cout<<"   "<<endl;
	ResetColor();
	ifstream inFile2("users.txt");
	if(!inFile2){
		crashScreen("STARTUP_PROCESS","USER_DB_FILE_UNAVAIL");
	}
    cout << "Username: ";
    int loop=0;
    HANDLE hThread = CreateThread(
        NULL,                     // Default security attributes
        0,                        // Default stack size
        clock,         // Thread function
        NULL,                 // Parameter to pass to the thread function
        0,                        // Default creation flags
        NULL                      // Thread ID (not used)
    );
    cin >> username;
    switch(user_exists("users.txt",username)){
    	case 0:
    		SetColor(12,0);
			cerr<<"User does not exist."<<endl;
			ResetColor();
			system("pause");
			main();
			break;
		case 1:
			cout<<"Password: ";
    		loop=0;
    		char getch_buffer;
			while(1){
				getch_buffer=getch();
				if(getch_buffer=='\r'){
					break;
				}else if(getch_buffer=='\b'){
					if(password.size()>0){
					cout<<'\b';
					cout<<" ";
					cout<<'\b';
					password.pop_back();					
					}
				}else{
					cout<<"*";
					password+=getch_buffer;
				}
			}
    		if(validate_password("users.txt",username,password)==true){
    			break;
			}else{
				SetColor(12,0);
				cerr<<"Password incorrect."<<endl;
				ResetColor();
				system("pause");
				main();
				break;
			}
			break;
		default:
			SetColor(14,0);
			cout<<"WARNING: Your account is not protected by a password! You can set one up in the system's settings."<<endl;
			ResetColor();
	}
	//cout<<"\n"<<user_exists("users.txt",username)<<endl;
	cout<<endl;
	SetColor(15,0);
    cout << "Welcome, " << username << "!" << endl;
    ResetColor();
    system("pause");
    system("del old.system.main.exe");
    loadSettings(username);
    
    hThread = CreateThread(
        NULL,                     // Default security attributes
        0,                        // Default stack size
        screensaverTimer,         // Thread function
        NULL,                 // Parameter to pass to the thread function
        0,                        // Default creation flags
        NULL                      // Thread ID (not used)
    );
 
 	if(globIsUserAdmin=="y"){
		globIsUserAdmin="Y";
	}
	if(globIsUserAdmin=="n"){
		globIsUserAdmin="N";
	}
    mainmenu(username);
    //debugscrsize();
    return 0;
}
 
