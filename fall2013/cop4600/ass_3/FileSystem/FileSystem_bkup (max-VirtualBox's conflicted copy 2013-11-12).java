

import java.io.*;
import java.util.StringTokenizer;
import java.lang.*;

class FileSystem {
      
      static final int MAX_LEVELS = 50; 
      static String[] currentWorkingDirectory;
      static int numLevels; 
      static Inode[] inodePath;
      static Inode currentWorkingDirectoryInode;
      static DirectoryBlock[] directoryBlockPath;
      static DirectoryBlock currentWorkingDirectoryDirNode;
      
      public static void main(String[] args)
      {
         String commandLine;
         
         try {
           currentWorkingDirectory = new String[MAX_LEVELS];
           numLevels = 0;
           System.out.println("Type help to find out the available commands");
           Block.init(); // Initializes file system and creates the root directory
           currentWorkingDirectoryInode = Block.rootInode;
           currentWorkingDirectoryDirNode = Block.rootDirectoryBlock; 
           inodePath = new Inode[MAX_LEVELS+1];
           inodePath[0] = Block.rootInode;
           directoryBlockPath = new DirectoryBlock[MAX_LEVELS+1];
           directoryBlockPath[0] = Block.rootDirectoryBlock; 
           BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
           while (true)
           {
               printWorkingDirectory();
               System.out.print("> ");  
               commandLine = br.readLine(); 
               if(commandLine.trim().equals("")) continue;          
               processCommand(commandLine);               
          }
        }
        catch(IOException e)
        {
           System.out.println(e);
           System.exit(1);
        }             
      }
      
      public static void help()
      {
         System.out.println("Command                    Description");
         System.out.println("======================     ==============================================");         
         System.out.println("help                       Displays commands and their description");
         System.out.println("pwd                        Print working directory");
         System.out.println("touch filename             Create empty file filename in the current working directory");
         System.out.println("cp filename1 filename2     Copy filename1 in the real current working directory to filename2");
         System.out.println("more filename              Display contents of file filename");
         System.out.println("rm filename                Delete file filename"); 
         System.out.println("stat filename              Shows number of blocks and number of links for file filename");
         System.out.println("mkdir dirname              Create firectory dirname");
         System.out.println("ls                         List files in the current working directory");
         System.out.println("cd dirname                 Changes to subdirectory dirname");
         System.out.println("up                         Changes to parent directory");
         System.out.println("ln filename1 filename2     Creates hard link filename 2 to filename1");
         System.out.println("ln -s filename1 filename2  Creates soft link filename 2 to filename1");
         System.out.println("exit                       Terminates the program");    	
         System.out.println("vi filename string         adds string to filename on newline");    	
         
         
      }
      
    public static void processCommand(String line){
       StringTokenizer st = new StringTokenizer(line);
       String [] parameters = new String[st.countTokens()-1];
       String commandName = st.nextToken();
       int count = 0;
       while (st.hasMoreElements()) 
       {
          parameters[count++] = st.nextToken();                
       }
       

       if (commandName.equals("help"))
          help();      
       else if(commandName.equals("num"))
          System.err.println(numLevels);
       else if(commandName.equals("root"))
          toRoot(); 
       else if (commandName.equals("ln")){
         if (count == 3){
             // System.out.println("soft link");
             symLink(parameters[1], parameters[2]);
         }
         else if (count == 2){
             // System.out.println("hard link");
                hardLink(parameters[0], parameters[1]);           
             }
         else
             System.out.println("Usage: ln filename1 filename2 or ln -s filename1 filename2");
       }
       else if (commandName.equals("vi")){
         if(count == 1)
           writeFile(parameters[0], null);
         else if (count == 2)
           writeFile(parameters[0], parameters[1]);
         else 
           System.out.println("Usage: vi filename text");
       }     
       else if (commandName.equals("pwd"))
          printWorkingDirectory();
       else if (commandName.equals("touch"))
       {
          if (count == 1)
              createFile(parameters);
          else System.out.println("Usage: touch filename");     
       }   
       else if (commandName.equals("cp"))
       {
          if (count == 2)
             copy(parameters[0],parameters[1]);
          else System.out.println("Usage: cp filename1 filename2");      
       } 
       else if (commandName.equals("more"))
       {
         if (count == 1)
            showFile(parameters[0]);
         else if(count == 2)
            showFile(parameters[0], true); 
         else System.out.println("Usage: more filename");   
       }
       else if (commandName.equals("rm"))
       {
         if (count == 1)
            deleteFile(parameters[0]);
         else System.out.println("Usage: rm filename");   
       }
       else if (commandName.equals("stat"))
       {
         if (count == 1)
            showInfo(parameters[0]);
         else if(count == 2)
            showInfo(parameters[0], parameters[1]);
         else System.out.println("Usage: stat filename");   
       } 
       else if (commandName.equals("mkdir"))
       {
         if (count == 1)
            createDirectory(parameters[0]);
         else System.out.println("Usage: mkdir dirname");   
       }
       else if (commandName.equals("ls"))
       {
         if (count == 0)
            listDirectory();
         else System.out.println("Usage: ls");   
       }
       else if (commandName.equals("cd"))
       {
         if (count == 1){
            changeWorkingDirectory(parameters);
            
          }
         else System.out.println("Usage: cd dirname");   
       }                                 
       else if (commandName.equals("up"))
       {
         if (count == 0)
            changeWorkingDirectoryToParent();
         else System.out.println("Usage: up");              
       }                                      
       else if (commandName.equals("exit"))
       {
         if (count == 0)
            System.exit(1);
         else System.out.println("Usage: exit");   
       }   
       System.out.println();
    }
      
    public static void printWorkingDirectory(){
       for(int i=0; i<numLevels; i++)         
          System.out.print("/"+currentWorkingDirectory[i]);            
    }  

    public static void createFile(String[] parameters){

       String[] currentDir = new String[1];

       currentDir[0] = currentDirectory();
       String filename = dirPrep(parameters[0]);
       if(filename == null){
         System.err.println("No file name was entered");
         return;
       }
       if (currentWorkingDirectoryDirNode.getInode(filename) != -1)
       {
          System.out.println("File exists!");
          return;
       }

       int i = Block.newInode();
       if (i != -1)
       {
          currentWorkingDirectoryDirNode.addEntry(filename,i);  
          Inode inode = (Inode)Block.getBlock(i);
          int j = Block.newDataBlock();
          if (j != -1)
             inode.addBlock(j);
          else System.out.println("Cannot create file: no available data block");
       }
       else {
          System.out.println("Cannot create file: Maximum file limit reached!");
       }
       toRoot();
       changeWorkingDirectory(currentDir);
    }  

    public static void copy(String file1, String file2){
       String[] currentDir = new String[1];
       int currentDirLevel = numLevels;

       currentDir[0] = currentDirectory();
       String filename1 = dirPrep(file1);
       if(filename1 == null){
         System.err.println("No file name was entered");
         return;
       }
       // System.err.println("blahb" + filename1);

       int m = currentWorkingDirectoryDirNode.getInode(filename1);
       // if file is on the virtual file system
       if (m  != -1){
          Inode inodefile1 = (Inode)Block.getBlock(m); // returns the actual inode 
          if (inodefile1.isDirectory())
          {
              System.out.println(filename1 + " is a directory!");
              return;
          }
          int[] blockAddressesFile1 = inodefile1.getBlockAddresses(); // just addresses to blocks

          toRoot();
          changeWorkingDirectory(currentDir);

          // go to directory where file2 is

          String filename2 = dirPrep(file2);

          if(filename2 == null){
            System.err.println("No file name was entered");
            return;
          }

          int k = currentWorkingDirectoryDirNode.getInode(filename2);
          if (k != -1) {

              Inode temp = (Inode)Block.getBlock(k);
              if (temp.isDirectory())
              {
                  System.out.println(filename2 + " is a directory!");
                  toRoot();
                  changeWorkingDirectory(currentDir);
                  return;
              }

              // new code
              if(temp.getLink()){

                StringBuffer dataBuffer = new StringBuffer();
                int[] blocks = temp.getBlockAddresses();
                for(int count = 0; count<blocks.length; count++)
                {
                  DataBlock datablock = (DataBlock)Block.getBlock(blocks[count]);
                  byte[] b = datablock.getBytes();
                  if (b != null)
                  {
                     dataBuffer.append(new String(b));
                  }   
                }
                filename2 = dirPrep(dataBuffer.toString());
              }

              deleteFile(filename2);
          }
          
          int i = Block.newInode(); // just returns address to next available inode
          if (i != -1){
              currentWorkingDirectoryDirNode.addEntry(filename2,i);
              Inode inodefile2 = (Inode)Block.getBlock(i);
              if(blockAddressesFile1 == null){
                int j = Block.newDataBlock();
                if (j != -1)
                   inodefile1.addBlock(j);
                else System.out.println("Cannot create file: no available data block");
              }
              else{
                for (int count = 0; count < blockAddressesFile1.length; count++) {
                    DataBlock datablock = (DataBlock) Block.getBlock(blockAddressesFile1[count]);
                    byte[] b = datablock.getBytes();
                    if (b != null) {
                        // System.err.println(b);
                        int j = Block.newDataBlock();
                        // System.err.println(j);
                        if (j == -1) {
                            System.out.println("Cannot complete copying: No available data block");
                            break;
                        }
                        if (!inodefile2.addBlock(j)) {
                            System.out.println("Max file size exceeded!");
                            return;
                        }
                        DataBlock datablockfile2 = (DataBlock) Block.getBlock(j);
                        datablockfile2.addBytes(b);
                    }
                }
              }
          }
          else {
            System.out.println("Cannot copy file: Maximum file limit reached!");
          }
          // return from directory where file2 is back to where the call was made from
          // printWorkingDirectory();
          // System.err.println("3nd");
          // System.err.println(numLevels);
          toRoot();
          changeWorkingDirectory(currentDir);

       // if file is on the real file system   
       }
       else{
          try {
            BufferedReader file = new BufferedReader(new FileReader(file1));


            // go to dir where file 2 is
            String filename2 = dirPrep(file2);
            if(filename2 == null){
              System.err.println("No file name was entered");
              return;
            }
            int f = currentWorkingDirectoryDirNode.getInode(filename2);
            if (f != -1) {
                Inode temp = (Inode)Block.getBlock(f);
                if (temp.isDirectory())
                {
                    System.out.println(filename2 + " is a directory!");
                    toRoot();
                    changeWorkingDirectory(currentDir);
                    return;
                }
                deleteFile(filename2);
            }

            if (currentWorkingDirectoryDirNode.getInode(filename2) != -1)
               deleteFile(filename2);
            int i = Block.newInode();
            if (i != -1) {
              currentWorkingDirectoryDirNode.addEntry(filename2,i);
                 String line = null;
                 byte[] data = null;
                 while ( (line = file.readLine()) != null)
                 {
                    byte[] b = (line+"\n").getBytes();
                    if (data == null)
                       data = b;
                    else {
                       int index;
                       byte[] temp = new byte[data.length+b.length];
                       for(index=0; index<data.length;index++)
                          temp[index] = data[index];
                       for(int k=0; k<b.length; k++)
                          temp[index+k] = b[k];
                       data = temp;       
                    }   
                 }
                 Inode inode = (Inode)Block.getBlock(i);
                 int count = 0;
                 while (count < data.length)
                 {   
                    int j = Block.newDataBlock();
                    if (j == -1)
                    {
                       System.out.println("Cannot complete copying: No available data block");
                       break;
                    }
                    if (!inode.addBlock(j))
                    { 
                       System.out.println("Max file size exceeded!");
                       return;
                    }
                    DataBlock datablock = (DataBlock) Block.getBlock(j);   
                    int num = datablock.addBytes(data,count);
                    count += num;
                 }
              }   
            else {
               System.out.println("Cannot create file: Maximum file limit reached!");
            }   
          }
          catch(FileNotFoundException e)
          {
             System.out.println(file1+" could not be found!");
          }      
          catch(IOException e)
          {
             System.out.println(e);
          }
          toRoot();
          changeWorkingDirectory(currentDir);
       }
    }
    public static void showFile(String file){
      showFile(file,false);
    }  
    public static void showFile(String file, boolean link) {

       String[] currentDir = new String[1];
       currentDir[0] = currentDirectory();

       String filename = dirPrep(file);
       if(filename == null){
         System.err.println("No file name was entered");
         return;
       }

       int i = currentWorkingDirectoryDirNode.getInode(filename);
       if (i != -1)
       {
          Inode inode = (Inode)Block.getBlock(i);
          if (inode.isDirectory())
          {
             System.out.println(filename+" is a directory!");
             return;
          }
          StringBuffer dataBuffer = new StringBuffer();
          int[] blocks = inode.getBlockAddresses();
          for(int count = 0; count<blocks.length; count++)
          {
            DataBlock datablock = (DataBlock)Block.getBlock(blocks[count]);
            byte[] b = datablock.getBytes();
            if (b != null)
            {
               dataBuffer.append(new String(b));
            }   
          }

          if(inode.getLink()){
             if(link) System.err.println("full path is " + dataBuffer.toString());
             String filename2 = dirPrep(dataBuffer.toString());
             showFile(filename2);
          }
          else
             System.err.println(dataBuffer.toString());

          toRoot();
          changeWorkingDirectory(currentDir);
       }
       else System.out.println("No such file");
    }
      
    public static void deleteFile(String file){

      String[] currentDir = new String[1];
      currentDir[0] = currentDirectory();

      String filename = dirPrep(file);
      if(filename == null){
        System.err.println("No file name was entered");
        return;
      }

      int i = currentWorkingDirectoryDirNode.getInode(filename);
      if (i != -1)
      {
          Inode inode = (Inode)Block.getBlock(i);
          if (inode.isDirectory())
          {
             System.out.println(filename+" is a directory!");
             return;
          }
          if(inode.linkCount == 0){   
            int[] blocks = inode.getBlockAddresses();
            for(int j=0; j<blocks.length; j++)
                  ((DataBlock)Block.getBlock(blocks[j])).setFree();
            int d = inode.getSingleIndirectBlockNo();   
            if (d != -1)
            {
               AddressBlock ab = ((AddressBlock)Block.getBlock(d));
               int[] addresses = ab.getAddresses();
               for(int j=0; j<addresses.length; j++)
                  ((DataBlock)Block.getBlock(addresses[j])).setFree();  
               ab.setFree();            
            }   
            inode.setFree();
          }
          currentWorkingDirectoryDirNode.removeEntry(filename,i);

          toRoot();
          changeWorkingDirectory(currentDir);
             
      }
      else System.out.println("No such file!");
    }
    
    public static void showInfo(String garbage, String file){

      String[] currentDir = new String[1];
      currentDir[0] = currentDirectory();

      String filename = dirPrep(file);
      if(filename == null){
        System.err.println("No file name was entered");
        return;
      }

      int i = currentWorkingDirectoryDirNode.getInode(filename);
      if (i != -1)
      {
         Inode inode = (Inode)Block.getBlock(i);
         if (inode.isDirectory())
         {
            System.out.println(filename+" is a directory!");
            return;
         }
         int[] blocks = inode.getBlockAddresses();
         for(int count = 0; count<blocks.length; count++)
         {
           DataBlock datablock = (DataBlock)Block.getBlock(blocks[count]);
           byte[] b = datablock.getBytes();
           if (b != null)
           {
              String filename2 = dirPrep(new String(b));
              showInfo(filename2);
           }   
         }
      }

      toRoot();
      changeWorkingDirectory(currentDir);                        

    }
    public static void showInfo(String file){
    
      String[] currentDir = new String[1];
      currentDir[0] = currentDirectory();

      String filename = dirPrep(file);
      if(filename == null){
        System.err.println("No file name was entered");
        return;
      }

      int i = currentWorkingDirectoryDirNode.getInode(filename);
      if (i != -1)
      {
         Inode inode = (Inode)Block.getBlock(i);
         if (inode.isDirectory())
            System.out.print("Directory ");
         else if(inode.getLink())
            System.out.print("SymLink ");
         else System.out.print("Regular file ");   
         System.out.print("InodeNo: "+ inode.getInodeNode() + "	# of data blocks " + inode.getSize() + " # of links: " + inode.linkCount);      
      }
      else System.out.println("No such file");

      toRoot();
      changeWorkingDirectory(currentDir);                  
    }     
      
    public static void createDirectory(String file){
       int i = currentWorkingDirectoryDirNode.getInode(file);
       if (i != -1)
           System.out.println("File exists!");
       else {
          i = Block.newInode();
          if (i == -1)
             System.out.println("Maximum file number reached!");
          else {
              currentWorkingDirectoryDirNode.addEntry(file,i);
              Inode inode = (Inode)Block.getBlock(i);
              inode.setDirectory();
              int j = Block.newDirectoryBlock();
              if (j == -1)
                 System.out.println("Maximum file number reached!");
              else {
                 inode.addBlock(j);                   
              }   
          } 
       }    
    }
      
    public static void listDirectory() {
       String[] names = currentWorkingDirectoryDirNode.getNames();
       int[] inodes = new int[names.length];
       for(int i=0; i<inodes.length; i++)
          inodes[i] = currentWorkingDirectoryDirNode.getInode(names[i]);
       for(int i=0; i<names.length; i++){
         Inode inode = (Inode)Block.getBlock(inodes[i]);
         if(inode.isDirectory()) System.out.println(names[i]+"/");
         else System.out.println(names[i]);
       }
    }

    public static void hardLink(String file1, String file2){

        String[] currentDir = new String[1];
        currentDir[0] = currentDirectory();

        String filename = dirPrep(file1);
        if(filename == null){
          System.err.println("No file name was entered");
          return;
        }
        
        int i = currentWorkingDirectoryDirNode.getInode(filename);

        toRoot();
        changeWorkingDirectory(currentDir);


        filename = dirPrep(file2);
        currentWorkingDirectoryDirNode.addEntry(filename,i);
        Inode inode = (Inode)Block.getBlock(i);
        inode.linkCount++;

        toRoot();
        changeWorkingDirectory(currentDir);
    }

    public static void symLink(String file1, String file2){

      String[] currentDir = new String[1];
      currentDir[0] = currentDirectory();

      String filename = dirPrep(file2);
      if(filename == null){
        System.err.println("No file name was entered");
        return;
      }

       if (currentWorkingDirectoryDirNode.getInode(filename) != -1)
       {
          System.out.println("Link exists!");
          return;
       }

       int i = Block.newInode(); // returns next available inode address
       if (i != -1)
       {

          currentWorkingDirectoryDirNode.addEntry(filename,i);  
          toRoot();
          changeWorkingDirectory(currentDir);


          Inode inode = (Inode)Block.getBlock(i);
          int j = Block.newDataBlock();
          
          if (j != -1){

            filename = dirPrep(file1);
            if(filename == null){
              System.err.println("No file name was entered");
              return;
            }
  
            StringBuffer buffer = new StringBuffer();
            buffer.append(currentDirectory());
         /*   for(int k=0; k<numLevels; k++){            
               buffer.append(currentWorkingDirectory[k]);
               buffer.append("/");
            }  */
            buffer.append(filename);

            toRoot();
            changeWorkingDirectory(currentDir);

            byte[] data = (buffer.toString()).getBytes();
            int count = 0;
            while (count < data.length)
            {   
               int f = Block.newDataBlock();
               if (f == -1)
               {
                  System.out.println("Cannot complete link creation: No available data block");
                  break;
               }
               if (!inode.addBlock(j))
               { 
                 System.out.println("Max file size exceeded!");
                  return;
               }
               DataBlock datablock = (DataBlock) Block.getBlock(j);   
               int num = datablock.addBytes(data,count);
               inode.setLink();
               count += num;
            }
          }
          else System.out.println("Cannot create link: no available data block");
       }
       else {
          System.out.println("Cannot create link: Maximum file limit reached!");
       }
    }

    public static void writeFile(String file1, String text){
      if(text == null){ System.err.println("No text entered"); return;}

      String[] currentDir = new String[1];
      currentDir[0] = currentDirectory();

      String filename = dirPrep(file1);
      if(filename == null){
        System.err.println("No file name was entered");
        return;
      }

      int i = currentWorkingDirectoryDirNode.getInode(filename);
      Inode inode = (Inode)Block.getBlock(i);
      if (i != -1) {

            byte[] data = (text+"\n").getBytes();

            int count = 0;
            while (count < data.length)
            {   
               int j = Block.newDataBlock();
               if (j == -1)
               {
                  System.out.println("Cannot complete writing: No available data block");
                  break;
               }
               if (!inode.addBlock(j))
               { 
                  System.out.println("Max file size exceeded!");
                  return;
               }
               DataBlock datablock = (DataBlock) Block.getBlock(j);   
               int num = datablock.addBytes(data,count);
               count += num;
            }
      }   
      else{
        System.out.println("Cannot create file: Maximum file limit reached!");
      }
      toRoot();
      changeWorkingDirectory(currentDir);   
    }

    public static String[] tokenize(String line){
      // System.err.println("yay");   
      StringTokenizer stLocal = new StringTokenizer(line, "/");
      String [] parametersLocal = new String[stLocal.countTokens()];
      // System.err.println(stLocal.countTokens());   
      int countLocal = 0;
      while (stLocal.hasMoreElements()) 
      {
         parametersLocal[countLocal++] = stLocal.nextToken();
         // System.err.println(parametersLocal[countLocal-1]);    
      }
      return parametersLocal;
    }

    public static void changeWorkingDirectory(String[] parameters){
      if(parameters[0].indexOf("/") > -1)
      {
          String[] parametersLocal = tokenize(parameters[0]);
          for(int ii = 0; ii < parametersLocal.length; ii++){
            changWorkDir(parametersLocal[ii]);
          }
       }
       else changWorkDir(parameters[0]);  
    }
      
    public static void changWorkDir(String file){
      if (file.equals("root")) {
        toRoot();
      }
      else if( file.equals("..")){
        changeWorkingDirectoryToParent();
      }
      else{
        int i = currentWorkingDirectoryDirNode.getInode(file);
        if (i == -1){
           System.err.println(file);
           System.out.println("No such file blah!");
         }
        else {
           Inode inode = (Inode)Block.getBlock(i);
           if (!inode.isDirectory())
              System.out.println("Not a directory!");
           else {
               currentWorkingDirectoryInode = inode;
               int[] b = inode.getBlockAddresses();
               currentWorkingDirectoryDirNode = (DirectoryBlock)Block.getBlock(b[0]); 
               currentWorkingDirectory[numLevels++] = file;
               inodePath[numLevels] = currentWorkingDirectoryInode;
               directoryBlockPath[numLevels] = currentWorkingDirectoryDirNode;
           }   
        }   
      }
    }

    public static int changeWorkingDirectoryToParent(){
         if (numLevels > 0)
         {
             numLevels--;
             currentWorkingDirectoryInode = inodePath[numLevels];
             currentWorkingDirectoryDirNode = directoryBlockPath[numLevels];  
             return 0;
         }
         return -1;
    }

    public static String dirPrep(String file){

      String[] parametersSlashed;
      parametersSlashed = tokenize(file);
      int delims = 0;
      for(int i = 0; i < file.length(); i++){
        if( file.charAt(i) == '/' ) {
            delims++;
        } 
      }
      if(delims>=parametersSlashed.length) return null;
            
      String filename1 = file;


      // go to directory where file1 is

      if(file.indexOf("/") > -1){

               StringBuffer temp = new StringBuffer();
               for(int i = 0; i < parametersSlashed.length-1; i++)
                  temp.append(parametersSlashed[i] + "/");
      
               String[] parametersLocal = new String[1];
               parametersLocal[0] = temp.toString();
               filename1 = parametersSlashed[parametersSlashed.length-1];
               changeWorkingDirectory(parametersLocal);
               
       }
       return filename1;     
    }

    public static String currentDirectory(){

      StringBuffer strbuf = new StringBuffer();
      strbuf.append("root");
      for(int i=0; i<numLevels; i++)         
         strbuf.append("/"+currentWorkingDirectory[i]); 
      strbuf.append("/");
      return strbuf.toString();
    }

    public static void toRoot(){
      while(changeWorkingDirectoryToParent() != -1);
    }
}
