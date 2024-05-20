#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

void worker();

void worker(){
  for(int i = 0; i < 10; ++i){
    Sleep(1000);
    cout << i << endl;
  }
}

int main() [
  thread t1(worker);
  t1.detach();      // 메인 스레드가 block되지 않음
  printf("===end of main()===\n");
  Sleep(5000);
  return 0;        // 프로세스가 종료되면 t1도 해제
}
