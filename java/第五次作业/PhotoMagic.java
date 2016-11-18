import java.awt.Color;

public class PhotoMagic {
	public static Picture transform(Picture picture, LFSR lfsr) {
		Picture dst= new Picture(picture.width(),picture.height());
		for (int i=0; i<picture.height(); i++)
			for (int j=0; j<picture.width(); j++) {
				Color c=picture.get(j, i);
				int r=c.getRed(), g=c.getGreen(), b=c.getBlue();
				r^=lfsr.generate(8);
				g^=lfsr.generate(8);
				b^=lfsr.generate(8);
				dst.set(j, i, new Color(r,g,b));
			}
		return dst;
	}
	
	public static void main(String arg[]) {
		String filename=arg[0];
		String bits=arg[1];
		int tap=Integer.parseInt(arg[2]);
		LFSR lfsr=new LFSR(bits, tap);
		Picture src= new Picture(filename);
		Picture dst=transform(src, lfsr);
		dst.show();
	}
}