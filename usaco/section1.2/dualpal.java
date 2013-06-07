/*
ID: mtawake3
LANG: JAVA
TASK: dualpal
 */
import java.util.*;
import java.io.*;

public class dualpal {
  static char[] mappingNumber = new char[]{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K'};
	public static void main(String args[]) throws IOException {
		Scanner input = new Scanner(new FileReader("dualpal.in"));
		PrintWriter output = new PrintWriter(new BufferedWriter(new FileWriter(
				"dualpal.out")));
		int N = input.nextInt();
		int S = input.nextInt()+1;
		while(N>0){
			int time = 0;
			for(int i=10;i>=2;i--){
				if(isPalindromic(useNumberBase(S,i))){
					time++;
				}
				if(time>=2){
					output.println(S);
					N--;
					break;
				}
			}
			S++;
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
