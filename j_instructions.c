#include <stdint.h>
#include "cpu.h"
#include <stdio.h> 
//#include <stdlib.h>

#define BITMASK_ADD 0x003FFFFF

void j(uint32_t instruction){ 
	uint32_t address = (instruction & BITMASK_ADD);

	//printf("We are now in j\n");
	npc = ((pc+4) & 0xf0000000) | (address << 2); 

}

void jal(uint32_t instruction){ 
	uint32_t address = (instruction & BITMASK_ADD);

	//printf("We are now in jal\n");	
	//printf("Register 31 is %d\n", registers[31]);

	//registers[31] = ((uint32_t)(pc + 4)); and i tried 

	registers[31] = ((uint32_t)(pc + 4)); 
	//printf("Register 31 is %d\n", registers[31]);
	npc = ((pc + 4) & 0xf0000000) | (address << 2);
}