
class DataBlock extends Block {
   protected byte[] data;
   protected int numBytes;
   protected static final int NUM_BYTES = 20;
   
   public DataBlock(int bNo)
   {
     super(bNo);
     data = new byte[NUM_BYTES];
     numBytes = 0;
   }


   public DataBlock(int bNo, boolean isFree)
   {
     super(bNo,isFree);
     data = new byte[NUM_BYTES];
     numBytes = 0;
   }
   
   public boolean isFull()
   {
      return (numBytes == NUM_BYTES);
   }
   
   public boolean addByte(byte b)
   {
     if (numBytes < NUM_BYTES - 1)
     {
        data[numBytes++] = b;
        return true;
     }
     return false;   
   }
   
   public int addBytes(byte[] b)
   {
      int i;
      for(i=0; numBytes < NUM_BYTES && i<b.length; i++)
         data[numBytes++] = b[i];
      return i;    
   }

   public int addBytes(byte[] b, int pos)
   {
      int i;
      for(i=pos; numBytes < NUM_BYTES && i<b.length; i++)
         data[numBytes++] = b[i];
      return i-pos;    
   }
   
   public byte[] getBytes()
   {
      if (numBytes == 0)
         return null;
      else 
      {   
         byte[] result = new byte[numBytes];
         for(int i=0; i<numBytes; i++)
            result[i] = data[i];
         return result;
      }      
   }
   
   public void setFree()
   {
     numBytes = 0;
     isFree = true;
   }
}
