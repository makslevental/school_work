
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_LINE_LENGTH 200
#define COMMAND_LENGTH 10
#define MAX_NUM_ARGS 10
#define MAX_NUM_PIPES 10
/* Breaks the string pointed by str into words and stores them in the arg array*/
int getArguments(char *,char *[]);

/* Breaks the string pointed by str into pipes and stores them in the arg array*/
int getPipes(char *,char *[]);

/* Reads a line and discards the end of line character */
int getLine(char *str,int max);

int numArgs = 0;
/* Simulates a shell, i.e., gets command names and executes them */
int main(int argc, char *argv[])
{
	int fd[2];
	pipe(fd);
	printf("%d %d", fd[0], fd[1] );
}