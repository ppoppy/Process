

#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <string.h>
#include <fstream>

using namespace std;



typedef struct stack {
    int arr[10000];\
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



typedef struct list_node {
    
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
    
    cout << "thread#" << id << ": " << i << endl;
    
  }
}
void monitor(){ //DQ와 WQ를 일정시간마다 보여주는 BG 프로세스

}

// void shell(string line){
    
// }


void readFile(const char* filename) {
    // 파일을 읽기 모드로 엽니다.
    HANDLE hFile = CreateFile(
        filename,               // 파일 이름
        GENERIC_READ,           // 읽기 접근 권한
        0,                      // 공유 모드 (공유하지 않음)
        NULL,                   // 기본 보안 속성
        OPEN_EXISTING,          // 파일이 존재할 경우 열기
        FILE_ATTRIBUTE_NORMAL,  // 일반 파일 속성
        NULL                    // 템플릿 파일 핸들 없음
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open file. Error: " << GetLastError() << std::endl;
        return;
    }

    // 파일의 크기를 구합니다.
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        std::cerr << "Failed to get file size. Error: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return;
    }

    // 파일의 내용을 저장할 버퍼를 할당합니다.
    char* buffer = new char[fileSize.QuadPart];

    // 파일에서 데이터를 읽어옵니다.
    DWORD bytesRead;
    BOOL result = ReadFile(
        hFile,                  // 파일 핸들
        buffer,                 // 데이터를 저장할 버퍼
        fileSize.QuadPart,      // 읽을 바이트 수
        &bytesRead,             // 실제로 읽은 바이트 수
        NULL                    // 동기식 읽기
    );

    if (!result) {
        std::cerr << "Failed to read file. Error: " << GetLastError() << std::endl;
    } else {
        cout << "File content:" << endl;
        //cout.write(buffer, bytesRead);
         for (DWORD i = 0; i < bytesRead; ++i) {
            std::cout << buffer[i] << " ";
        }
		cout << endl;
    }

	// while(!buffer){
	// 	if 

	// }

    // 메모리 해제 및 파일 핸들 닫기
    delete[] buffer;
    CloseHandle(hFile);
}

int main() {
    const char* filename = "commands.txt";
    readFile(filename);
    return 0;
}
/*
int main() {
    const string filename = "commands.txt";

	ifstream CF;
	CF.open(filename);
	if(!CF){
		cout << "파일을 열 수 없습니다." << endl;
	}
	else cout <<"success" << endl;
    return 0;
   
}
*/