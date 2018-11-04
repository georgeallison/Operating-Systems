#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
  int r;
  int result = syscall(333, 4, 5, &r);
  printf("Result of addition: %d\n", r);
}
