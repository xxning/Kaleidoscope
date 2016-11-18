
public class SpecDay {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int year=Integer.parseInt(args[0]);
		int month=Integer.parseInt(args[1]);
		int day=Integer.parseInt(args[2]);
		int number=Integer.parseInt(args[3]);
		System.out.print("> java SpecDay ");
		System.out.print(year+" ");
		System.out.print(month+" ");
		System.out.print(day+" ");
		System.out.println(number);
		
		int days[][]={
				{0,31,28,31,30,31,30,31,31,30,31,30,31},
				{0,31,29,31,30,31,30,31,31,30,31,30,31},
		  };
		int m=100*number-1;
		int i;
		if((year%4==0&&year%100!=0)||year%400==0)
		i=1;
		else i=0;
		m=m-days[i][month]+day;
		if(month==12){
			month=1;
			year++;
		}
		else month++;
		
				
		do{
			if(month>12){
				month=1;
				year++;}
			if((year%4==0&&year%100!=0)||year%400==0)
				i=1;
			else i=0;
			m=m-days[i][month];
			month++;	
			
		}while(m>=31);
		    if(m<days[i][month])
		    	day=m;
		    else{
		    	day=m-days[i][month];
		        month++;
		    }
		    System.out.println("Year:"+year);
		    System.out.println("Month:"+month);
		    System.out.println("Day:"+day);
		}
	}


