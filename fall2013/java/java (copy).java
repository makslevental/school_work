/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter3;
import edu.princeton.cs.introcs.*;
import java.awt.Color;
import java.util.*;

public class Chapter3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        /*
        double[] stats = new double[256];
        Picture pic = new Picture(args[0]);
        for(int x = 0; x < pic.width(); x++){
            for(int y = 0; y < pic.height(); y++){
                Color color = pic.get(x, y);
                stats[color.getGreen()]++;
                
            }
        }
        
        StdDraw.setYscale(0, StdStats.max(stats));
        StdStats.plotBars(stats);
        */
        /*
        Picture pic = new Picture(args[0]);
        Picture flipPic = new Picture(pic.width(), pic.height());
        for(int x = 0; x < pic.width(); x++){
            for(int y = 0; y < pic.height(); y++){
                Color color = pic.get(x, y);
                flipPic.set(x, flipPic.height()-y-1, color);
                
            }
        }
        
        flipPic.show();
        */
        /*
        Picture pic = new Picture(args[0]);
        Picture red = new Picture(pic.width(),pic.height());
        Picture green = new Picture(pic.width(),pic.height());
        Picture blue = new Picture(pic.width(),pic.height());
        for(int x = 0; x < pic.width(); x++){
            for(int y = 0; y < pic.height(); y++){
                Color color = pic.get(x, y);
                Color redC = new Color(color.getRed(), 0, 0);
                Color blueC = new Color(0, color.getGreen(), 0);
                Color greenC = new Color(0, 0, color.getBlue());
                red.set(x,y,redC);
                blue.set(x,y,blueC);
                green.set(x,y,greenC);
            }
        }
        red.show();
        blue.show();
        green.show();
        */
        
        
        
        
        
        /*
        double w = Double.parseDouble(args[0]);
        
        Charge[] c = new Charge[4];
        for(int i = 0; i < 4; i++){
            
            c[i] = new Charge(.5 + w*Math.cos(2.*Math.PI*i/4.),.5 + w*Math.sin(2.*Math.PI*i/4.),1.);
            
        }
        double sum = 0;
        for(int i = 0; i < 4; i++){
            
            sum += c[i].potentialAt(.25, .5);
            
        }
        
        StdOut.print(sum);
        */
        /*
        In stream = new In("ecoli.txt");
        
        while(!stream.isEmpty()){
            char ch = stream.readChar();
            if(ch != 'a' && ch != 't' && ch != 'g' && ch != 'c') {System.out.println("false"); break;}
            
            
        }
        */
        /*
        String name = args[0];               // base file name
        int N = Integer.parseInt(args[1]);   // number of fields
        String delimiter = args[2];          // delimiter (comma)

        // create one output stream for each of the N fields
        Out[] out = new Out[N];
        for (int i = 0; i < N; i++) {
            out[i] = new Out(name + i + ".csv");
        }
        
        double max1 = Double.MIN_VALUE;
        double max2 = Double.MIN_VALUE;
        double min1 = Double.MAX_VALUE;
        double min2 = Double.MAX_VALUE;
        // read in the input and divide by field
        In in = new In(name + ".csv");
        int lines = 0;
        while (in.hasNextLine()) {
            String line = in.readLine();
            String[] fields = line.split(delimiter);
            for (int i = 0; i < N; i++) {
                out[i].println(fields[i+4]);
                if(Double.parseDouble(fields[4]) >= max1) max1 = Double.parseDouble(fields[4]);
                if(Double.parseDouble(fields[5]) >= max2) max2 = Double.parseDouble(fields[5]);
                if(Double.parseDouble(fields[4]) <= min1) min1 = Double.parseDouble(fields[4]);
                if(Double.parseDouble(fields[5]) <= min2) min2 = Double.parseDouble(fields[5]);
            }
            lines++;
        }
        
        In[] in1 = new In[2];
        for (int i = 0; i < N; i++) {
             in1[i] = new In(name + i + ".csv");
        }
        
        Draw test = new Draw();
        test.show();
        test.setPenRadius(.25);
        test.point(.5, .5);
        test.point(.5, .75);
        
        int ii = 0;
        
        Draw plot1 = new Draw();
        Draw plot2 = new Draw();
        plot1.setYscale(min1, max1);
        plot2.setYscale(min2, max2);
        plot1.setXscale(0, lines);
        plot2.setXscale(0, lines);
        plot1.setPenColor(Color.RED);
        plot2.setPenColor(Color.BLUE);
        plot1.show();
        plot2.show();
        //you have to show first, then they'll slowly appear on the canvas 
        
        while (in1[0].hasNextLine()) {
            
            
            double tick1 = Double.parseDouble(in1[0].readLine());
            double tick2 = Double.parseDouble(in1[1].readLine());
            
            System.out.println(tick2);
            
            plot1.filledCircle(ii, tick1, (max1-min1)/lines);
            plot2.filledCircle(ii, tick2, (max2-min2)/lines);
            ii++;
        }
        */
        
        In stream = new In("https://en.wikipedia.org/wiki/Slavoj_%C5%BDi%C5%BEek");
        //In stream = new In("ecoli.txt");
        ArrayList<String> charList = new ArrayList<String>();
        int ii = 0;
        while(!stream.isEmpty()){
            String char1 = String.valueOf(stream.readChar());
            if(!charList.contains(char1)) charList.add(char1);
            ii++;
            
        }
        
        stream.close();
        stream = new In("https://en.wikipedia.org/wiki/Slavoj_%C5%BDi%C5%BEek");
        double[] tally = new double[ii];
        int jj = 0;
        while(!stream.isEmpty()){
            String char1 = String.valueOf(stream.readChar());
            int k = charList.indexOf(char1);
            
            tally[k]++;
            jj++;
            
        }
       
        
        double[] tally2 = new double[tally.length];
        for(int i = 0; i < ii; i++){
            
            tally2[i] = tally[i]/ii;
            System.out.println(tally[i] +" "+ tally2[i]);
        }
        
        plotBars1(tally);
        Out out1 = new Out("chars.txt");
        //System.out.println(out1);
        
        out1.print(charList);
    }
    
    public static void plotBars1(double[] a) {
        int N = a.length;
        StdDraw.setXscale(0, N-1);
        StdDraw.setYscale(StdStats.min(a), StdStats.max(a));
        for (int i = 0; i < N; i++) {
            StdDraw.filledRectangle(i, a[i]/2, .25, a[i]/2);
        }
    }
    
}
