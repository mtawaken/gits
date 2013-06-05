/*
ID: mtawaken
LANG: JAVA
TASK: friday
 */

import java.io.*;
import java.util.*;

public class friday {
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(new FileReader("friday.in"));
		PrintWriter pw = new PrintWriter(new FileWriter("friday.out"));
		int N = scanner.nextInt();
		int[] monthDays = new int[]{31,28,31,30,31,30,31,31,30,31,30,31};
		int[] appear = new int[7];
		int now = 13%7;
		appear[now]++;
		for(int year=1900;year<1900+N;year++){
			for(int month=0;month<12;month++){
				now+=monthDays[month];
				if(month==1&&(year%400==0||(year%100!=0&&year%4==0))){
					now++;
				}
				now=now%7;
				if(year==1899+N&&month==11){
					break;
				}
				appear[now]++;
			}
		}
		pw.print(appear[6]);
		for(int i=0;i<6;i++){
			pw.print(" "+appear[i]);
		}
		pw.println();
		scanner.close();
		pw.close();
		System.exit(0);
	}
	
}
