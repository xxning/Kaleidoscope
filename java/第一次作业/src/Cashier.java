
public class Cashier {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int a[]=new int[3];
		a[0]=Integer.parseInt(args[0]);
		System.out.println("> java Cashier"+a[0]) ;
		a[1]=100-a[0];
		System.out.println("Your change of "+a[1]+" cents is given as:");
		
			a[2]=a[0]/25;
			if(a[2]>=2)
			    {System.out.println(a[2]+" Quraters");}
			else
			    {System.out.println(a[2]+" Qurater");}
			a[0]=a[0]-a[2]*25;
			a[2]=a[0]/10;
			if(a[2]>=2)
			    {System.out.println(a[2]+" Dimes");}
			else
				{System.out.println(a[2]+" Dime");}
			a[0]=a[0]-a[2]*10;
			a[2]=a[0]/5;
			if(a[2]>=2)
				{System.out.println(a[2]+" Nickels");}
			else
				{System.out.println(a[2]+" Nickel");}
			a[0]=a[0]-a[2]*5;
			a[2]=a[0];
			if(a[2]>=2)
				{System.out.println(a[2]+" Pennies");}
			else
				{System.out.println(a[2]+" Penny");}
			
				
		

	}

}
