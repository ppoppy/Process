#include <iostream>
#include <thread>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;
//mutex mtx;

int main(){
    ifstream file("commands.txt");
	string command;
	file >> command;
    if(!file.is_open()){
        cout << "file not found" << endl;
    }
    else {
        cout <<"file content: " << command << endl;
    }
	return 0;
}