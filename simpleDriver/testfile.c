#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/*MAJOR NUMBER IS 240*/

typedef int bool;
enum { false, true };

int main(){
	bool run = true;/*for while loop*/
	char option;/*for switch statement*/
	char numbytes[BUFFER_SIZE];/*number of bytes to edit*/
	char* buffer;/*for memory allocation*/
	int myOffset, myWhence;/*params for llseek()*/

	int file = open("/dev/simple_character_device", O_RDWR);/*opening file in /dev/ with read/write access mode*/

	printf("**************************************\n");
	printf("Hello!\nThis is a test program for the simple_character_driver\n");
	printf("CSCI 3753 | Assignment Two | October 2017 | by George Allison");

	while(run){
	printf("\n-- MENU --\n\nr: read from device\nw: write to device\ns: seek into device\ne: exit from the device\nPress anything else to keep reading or writing to the device\nEnter command: ");
		scanf("%c", &option);
		switch(option){
			case 'r':
			case 'R':/*read from device*/
				printf("Enter the number of bytes you want to read (from 0 to 1024): ");
				scanf("%s", numbytes);				
				buffer = (char *)malloc(numbytes);/*allocating space*/
				read(file, buffer, &numbytes);
				printf("Data read from device: %s\n", buffer);
				break;
			case 'w':
			case 'W':/*write to device*/
				printf("Enter data you want to write to the device: \n");
				scanf("%s", numbytes);
				write(file, buffer, BUFFER_SIZE);
				while(getchar() != '\n');/*flushes input buffer once newline (enter) is read*/
				break;
			case 's':
			case 'S':/*seek into device*/
				printf("Enter an offset value: ");
				scanf("%d", myOffset);
				printf("Enter a value for whence (third parameter): ");
				scanf("%d", myWhence);
				llseek(file, myOffset, myWhence);
				break;
			case 'e':
			case 'E':/*exit*/
				printf("Quitting test app...\n");
				run = false;
				return 0;
			default:
				while(getchar() != '\n');/*await input*/
		}
	}	
	close(file);
	free(buffer);
	return 0;
}					
