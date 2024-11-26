#include <iostream>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

bool fileismoved = false;


// Set console text color
void SetColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Reset to default console color
void ResetColor() {
    SetColor(7, 0); // Light Gray on Black
}

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
            return "Error: File is empty or could not read the first line.";
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
        cerr << "Error installing the new system image." << endl;
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
        cerr << "Error opening USB directory." << endl;
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
        cerr << "Failed to get current directory. Error: " << GetLastError() << endl;
        ResetColor();
        return "";
    }
    return string(buffer);
}

// Main function for moving files
int main_filemover() {
    string currentDir = getCurrentDirectory();
    // Path to your USB drive and destination folder (replace these with your actual paths)
    string usb_path = "H:\\";  // Example: "E:\" (update this to your USB path or letter)
    string destination_folder = currentDir; // Destination folder

    SetColor(10, 0);  // Green text
    cout << "Waiting for USB stick to be inserted..." << endl;

    // Continuously check for USB drive
    while (true) {
        // Check if the USB is present
        if (is_usb_present(usb_path)) {
            SetColor(10, 0);  // Green text
            cout << "USB stick detected!\nSystem update in progress..." << endl;
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
        cout << "Something went wrong. Aborting System Update...";
        Sleep(700);
        cout << "\r                                                     ";
        Sleep(700);
        cout << "\rSomething went wrong. Aborting System Update...";
        Sleep(700);
        cout << "\r                                                     ";
        Sleep(700);
        cout << "\rSomething went wrong. Aborting System Update..." << endl;
        ResetColor();
        return 404;
    }

    system("pause");
    return 0;
}

int main() {
    string oldFileName = "SYSTEM.MAIN.exe"; // Replace with your file's current name
    string newFileName = "old.system.main.exe"; // Replace with the desired new name
    renameFile("changelog.txt", "changelog.OLD.txt");
    renameFile(oldFileName, newFileName);
    
    //main_filemover();

    switch (main_filemover()) {
        case 0:
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
            cout << "Unable to update system. Verify installation files in USB drive and try again." << endl;
            ResetColor();
            system("PAUSE");
            break;
    }

    exit(0);
}

