
class LFSR {
	
	   
	    private int N;      
	    private int[] reg;   
	    private int tap;     

	   
	    public LFSR(String seed, int t) {
	        N=seed.length();
	        reg=new int[N];
	        tap=t;
	        for(int i=0;i<N;i++){
	        	char s=seed.charAt(N-i-1);
	        	if(s=='1')reg[i]=1;
	        	else      reg[i]=0;
	        }
	    }
	  
	    // simulate one step and return the new bit as 0 or 1
	    public int step() {
	        int a=reg[N-1];
	        int b=reg[tap];
	        for(int i=N-1;i>=1;i--){
	        	reg[i]=reg[i-1];
	        }
	        if(a==b)reg[0]=0;
	        else    reg[0]=1;
	        return reg[0];
	    }
	  
	    
	    public int generate(int k) {
	    	int r=0;
			for (int i=0; i<k; i++) {
				r=r*2+step();
			}
			return r;
	    }

	    
	    public String toString()  {
	    	String s="";
	        for(int i=N-1;i>=0;i--){
	        	if(reg[i]==1)s=s+'1';
	        	else         s=s+'0';
	        }
	        return s;	
	    }	  
	    
	    public static void main(String arg[]) {
	    	
	    }
}

