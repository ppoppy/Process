#include <iostream>
#include <thread>
#include <windows.h> //sleep()


using namespace std;

void worker();

void worker() {
  for (int i = 0; i < 10; ++i){
    Sleep(1000);
    cout << i << endl;
  }
}

int main() {
  //thread t1(worker);
  //t1.join();         //t1 해제, 메인 스레드는 t1이 끝날 때까지 block
  printf("===end of main()===\n"); //printf()도 사용 가능
  return 0;
}
