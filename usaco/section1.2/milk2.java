/*
ID: mtawake3
LANG: JAVA
TASK: milk2
 */
import java.util.*;
import java.io.*;

public class milk2 {
  
	public static void main(String args[]) throws IOException {
		Scanner input = new Scanner(new FileReader("milk2.in"));
		PrintWriter output = new PrintWriter(new BufferedWriter(new FileWriter(
				"milk2.out")));
		int N = input.nextInt();
		input.nextLine();
		Section[] sections = new Section[N];
		for(int i=0;i<N;i++){
			sections[i] = new Section();
			sections[i].from = input.nextInt();
			sections[i].to = input.nextInt();
			input.nextLine();
		}
		for(int i=0;i<N;i++){
			for(int j=0;j<N-i-1;j++){
				if(sections[j].from>sections[j+1].from){
					Section tmp = sections[j];
					sections[j] = sections[j+1];
					sections[j+1] = tmp;  
				}
			}
		}
		int finishIndex = 0;
		int processIndex = 1;
		while(processIndex<N){
			if(sections[processIndex].from<=sections[finishIndex].to){
				if(sections[processIndex].to > sections[finishIndex].to){
					sections[finishIndex].to = sections[processIndex].to;
				}
			}else{
				finishIndex++;
				sections[finishIndex] = sections[processIndex];
			}
			processIndex++;
		}
		int maxInside=0;
		int maxOutside=0;
		int tmp;
		for(int i=0;i<=finishIndex;i++){
			tmp=sections[i].to - sections[i].from;
			if(tmp>maxInside){
				maxInside = tmp;
			}
			if(i!=finishIndex){
				tmp = sections[i+1].from - sections[i].to;
				if(tmp>maxOutside){
					maxOutside = tmp;
				}
			}
		}
		output.println(maxInside+" "+maxOutside);
		input.close();
		output.close();
		System.exit(0);
	}
}
class Section{
	int from,to;
}
