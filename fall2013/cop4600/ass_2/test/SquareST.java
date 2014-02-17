
import java.io.*;

/* Reads int values from the input file, computes the square value, and writes it to the output file */

public class SquareST {

    public static void main(String[] argsv)
    {
        long start, end; 

        start = System.nanoTime();

        DataInputStream input = null;
        DataOutputStream output = null;
      
	try {
            System.out.println("Opening " + argsv[0] + " for input.."); 
            input = new DataInputStream(new BufferedInputStream(new FileInputStream(argsv[0])));
          
            System.out.println("Opening " + argsv[1] + " for output.."); 
            output = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(argsv[1])));        

            while (true)
	    {
	       int x = input.readInt();
               x = x * x;
               output.writeInt(x);                 
	     }
         }
	catch (FileNotFoundException e) {
	    System.out.println(e);
        }
        catch (EOFException e) {
            System.out.println("Finished reading from the input file");
	}
        catch (IOException e) {
            System.out.println(e); 
	} 


        try {
	    input.close();
            output.close();
            end = System.nanoTime();
            System.out.println("Time elapsed= " + (end-start)/1000000.0 + " milli seconds");
        }
        catch (IOException e) {
           System.out.println(e);   
	} 
    }
}