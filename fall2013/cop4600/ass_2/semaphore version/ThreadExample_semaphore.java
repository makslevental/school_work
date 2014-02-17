// ThreadDemo.java
import java.io.*;
import java.util.concurrent.Semaphore;

public class ThreadExample_semaphore{
  
  public static void main(String[] args){

    // instantiate objects that each have run methods that will be the individual threads
    reader read = new reader();
    cruncher crunch = new cruncher();
    writer write = new writer();

    read.start();
    crunch.start();
    write.start();

  }
  }
// global vars
class Global{
  public static int x;
  public static int xSqr;
  public static int temp;
  public static boolean eof = true;
  // read and crunch semaphores
  public static Semaphore valueReadConsumed = new Semaphore(1,true);
  public static Semaphore valueReadProduced = new Semaphore(0,true);
  // crunch and write semaphores
  public static Semaphore valueCrunchedConsumed = new Semaphore(1,true);
  public static Semaphore valueCrunchedProduced = new Semaphore(0,true);
}

class reader extends Thread{
  public void run(){
    try{

        // file reading objects
        String listLine;
        FileReader fr = new FileReader("numbers.txt");
        BufferedReader textReader = new BufferedReader(fr);

        // temp variable shared between reader and cruncher
        int temp = 0;
        // instantiate Global so can access global vars
        Global globs = new Global();
        // globs.eof stores boolean result of ((listLine = textReader.readLine()) != null) and listLine actually stores the read line
        while(globs.eof = ((listLine = textReader.readLine()) != null)){

          temp = Integer.parseInt(listLine);
          // begin critical region
          try{globs.valueReadConsumed.acquire();}catch(InterruptedException e){e.printStackTrace();}
          
          globs.x = temp;
          // end critical region
          globs.valueReadProduced.release();

        }

    }catch(IOException e){e.printStackTrace();}

  }

}

class cruncher extends Thread{
  public void run(){

    Global globs = new Global();
    // temp variable shared by cruncher and writer
    int temp = 0;
    while(globs.eof  || globs.valueReadProduced.availablePermits() > 0){
        // begin first critical region
        try{globs.valueReadProduced.acquire();}catch(InterruptedException e){e.printStackTrace();}
        
        temp = globs.x*globs.x;
        // end first critical region
        globs.valueReadConsumed.release();
        
        try{globs.valueCrunchedConsumed.acquire();}catch(InterruptedException e){e.printStackTrace();} 
        // begin second critical region
        globs.xSqr = temp;
        // end second critical region
        globs.valueCrunchedProduced.release();

    }

  }

}

class writer extends Thread{
  public void run(){
    try{
        
        // file writing objects        
        FileWriter write = new FileWriter("out.txt", true);
        PrintWriter print_line = new PrintWriter(write);
        Global globs = new Global();
    
        while(globs.eof || globs.valueCrunchedProduced.availablePermits() > 0){

          // begin critical region
          try{globs.valueCrunchedProduced.acquire();}catch(InterruptedException e){e.printStackTrace();} 
          
          System.err.println(globs.xSqr);

          print_line.printf("%d,\n", globs.xSqr);
          // end critical region
          globs.valueCrunchedConsumed.release();
          
        }

        print_line.close();

    }catch(IOException e){e.printStackTrace();}
  }
}