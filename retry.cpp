#include <iostream>
#include <thread>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
//#include <mutex>

using namespace std;

//공백제거
vector<string> deleteSpace(const string& cmd){
    vector<string> token;
    string temp = cmd;

    // 앞뒤 공백 제거
    temp.erase(temp.begin(), find_if(temp.begin(), temp.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    temp.erase(find_if(temp.rbegin(), temp.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), temp.end());

    token.push_back(temp);
    return token;

}

vector<string> parse (string command){
    stringstream ssr(command);  // string -> vector로 변환, 이제 ; 기준으로 나누기
    string cmd;
    vector<string> token;
    
    while (getline(ssr, cmd, ';')) {
        cout << "here " << cmd << endl;
        vector<string> cleanedCmd = deleteSpace(cmd);    
        token.insert(token.end(), cleanedCmd.begin(), cleanedCmd.end());
        
    }
    for (const auto& c : token) {
        cout << c << endl;
    }
    return token;
}

void exec(){

}

int main (){
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    string currentDirectory = string(buffer).substr(0, pos);
    //cout << "Current working directory: " << currentDirectory << endl;

    ifstream commands(currentDirectory + "\\commands.txt");
    string command;
    
    vector<string> cmd;
    

    

    if(!commands.is_open()){
        cout << "File not found" << endl;
        return 1; 
    }
    else {
        while(getline(commands, command)){
            //cout << command << endl;
            
            parse(command);
        }
        cout << endl;
    }

    commands.close();  // 파일을 닫음
    return 0;
}