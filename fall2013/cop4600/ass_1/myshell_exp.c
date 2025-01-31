/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 0556

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

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
  int i,j; //for loop vars
  
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
      arguments = malloc(numPipes * sizeof(char **)); // each element in the first level is a ptr to array of ptrs which each point to the
      						      // actual commands
      						      
      // these 2 loops fill an array with the commands in the command line.
      // a pipe string is command string that comes before a pipe or after. if no | in command line numPipes = 1
      // array has 1 row for each pipe string. and then each entry in the row for the actual command words

      for(i = 0; i < numPipes; i++){
      	
	// pipe string is passed to getArguments, tokenized, then individual words fill temp. temp will then be copied into the arguments array      	
      	numArgs = getArguments(pipes[i],temp);
      	arguments[i] = malloc(numArgs * sizeof(char *)); //each element in the second level pts to a command/arg
      	
      	for(j = 0; j < numArgs; j++){
      	
      		arguments[i][j] = malloc(strlen(temp[j]) * sizeof(char)); // element in the 3rd level is an actual command/array of chars
      		//actual copying of words into argument array happens here
      		strcpy(arguments[i][j], temp[j]);
      		
	        //scans the commands in all pipes and terminates the program when the user types exit or quit 
	        if (!strcmp(arguments[i][j],"quit") || !strcmp(arguments[i][j],"exit"))
 	      	  return(0);
         	      	
      	}
      	
        
      }
      
      // conditional run only if a pipe is used in the command line. otherwise flow goes to 115, standard execvp
      if(numPipes == 2){
	      //file descriptor array to be used with sys call pipes
	      int fd[2];
	      if(pipe(fd) == -1){ perror("pipe error"); return(1);}
	      //first child, which does the writing to the opened pipe
	      if(fork() == 0){
	      	//std_out is rerouted to pipe read end
	      	dup2(fd[1], STDOUT_FILENO);
	      	//both ends of pipe are now closed. read end because it was never meant to be used and write end because it's
	      	//re-aliased to std_out
	      	close(fd[0]);
	      	close(fd[1]);
	      	//command is executed using first row of arguments array
	      	execvp(arguments[0][0], arguments[0]);
	      	perror("execvp failed");
	      	return(1);         
	      
	      }
	      //second child, which does the reading
	      if(fork() == 0){
	      	//std_in is rerouted to read end of the pipe.
	      	dup2(fd[0], STDIN_FILENO);
	      	//both ends of pipe are now closed. write end because it was never going to be used and read end 
	      	//because it's re-aliased to std_in
	      	close(fd[1]);
	      	close(fd[0]);
	      	//command is executed using second row of arguments array
	      	execvp(arguments[1][0], arguments[1]);
	    	perror("execvp failed");
	      	return(1);
	      	
	      }
	      //parent closes both pipe ends and waits for child processes to terminate. go to is used so that command prompt comes
	      //back up
	      close(fd[0]);
	      close(fd[1]);
	      wait(0);
	      wait(0);
	      goto loop;
      }
      
      else{
      
	      /* Creates a child process */   
	      int pid = fork();
	      
	      switch (pid)
	      {
		  case 0: /* Executed by the child process only */ 
		          execvp(arguments[0][0],arguments[0]);
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
      
  }
  while (1); /* Use int values to represent boolean in C language: 0 denotes false, non-zero denotes true */


  return 0;
}

/* Breaks the string pointed by str into string before pipe and after pipe and stores them in the arg array*/
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
