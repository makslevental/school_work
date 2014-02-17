
import java.io.*;
import java.util.Random;

/* Generates args[1] number of random int and writes it to args[0] */

public class Generate {
 
    public static void main(String[] args)
    {
	try { 

            if (args.length != 2)
	    {
		System.out.println("Expects the following commandline parameters: outputfilename number of ints to be generated");
                return ;
	    }  

            System.out.println("Opening " + args[0] + " for output");
	    DataOutputStream output = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(args[0])));

        
            int num = Integer.parseInt(args[1]);

            System.out.println("Generating " + num + " random integers and writing to " + args[0]); 
            Random gen = new Random();
            for(int i=0; i < num; i++)
	    {
	       int x = gen.nextInt();
               output.writeInt(x);  
	    }
            output.close(); 
        }
        catch(IOException e)
	{
	    System.out.println(e);
	}
    }
}