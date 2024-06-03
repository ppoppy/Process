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
#include <mutex>
//#include <cctype>

using namespace std;
mutex sum_mutex;
int pid = 1;
int seelpsecond = 3;
atomic<long long> total_sum(0);

struct Command {
    string command;
    string args;
    int process = 1;
    int duration = -1;
    int period = 0;
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
vector<string> parse(string command) {
    stringstream ssr(command);
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
        //cout << c << "endl" << endl;
    }
    return token;
}

void echo(string args) {
    cout << args << endl;
}

void echo_divide(string args, int process, int duration, int period) {
    pid++;

    auto start = chrono::steady_clock::now();
    /*
    while (true) {
        auto current = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(current - start).count() >= 20) {
            break;
        }
        cout << args << endl;
        std::this_thread::sleep_for(chrono::seconds(period));
    }*/
    if (process > 1) {
        if (period > 0) {
            while (true) {
                auto current = chrono::steady_clock::now();

                if (chrono::duration_cast<chrono::seconds>(current - start).count() >= duration) {
                    break;
                }
                for(int i = 0; i < process; ++i) {
                    echo(args);
                }
                std::this_thread::sleep_for(chrono::seconds(period));

            }
        }
        else {
            for (int i = 1; i <= process; i++) {
                echo(args);
                pid++;
            }
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));
        }
    }
    else {
        if (period > 0) {
            
            while (true) {

                auto current = chrono::steady_clock::now();

                if (chrono::duration_cast<chrono::seconds>(current - start).count() >= duration) {
                    break;
                }
                echo(args);
                std::this_thread::sleep_for(chrono::seconds(period));

            }
        }
        else {
            echo(args);
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));
        }
    }
}

void dummy() {
    cout << "프로세스 생성" << endl;
}

