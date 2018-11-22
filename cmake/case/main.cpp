#include <iostream>

#include "hello.h"
//#include <dlfcn.h>

#define dynamic 1

using namespace std;

int main(int argc, char *argv[])
{
  int num;
  cout << "start programe" << endl;
  cin >> num;
  HelloFunc();
#ifndef dynamic
  //void* handle = dlopen("/root/workstation/studio/c++/cmake/case/lib/libhello.so", RTLD_LAZY);
  void* handle = dlopen("/root/workstation/studio/c++/cmake/case/build/lib/libhello.so", RTLD_NOW);
  if (!handle) {
    cout << "Cann't load lib" << endl;
    return -1;
  }

  typedef void (*hello_t)();

  dlerror();
  hello_t hello = (hello_t) dlsym(handle, "HelloFunc");
  const char *dlsym_error = dlerror();
  if (dlsym_error) {
    cout << "Cann't load symbol HelloFunc" << dlsym_error <<endl;
    dlclose(handle);
    return -1;
  }

  hello();

  dlclose(handle);
#endif

  return 0;
}
