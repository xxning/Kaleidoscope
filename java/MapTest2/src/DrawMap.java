import java.awt.Color;


public class DrawMap
{
	public static void drawProvince(Province p)
	{
//		System.out.println(p.getSalary());
		int salary = p.getSalary();
		if(salary>20000)
		{
			StdDraw.setPenColor(new Color((salary-20000)/80+50, 0, 0));
		}
		else if(salary!=0)
		{
			StdDraw.setPenColor(new Color(0, (20000-salary)/33+50, 0));
		}
		StdDraw.filledPolygon(p.x, p.y);
	}
	
	public static void drawMap(Map map)
	{
		StdDraw.setXscale(0, 600);
		StdDraw.setYscale(600, 0);
		for(String key:map.provinces.keySet())
		{
			drawProvince(map.provinces.get(key));
		}
//		for(int i=0;i<map.provinces.size();i++)
//		{
//			
//		}
	}
	
	public static void main(String[] args)
	{
		Map map = new Map("C:\\Users\\simin\\Desktop\\map.txt");
		map.loadSalary("C:\\Users\\simin\\Desktop\\shouru.txt");
		drawMap(map);
//		drawProvince(p);
	}

}
