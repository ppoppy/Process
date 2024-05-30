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

int pid=1;

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
int gcd(int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int prime(int x) {
    vector<bool> isPrime(x + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= x; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= x; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return count(isPrime.begin(), isPrime.end(), true);
}

int sum(int x) {
    return (x * (x + 1) / 2) % 1000000;
}
void exec(vector<string> cmd){
    for (const auto& c : cmd){
        stringstream ssr(c);
        string tmp;
        vector<string> token;

        while( ssr >> tmp){
            token.push_back(tmp);
        }
        if (token[0] == "echo" || token[0] == "&echo"){
            cout << token[1] << endl;
        }
        else if (token[0] == "dummy" || token[0] == "&dummy"){
            //아무일도 하지 않는 프로세스 생성
        }
        else if (token[0] == "gcd" || token[0] == "&gcd"){
            int x = stoi(token[1]);
            int y = stoi(token[2]);
            cout << gcd(x, y) << endl;
        }
        else if (token[0] == "prime" || token[0] == "&prime"){
            int x = stoi(token[1]);
            cout << prime(x) << endl;
        }
        else if (token[0] == "sum" || token[0] == "&sum"){
            int x = stoi(token[1]);
            cout << sum(x) << endl;
        }
        else{
            cout << "command is fail" << endl;
        }
    }
    

}

void shell(){

}

void monitor(){
    cout << "Running: " << "[" << pid << "]" << endl;
    cout << "--------------------------------" << endl;
    cout << "DQ: " << endl;
    cout << "--------------------------------" << endl;
    cout << "WQ: " << endl;
}



int main (){
    monitor(); 
     
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
            
            cmd = parse(command);
            exec(cmd);
        }
        cout << endl;
    }

    commands.close();  // 파일을 닫음
    return 0;
}