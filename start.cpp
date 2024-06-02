// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <vector>
// #include <list>
// #include <condition_variable>
// #include <cctype>
// #include <sstream>

// using namespace std;

// int pid = 2;

// class Process {
// public:
//     int id;
//     char type; // 'F' for foreground, 'B' for background
//     Process(int id, char type) : id(id), type(type) {}
// };

// class DynamicQueue {
//     list<list<Process*>> stack;

// public:
//     void enqueue(Process* process) {
//         if (process->type == 'F') {
//             if (!stack.empty()) {
//                 stack.front().push_back(process);
//             } else {
//                 list<Process*> newQueue;
//                 newQueue.push_back(process);
//                 stack.push_front(newQueue);
//             }
//         } else {
//             if (!stack.empty()) {
//                 stack.back().push_back(process);
//             } else {
//                 list<Process*> newQueue;
//                 newQueue.push_back(process);
//                 stack.push_back(newQueue);
//             }
//         }
//     }

//     Process* dequeue() {
//         if (!stack.empty()) {
//             auto& frontQueue = stack.front();
//             Process* process = frontQueue.front();
//             frontQueue.pop_front();
//             if (frontQueue.empty()) {
//                 stack.pop_front();
//             }
//             return process;
//         }
//         return nullptr;
//     }

//     void promote() {
//         // Implement the logic to move a process from one queue to another
//     }
// };

// DynamicQueue dq;

// void exec(string command){
//     cout << "명령어 실행" << endl;
// }
// void Shell(string command){
//     exec(command);
//     _sleep(3);
// }
// void Monitor(){
//     cout << "Running: [" << "]" << endl;
//     cout << "---------------------------" << endl;
//     cout << "DQ: " << endl;
//     cout << "---------------------------" << endl;
//     cout << "WQ: " << endl;
// }
// int main() {

//     Process* shell = new Process(0, 'F');
//     Process* monitor = new Process(1, 'B');


//     char buffer[_MAX_PATH];
//     GetModuleFileNameA(NULL, buffer, _MAX_PATH);
//     string::size_type pos = string(buffer).find_last_of("\\/");
//     string currentDirectory = string(buffer).substr(0, pos);
//     //cout << "Current working directory: " << currentDirectory << endl;

//     ifstream commands(currentDirectory + "\\commands.txt");
//     string command;

//     vector<string> cmd;




//     if(!commands.is_open()){
//         cout << "File not found" << endl;
//         return 1; 
//     }
//     else {
//         while(getline(commands, command)){
//             //cout << command << endl;

//             cmd = parse(command);
//             exec(cmd);
//         }
//         cout << endl;
//     }

//     commands.close(); 
//     string command = "echo aaa;";
//     Shell(command);
//     Monitor();
//     // Process* dequeued = dq.dequeue();
//     // if (dequeued != nullptr) {
//     //     cout << "Dequeued process ID: " << dequeued->id << endl;
//     // }

//     return 0;
// }
