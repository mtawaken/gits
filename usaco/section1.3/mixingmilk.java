import java.io.*;
import java.util.*;

/*
ID: mtawaken
LANG: JAVA
PROG: milk
 */
/*
 * do the greedy
 */
public class milk {
  public static void main(String[] args) throws Exception{
		Scanner input = new Scanner(new FileReader("milk.in"));
		PrintWriter pw = new PrintWriter(new FileWriter("milk.out"));
		int N = input.nextInt();
		int M = input.nextInt();		
		Farmer[] arr = new Farmer[M];
		for(int i=0;i<M;i++){
			Farmer f = new Farmer();			
			input.nextLine();
			f.p = input.nextInt();
			f.a = input.nextInt();
			arr[i] = new Farmer();
			int j = i-1;
			for(;j>=0;j--){
				if(arr[j].p>f.p){
					arr[j+1].p = arr[j].p;
					arr[j+1].a = arr[j].a;
				}else{
					break;
				}
			}
			arr[j+1].p = f.p;
			arr[j+1].a = f.a;
		}
		int sumPrice = 0;
		int sumMilk = 0;
		for(int i=0;i<M;i++){
			if(sumMilk+arr[i].a>N){
				sumPrice+=arr[i].p*(N-sumMilk);
				break;
			}else{
				sumPrice+=arr[i].a*arr[i].p;
				sumMilk+=arr[i].a;
			}			
		}
		pw.println(sumPrice);
		pw.close();
		input.close();
		System.exit(0);
	}
}
class Farmer{
	int p,a;
}
