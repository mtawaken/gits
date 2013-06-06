/*
ID: mtawake3
LANG: JAVA
TASK: transform
 */
import java.util.*;
import java.io.*;

public class transform {

  public static void main(String args[]) throws IOException {
		Scanner input = new Scanner(new FileReader("transform.in"));
		PrintWriter output = new PrintWriter(new BufferedWriter(new FileWriter(
				"transform.out")));
		int N = input.nextInt();
		input.nextLine();
		char[][] orig = new char[N][];
		char[][] trans = new char[N][];
		char[][] tmp = new char[N][];
		String tmpStr;
		for (int i = 0; i < N; i++) {
			tmpStr = input.nextLine();
			orig[i] = tmpStr.toCharArray();
			tmp[i] = new char[N];
		}
		for (int i = 0; i < N; i++) {
			tmpStr = input.nextLine();
			trans[i] = tmpStr.toCharArray();
		}
		int result = 7;
		//try #6
		if (equal(orig, trans, N)) {
			result = 6;
		}
		//try #1~3
		if (result == 7) {
			copy(orig, tmp, N);
			for (int i = 1; i <= 3; i++) {
				rotate90(tmp, tmp, N);
				if (equal(trans, tmp, N)) {
					result = i;
					break;
				}
			}
		}
		//try #4~5
		if (result == 7) {
			reflect(orig, tmp, N);
			if (equal(trans, tmp, N)) {
				result = 4;
			} else {
				for (int i = 0; i < 3; i++) {
					rotate90(tmp, tmp, N);
					if (equal(trans, tmp, N)) {
						result = 5;
						break;
					}
				}
			}
		}
		output.println(result);
		input.close();
		output.close();
		System.exit(0);
	}

	public static void copy(char[][] orig, char[][] tmp, int N) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				tmp[i][j] = orig[i][j];
			}
		}
	}

	public static void rotate90(char[][] orig, char[][] tmp, int N) {
		for (int level = N; level >= 2; level--) {
			for (int i = level - N; i < level - 1; i++) {
				tmp[level - N][i] = orig[level - 1 - i][level - N];
				tmp[i][level - 1] = orig[level - N][i];
				tmp[level - 1][i] = orig[level - 1 - i][level - 1];
				tmp[i][level - N] = orig[level - 1][i];
			}
		}
		print(tmp,N);
	}

	public static void reflect(char[][] orig, char[][] tmp, int N) {
		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N; j++) {
				tmp[i][j] = orig[N - i - 1][j];
				tmp[N - i - 1][j] = orig[i][j];
			}
		}
		if (N % 2 == 1) {
			for (int i = 0; i < N; i++) {
				tmp[N / 2 + 1][i] = orig[N / 2 + 1][i];
			}
		}
		print(tmp,N);
	}

	public static boolean equal(char[][] orig, char[][] tmp, int N) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (orig[i][j] != tmp[i][j])
					return false;
			}
		}
		return true;
	}
	
	public static void print(char[][] tmp,int N){
		System.out.println("changing to:");
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(tmp[i][j]+" ");
			}
			System.out.println();
		}
	}
}
