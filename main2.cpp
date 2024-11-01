#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>


int main(){
    std::string input , line;
    int a=4;
    float b=0.5;
    char c='r';
    bool e=false;
    std::fstream file("variables.txt", std::ios::in | std::ios::out);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    DWORD processID = GetCurrentProcessId();
    std::cout << "Process ID: " << processID << std::endl;
    while(!e){
        file<<processID<<"\n";
        file<<"int : "<< a << " : "<< &a <<"\n";
        file<<"float : "<< b << " : "<< &b <<"\n";
        file<<"char : "<< c << " : "<< (void*)&c <<"\n";
        // file.seekg(0);
        // while (std::getline(file, line)) {
        //     std::cout << line << std::endl;
        // }
        // file.seekg(0);
        std::cout<<"int a : "<< a << " adress : "<< &a <<"\n";
        std::cout<<"float b : "<< b << " adress : "<< &b <<"\n";
        std::cout<<"char c : "<< c << " adress : "<< (void*)&c <<"\n";
        std::cin >> input;
        if(input == "Q" || input == "q") break;
    }
    return 0;
}