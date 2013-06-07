/*
ID: mtawake3
LANG: JAVA
TASK: namenum
 */
import java.util.*;
import java.io.*;

public class namenum {
  static boolean has = false;
	public static void main(String args[]) throws IOException {
		String[] keypad = new String[] { "", "", "ABC", "DEF", "GHI", "JKL",
				"MNO", "PRS", "TUV", "WXY" };
		Scanner input = new Scanner(new FileReader("namenum.in"));
		PrintWriter output = new PrintWriter(new BufferedWriter(new FileWriter(
				"namenum.out")));
		String number = input.nextLine();
		input = new Scanner(new FileReader("dict.txt"));
		HashSet<String> set = new HashSet<String>();
		while (input.hasNext()) {
			set.add(input.nextLine());
		}
		translateChar(keypad, number, 0, "", set, output);
		if(!has){
			output.println("NONE");
		}
		input.close();
		output.close();
		System.exit(0);
	}

	public static void translateChar(String[] keypad, String number,
			int position, String translated, HashSet<String> set, PrintWriter pw) {
		if (position >= number.length()) {
			if (set.contains(translated)) {
				pw.println(translated);
				has = true;
			}
			return;
		}
		int num = number.charAt(position) - '0';
		for (int i = 0; i < keypad[num].length(); i++) {
			translateChar(keypad, number, position + 1, translated
					+ keypad[num].charAt(i), set, pw);
		}
	}
}
