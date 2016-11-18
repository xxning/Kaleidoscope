import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;


public class Map
{
	HashMap<String, Province> provinces = new  HashMap<String, Province>();
//	List<Province> provinces = new ArrayList<Province>();
	public Map(String path)
	{
		try
		{
			Scanner s = new Scanner(new File(path));
			while(s.hasNext())
			{
				String name = s.next();
				int number = s.nextInt();
				double x[] = new double[number];
				double y[] = new double[number];
				for(int i=0;i<number;i++)
				{
					String line = s.next();
					//136.60,79.31
					String temp[] = line.split(",");
					x[i] = Double.parseDouble(temp[0]);
					y[i] = Double.parseDouble(temp[1]);
				}
				provinces.put(name, new Province(name, x, y));
//				provinces.add(new Province(name, x, y));
			}
		} catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
	}
	
	public void loadSalary(String path)
	{
		try
		{
			Scanner s = new Scanner(new File(path));
			while(s.hasNext())
			{
				String name = s.next();
				int salary = s.nextInt();
				System.out.println(name);
				System.out.println(salary);
				Province p = provinces.get(name);
				p.setSalary(salary);
			}
		} catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
	}
	
	public static void main(String []a)
	{
		Map map = new Map("C:\\Users\\simin\\Desktop\\map.txt");
		System.out.println(map.provinces);
		map.loadSalary("C:\\Users\\simin\\Desktop\\shouru.txt");
		
	}
}
