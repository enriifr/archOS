#include <iostream>
#include <string>
#include <windows.h>
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

// Function to check if the USB drive exists
bool is_usb_present(const string& usb_path) {
    DWORD ftyp = GetFileAttributes(usb_path.c_str());
    return (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY));
}

// Function to check if the file is a system or hidden file
bool is_system_or_hidden(const string& file_path) {
    DWORD file_attributes = GetFileAttributes(file_path.c_str());
    if (file_attributes == INVALID_FILE_ATTRIBUTES) {
        return true; // Invalid file attributes (not accessible)
    }
    return (file_attributes & FILE_ATTRIBUTE_SYSTEM) || (file_attributes & FILE_ATTRIBUTE_HIDDEN);
}

// Function to check if the file has a .exe extension
bool is_exe_file(const string& file_name) {
    size_t pos = file_name.rfind(".exe");
    return (pos != string::npos && pos == file_name.length() - 4);
}

// Function to move files from source to destination
void move_file(const string& source, const string& destination) {
    if (rename(source.c_str(), destination.c_str()) != 0) {
        SetColor(12, 0);  // Red text
        cerr << "Error moving file from " << source << " to " << "Applications Folder" << endl;
        ResetColor();
    } else {
        SetColor(10, 0);  // Green text
        cout << "Moved: " << source << " -> " << "Applications Folder" << endl;
        ResetColor();
        fileismoved = true;
    }
}

// Function to move files from USB to destination folder
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

            // Only move .exe files
            if (is_exe_file(file_name)) {
                // Move the file to the destination folder
                move_file(source_path, destination_path);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main() {
    // Path to your USB drive and destination folder (replace these with your actual paths)
    string usb_path = "D:\\";  // Example: "E:\" (update this to your USB path or letter)
    string destination_folder = "apps"; // Destination folder

    SetColor(10, 0);  // Green text
    cout << "Waiting for USB stick to be inserted..." << endl;
    ResetColor();

    // Continuously check for USB drive
    while (true) {
        // Check if the USB is present
        if (is_usb_present(usb_path)) {
            SetColor(10, 0);  // Green text
            cout << "USB stick detected at: " << usb_path << endl;
            ResetColor();
            Sleep(300);

            // Move .exe files from USB to destination folder
            move_files(usb_path, destination_folder);
            break;  // Exit loop after moving files
        }

        // Wait for a short time before checking again
        Sleep(2000);
    }

    if (fileismoved == false) {
        SetColor(14, 0);  // Yellow text
        cout << "No applications found!";
        Sleep(700);
        cout << "\r                      ";
        Sleep(700);
        cout << "\rNo applications found!";
        Sleep(700);
        cout << "\r                      ";
        Sleep(700);
        cout << "\rNo applications found!" << endl;
        ResetColor();
    }

    system("pause");
    return 0;
}

