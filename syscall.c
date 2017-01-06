#include <stdint.h>
#include <stdio.h>
//#include <stdlib.h>
//#This is just for testing Git
#include "cpu.h"
void syscall (uint32_t instruction) {
int readIn;
char character[registers[5]];
	
	if (registers[2]==1){
	printf ("%d\n",registers[4]);
	} 

	else if (registers[2]==2){
	printf("error: float data type is not supported\n");
	cpu_exit(1);
	}


	else if (registers[2]==3){
	printf("error: double data type is not supported\n");
	cpu_exit(1);
	}

	else if (registers[2]==4){
	printf("%s", &(memory[registers[4]]));
	}

	else if (registers[2]==5){ 
	scanf("%d", &readIn);
	registers[2]=(uint32_t)readIn;
	}
	
	else if (registers[2]==6){
	printf("error: read_float is not supported\n");
	cpu_exit(1);
	}

	else if (registers[2]==7){
	printf("error: read_double is not supported\n");
	cpu_exit(1);
	}
	
	else if (registers[2]==8){
	//printf("This should be where the string is printed\n");
	//printf("The size of r5 is %d\n", registers[5]);
	scanf("%s", &(*(memory+registers[4])));
	//fgets(character, registers[5], stdin);
	}

	else if (registers[2]==9){
	printf("error: not supported\n");
	cpu_exit(1);
	}
	
	else if (registers[2]==10)	
	cpu_exit(0);
	
	else {
	printf("error: unsupported operation.\n");
	cpu_exit(1);
}
}
