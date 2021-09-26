#include <stdio.h>
#include <thread>
#include <emscripten.h>

EM_JS(void, await_something, (), {
  return Asyncify.handleSleep(function(wakeUp) {
    console.log("waiting...");
    setTimeout(_ => { console.log("wake up!"); wakeUp()}, 1000);
  });
});

// EM_ASYNC_JS(void, await_something, (), {
//   out("waiting for a fetch");
//   await new Promise((res, rej) => {
//     setTimeout(_ => res(), 1000);
//   }).then(_ => {
//     console.log("resolved!");
//   });
//   // const response = await fetch("a.html");
//   // out("got the fetch response");
//   // (normally you would do something with the fetch here)
//   return 42;
// });

void thread_inner() {
  printf("hello by INNER!!!\n");

  FILE *file = fopen("message.txt", "rb");
  if (!file) { printf("cannot open file\n"); }
  while (!feof(file)) {
    char c = fgetc(file);
    if (c != EOF) {
      putchar(c);
    }
  }
  fclose(file);
}

void thread_outer() {
  printf("hello by outer\n");

  await_something();

  // for 2 threads the thread-pool needs size 3
  // std::thread t1(thread_inner);
  // std::thread t2(thread_inner);
  // std::thread t2([]{ printf("hello from closure"); });

  // std::thread* t2 = new std::thread(
  //   []{ printf("hello from closure\n"); }
  // );

  // w/o join throws unreachable
  // t1.join();
  // t2->join();
}

int main() {
  printf("running main...\n");


  // await_something();


  // MainCmds::my_async();


  std::thread t1(thread_outer); t1.join();
  // std::thread t2(thread_outer); t2.join();
  // std::thread t3(thread_outer); t3.join();

  return 0;
}
