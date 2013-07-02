
/*
 ID: mtawake3
 LANG: JAVA
 PROG: crypt1
 */
import java.io.*;
import java.util.*;
public class crypt1 {
  public static boolean inArray(int x,int[] nums){
		for(int i=0;i<nums.length;i++){
			if(nums[i]==x)
				return true;
		}
		return false;
	}
	public static void main(String[] args) throws Exception{
		Scanner input = new Scanner(new FileReader("crypt1.in"));
		PrintWriter pw = new PrintWriter(new FileWriter("crypt1.out"));
		int N = input.nextInt();
		input.nextLine();
		int[] nums = new int[N];
		for(int i=0;i<N;i++){
			nums[i] = input.nextInt();
		}
		int results = 0;
		for(int a=0;a<N;a++){
			for(int b=0;b<N;b++){
				for(int c=0;c<N;c++){
					for(int d=0;d<N;d++){
						for(int e=0;e<N;e++){
							int m3 = (nums[e]*nums[c]);
							int m2 = (nums[e]*nums[b]+m3/10);
							int m1 = (nums[e]*nums[a]+m2/10);
							if(m1>9)
								continue;
							m3 = m3%10;
							m2 = m2%10;
							if(!inArray(m3,nums) || !inArray(m2,nums) || !inArray(m1,nums)){
								continue;
							}
							
							int n3 = (nums[d]*nums[c]);
							int n2 = (nums[d]*nums[b]+n3/10);
							int n1 = (nums[d]*nums[a]+n2/10);
							if(n1>9)
								continue;
							n3 = n3%10;
							n2 = n2%10;
							if(!inArray(n3,nums) || !inArray(n2,nums) || !inArray(n1,nums)){
								continue;
							}
							
							int r4 = m3;
							int r3 = m2 + n3;
							int r2 = (m1 + n2 + r3/10);
							int r1 = (n1 + r2/10);
							if(r1>9)
								continue;
							r3 = r3%10;
							r2 = r2%10;
							if(!inArray(r3,nums) || !inArray(r2,nums) || !inArray(r1,nums)){
								continue;
							}
							results++;
						}
					}
				}
			}
		}
		pw.println(results);
		pw.close();
		input.close();
		System.exit(0);
	}
}
