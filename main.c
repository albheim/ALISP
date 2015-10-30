#include <stdio.h>

int main()
{
	char* buffer;
	int parencnt;
	int c, n;

	buffer = malloc(1024);




	printf("Albin interactive promt, the REPLY\n");

	while (1) {
		parentcnt = 0;
		n = 0;
		printf(">> ");
		while (parencnt > 0) {
			c = getchar();
			if (c == EOF) {
				printf("Bye bye\n");
				exit(1);
			}
			buffer[n++] =

