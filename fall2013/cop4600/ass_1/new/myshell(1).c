
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_LINE_LENGTH 200
#define COMMAND_LENGTH 10
#define MAX_NUM_ARGS 10

/* Breaks the string pointed by str into words and stores them in the arg array*/
int getArguments(char *,char *[]);

/* Reads a line and discards the end of line character */
int getLine(char *str,int max);


/* Simulates a shell, i.e., gets command names and executes them */
int main(int argc, char *argv[])
{

  char commandLine[COMMAND_LINE_LENGTH+1]; 
  char *arguments[MAX_NUM_ARGS];
  
  printf("Welcome to Extremely Simple Shell\n");

  int exit= 0;
  do { 
      int status;
      char *temp;
      
      /* Prints the command prompt */
      printf("\n$ ");
      
      /* Reads the command line and stores it in array commandLine */
      getLine(commandLine,COMMAND_LINE_LENGTH+1);

      /* The user did not enter any commands */
      if (!strcmp(commandLine,""))
         continue;
      
      /* Breaks the command line into arguments and stores the arguments in arguments array */
      int numArgs = getArguments(commandLine,arguments);
      
      /* Terminates the program when the user types exit or quit */
      if (!strcmp(arguments[0],"quit") || !strcmp(arguments[0],"exit"))
         break;
         
      /* Creates a child process */   
      int pid = fork();
      
      switch (pid)
      {
          case 0: /* Executed by the child process only */ 
                  execvp(arguments[0],arguments);
                  perror("Exec error\n");
                  break;
          case -1: /* Executed only when the fork system call fails */
                  perror("Fork error\n");
                  break;
          default: /* Executed by parent process only  */
                  wait(&status);
                  break;        
      }
  }
  while (1); /* Use int values to represent boolean in C language: 0 denotes false, non-zero denotes true */


  return 0;
}

/* Breaks the string pointed by str into words and stores them in the arg array*/
int getArguments(char *str, char *arg[])
{
     char delimeter[] = " ";
     char *temp = NULL;
     int i=0;
     temp = strtok(str,delimeter);
     while (temp != NULL)
     {
           arg[i++] = temp;                   
           temp = strtok(NULL,delimeter);
     }
     arg[i] = NULL;     
     return i;
}

/* Reads a line and discards the end of line character */
int getLine(char *str,int max)
{
    char *temp;
    if ((temp = fgets(str,max,stdin)) != NULL)
    {
       int len = strlen(str);
       str[len-1] = '\0';
       return len-1;
    }   
    else return 0;
}
