
public class Sierpinski {
        
	     
	     
	     public static void sierpinski(int n,double x,double y,double sz){
	    	 
	    	 double []a=new double[3];
		     double []b=new double[3];
		     
		     for(int i=0;i<3;i++){
		    	 a[i]=b[i]=0;
		     }
		     
	    	 if(n==0)return;
	    	 
	    	 double x0=x+sz,
	 			    x1=x+sz/2,
					y0=y,
					y1=y-(sz/2)*Math.sqrt(3);
					    	
	    	 StdDraw.line(x,y,x0,y0);
    		 StdDraw.line(x,y,x1,y1);
    		 StdDraw.line(x0,y0,x1,y1);
    		 a[0]=x;   b[0]=y;
    		 a[1]=x0;  b[1]=y0; 
    		 a[2]=x1;  b[2]=y1;
    		 StdDraw.filledPolygon(a,b);
    		 
    		 sierpinski(n-1,x+sz/4,y+(sz/4)*Math.sqrt(3),sz/2);
    		 sierpinski(n-1,x-sz/4,y-(sz/4)*Math.sqrt(3),sz/2);
    		 sierpinski(n-1,x+3*sz/4,y-(sz/4)*Math.sqrt(3),sz/2);
    		 
	     }
	         
	public static void main(String[] args) {
		
		 int n=StdIn.readInt();
		 StdDraw.line(0.0,0.0,1.0,0.0);
		 StdDraw.line(0.0,0.0,0.5,Math.sqrt(3)/2);
		 StdDraw.line(1.0,0.0,0.5,Math.sqrt(3)/2);
		 sierpinski(n,0.25,Math.sqrt(3)/4,0.5);

	}

}
