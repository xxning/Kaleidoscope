
public class GreatCircle {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
       System.out.print("java GreatCircle "+args[0]);
       System.out.print(" "+args[1]);
       System.out.print(" "+args[2]);
       System.out.println(" "+args[3]);
       double x1,x2,y1,y2;
       x1=Math.toRadians(Double.parseDouble(args[0]));
	   y1=Math.toRadians(Double.parseDouble(args[1]));
	   x2=Math.toRadians(Double.parseDouble(args[2]));
	   y2=Math.toRadians(Double.parseDouble(args[3]));
		double distance=60*Math.toDegrees(Math.acos(Math.sin(x1)*Math.sin(x2)
				+Math.cos(x1)*Math.cos(x2)*Math.cos(y1-y2)));
		
		System.out.println(distance+" nautical miles");
       
       
	}

}
