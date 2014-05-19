/*
ID: mtawake3
LANG: JAVA
TASK: palsquare
 */
import java.util.*;
import java.io.*;

public class palsquare {
  static char[] mappingNumber = new char[]{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K'};
	public static void main(String args[]) throws IOException {
		Scanner input = new Scanner(new FileReader("palsquare.in"));
		PrintWriter output = new PrintWriter(new BufferedWriter(new FileWriter(
				"palsquare.out")));
		int base = input.nextInt();
		int square;
		String squareStr;
		for(int n=1;n<=300;n++){
			square = n*n;
			squareStr = useNumberBase(square,base);
			if(isPalindromic(squareStr)){
				output.println(useNumberBase(n,base)+" "+squareStr);
			}
		}
		input.close();
		output.close();
		System.exit(0);
	}
	public static boolean isPalindromic(String str){
		if(str.length()<=1)
			return true;
		for(int i=0;i<str.length()/2;i++){
			if(str.charAt(i)!=str.charAt(str.length()-1-i)){
				return false;
			}
		}
		return true;
	}
	public static String useNumberBase(int number,int base){
		StringBuilder sb = new StringBuilder();
		while(number>0){
			sb.insert(0, mappingNumber[number%base]);
			number = number / base;
		}
		return sb.toString();
	}
}
