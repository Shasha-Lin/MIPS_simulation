#include <stdint.h>
#include <stdio.h>
//#include <stdlib.h>
#include "cpu.h"
#define BITMASK_RS 0x03E00000
#define BITMASK_RT 0x001F0000
#define BITMASK_RD 0x0000F800
#define BITMASK_SHAMT 0x000007C0
#define BITMASK_LO 0x0000FFFF


void add(uint32_t instruction){
    
	uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;

	registers[rd] = (uint32_t) ((int32_t) registers[rs] + (int32_t) registers[rt]);
}

void addu(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint8_t rd = (instruction & BITMASK_RD) >> 11;

	registers[rd] = (uint32_t) ((uint32_t) registers[rs] + (uint32_t) registers[rt]);
}


void sub(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
	//uint32_t registers[rd];

	registers[rd] = (uint32_t) ((int32_t) registers[rs] - (int32_t) registers[rt]);
	//printf ("register[rd] has %d",registers[rd]);
}

void subu(uint32_t instruction){

uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
	//uint32_t registers[rd];

	registers[rd] = (uint32_t) ((uint32_t) registers[rs] - (uint32_t) registers[rt]);
}

void mult(uint32_t instruction){
	uint64_t multresult;
	
uint8_t rs = (instruction & BITMASK_RS)>>21;
uint8_t rt = (instruction & BITMASK_RT)>>16;
	
  multresult= (uint64_t)(int64_t)((int32_t) registers[rs])* (int64_t)((int32_t) registers[rt]);
		HI= (uint32_t)(multresult>>32);
		LO= (uint32_t)(multresult & BITMASK_LO);
}

void multu(uint32_t instruction){
	uint64_t multresult;
uint8_t rs = (instruction & BITMASK_RS)>>21;
uint8_t rt = (instruction & BITMASK_RT)>>16;
multresult= (uint64_t) registers[rs] * (uint64_t) registers[rt];
		HI= (uint32_t)(multresult>>32);
		LO= (uint32_t)(multresult & BITMASK_LO);
}
// void mult(uint32_t instruction){

// 	uint8_t rs = (instruction & BITMASK_RS) >> 21;
// 	uint8_t rt = (instruction & BITMASK_RT) >> 16;

// 	 HI:LO = (uint32_t) ((int32_t) registers[rs] * (int32_t) registers[rt]);
// } 

// void multu(uint32_t instruction){

// 	uint8_t rs = (instruction & BITMASK_RS) >> 21;
// 	uint8_t rt = (instruction & BITMASK_RT) >> 16;

// 	HI:LO = (uint32_t) ((uint32_t) registers[rs] * (uint32_t) registers[rt]);
// }  

void div(uint32_t instruction){

uint8_t rs = (instruction & BITMASK_RS)>>21;
uint8_t rt = (instruction & BITMASK_RT)>>16;

LO = (uint32_t) ((int32_t) registers[rs] / (int32_t) registers[rt]);
HI = (uint32_t) ((int32_t) registers[rs] % (int32_t) registers[rt]);
}  

void divu(uint32_t instruction){

uint8_t rs = (instruction & BITMASK_RS)>>21;
uint8_t rt = (instruction & BITMASK_RT)>>16;

LO = (uint32_t) ((uint32_t) registers[rs] / (uint32_t) registers[rt]);
HI = (uint32_t) ((uint32_t) registers[rs] % (uint32_t) registers[rt]);
} 

void and(uint32_t instruction){
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = (uint32_t) ((int32_t) registers[rs] & (int32_t) registers[rt]);
} 

void nor(uint32_t instruction){
	
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;

registers[rd] = (uint32_t) ~((int32_t) registers[rs] | (int32_t) registers[rt]);
} 

void or(uint32_t instruction){
	
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = (uint32_t) ((int32_t) registers[rs] | (int32_t) registers[rt]);
}  

void xor(uint32_t instruction){
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = (uint32_t) ((int32_t) registers[rs] ^ (int32_t) registers[rt]);
}  

void sll(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = (uint32_t) ((int32_t) registers[rt] << ((instruction & BITMASK_SHAMT)>>6));
}  

void sllv(uint32_t instruction){
	
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;

registers[rd] = (uint32_t) ((int32_t) registers[rs] << ((int32_t) registers[rt]));
}  

void srl(uint32_t instruction){
	
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = (uint32_t) ((uint32_t) registers[rt] >> ((instruction & BITMASK_SHAMT)>>6));
}  

void srlv(uint32_t instruction){
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;

registers[rd] = (uint32_t) ((uint32_t) registers[rs] >> ((int32_t) registers[rt]));
}  

void sra(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
	uint8_t shamt=(instruction & BITMASK_SHAMT)>>6;


	
	registers[rd]=((int32_t)registers[rt])>>shamt;
}   


void srav(uint32_t instruction){
	
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = (uint32_t) ((int32_t) registers[rt] >> ((instruction & BITMASK_SHAMT)>>6));
}  


void slt(uint32_t instruction) {
    uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;

	if((int32_t) registers[rs] < (int32_t) registers[rt]) {
	registers[rd] = 1; 
	}
	else {
	registers[rd] = 0;
	}

} 

void sltu(uint32_t instruction){
uint8_t rs = (instruction & BITMASK_RS)>>21;
	uint8_t rt = (instruction & BITMASK_RT)>>16;
	uint8_t rd = (instruction & BITMASK_RD)>>11;

if((uint32_t) registers[rs] < (uint32_t) registers[rt]){
		registers[rd] = 1; 
}
else {
 	registers[rd] = 0;
}
}  

void jr(uint32_t instruction){

uint8_t rs = (instruction & BITMASK_RS)>>21;
	
npc = (uint32_t) registers[rs];
	
}

void jalr(uint32_t instruction) {
	uint8_t rs = (instruction & BITMASK_RS)>>21;
	registers[31]=pc+4;
	registers[rs]=npc;
}

void mfhi(uint32_t instruction){
uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = HI;
}

void mflo(uint32_t instruction){
uint8_t rd = (instruction & BITMASK_RD)>>11;
registers[rd] = LO;
} 
