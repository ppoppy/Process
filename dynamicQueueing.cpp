#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>

using namespace std;
mutex mtx;

typedef struct stack {
    int arr[10000];
	int last;

	void init() {
		last = -1;
	}
	void push(int data) {
		arr[++last] = data;
	}
	bool empty() {
		return (last < 0);
	}
	int pop() {
		if (empty()) {
			return -1;
		}
		return arr[last--];
	}
	int size() {
		return last + 1;
	}
	int top() {
		if (empty()) {
			return -1;
		}
		return arr[last];
	}
}STACK;

typedef struct process{
    char* name;
    int size;
    int exec_time;
    int time_slice;
    STATE state;
}PROC;

typedef struct list_node {
    PROC* proc;
    struct list_node* next;
}NODE;

typedef struct DynamicQueue {
    STACK* next_stack;
    NODE* next;
}DQ;

void worker(int, int);

void worker(int id, int delay_ms){
  for (int i = 0; i < 10; ++i){
    Sleep(delay_ms);
    mtx.lock();
    cout << "thread#" << id << ": " << i << endl;
    mtx.unlock();
  }
}
void monitor(){ //DQ와 WQ를 일정시간마다 보여주는 BG 프로세스

}
int main() {
  thread t1(worker, 1, 1000);
  thread t2(worker, 2, 300);
  t1.join();
  t2.join();
  printf("===end of main()===\n");
}
