#include<stdio.h>
#include"vm.h"
#include"compiler.h"

int main(int argc, char **argv){
  /*init_vm();
	printf("A: 0x%04X\n", registers[REG_A]);
	vm_step();
	printf("A: 0x%04X\n", registers[REG_A]);
	vm_step();
	printf("[0x1000]: 0x%04X\n", mem_get(0x1000));
	vm_step();
	printf("A: 0x%04X\n", registers[REG_A]);
	vm_step();

	char *cur_token = 0;
	printf("Loading test.dasm: \n");
	open_input("test.dasm");
	read_input_line();
	printf("%s", input_file_stack->line_buffer);
	read_input_line();
	printf("%s", input_file_stack->line_buffer);
	cur_token = get_next_token();
	printf("Token: %s\n", cur_token);
	free(cur_token);
	cur_token = get_next_token();
	printf("Token: %s\n", cur_token);
	free(cur_token);
	read_input_line();
	printf("%s", input_file_stack->line_buffer);

	cur_token = get_next_token();
	printf("Token: %s\n", cur_token);
	free(cur_token);

	cur_token = get_next_token();
	printf("Token: %s\n", cur_token);
	printf("Token int val: %d\n", get_string_as_number(cur_token));
	free(cur_token);

	read_input_line();
	printf("%s", input_file_stack->line_buffer);
	close_input();*/

	compile_file("test.dasm", "test.dbin");
	
  return 0;
}
