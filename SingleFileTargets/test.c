
#include <stdio.h>
#include <stdlib.h>

typedef struct MyStruct MyStruct;

int main() {
	MyStruct* ss = malloc(sizeof(int));
	*(int *)ss = 5;
	printf("%d", *(int *)ss);
	free(ss);
	return 0;
}