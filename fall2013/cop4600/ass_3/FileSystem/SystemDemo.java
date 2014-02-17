import java.lang.*;


public class SystemDemo {

   public static void main(String[] args) {

   String [] s1={"Hello","Hai","Hi","Bonjour","Namaste"};  
        String [] s2={"Good morning","Shubhodayam","Shubhodaya"};  
  
        System.arraycopy(s2,0,s1,1,s2.length);  
        System.out.println("");  
          
        for(String str:s1) {  
            System.out.println(str);  
   }
}
}