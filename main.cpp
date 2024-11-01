#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <windows.h>

void removeSpaces(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

int main(){
    const char delimiter = ':';
    std::string line, type, value, adress;
    std::fstream file("variables.txt", std::ios::in);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    std::getline(file, line);
    // DWORD targetID = std::stoul(line);
    while (std::getline(file, line)) {
            // std::cout << line << std::endl;
            removeSpaces(line);
            std::istringstream stream(line);
            std::getline(stream, type, delimiter);
            std::getline(stream, value, delimiter);
            std::getline(stream, adress, delimiter);
            std::cout << type << " : " << value << " : " << adress << "\n";
        }
    return 0;
}