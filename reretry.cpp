#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <algorithm>

using namespace std;

int pid = 1;

struct Command
{
    string name;
    string args;
    int repeat = 1;        // -n
    int duration = -1;     // -d, 기본값 -1은 제한 없음
    int period = 0;        // -p, 기본값 0은 반복 없음
    int multithread = 1;

    Command() {}
};
vector<string> deleteSpace(string cmd) {
    vector<string> token;
    string temp = cmd;

    temp.erase(temp.begin(), find_if(temp.begin(), temp.end(), [](unsigned char ch) {
        return !isspace(ch);
        }));
    temp.erase(find_if(temp.rbegin(), temp.rend(), [](unsigned char ch) {
        return !isspace(ch);
        }).base(), temp.end());

    token.push_back(temp);
    return token;
}
void parse(string command) {
    stringstream ssr(command);
    string cmd;
    while (getline(ssr, cmd, ';')) {
        deleteSpace(cmd);
    }
}



int main() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    string currentDirectory = string(buffer).substr(0, pos);
    //cout << "Current working directory: " << currentDirectory << endl;

    ifstream commands(currentDirectory + "\\commands.txt");
    string command;

    vector<string> cmd;




    if (!commands.is_open()) {
        cout << "File not found" << endl;
        return 1;
    }
    else {
        while (getline(commands, command)) {
            //cout << command << endl;

            //cmd = parse(command);
            //exec(cmd);
        }
        cout << endl;
    }

    commands.close();
}