void gcd(int x, int y, int process, int duration, int period) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    cout << x << endl;
}
void gcd_divide(int x, int y, int process, int duration, int period) {
    pid++;

    auto start = chrono::steady_clock::now();
    /*
    while (true) {
        auto current = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(current - start).count() >= 20) {
            break;
        }
        cout << args << endl;
        std::this_thread::sleep_for(chrono::seconds(period));
    }*/
    if (process > 1) {
        if (period > 0) {
            while (true) {
                auto current = chrono::steady_clock::now();
                if (chrono::duration_cast<chrono::seconds>(current - start).count() >= duration) {
                    break;
                }
                for (int i = 0; i < process; ++i) {
                    gcd(x, y, process, duration, period);
                }
                    
                std::this_thread::sleep_for(chrono::seconds(period));

            }
        }
        else {
            for (int i = 1; i <= process; i++) {
                gcd(x, y, process, duration, period);
                pid++;
            }
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));
        }
    }
    else {
        if (period > 0) {
            while (true) {

                auto current = chrono::steady_clock::now();

                if (chrono::duration_cast<chrono::seconds>(current - start).count() >= duration) {
                    break;
                }
                gcd(x, y, process, duration, period);
                std::this_thread::sleep_for(chrono::seconds(period));
            }
        }
        else {
            gcd(x, y, process, duration, period);
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));

        }
    }
}
void prime(int x, int process, int duration, int period) {
    vector<bool> isPrime(x + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= x; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= x; j += i) {
                isPrime[j] = false;
            }
        }
    }
    cout << count(isPrime.begin(), isPrime.end(), true) << endl;
}
void prime_divide(int x, int process, int duration, int period) {
    pid++;

    auto start = chrono::steady_clock::now();
    /*
    while (true) {
        auto current = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(current - start).count() >= 20) {
            break;
        }
        cout << args << endl;
        std::this_thread::sleep_for(chrono::seconds(period));
    }*/
    if (process > 1) {
        if (period > 0) {
            while (true) {
                auto current = chrono::steady_clock::now();

                if (chrono::duration_cast<chrono::seconds>(current - start).count() >= duration) {
                    break;
                }
                for (int i = 0; i < process; ++i) {
                    prime(x, process, duration, period);
                }
                    
                std::this_thread::sleep_for(chrono::seconds(period));

            }
        }
        else {
            for (int i = 1; i <= process; i++) {
                prime(x, process, duration, period);
                pid++;
            }
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));
        }
    }
    else {
        if (period > 0) {
            while (true) {

                auto current = chrono::steady_clock::now();

                if (chrono::duration_cast<chrono::seconds>(current - start).count() >= duration) {
                    break;
                }
                prime(x, process, duration, period);
                std::this_thread::sleep_for(chrono::seconds(period));
            }
        }
        else {
            prime(x, process, duration, period);
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));
        }
    }
}
int sum(int x) {
    long long result = static_cast<long long>(x) * (x + 1) / 2; // long long으로 캐스팅하여 계산
    return result % 1000000;
}
void calculate_sum(int start, int end, int period, atomic<bool>& done) {
    long long local_sum = 0;
    for (int i = start; i <= end && !done; ++i) {
        local_sum += i;
        if (period > 0 && i % period == 0) {
            //this_thread::sleep_for(chrono::seconds(period));
        }
    }
    lock_guard<mutex> lock(sum_mutex);
    //cout << local_sum << endl;
    total_sum += local_sum;
}
void sum_divide(int x, int process, int duration, int period, int multithread) {
    pid++;
    auto start = chrono::steady_clock::now();
    /*
    while (true) {
        auto current = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(current - start).count() >= 20) {
            break;
        }
        cout << args << endl;
        std::this_thread::sleep_for(chrono::seconds(period));
    }*/
    vector<thread> threads;
    vector<int> thread(multithread);
    int data_per_thread = x / multithread;
    atomic<bool> done(false);
    if (process > 1) {
        if (period > 0) {
            if (duration > 0) {
                while (true) {
                    auto current = chrono::steady_clock::now();

                    for (int i = 0; i < multithread; ++i) {
                        int start = i * data_per_thread + 1;
                        int end = (i == multithread - 1) ? x : (i + 1) * data_per_thread;
                        thread[i] = sum(data_per_thread);
                        threads.emplace_back(calculate_sum, start, end, period, ref(done));
                    }
                    if (duration > 0) {
                        //this_thread::sleep_for(chrono::seconds(duration));
                        done = true;
                        
                    }
                    for (auto& thread : threads) {
                        thread.join();
                    }

                    for (int j = 0; j < process; ++j) {
                        for (int i = 0; i < multithread; ++i) {
                            thread[i] = sum(data_per_thread);
                            cout << "thread " << i + 1 << ": " << thread[i] << endl;
                        }

                        cout << "Total sum modulo : " << total_sum % 1000000 << endl;
                        //sum(x, process, duration, period, multithread);
                        
                    }
                    this_thread::sleep_for(chrono::seconds(seelpsecond));
                }
            }
            else {
                for (int i = 0; i < multithread; ++i) {
                    int start = i * data_per_thread + 1;
                    int end = (i == multithread - 1) ? x : (i + 1) * data_per_thread;
                    thread[i] = sum(data_per_thread);
                    threads.emplace_back(calculate_sum, start, end, period, ref(done));
                }
                //sum(x, process, duration, period, multithread);

                if (duration > 0) {
                    //this_thread::sleep_for(chrono::seconds(duration));
                    done = true;
                }


                for (auto& thread : threads) {
                    thread.join();
                }

                for (int j = 0; j < process; ++j) {
                    for (int i = 0; i < multithread; ++i) {
                        thread[i] = sum(data_per_thread);
                        cout << "thread " << i + 1 << ": " << thread[i] << endl;
                    }

                    cout << "Total sum modulo : " << total_sum % 1000000 << endl;
                    //sum(x, process, duration, period, multithread);
                    
                }std::this_thread::sleep_for(chrono::seconds(seelpsecond));
            }

        }
        else {

            for (int i = 0; i < multithread; ++i) {
                int start = i * data_per_thread + 1;
                int end = (i == multithread - 1) ? x : (i + 1) * data_per_thread;

                threads.emplace_back(calculate_sum, start, end, period, ref(done));
            }


            // 스레드 종료 대기
            for (auto& thread : threads) {
                thread.join();
            }

            for (int j = 0; j < process; ++j) {
                for (int i = 0; i < multithread; ++i) {
                    thread[i] = sum(data_per_thread);
                    cout << "thread " << i + 1 << ": " << thread[i] << endl;
                }

                cout << "Total sum modulo : " << total_sum % 1000000 << endl;
                //sum(x, process, duration, period, multithread);
               
            }
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));

        }
    }
    else {
        if (period > 0) {
            if (duration > 0) {
                while (true) {
                    auto current = chrono::steady_clock::now();

                    for (int i = 0; i < multithread; ++i) {
                        int start = i * data_per_thread + 1;
                        int end = (i == multithread - 1) ? x : (i + 1) * data_per_thread;
                        thread[i] = sum(data_per_thread);
                        threads.emplace_back(calculate_sum, start, end, period, ref(done));
                    }
                    //sum(x, process, duration, period, multithread);

                    if (duration > 0) {
                        //this_thread::sleep_for(chrono::seconds(duration));
                        done = true;
                    }

                    // 스레드 종료 대기
                    for (auto& thread : threads) {
                        thread.join();
                    }

                    for (int i = 0; i < multithread; ++i) {
                        thread[i] = sum(data_per_thread);
                        cout << "thread " << i + 1 << ": " << thread[i] << endl;
                    }

                    cout << "Total sum modulo : " << total_sum % 1000000 << endl;
                    //sum(x, process, duration, period, multithread);
                    std::this_thread::sleep_for(chrono::seconds(seelpsecond));

                }
            }
            else {
                cout << "무한루프 방지" << endl;
                std::this_thread::sleep_for(chrono::seconds(seelpsecond));
            }
        }
        else {
            for (int i = 0; i < multithread; ++i) {
                int start = i * data_per_thread + 1;
                int end = (i == multithread - 1) ? x : (i + 1) * data_per_thread;
                thread[i] = sum(data_per_thread);
                //cout << "thread " << i << ": " << thread[i] << endl;
                threads.emplace_back(calculate_sum, start, end, period, ref(done));
            }


            // 스레드 종료 대기
            for (auto& thread : threads) {
                thread.join();
            }
            for (int i = 0; i < multithread; ++i) {
                thread[i] = sum(data_per_thread);
                cout << "thread " << i + 1 << ": " << thread[i] << endl;
            }
            cout << "Total sum modulo : " << total_sum % 1000000 << endl;
            //sum(x, process, duration, period, multithread);
            std::this_thread::sleep_for(chrono::seconds(seelpsecond));

        }
    }
}


