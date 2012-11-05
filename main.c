#include<stdio.h>
#include"vm.h"

int main(int argc, char **argv){
  init_vm();
  /*unsigned short word = get_next_word();
	vm_loc a, b;
	a = code_word_a(word);
	b = code_word_b(word);
  printf("Op: 0x%02X, A: 0x%02X, B: 0x%02X\n",
				 code_word_op(word),
				 get_value(&a),
				 get_value(&b));*/
	printf("A: 0x%04X\n", registers[REG_A]);
	vm_step();
	printf("A: 0x%04X\n", registers[REG_A]);
	vm_step();
	printf("[0x1000]: 0x%04X\n", mem_get(0x1000));
	vm_step();
	printf("A: 0x%04X\n", registers[REG_A]);
	vm_step();
  return 0;
}
