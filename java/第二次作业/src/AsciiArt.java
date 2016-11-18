
public class AsciiArt {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
       int a=Integer.parseInt(args[0]);
       if(a>=1&&a<=20){
    	   System.out.print("+");
    	   int i,j;
    	   for(i=0;i<a;i++)System.out.print("--");
    	   System.out.println("---+");
    
    	   for(i=0;i<=a;i++){
    		   System.out.print("|");
    		   for(j=a;j>=0;j--){
    			   if(j<i)
    				   System.out.print("/");
    			   else
    				   System.out.print(" ");
    		     }
    	   
    		   System.out.print("*");
    		   
    		   for(j=0;j<=a;j++){
    			   if(j<i)
    				   System.out.print("\\");
    			   else
    				   System.out.print(" ");
    			   
    		     }
    		   System.out.println("|");
    	   }
    	   
    	   for(i=a;i>=0;i--){
    		   System.out.print("|");
    		   for(j=a;j>=0;j--){
    			   if(j<i)
    				   System.out.print("\\");
    			   else
    				   System.out.print(" ");
    		     }
    		   System.out.print("*");
    		   
    		   for(j=0;j<=a;j++){
    			   if(j<i)
    				   System.out.print("/");
    			   else
    				   System.out.print(" ");
    		     }
		   
		        System.out.println("|");
    	     }
    		
    	   System.out.print("+");
    	   for(i=0;i<a;i++)System.out.print("--");
    	   System.out.println("---+");
    	   
    	   for(i=a;i>=0;i--){
    		   System.out.print("|");
    		   for(j=a;j>=0;j--){
    			   if(j<i)
    				   System.out.print("\\");
    			   else
    				   System.out.print(" ");
    		     }
    		   System.out.print("*");
    		   
    		   for(j=0;j<=a;j++){
    			   if(j<i)
    				   System.out.print("/");
    			   else
    				   System.out.print(" ");
    		     }
		   
		        System.out.println("|");
    	     }
    	       
    	       System.out.print("*");
    	       
    	       for(i=0;i<=a;i++){
        		   System.out.print("|");
        		   for(j=a;j>=0;j--){
        			   if(j<i)
        				   System.out.print("/");
        			   else
        				   System.out.print(" ");
        		     }
        	   
        		   System.out.print("*");
        		   
        		   for(j=0;j<=a;j++){
        			   if(j<i)
        				   System.out.print("\\");
        			   else
        				   System.out.print(" ");
        			   
        		     }
        		   System.out.println("|");
        	   }
    	   
    	       System.out.print("+");
        	   for(i=0;i<a;i++)System.out.print("--");
        	   System.out.println("---+");
    		       		       			   
    				   		    				   		    				   		    		   
    		   }
       else
    	  System.out.println("The number must be between 1 and 20.");
    	   }
    }
   
    		   
    		   
       
	