void exec(vector<string> command) {
    //vector<string> cmds;
    int process = 1;
    int duration = 110;
    int period = 0;
    int multithread = 1;
    for (auto& c : command) {
        //cout << "c: " << c << endl;

        if (!c.empty()) {

            if (c.front() == '&') {
                cout << "prompt> " << c << endl;
            }
        }

    }
    for (auto& c : command) {
        stringstream ssr(c);
        string tmp;
        string cmd;
        string args;
        int x;
        int y;
        //unsigned long sum_x;
        if (!c.empty()) {

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
                        //cout << "period: " << period << endl;
                    }
                    else if (tmp == "-m") {
                        ssr >> tmp;
                        multithread = stoi(tmp);
                    }
                    else {
                        cout << "옵션을 잘 못 입력하셨습니다. 잘 못 입력된 값: " << tmp << endl;
                    }
                }
                //명령어 실행
                if (cmd == "echo") {
                    cout << "prompt> " << c << endl;
                    echo_divide(args, process, duration, period);
                }
                else if (cmd == "dummy") {
                    cout << "prompt> " << c << endl;
                    dummy();
                }
                else if (cmd == "gcd") {
                    cout << "prompt> " << c << endl;
                    gcd_divide(x, y, process, duration, period);
                }
                else if (cmd == "prime") {
                    cout << "prompt> " << c << endl;
                    prime_divide(x, process, duration, period);
                }
                else if (cmd == "sum") {
                    cout << "prompt> " << c << endl;
                    sum_divide(x, process, duration, period, multithread);
                }
                else {

                }
                process = 1;
                duration = 110;
                period = 0;
                multithread = 1;
            }
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
    //cout << currentDirectory << "\\commands.txt" << endl;
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

    commands.close();
    return 0;
}
