#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GEORGEALLISON");

#define BUFFER_SIZE 1024

static char myBuffer[BUFFER_SIZE];
int openCount = 0; 
int closeCount = 0;

ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	int dbs = strlen(myBuffer);/*device buffer size*/
	if(dbs == 0){
		return dbs;
	}
	copy_to_user(buffer, myBuffer, dbs);
	return 0;
}

ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	int dbs = strlen(myBuffer);/*device buffer size*/
	if(length == 0){
		return 0;
	}
	*offset = dbs;/*set offset to size of buffer*/
	copy_from_user(myBuffer + *offset, buffer, length);
	return length;
}

int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	printk(KERN_ALERT "open count = %d", ++openCount);
	return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	printk(KERN_ALERT "close count = %d", ++closeCount);
	return 0;
}

loff_t simple_char_driver_seek (struct file* pfile, loff_t offset, int whence)
{	/*Params are file pointer, offset whose values are interpretred using third param*/
	//f_pos for position
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	loff_t newpos = 0;/*new position*/
	switch(whence){
	case 0: newpos = offset; break;/*SEEK_SET*/
	case 1: newpos = pfile->f_pos + offset; break;/*SEEK_CUR*/
	case 2: newpos = BUFFER_SIZE - offset; break;/*SEEK_END*/
	}
	if(newpos > BUFFER_SIZE){
		newpos = BUFFER_SIZE;
	}
	if(newpos < 0){
		newpos = 0;
	}
	pfile->f_pos = newpos;
	return newpos;
}

struct file_operations simple_char_driver_file_operations = {
	.owner   = THIS_MODULE,				
	.open	 = simple_char_driver_open,					
	.release = simple_char_driver_close,					
	.read	 = simple_char_driver_read,					
	.write	 = simple_char_driver_write,				
	.llseek	 = simple_char_driver_seek,	
};

int simple_char_driver_init(void)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	register_chrdev(240, "MyCharDvr", &simple_char_driver_file_operations);
	kmalloc(myBuffer, GFP_KERNEL);
	return 0;
}

void simple_char_driver_exit(void)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	unregister_chrdev(240, "MyCharDvr"/*,&simple_char_driver_file_operations*/);
	kfree(&myBuffer);
}

module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);
