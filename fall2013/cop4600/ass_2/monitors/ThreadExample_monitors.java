// ThreadDemo.java
import java.io.*;
import java.util.concurrent.Semaphore;

public class ThreadExample_monitors{
  
  public static void main(String[] args){

    // instantiate objects that each have run methods that will be the individual threads
    SynchedReadCrunchBuffer srcbuf = new SynchedReadCrunchBuffer();
    SynchedCrunchWriteBuffer scwbuf = new SynchedCrunchWriteBuffer();
    reader read = new reader(srcbuf);
    cruncher crunch = new cruncher(srcbuf, scwbuf);
    writer write = new writer(scwbuf);

    read.start();
    crunch.start();
    write.start();

  }
}

interface Buffer{
  public void set(int value);
  public int get();
  public int readOccupied();
}
// global vars
class Global{

  public static boolean eof = true;
}

// Buffer between reader and cruncher
class SynchedReadCrunchBuffer implements Buffer{
  
  private static int buffer = -1;
  private static int occupiedBuf = 0;
  // set method, encapsulates synchronized write
  public synchronized void set(int value){
    while(occupiedBuf == 1){
      try{wait();}catch(InterruptedException e){e.printStackTrace();}
    }

    buffer = value;
    ++occupiedBuf;
    notify();
  }
  // get method, encapsulates synchronized 
  public synchronized int get(){
    while(occupiedBuf == 0){
      try{wait();}catch(InterruptedException e){e.printStackTrace();}
    }

    --occupiedBuf;
    notify();
    return buffer;
  }
  // public method to check to see if buffer is empty so that while loop can run in cruncher 
  public int readOccupied(){
    return occupiedBuf;
  }

}
// buffer between cruncher and writer
class SynchedCrunchWriteBuffer implements Buffer{
  
  private static int buffer = -1;
  private static int occupiedBuf = 0;
  // set method, encapsulates synchronized write
  public synchronized void set(int value){
    while(occupiedBuf == 1){
      try{wait();}catch(InterruptedException e){e.printStackTrace();}
    }

    buffer = value;
    ++occupiedBuf;
    notify();
  }
  // get method, encapsulates synchronized 
  public synchronized int get(){
    while(occupiedBuf == 0){
      try{wait();}catch(InterruptedException e){e.printStackTrace();}
    }

    --occupiedBuf;
    notify();
    return buffer;
  }
  // public method to check to see if buffer is empty so that while loop can run in writer 
  public int readOccupied(){
    return occupiedBuf;
  }

}

class reader extends Thread{
  private Buffer sharedLocation;
  public reader(Buffer shared){
    super("reader");
    sharedLocation = shared;
  }

  public void run(){
    try{

        // file reading objects
        int temp = 0;
        String listLine;
        FileReader fr = new FileReader("numbers.txt");
        BufferedReader textReader = new BufferedReader(fr);

        // instantiate Global so can access global var globs.eof
        Global globs = new Global();
        // instantiate synched buffer shared by reader and cruncher

        // globs.eof stores boolean result of ((listLine = textReader.readLine()) != null) and listLine actually stores the read line
        while(globs.eof = ((listLine = textReader.readLine()) != null)){
          temp = Integer.parseInt(listLine);
          // begin critical region
          sharedLocation.set(temp);
          // end critical region

        }

    }catch(IOException e){e.printStackTrace();}

  }

}

class cruncher extends Thread{
  private Buffer sharedLocation1;
  private Buffer sharedLocation2;
  public cruncher(Buffer shared1, Buffer shared2){
    super("cruncher");
    sharedLocation1 = shared1;
    sharedLocation2 = shared2;
  }
  public void run(){

    Global globs = new Global();
    // temp variable shared by cruncher and writer
    int temp = 0;


    while(globs.eof || sharedLocation1.readOccupied() > 0){
        // begin first critical region
        temp = sharedLocation1.get();
        // end first critical region
        temp = temp*temp;

        // begin second critical region
        sharedLocation2.set(temp);
        // end second critical region
    }

  }

}

class writer extends Thread{
  private Buffer sharedLocation;
  public writer(Buffer shared){
    super("reader");
    sharedLocation = shared;
  }

  public void run(){
    try{
        int temp = 0;

        // file writing objects        
        FileWriter write = new FileWriter("out.txt", true);
        PrintWriter print_line = new PrintWriter(write);
        Global globs = new Global();
    
        while(globs.eof || sharedLocation.readOccupied() > 0){

          // begin critical region
          temp = sharedLocation.get();
          // end critical region 

          System.err.println(temp);

          print_line.printf("%d,\n", temp);
          
        }

        print_line.close();

    }catch(IOException e){e.printStackTrace();}
  }
}