
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

  char commandLine[COMMAND_LINE_LENGTH+1]; 
  
  char *pipes[MAX_NUM_PIPES]; //array len MAX_NUM_PIPES of ptr to char
  
  printf("Welcome to Extremely Simple Shell\n");

  int exit= 0;
  
  loop:
  
  do { 
      int status;
      char *temp[MAX_NUM_ARGS];
      
      /* Prints the command prompt */
      printf("\n$ ");
      
      /* Reads the command line and stores it in array commandLine */
      getLine(commandLine,COMMAND_LINE_LENGTH+1);

      /* The user did not enter any commands */
      if (!strcmp(commandLine,""))
         continue;
      
      /* Breaks the command line into arguments and stores the arguments in arguments array */
      int numPipes = getPipes(commandLine,pipes);
      
      
      char ***arguments; //ptr to array of ptrs each of which is itself a ptr to array of ptrs to char arrays/ptrs (the actual commands)
      arguments = malloc(numPipes * sizeof(char **)); //each element in the first level is a ptr to array of ptrs which each point to the 								actual commands
      
      for(int i = 0; i < numPipes; i++){
      
      	numArgs = getArguments(pipes[i],temp);
      	arguments[i] = malloc(numArgs * sizeof(char *)); //each element in the second level pts to a command/arg
      	
      	for(int j = 0; j < numArgs; j++){
      	
      		arguments[i][j] = malloc(strlen(temp[j]) * sizeof(char)); // element in the 3rd level is an actual command/array of chars
      		strcpy(arguments[i][j], temp[j]);
      		//printf("%s ", arguments[i][j]);
	        //scans the commands in all pipes and terminates the program when the user types exit or quit 
	        if (!strcmp(arguments[i][j],"quit") || !strcmp(arguments[i][j],"exit"))
 	      	  return(0);
         	      	
      	}
      	
        
      }
      
      
      int fd[2];
      pipe(fd);
      char *buf[1000*MAX_NUM_ARGS];
      for(int i = 0; i < numArgs; i++){//initialize buf with first set of arguments
      
      	strcpy(buf[i], arguments[0][i]);
      
      }

      for(int i = 0; i < numPipes; i++){
      	
      
      	
		      // Creates a child process 
		      int pid = fork();
		      
		      switch (pid)
		      {
			  case 0: //Executed by the child process only 

				  close(fd[0]); // child writes to pipe so read end is closed
				  dup2(fd[1], STDOUT_FILENO); //stdout file descriptor is re-aliased to pipe write end so output of exec is sent there
				  execvp(arguments[i][0], buf);				  
				  perror("Exec error\n");
				  break;
			  
			  case -1: // Executed only when the fork system call fails 
				  
				  perror("Fork error\n");
				  break;
			  
			  default: // parent reads  
				  
				  close(fd[1]); // parent reads from pipe so write end is closed
				  //write from pipe to buf
				  char temp_commandLine[1000*COMMAND_LINE_LENGTH+1]; 
				  while (read(fd[0], &temp_commandLine, 1) > 0);
         			  getArguments(temp_commandLine, buf);				  
			
				  wait(&status);
				  break;        
		      
		      }  	
      	
      	
      	
      
      
      }

      
      
  }
  while (1); /* Use int values to represent boolean in C language: 0 denotes false, non-zero denotes true */


  return 0;
}

/* Breaks the string pointed by str into pipes and stores them in the arg array*/
int getPipes(char *str, char *arg[])
{
     char delimeter[] = "|";
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
