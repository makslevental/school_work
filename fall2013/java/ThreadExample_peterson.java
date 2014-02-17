// ThreadDemo.java
import java.io.*;


public class ThreadExample_peterson{
  
  public static void main(String[] args){
    System.out.println(Thread.currentThread().getName());
    
    reader read = new reader();
    cruncher crunch = new cruncher();
    writer write = new writer();

    read.start();
    crunch.start();
    //write.start();


  }
}

class Global{
  public static int x;
  public static int xSqr;
  public static volatile int favoredThread = 1;
  public static volatile boolean t1WantsToEnter = false;
  public static volatile boolean t2WantsToEnter = false;
  public static volatile boolean eof = true;
}

class reader extends Thread{
  public void run(){
    try{
        FileReader fr = new FileReader("numbers.txt");
        BufferedReader textReader = new BufferedReader(fr);
        Global globs = new Global();

        while(globs.eof = (textReader.readLine() != null)){

          globs.t1WantsToEnter = true;
          globs.favoredThread = 2;
          //while(globs.t2WantsToEnter && globs.favoredThread == 2) System.err.println("waiting1"); //busy wait
          while(globs.t2WantsToEnter && globs.favoredThread == 2) ; //busy wait
          //critical region beginning
          
         
          globs.x = Integer.parseInt(textReader.readLine());
          //System.err.println(globs.x + " thread 1");

          globs.t1WantsToEnter = false;
          try{Thread.sleep(1);}catch(InterruptedException e){e.printStackTrace();}
          //System.err.println(globs.x);
          //critical region end
        }
        
    }catch(IOException e){
      e.printStackTrace();
    }
  }
}

class cruncher extends Thread{
  public void run(){

    Global globs = new Global();
    while(globs.eof){

        globs.t2WantsToEnter = true;
        globs.favoredThread = 1;

        //while(globs.t1WantsToEnter && globs.favoredThread == 1) System.err.println("waiting2");
        while(globs.t1WantsToEnter && globs.favoredThread == 1) ;
        //critical region
        globs.xSqr = globs.x*globs.x;
        System.err.println(globs.xSqr);

        globs.t2WantsToEnter = false;
        //critical region end
    }
  }
}

class writer extends Thread{
  public void run(){
    try{
        FileWriter write = new FileWriter("out.txt", true);
        PrintWriter print_line = new PrintWriter(write);
        Global globs = new Global();
        
        //critical region
        print_line.printf("%d,\n", globs.xSqr);
        //critical region end
        System.out.println("hello");
        print_line.close();
    }catch(IOException e){
      e.printStackTrace();
    }
  }

}
