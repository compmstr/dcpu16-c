#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void ltrim(char *s){
	char *cpy = s;
	int i = 0;

	while(isspace(*cpy)){
		cpy++;
	}
	while(cpy[i]){
		s[i] = cpy[i];
		i++;
	}
	s[i] = '\0';
}

void rtrim(char *s){
	char *end = s + (strlen(s) - 1);
	while(isspace(*end)){
		*end-- = 0;
	}
}
void remove_string_ends(char *str){
	char *cur = str + 1;
	while(*cur){
		*(cur - 1) = *cur;
		cur++;
	}
	*(cur - 2) = 0;
}

int main(int argc, char **argv){
	//char *buf = 0;
	//size_t buf_size;
	//int args;
	//int num;
	
	//printf("Enter a dat line with hex: ");
	//getline(&buf, &buf_size, stdin);
	/* %i reads 0x... as hex 0... as oct */
	//sscanf(buf, "%i", &num);
	//printf("Num: %d\n", num);
	//free(buf);

	char s1[] = "   foo bar   ";
	char s2[] = "foo bar";
	printf("ltrim tests---\n");
	ltrim(s1);
	ltrim(s2);
	rtrim(s1);
	rtrim(s2);
	printf("\"%s\"\n", s1);
	printf("\"%s\"\n", s2);

	char s3[] = "[hello]";
	char s4[] = "hello there";
	remove_string_ends(s3);
	remove_string_ends(s4);
	printf("\"%s\"\n", s3);
	printf("\"%s\"\n", s4);

  return 0;
}
