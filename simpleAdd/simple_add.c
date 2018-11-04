#include <linux/kernel.h>
#include <linux/linkage.h>
#include <asm/uaccess.h>

asmlinkage long sys_simple_add(int number1, int number2, int* result){
  printk(KERN_ALERT "First number: %d", number1);
  printk(KERN_ALERT "Second number: %d", number2);
  int num3 = number1 + number2;
  copy_to_user(result, &num3, sizeof(int));
  printk(KERN_ALERT "Result is %d", num3);//pointer is used with %p
  return 0;
}
