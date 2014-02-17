
class DirectoryBlock extends Block {
      protected int[] inodeNo;
      protected String[] name;
      protected int numEntries;
      public static final int NUM_ENTRIES = 100;
      public DirectoryBlock(int bNo)
      {
         super(bNo);
         numEntries = 0;
         inodeNo = new int[NUM_ENTRIES];
         name = new String[NUM_ENTRIES];
      }
      
      public DirectoryBlock(int bNo, boolean isFree)
      {  
         super(bNo,isFree);
         numEntries = 0;
         inodeNo = new int[NUM_ENTRIES];
         name = new String[NUM_ENTRIES];
      }
                         
      public boolean addEntry(String name, int iNo)
      {
         if (numEntries < NUM_ENTRIES)
         {
             inodeNo[numEntries] = iNo;
             this.name[numEntries] = name;
             numEntries++;
             return true;
         }  
         else return false;
      }                    
      
      public boolean entryExists(String name, int iNo)
      {
         for(int i=0; i<numEntries; i++)
            if (inodeNo[i] == iNo && this.name[i].equals(name))
               return true;
         return false;      
      }               
      
      public int getInode(String name)
      {
         for(int i=0; i<numEntries; i++)
            if (this.name[i].equals(name))
               return inodeNo[i];
         return -1;      
      } 
 
      public boolean isFull()
      {
        return (numEntries == NUM_ENTRIES);
      }
      
      public void setFree()
      {
        numEntries = 0;
        isFree = true;
      }
      
      public void removeEntry(String file, int iNo)
      {

         int index = -1;
         for(int i=0; i<numEntries; i++)
         {
            if (name[i].equals(file) && iNo == inodeNo[i])
            {
               index = i;
               break;
            }   
         }
         if (index != -1)
         {
            for(int i=index+1; i<numEntries; i++)
            {
               name[i-1] = name[i];
               inodeNo[i-1] = inodeNo[i];
            }
            numEntries--;   
         }
      }
      
      public String[] getNames()
      {
         String[] r = new String[numEntries];
         for(int i=0; i<numEntries; i++)
            r[i] = name[i];
         return r;   
      }
      
      public int[] getInodes()
      {
         int[] r = new int[numEntries];
         for(int i=0; i<numEntries; i++)
            r[i] = inodeNo[i];
         return r;   
         
      }
      
      public void print()
      {
         for(int i=0; i<numEntries; i++)
         {
             System.out.println(name[i]+ " "+inodeNo[i]);
         }
      }
}
