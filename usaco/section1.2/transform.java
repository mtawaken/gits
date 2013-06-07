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
		char[][] tmp_orig = new char[N][];
		String tmpStr;
		for (int i = 0; i < N; i++) {
			tmpStr = input.nextLine();
			orig[i] = tmpStr.toCharArray();
			tmp[i] = new char[N];
			tmp_orig[i] = new char[N];
		}
		for (int i = 0; i < N; i++) {
			tmpStr = input.nextLine();
			trans[i] = tmpStr.toCharArray();
		}
		int result = 7;

		// try #1~3
		if (result == 7) {
			copy(orig, tmp_orig, N);
			for (int i = 1; i <= 3; i++) {
				rotate90(tmp_orig, tmp, N);
				if (equal(trans, tmp, N)) {
					result = i;
					break;
				}
				copy(tmp, tmp_orig, N);
			}
		}
		// try #4~5
		if (result == 7) {
			reflect(orig, tmp, N);
			if (equal(trans, tmp, N)) {
				result = 4;
			} else {
				copy(tmp, tmp_orig, N);
				for (int i = 0; i < 3; i++) {
					rotate90(tmp_orig, tmp, N);
					if (equal(trans, tmp, N)) {
						result = 5;
						break;
					}
					copy(tmp, tmp_orig, N);
				}
			}
		}
		// try #6
		if (result == 7) {
			if (equal(orig, trans, N)) {
				result = 6;
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
		copy(orig, tmp, N);
		for (int i = 0; i < N / 2; i++) {
			for (int j = i; j < N - i; j++) {
				tmp[i][j] = orig[N - j - 1][i];
				tmp[j][N - i - 1] = orig[i][j];
				tmp[N - i - 1][j] = orig[N - j - 1][N - i - 1];
				tmp[j][i] = orig[N - i - 1][j];
			}
		}
		print(tmp, N);
	}

	public static void reflect(char[][] orig, char[][] tmp, int N) {
		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N; j++) {
				tmp[j][i] = orig[j][N - i - 1];
				tmp[j][N - i - 1] = orig[j][i];
			}
		}
		if (N % 2 == 1) {
			for (int i = 0; i < N; i++) {
				tmp[i][N / 2] = orig[i][N / 2];
			}
		}
		print(tmp, N);
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

	public static void print(char[][] tmp, int N) {
		System.out.println("changing to:");
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(tmp[i][j]);
			}
			System.out.println();
		}
	}
}
