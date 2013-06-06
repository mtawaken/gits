/*
ID: mtawaken
LANG: JAVA
TASK: gift1
*/

import java.io.*;
import java.util.*;

public class gift1 {
  public static void main(String[] args) throws IOException{
		Scanner scanner = new Scanner(new File("gift1.in"));
		PrintWriter pw = new PrintWriter(new FileWriter("gift1.out"));
		int NP = scanner.nextInt();
		scanner.nextLine();
		Node[] nodes = new Node[NP];
		for(int i=0;i<NP;i++){
			nodes[i] = new Node(scanner.nextLine());
		}
		while(scanner.hasNext()){
			String name = scanner.nextLine();
			int money = scanner.nextInt();
			int NG = scanner.nextInt();
			if(scanner.hasNext()){
				scanner.nextLine();
			}
			int piece,moneyUsed;
			if(NG == 0){
				piece = 0;
				moneyUsed = 0;
			}else{
				piece = money/NG;
				moneyUsed = (piece*NG) ;
			}
			Node node = find(nodes,name);
			node.give = moneyUsed;
			for(int i=0;i<NG;i++){
				node = find(nodes,scanner.nextLine());
				node.receive += piece;
			}
		}
		for(int i=0;i<nodes.length;i++){
			pw.println(nodes[i].name+" "+(nodes[i].receive-nodes[i].give));
		}
		scanner.close();
		pw.close();
		System.exit(0);
	}
	public static Node find(Node[] nodes,String name){
		for(int i=0;i<nodes.length;i++){
			if(nodes[i].name.equals(name)){
				return nodes[i];
			}
		}
		return null;
	}
	static class Node{
		String name;
		int give,receive;
		public Node(String name){
			this.name = name;
			give = 0;
			receive = 0;
		}
	}
}
