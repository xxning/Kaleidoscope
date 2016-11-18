import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class ScannerTest
{
	 public static void main(String[]a) throws FileNotFoundException
	 {
		 
		 List<Integer> l = new ArrayList<Integer>();
		 l.add(1);
		 l.add(3);
		 l.add(4);
		 l.add(2);
		 l.remove(new Integer(2));
		 System.out.println(l);
	 }
}
