#include <stdio.h>
#include <stdlib.h>

void destroy_data(void *data)
{
    free(data);
}

int compare_to(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main(void)
{
  printf("hello world\n");
  return 0;
}
