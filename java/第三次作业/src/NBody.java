
public class NBody {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		    double T=Double.parseDouble(args[0]),
			       dt=Double.parseDouble(args[1]);
			int    n=StdIn.readInt();
			double R=StdIn.readDouble();
			
			StdDraw.setXscale(-R, R);
			StdDraw.setYscale(-R, R);
			
			double x[]=new double [10];
			double y[]=new double [10];
			double vx[]=new double [10];
			double vy[]=new double [10];
			double ax[]=new double [10];
			double ay[]=new double [10];
			double mass[]=new double [10];
			String file[]=new String[10];
			
			for (int i=1;i<=n;i++){ 		
			    x[i]=StdIn.readDouble();
			    y[i]=StdIn.readDouble();
			    vx[i]=StdIn.readDouble();
			    vy[i]=StdIn.readDouble();
			    mass[i]=StdIn.readDouble();
			    file[i]=StdIn.readString();
			}		

			int i,j;
			Double G=6.67/Math.pow(10,11);
			StdAudio.play("2001.mid");
			
			for (double t=0;t<=T;t=t+dt){		
			    for (i=1;i<=n;i++){		  
			        ax[i]=0;
			        ay[i]=0;
			          for (j=1;j<=n;j++) 
			        	  if (i!=j){		            
			                Double s=Math.sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			                ax[i]=ax[i]+G*mass[j]/(s*s)*(x[j]-x[i])/s;
			                ay[i]=ay[i]+G*mass[j]/(s*s)*(y[j]-y[i])/s;
			               }
			  }
			  StdDraw.show(30);
			  StdDraw.picture(0,0,"starfield.jpg");
			  for (i=1;i<=n;i++){		  
			      vx[i]=vx[i]+ax[i]*dt;
			      vy[i]=vy[i]+ay[i]*dt;
			      x[i]=x[i]+vx[i]*dt;
			      y[i]=y[i]+vy[i]*dt;
			      
			  	  StdDraw.picture(x[i],y[i],file[i]);		  
			   }
			  
			  
		     }
	  }
}
