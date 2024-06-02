#include <thread>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <chrono>
//#include <cctype>

using namespace std;

int pid = 1;



struct Command {
    string command;
    string args;
    int process = 1;        // -n
    int duration = -1;     // -d, 기본값 -1은 제한 없음
    int period = 0;        // -p, 기본값 0은 반복 없음
    int multithread = 1;

    Command() {};
};

list<Command> commands;


vector<string> deleteSpace(const string& cmd) {
    vector<string> token;
    string temp = cmd;

    temp.erase(temp.begin(), find_if(temp.begin(), temp.end(), [](unsigned char ch) {
        return !isspace(ch);
        }));
    temp.erase(find_if(temp.rbegin(), temp.rend(), [](unsigned char ch) {
        return !isspace(ch);
        }).base(), temp.end());

    token.push_back(temp);
    token.push_back("");

    return token;

}
//명령어 파싱
vector<string> parse(string command) {
    stringstream ssr(command);  // string -> vector로 변환, 이제 ; 기준으로 나누기
    string cmd;
    vector<string> token;

    while (getline(ssr, cmd, ';')) {
        //cout << "here " << cmd  << "end" << endl;
        vector<string> cleanedCmd = deleteSpace(cmd);
        token.insert(token.end(), cleanedCmd.begin(), cleanedCmd.end());
        //token.push_back("");
        //cout << "here " << cmd  << "end" << endl;
    }
    for (const auto& c : token) {
        cout << c << "endl" << endl;
    }
    return token;
}

void echo(string args, int process, int duration, int period) {
    pid++;
    auto start = chrono::steady_clock::now();  // 시작 시간 기록

    while (true) {
        auto current = chrono::steady_clock::now(); // 현재 시간 업데이트
        if (chrono::duration_cast<chrono::seconds>(current - start).count() >= 20) {
            break; // 총 실행 시간이 20초 이상이면 반복문 종료
        }
        cout << args << endl;
        this_thread.sleep_for(chrono::seconds(period));
    }
}

void dummy() {
    cout << "dummy" << endl;
}

int gcd(int x, int y, int process, int duration, int period) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int prime(int x, int process, int duration, int period) {
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

int sum(int x, int process, int duration, int period, int multithread) {
    return (x * (x + 1) / 2) % 1000000;
}


void exec(vector<string> command) {
    //vector<string> cmds;
    int process = 1;        // -n
    int duration = -1;     // -d, 기본값 -1은 제한 없음
    int period = 0;        // -p, 기본값 0은 반복 없음
    int multithread = 1;
    for (auto& c : command) {
        cout << "c: " << c << endl;
        if (c.front() == '&') {

        }
    }
    for (auto& c : command) {
        stringstream ssr(c);
        string tmp;
        string cmd;
        string args;
        int x;
        int y;
        if (c.front() != '&') {
            ssr >> cmd;
            if (cmd == "echo") {
                ssr >> args;
            }
            else if (cmd == "dummy") {

            }
            else if (cmd == "gcd") {
                ssr >> tmp;
                x = stoi(tmp);
                ssr >> tmp;
                y = stoi(tmp);
            }
            else if (cmd == "prime") {
                ssr >> tmp;
                x = stoi(tmp);
            }
            else if (cmd == "sum") {
                ssr >> tmp;
                x = stoi(tmp);
            }
            while (ssr >> tmp) {
                if (tmp == "-n") {
                    ssr >> tmp;
                    process = stoi(tmp);
                }
                else if (tmp == "-d") {
                    ssr >> tmp;
                    duration = stoi(tmp);
                }
                else if (tmp == "-p") {
                    ssr >> tmp;
                    period = stoi(tmp);
                    cout << "period: " << period << endl;
                }
                else if (tmp == "-m") {
                    ssr >> tmp;
                    multithread = stoi(tmp);
                }
                else {
                    cout << "nothing" << endl;
                }
            }
            //여기서 명령어 실행
            if (cmd == "echo") {
                echo(args, process, duration, period);
            }
            else if (cmd == "dummy") {
                dummy();
            }
            else if (cmd == "gcd") {
                gcd(x, y, process, duration, period);
            }
            else if (cmd == "prime") {
                prime(x, process, duration, period);
            }
            else if (cmd == "sum") {
                sum(x, process, duration, period, multithread);
            }
            else {

            }
            process = 1;        // -n
            duration = -1;     // -d, 기본값 -1은 제한 없음
            period = 0;        // -p, 기본값 0은 반복 없음
            multithread = 1;
        }

    }
    /*
    for(auto& c:cmds){
        if(c.front()!='&'){
            int i = 0;
            while(c==""){
                i++;
                if(c=="-n"){
                    process=stoi(cmds[i]);
                }
                else if(c=="-d"){
                    duration=stoi(cmds[i]);
                }
                else if(c=="-p"){
                    period=stoi(cmds[i]);
                }
                else if(c=="-m"){
                    multithread=stoi(cmds[i]);
                }
            }
            if (c=="echo"){
                cout << "echo" << endl;
            }
            else if(c=="dummy"){
                cout <<"dummy" << endl;
            }
            else if(c == "gcd"){
                int x = stoi(cmds[1]);
                int y = stoi(cmds[2]);
                gcd(x,y);
            }
            else if(c=="prime"){

            }
            else if(c=="sum"){

            }
            else{

            }
        }
    }*/

}

int main() {
    //monitor(); 

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

            cmd = parse(command);
            exec(cmd);
        }
        cout << endl;
    }

    commands.close();  // 파일을 닫음
    return 0;
}