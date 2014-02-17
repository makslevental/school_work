
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

long isAddressCow(unsigned long address)
{

      long ret;
      __asm__("mov $312, %rax"); // storing the system call number
      printf("test1");
      __asm__("syscall");
      printf("test2");
      __asm__("mov %rax, -8(%rbp)"); // getting the return value from the stack
      printf("test3");

      return ret;
}
                              
int cowByParent[2000];       
long stuff[1000];
int cowByChild[2000];


void checkCowStatus()
{
   printf("Global variables: cowByParent[0](@%lx)=%d cowByChild[1999](@%lx)=%d\n", 
        (unsigned long)cowByParent,cowByParent[0], (unsigned long)&cowByChild[1999], cowByChild[1999]);
   printf("%lx on a cow page?=%ld\n",(unsigned long)cowByParent,isAddressCow((unsigned long)cowByParent));
   printf("%lx on a cow page?=%ld\n",(unsigned long)&cowByChild[1999],isAddressCow((unsigned long)&cowByChild[1999]));
}
                                        
int main()
{
   /* You should give another name to your semaphore! */
   /* 0600 has RW permission and 0 for initial value of 0 */
   sem_t *parentGoPtr = sem_open("tyavuz_parentGo", O_CREAT, 0600, 0);
   sem_t *childGoPtr = sem_open("tyavuz_childGo", O_CREAT, 0600, 0);
   
   printf("*************PARENT*************\n");
   printf("Creating a child\n");
   int pid = fork();
   if (pid == 0) 
   { // Child
     printf("=============CHILD=============\n");
     checkCowStatus();
     printf("Changing GLOBAL variable at address %lx\n",(unsigned long)&cowByChild[1999]);
     cowByChild[1999] = 10;
     checkCowStatus();
     printf("=============Let me wake up my parent...=============\n");
     sem_post(parentGoPtr);
     sem_wait(childGoPtr);
     printf("=============CHILD again...=============\n");     
     checkCowStatus();
     printf("Changing GLOBAL variable at address %lx\n",(unsigned long)cowByParent);
     cowByParent[0] = 2;
     checkCowStatus();    
     printf("That's all folks\n");
     return 0;           
   }
   else 
   { // Parent
     int status;
     sem_wait(parentGoPtr);
     printf("*************PARENT again...*************\n");
     checkCowStatus();
     printf("Changing GLOBAL variable at address %lx\n",(unsigned long)cowByParent);
     cowByParent[0] = 3;
     checkCowStatus();
     printf("Changing GLOBAL variable at address %lx\n",(unsigned long)&cowByChild[1999]);
     cowByChild[1999] = 11;
     checkCowStatus();     
     printf("*************Let me wake up my child...*************\n");
     sem_post(childGoPtr);
     wait(&status);
   }
   return 0;
}
