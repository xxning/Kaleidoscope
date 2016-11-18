
public class RandomWalkers {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int a=Integer.parseInt(args[0]);
		int b=Integer.parseInt(args[1]);
		System.out.print(a);
		System.out.println(" "+b);
		
		double d[]=new double[b];
		int i,j,x=0,y=0;
		double m;
		for(j=0;j<b;j++){
		   for(i=1;i<=a;i++){
			  m=Math.random();
	    	  if(m>=0&&m<=0.25){
	    		  y++;	    		
	    	     }
	    	
	    	  else if(m>0.25&&m<=0.50){
	    		  y--;
	    	     }
	    	
	    	  else if(m>0.50&&m<=0.75){
                  x--;
	    	     }
	    	
	    	  else
	    	      x++;
	    	}
		      d[j]=x*x+y*y;
	    	  x=0;y=0;
	       
			
		}
		    double sum=0;
	        for(i=0;i<b;i++) sum+=d[i];
	        
	        sum=sum/b;
	        System.out.println("mean squared distance ="+sum);
	}

}
