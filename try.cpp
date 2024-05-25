#include <iostream>
#include <list>
#include <stack>
#include <memory>

using namespace std;

class Process {
public:
    int id;
    bool isForeground;
    Process(int id, bool isForeground) : id(id), isForeground(isForeground) {}
};

class DynamicQueue {
private:
    stack<list<shared_ptr<Process>>> processStack;
    int threshold; // Define the threshold

public:
    DynamicQueue(int threshold) : threshold(threshold) {}

    void enqueue(shared_ptr<Process> process) {
        if (processStack.empty() || (processStack.top().size() >= threshold)) {
            processStack.push(list<shared_ptr<Process>>());
        }
        processStack.top().push_back(process);
    }

    shared_ptr<Process> dequeue() {
        if (processStack.empty()) return nullptr;

        auto process = processStack.top().front();
        processStack.top().pop_front();

        if (processStack.top().empty()) {
            processStack.pop();
        }
        return process;
    }

    void promote() {
        if (processStack.empty()) return;

        auto process = processStack.top().front();
        processStack.top().pop_front();

        if (!processStack.top().empty()) {
            processStack.push(processStack.top());
        }
        processStack.top().push_back(process);

        if (processStack.top().empty()) {
            processStack.pop();
        }
    }

    void split_and_merge() {
        // Implement split and merge logic here
    }

    void print() {
        stack<list<shared_ptr<Process>>> tempStack = processStack;
        while (!tempStack.empty()) {
            for (auto process : tempStack.top()) {
                cout << (process->isForeground ? "F" : "B") << process->id << " ";
            }
            cout << endl;
            tempStack.pop();
        }
    }
};

int main() {
    int threshold = 3; // Initialize the threshold value
    DynamicQueue dq(threshold);

    for (int i = 0; i < 5; ++i) {
        dq.enqueue(make_shared<Process>(i, true));
    }
    for (int i = 5; i < 10; ++i) {
        dq.enqueue(make_shared<Process>(i, false));
    }

    dq.print();
    return 0;
}
