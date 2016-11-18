
public class RGBtoCMYK {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int r,g,b;
		 r=Integer.parseInt(args[0]);
		 g=Integer.parseInt(args[1]);
		 b=Integer.parseInt(args[2]);
		double w,c,m,y,k;
	     w=Math.max(Math.max(r,g),b)*1.0/255;
         c=(w-(r*1.0/255))/w;
         m=(w-(g*1.0/255))/w;
         y=(w-(b*1.0/255))/w;
         k=1-w;
        System.out.println("cyan="+c);	
        System.out.println("magenta="+m);
        System.out.println("yellow="+y);
        System.out.println("black="+k);
	}

}
