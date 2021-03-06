import java.awt.Color;

public class PhotoMagic {
	public static Picture transform(Picture picture, LFSR lfsr) {
		Picture res= new Picture(picture.width(),picture.height());
		for (int x=0; x<picture.width(); x++)
			for (int y=0; y<picture.height();y++) {
				Color c=picture.get(x,y);
				int r=c.getRed(), 
					g=c.getGreen(),
					b=c.getBlue();
				r^=lfsr.generate(8);
				g^=lfsr.generate(8);
				b^=lfsr.generate(8);
				res.set(x,y,new Color(r,g,b));
			}
		return res;
	}
	
	public static void main(String arg[]) {
		String filename=arg[0];
		String bits=arg[1];
		int tap=Integer.parseInt(arg[2]);
		LFSR lfsr=new LFSR(bits, tap);
		Picture pic= new Picture(filename);
		Picture result=transform(pic, lfsr);
		result.show();
	}
}