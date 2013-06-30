import java.io.*;
import java.util.*;

/*
ID: mtawaken
LANG: JAVA
PROG: barn1
 */
/*
 * consider one board cover from minimum to maximum,now we
 * cut M-1 gaps to split one board to M boards. The gaps we choose
 * are biggest gaps using greedy
 * 
 * When facing big problem,
 * try 1. divide to small problems
 * try 2. transform to other problems
 * try 3. choose another view or cutting point
 */
public class barn1 {
  public static void main(String[] args) throws Exception{
		Scanner input = new Scanner(new FileReader("barn1.in"));
		PrintWriter pw = new PrintWriter(new FileWriter("barn1.out"));
		int M = input.nextInt();
		int S = input.nextInt();
		int C = input.nextInt();
		if(M>=C){
			pw.println(C);
			pw.close();
			input.close();
			System.exit(0);
		}
		int minium=S+1;
		int maxium=-1;
		int tmp;
		int[] gaps = new int[C-1];
		int[] stalls = new int[C];
		for(int i=0;i<C;i++){
			input.nextLine();
			stalls[i] = input.nextInt();
		}
		for(int i=0;i<C;i++){
			for(int j=0;j<C-i-1;j++){
				if(stalls[j]>stalls[j+1]){
					tmp = stalls[j];
					stalls[j]=stalls[j+1];
					stalls[j+1]=tmp;
				}
			}
		}
		for(int i=1;i<C;i++){
			gaps[i-1] = stalls[i]-stalls[i-1];			
		}
		
		for(int i=0;i<gaps.length;i++){
			for(int j=0;j<gaps.length-i-1;j++){
				if(gaps[j]<gaps[j+1]){
					int t = gaps[j+1];
					gaps[j+1] = gaps[j];
					gaps[j] = t;
				}
			}
		}
		int totalGap = 0;
		for(int i=0;i<M-1;i++){
			totalGap += gaps[i]-1;
		}
		maxium = stalls[C-1];
		minium = stalls[0];
		pw.println(maxium - minium + 1 -totalGap);
		pw.close();
		input.close();
		System.exit(0);
	}
}
