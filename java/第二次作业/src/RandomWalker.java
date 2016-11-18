
public class RandomWalker {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int a=Integer.parseInt(args[0]);
	    int i,j;
	    double m;
	    int x=0,y=0;
	    for(i=1;i<=a;i++){
	    	m=Math.random();
	    	if(m>=0&&m<=0.25){
	    		y++;
	    		System.out.println("("+x+","+y+")");
	    	   }
	    	
	    	else if(m>0.25&&m<=0.50){
	    		y--;
	    		System.out.println("("+x+","+y+")");
	    	   }
	    	
	    	else if(m>0.50&&m<=0.75){
	    		x--;
	    		System.out.println("("+x+","+y+")");
	    	   }
	    	
	    	else
	    	    {x++;System.out.println("("+x+","+y+")");}
	    	
	    	
	    	}
	        j=x*x+y*y;
    	    System.out.println("squared distance ="+j);
	    		
	    	
	    }
	}


