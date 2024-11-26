#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <windows.h>

void removeSpaces(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

LPCVOID convertStringToLPCVOID(const std::string& addressStr) {
    uintptr_t address;
    std::stringstream ss;
    ss << std::hex << addressStr;
    ss >> address;
    return reinterpret_cast<LPCVOID>(address);
}

// struct variable{
//     std::string type;
//     std::string value;
//     std::string adress;
// };

int main(){
    const char delimiter = ':';
    char buffer;
    std::string line, type, value, adress;
    std::fstream file("variables.txt", std::ios::in);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    std::getline(file, line);
    DWORD targetID = std::stoul(line);
    HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, targetID);
    if (process == NULL) {
        std::cerr << "Failed to open process." << std::endl;
        file.close();
        return 1;
    }
    while (std::getline(file, line)) {
            // std::cout << line << std::endl;
            removeSpaces(line);
            if(line != ""){
                std::istringstream stream(line);
                std::getline(stream, type, delimiter);
                std::getline(stream, value, delimiter);
                std::getline(stream, adress, delimiter);
                std::cout << type << " : " << value << " : " << adress << "\n";
            }
        }
    SIZE_T bytesRead;
    // LPCVOID targetAddress = (LPCVOID)stoul(adress);
    if (ReadProcessMemory(process, convertStringToLPCVOID(adress), &buffer, sizeof(buffer), &bytesRead)) {
        std::cout << "Value read from memory: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to read memory." << std::endl;
    }
    file.close();
    CloseHandle(process);
    return 0;
}