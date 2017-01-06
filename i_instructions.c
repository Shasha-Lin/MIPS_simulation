
#include <stdint.h>
#include "cpu.h"
#include <stdio.h> 
//#include <stdlib.h>

#define BITMASK_IMM 0x0000FFFF
#define BITMASK_RT 0x001F0000
#define BITMASK_RS 0x03E00000
#define BITMASK_SIGN 0x8000 

#define BITMASK_1 0xFFFF0000
/*this is the bitmask to sign-extend*/

#define BITMASK_2 0xFFFFFF00
/*this is the bitmask to sign-extend memory content into 32 bits*/
uint32_t sign_extend(uint16_t imm){ 
	if ((imm>>15)==1)
return (((uint32_t)imm) | BITMASK_1);

	else 
	{uint16_t value = (uint16_t)imm;
	return(uint32_t)value; }
}
//the following is the function to sign extent memory (one byte) into 32 bits
uint32_t sign_extend2(uint8_t mem){ 
	if ((mem>>7)==1)
return (((uint32_t)mem) | BITMASK_2);

	else 
	{uint32_t value = (uint8_t)mem;
	return(uint32_t)value; }
}

void addi(uint32_t instruction){

	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 


	registers[rt] = (uint32_t) ((int32_t) registers[rs] + (int32_t)(sign_extend(imm)));
}

void addiu(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	registers[rt] = (uint32_t) ((uint32_t) registers[rs] + sign_extend(imm));
}

void andi(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	registers[rt] = (uint32_t) (registers[rs] & ((uint32_t)imm));
//printf("register[rt] has %d", registers[rt]);
}
void ori(uint32_t instruction){

	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	registers[rt] = (uint32_t) (registers[rs] | ((uint32_t)imm));
}

void xori(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	registers[rt] = (uint32_t) (registers[rs] ^ ((uint32_t)imm));
}

void slti(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	if((int32_t) registers[rs] < ((int32_t) sign_extend(imm))){
		registers[rt] = 1; 
	}
	else {
		registers[rt] = 0;
	}
}

void sltiu(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	if (registers[rs] < sign_extend(imm)){
		registers[rt] = 1; 
	}
	else {
		registers[rt] = 0;
	}
}

void beq(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	//ERROR np
	if (((int32_t)registers[rs])== ((int32_t)registers[rt])){
		npc = pc + 4 + ((int32_t)(sign_extend(imm) << 2));
	}
}


void bne(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	if (((int32_t)registers[rs]) != ((int32_t)registers[rt])){
		npc = pc + 4 + ((int32_t)(sign_extend(imm) << 2));
	}
}


void lb(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	//One byte is loaded from memory (abscense of *) into the lowest byte of [R[rt]
	//Should be finished 
	registers[rt] = sign_extend2(memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))]);

}

void lbu(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	//One byte is loaded from memory into the lowest byte of R[rt], the rest contains 0
	//Finished since uint32_t without * references only one byte in memory 
	registers[rt] = memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))];
}


void lh(uint32_t instruction){

	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 
	uint16_t* mem16;
	mem16=&memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))];

	//Two bytes are loaded from memory into the lower half of R[rt]. Upper half of R[rt] results 
	//from sign extending the loaded value 
	//Not done, how to access only two bytes
	registers[rt] = (uint32_t)(sign_extend(*mem16));
}

void lhu(uint32_t instruction){

	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 
	uint16_t* mem16;
	mem16=&memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))];
	registers[rt] = (uint32_t)(*mem16);
}

void lw(uint32_t instruction){

	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 
	uint32_t* mem32;
	mem32=&memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))];
	//Should be finished 
	registers[rt] = (*mem32);
}

void lui(uint32_t instruction){

	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 

	registers[rt] = ((uint32_t)imm) << 16;
}	

void sb(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM);


	//Lowest byte R[rt] should be stored in Memory 
	memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))]= (registers[rt]&0x000000FF); 
}

void sh(uint32_t instruction){
	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 
uint16_t* mem16;
	 mem16=&memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))];
	 *mem16= (registers[rt]&0x0000FFFF); 
}
void sw(uint32_t instruction){

	uint8_t rs = (instruction & BITMASK_RS) >> 21;
	uint8_t rt = (instruction & BITMASK_RT) >> 16;
	uint16_t imm = (instruction & BITMASK_IMM); 
uint32_t* mem32;
	mem32=&memory[((int32_t)registers[rs]) + ((int32_t)(sign_extend(imm)))];
	 *mem32= registers[rt]; 
}