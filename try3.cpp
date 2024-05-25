#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

int gcd(int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int countPrimes(int x) {
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

void executeCommand(const string& command, const vector<string>& options) {
    if (command.substr(0, 4) == "echo") {
        cout << command.substr(5) << endl;
    } else if (command == "dummy") {
        //thread 생성
    } else if (command.substr(0, 3) == "gcd") {
        int x, y;
        sscanf(command.c_str(), "gcd %d %d", &x, &y);
        cout << "GCD of " << x << " and " << y << " is " << gcd(x, y) << endl;
    } else if (command.substr(0, 5) == "prime") {
        int x;
        sscanf(command.c_str(), "prime %d", &x);
        cout << "Number of primes less than or equal to " << x << " is " << countPrimes(x) << endl;
    } else if (command.substr(0, 3) == "sum") {
        int x;
        sscanf(command.c_str(), "sum %d", &x);
        cout << "Sum of integers up to " << x << " modulo 1,000,000 is " << sum(x) << endl;
    }
}

void parseAndExecuteCommand(const string& line) {
    vector<string> parts;
    stringstream ss(line);
    string part;
    while (ss >> part) {
        parts.push_back(part);
    }

    string command = parts[0];
    vector<string> options(parts.begin() + 1, parts.end());

    executeCommand(command, options);
}

int main() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    string currentDirectory = string(buffer).substr(0, pos);
    cout << "Current working directory: " << currentDirectory << endl;

    
    ifstream commands(currentDirectory + "\\commands.txt");
    string line;
    
    if(!commands.is_open()){
        cout << "File not found" << endl;
        return 1; 
    } else {
        
        while(getline(commands, line)){
            cout << "promt > "<< line << endl;
            parseAndExecuteCommand(line);
        }
        cout << endl;
    }
    commands.close(); 
    return 0;
}
