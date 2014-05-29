#include <stdlib.h>
#include <stdio.h>

int main(){
  int limit = 1000, i;

  printf("addr=%lx\n", &limit);
  sleep(80);

  for(i = 0; i < limit; i++)
    printf("%d\n", i);
    
  return 0;
}
