// #define _GNU_SOURCE
// pthread_tryjoin_np
#include <stdio.h>
#include <pthread.h>
#include <emscripten.h>

EM_JS(void, await_something, (), {
  Asyncify.handleSleep(function(wakeUp) {
    console.log("waiting...");
    setTimeout(_ => { console.log("wake up!"); wakeUp()}, 1000);
  });
});

void* task_leaf(void* arg) {
  printf("- task_leaf!!!\n");

  FILE *file = fopen("message.txt", "rb");
  if (!file) { printf("cannot open file\n"); return NULL; }
  while (!feof(file)) {
    char c = fgetc(file);
    if (c != EOF) {
      putchar(c);
    }
  }
  fclose(file);

  return NULL;
}

void* task_outer(void* arg) {
  printf("- task_outer\n");

  await_something();
  printf("returned!\n");

  pthread_t t;
  pthread_create(&t, NULL, task_leaf, NULL);
  pthread_join(t, NULL);
  return NULL;
}

int main() {
  printf("running main...\n");




  pthread_t t;
  pthread_create(&t, NULL, task_outer, NULL);
  pthread_join(t, NULL);

  return 0;
}
