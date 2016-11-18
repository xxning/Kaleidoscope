
public class Province
{
	String name;
	double x[];
	double y[];
	int salary;
	
	@Override
	public boolean equals(Object obj)
	{
		return super.equals(obj);
	}
	public int getSalary()
	{
		return salary;
	}
	public void setSalary(int salary)
	{
		this.salary = salary;
	}
	public String getName()
	{
		return name;
	}
	public void setName(String name)
	{
		this.name = name;
	}
	public double[] getX()
	{
		return x;
	}
	public void setX(double[] x)
	{
		this.x = x;
	}
	public double[] getY()
	{
		return y;
	}
	public void setY(double[] y)
	{
		this.y = y;
	}
	public Province(String name, double[] x, double[] y)
	{
		super();
		this.name = name;
		this.x = x;
		this.y = y;
	}
	
	
	
}
