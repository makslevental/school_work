
class Inode extends Block {
   protected int inodeNo;
   protected boolean isDirectory;
   protected int blockAddress[];
   protected int numBlockAddresses;
   protected int singleIndirectAddress;
   // counter and flag to keep track of sym and hardlinks
   protected int linkCount;
   protected boolean isLink;
   protected static final int NUM_DIRECT_ADDRESSES = 5;
   
   public Inode(int bNo, boolean isFree)
   {
     super(bNo,isFree);
     inodeNo = -1;
     numBlockAddresses = 0;
     isLink = false;
     blockAddress = new int[NUM_DIRECT_ADDRESSES];
     singleIndirectAddress = -1;
     isDirectory = false;
   }
         
   public Inode(int bNo, int inodeNo,boolean isFree)
   {
     super(bNo,isFree); 
     this.inodeNo = inodeNo;
     numBlockAddresses = 0;
     isLink = false;
     blockAddress = new int[NUM_DIRECT_ADDRESSES];
     singleIndirectAddress = -1;
     isDirectory = false;
   }
   
   public int getInodeNode()
   {
      return inodeNo;
   }
   // method used by symlink 
   public void setLink(){
      this.isLink = true;
   }
   // method used in stat -l 
   public boolean getLink(){
      return isLink;
   }

   public void setInodeNo(int inodeNo)
   {
      this.inodeNo = inodeNo;
   }
   
   public boolean addBlock(int bNo)
   {
      if (numBlockAddresses < NUM_DIRECT_ADDRESSES)
      {
         blockAddress[numBlockAddresses++] = bNo;
         return true; 
      }   
      else if (singleIndirectAddress !=-1)
      {
         AddressBlock a = (AddressBlock)Block.getBlock(singleIndirectAddress);
         return a.addAddress(bNo);                 
      }    
      else {
         singleIndirectAddress = Block.newAddressBlock();
         AddressBlock a = (AddressBlock)Block.getBlock(singleIndirectAddress);
         return a.addAddress(bNo);
      }
   }
   
   public int[] getBlockAddresses()
   {
      if (numBlockAddresses == 0 && singleIndirectAddress == -1)
         return null;
      else if (singleIndirectAddress == -1)
      {
         int[] a = new int[numBlockAddresses];
         for(int i=0; i<numBlockAddresses; i++)
            a[i] = blockAddress[i];
         return a;
      }   
      else {
         AddressBlock a = (AddressBlock)Block.getBlock(singleIndirectAddress);
         int[] a1 = a.getAddresses(); 
         int[] addresses = new int[a1.length+numBlockAddresses];         
         int i,j;
         for(j=0; j<numBlockAddresses; j++)
            addresses[j] = blockAddress[j];    
         for(i=0; i<a1.length; i++)
            addresses[j++] = a1[i];
         return addresses;   
      }
         
   }
   
   /* Returns number of blocks */   
   public int getSize()
   {
      if (singleIndirectAddress == -1)
         return numBlockAddresses;
      else {
         AddressBlock a = (AddressBlock)Block.getBlock(singleIndirectAddress);
         return numBlockAddresses + a.getNumAddresses();
      }    
   }
   
   public void setFree()
   {
      numBlockAddresses = 0;
      singleIndirectAddress = -1;
      isFree = true;
      isDirectory = false;
   }
   
   
   public int getSingleIndirectBlockNo()
   {
     return singleIndirectAddress;
   }
 
 
   public void setDirectory()
   {
      isDirectory = true;
   }   
   
   public boolean isDirectory()
   {
      return isDirectory;
   }
}
