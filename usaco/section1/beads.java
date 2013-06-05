/*
id:mtawake3
LANG:JAVA
TASK:beads
 */
import java.util.*;
import java.io.*;
public class beads {
  public static void main(String[] args) throws IOException{
		Scanner scanner = new Scanner(new FileReader("beads.in"));
		PrintWriter pw = new PrintWriter(new FileWriter("beads.out"));
		int N = scanner.nextInt();
		scanner.nextLine();
		String beads = scanner.nextLine();
		int max = 0;
		for(int i=0;i<N;i++){
			int tmp = cut(i,N,beads);
			if(tmp>max){
				max = tmp;
			}
		}
		pw.println(max);
		scanner.close();
		pw.close();
		System.exit(0);
	}
	public static int cut(int before,int N,String beads){
		int sum = 2;
		int leftIndex = before-1;
		if(leftIndex<0){
			leftIndex = N-1;
		}
		int rightIndex = before;
		char leftBead = beads.charAt(leftIndex);
		char rightBead = beads.charAt(rightIndex);
		boolean[] occupy = new boolean[N];
		occupy[leftIndex]=true;
		occupy[rightIndex]=true;
		while(leftIndex!=rightIndex){
			leftIndex --;
			if(leftIndex<0){
				leftIndex = N-1;
			}
			if(leftIndex==rightIndex&&occupy[leftIndex]){
				break;
			}
			if(occupy[leftIndex]){
				break;
			}
			if(leftBead=='w'){
				leftBead = beads.charAt(leftIndex);
				sum++;
				occupy[leftIndex]=true;
			}else if(beads.charAt(leftIndex)=='w' || leftBead==beads.charAt(leftIndex)){
				sum++;
				occupy[leftIndex]=true;
			}else{
				break;
			}
		}
		while(rightIndex!=leftIndex){
			rightIndex++;
			if(rightIndex>=N){
				rightIndex=0;
			}
			if(leftIndex==rightIndex&&occupy[rightIndex]){
				break;
			}
			if(occupy[rightIndex]){
				break;
			}
			if(rightBead=='w'){
				rightBead = beads.charAt(rightIndex);
				sum++;
				occupy[rightIndex]=true;
			}else if(beads.charAt(rightIndex)=='w'||rightBead==beads.charAt(rightIndex)){
				sum++;
				occupy[rightIndex]=true;
			}else{
				break;
			}
		}		
		return sum;
	}
}
