
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
      //printf("%d sdfsdf", numPipes);
      
      char ***arguments; //ptr to array of ptrs each of which is itself a ptr to array of ptrs to char arrays/ptrs (the actual commands)
      arguments = malloc(numPipes * sizeof(char **)); //each element in the first level is a ptr to array of ptrs which each point to the 								actual commands
      
      for(int i = 0; i < numPipes; i++){
      	//printf("holla");
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
      
      if(numPipes > 1){
	      
	      int fd[numPipes][2];
	      for(int i = 0; i < numPipes; i++){
	      
	      	if(pipe(fd[i]) == -1){ perror("pipe error"); return(1);}  
	     
	      }  
		      
	      for(int i = 0; i < numPipes-1; i++){
	      	      		
	      	     if(fork() == 0){// beginning fork
		     
		     	if(i == 0){
		     	
			      	dup2(fd[0][1], STDOUT_FILENO);
			      	close(fd[0][0]); //close read end
			      	close(fd[0][1]); //close write end because it's already been re-aliased
			      	
			      	execvp(arguments[0][0], arguments[0]);
			      	perror("execvp failed");
			      	return(1);
		     	
		     	}
		     	else if(i == numPipes-2) goto fork2; 
		     	/*else{
		     		
		     		dup2(fd[i][0], STDIN_FILENO); //std_in comes from pipe before
		     		dup2(fd[i+1][1], STDOUT_FILENO); //std_out goes to current
		      				      		      	
			      	execvp(arguments[i][0], arguments[i]);
			      	perror("execvp failed");
			      	return(1);
		     		     	
		     	}*/
		     	
	     	     }
	     	     fork2:
	     	     if(fork == 0){ //end fork
		     	if(i == numPipes-2){
		     	
	     		      	dup2(fd[numPipes-2][0], STDIN_FILENO);
		      		close(fd[i][1]);
			      	close(fd[i][0]);
			      	
			      	execvp(arguments[i+1][0], arguments[i+1]);
			    	perror("execvp failed");
			      	return(1);
			     		
		      	}
		      	else{
		      	
		     		dup2(fd[i][0], STDIN_FILENO); //std_in comes from current pipe
			      	dup2(fd[i+1][1], STDOUT_FILENO); //std_out goes to next pipe
			      	
			      	execvp(arguments[i+1][0], arguments[i+1]);
			      	perror("execvp failed");
			      	return(1);
		      	
		      	
		      	}
		     	
		     	
		     }	
		     
		     close(fd[i][0]);
		     close(fd[i][1]);
		     wait(0);
		     wait(0);
		     //break;
			     	
		  
		     	
		     	
		     	

	      }
	      
      }
      else{
      	      //printf("holla");
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
	      
	
	      
	   
      
  }while (1); /* Use int values to represent boolean in C language: 0 denotes false, non-zero denotes true */
  


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
