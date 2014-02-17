
class Block {
   protected int blockNo;
   protected boolean isFree;
   protected static Block blocks[];
   protected static int numBlocks;
   public static final int NUM_BLOCKS = 7000;
   public static final int NUM_INODES = 50; 
   public static DirectoryBlock rootDirectoryBlock;
   public static Inode rootInode;
        
   public static void init()
   {
      blocks = new Block[NUM_BLOCKS];
      for(int i=0; i< NUM_INODES; i++)
         blocks[i]= new Inode(i,i,true);
      numBlocks = NUM_INODES;
      int k = Block.newInode();
      rootInode = (Inode)Block.getBlock(k);
      int j = Block.newDirectoryBlock();
      rootDirectoryBlock = (DirectoryBlock)Block.getBlock(j);
      rootInode.addBlock(rootDirectoryBlock.getBlockNo());
   }  
     
   public Block(int bNo)
   {
      blockNo = bNo;
      isFree = true;
   }   
   
   public Block(int bNo, boolean isFree)
   {
      blockNo = bNo;
      this.isFree = isFree;
   }

   public static int newAddressBlock()
   {
      if (numBlocks < NUM_BLOCKS)
      {
         blocks[numBlocks] = new AddressBlock(numBlocks,false);
         return numBlocks++;
      }
      else {
        for(int i=NUM_INODES; i<NUM_BLOCKS; i++)
           if (blocks[i].isFree())
           {
              blocks[i] = new AddressBlock(i,false);
              return i;
           }   
      }    
      return -1;
   }   

   public static int newDataBlock()
   {
      if (numBlocks < NUM_BLOCKS)
      {
         blocks[numBlocks] = new DataBlock(numBlocks,false);
         return numBlocks++;
      }
      else {
        for(int i=NUM_INODES; i<NUM_BLOCKS; i++)
           if (blocks[i].isFree())
           {
              blocks[i] = new DataBlock(i,false);
              return i;       
           }   
      }   
      return -1;
   }   

   public static int newInode()
   {
     for(int i=0; i<NUM_INODES; i++)
        if (blocks[i].isFree())
        {
           blocks[i].setNotFree();
           return i;
        }        
     return -1;   
   }
  
   public static int newDirectoryBlock()
   {
      if (numBlocks < NUM_BLOCKS)
      {
         blocks[numBlocks] = new DirectoryBlock(numBlocks,false);
         return numBlocks++;
      }
      else {
        for(int i=NUM_INODES; i<NUM_BLOCKS; i++)
           if (blocks[i].isFree())
           {
              blocks[i] = new DirectoryBlock(i,false);
              return i;       
           }   
      }   
      return -1;
   }
   
   public static Block getBlock(int bNo)
   {
      if (bNo < numBlocks)
         return blocks[bNo];
      else return null;   
   }
   
   
   public int getBlockNo()
   {
      return blockNo;
   }
   
   public void setBlockNo(int bNo)
   {
      if (bNo >= 0 && bNo < NUM_BLOCKS)
         blockNo = bNo;
   }
   
   public void setNotFree()
   {
      isFree = false;
   }
   
   public boolean isFree()
   {
     return isFree;
   }  
}
