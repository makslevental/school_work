#ifndef myexception_ 
#define myexception_ 
#include <iostream>
#include <exception>

using namespace std; 


class illegalParameterValue : public exception 
{  
   public:  
      illegalParameterValue(string theMessage = "Illegal parameter value");
      void outputMessage();
	virtual ~illegalParameterValue() throw();   
	 private:  
      string message;  
};  


class illegalIndex  : public exception
{  
   public:  
      illegalIndex(string theMessage = "Illegal index") ;
      void outputMessage() ;
	virtual ~illegalIndex() throw();   
   private:  
      string message;  
};  


#endif 
