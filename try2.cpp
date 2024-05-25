#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>

using namespace std;

void shell(string command){
    string buffer;
    istringstream c1(command);
    while(getline(c1,buffer,' ')){
        cout << buffer << endl;

    }
    if (buffer == "echo"){
        system(buffer.c_str());
    }
    

}



int main() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    string currentDirectory = string(buffer).substr(0, pos);
    cout << "Current working directory: " << currentDirectory << endl;

    // 현재 작업 디렉토리에 있는 commands.txt 파일 열기
    ifstream commands(currentDirectory + "\\commands.txt");
    string command;
    
    if(!commands.is_open()){
        cout << "File not found" << endl;
        return 0;// 파일이 열리지 않는 경우 프로그램 종료
    }
    else {
        while(getline(commands, command)){
            //cout << command << endl;
            system(command.c_str());
        }
        cout << endl;
    }
    commands.close();  // 파일을 닫음
    return 0;
}
