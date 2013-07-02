/*
ID: mtawake3
LANG: JAVA
TASK: calfflac
 */
import java.util.*;
import java.io.*;

public class calfflac {
  public static void main(String[] args) throws IOException {
		new calfflac().work();
	}

	StringBuffer sb = null;
	int maxCount = 0;
	int maxIndex = 0;
	PrintWriter pw = null;
	Scanner input = null;
	int sLength = 0;
	char[] sArray = null;
	int[] hash = new int[20000];
	int left, right;

	public void work() throws IOException {
		input = new Scanner(new FileReader("calfflac.in"));
		pw = new PrintWriter(new FileWriter("calfflac.out"));
		sb = new StringBuffer();
		while (input.hasNext()) {
			sb.append(input.nextLine() + "\n");
		}
		// cal sArray
		int pointer = 0;
		sArray = new char[sb.length()];
		for (int i = 0; i < sb.length(); i++) {
			if (valid(i)) {
				sArray[pointer] = sb.charAt(i);
				hash[pointer] = i;
				pointer++;
			}
		}
		sLength = pointer;
		// check from middle,position switch left,right from middle
		int middle = sLength / 2;
		int tmp1, tmp2;
		for (int i = 0; middle + i < sLength || middle - i >= 0; i++) {
			for (int j = -1; j <= 1; j += 2) {
				pointer = middle + i * j;
				if (pointer < 0 || pointer >= sLength) {
					continue;
				}
				// if we've found one P that enough long,then points nearby two
				// sides are not
				// needed to check because the longest P they can be are not
				// long enough
				if ((sLength - pointer) < (maxCount / 2)) {
					break;
				}
				// odd
				left = pointer - 1;
				right = pointer + 1;
				tmp1 = countP() + 1;
				// even
				left = pointer;
				right = pointer + 1;
				tmp2 = countP();
				if (tmp1 > tmp2) {
					tmp2 = tmp1;
				}
				if (j < 0) {
					if (tmp2 >= maxCount) {
						maxIndex = pointer;
						maxCount = tmp2;
					}
				} else {
					if (tmp2 > maxCount) {
						maxIndex = pointer;
						maxCount = tmp2;
					}
				}
			}
		}
		// odd
		left = maxIndex - 1;
		right = maxIndex + 1;
		tmp1 = countP() + 1;
		// even
		left = maxIndex;
		right = maxIndex + 1;
		tmp2 = countP();
		pw.println(maxCount);
		if (tmp1 > tmp2) {
			left = hash[maxIndex] - 1;
			right = hash[maxIndex] + 1;
			print(1);
		} else {
			left = hash[maxIndex];
			right = hash[maxIndex] + 1;
			print(0);
		}
		pw.close();
		input.close();
		System.exit(0);
	}

	public int countP() {
		int count = 0;
		while (left >= 0 && right < sLength) {
			if (equal(left, right)) {
				left--;
				right++;
				count += 2;
			} else {
				return count;
			}
		}
		return count;
	}

	public void print(int count) {
		while (count != maxCount) {
			if (!valid(left)) {
				left--;
				continue;
			}
			if (!valid(right)) {
				right++;
				continue;
			}
			count += 2;
			left--;
			right++;
		}
		pw.println(sb.substring(left + 1, right));
	}

	public boolean valid(int index) {
		char c = sb.charAt(index);
		if ('a' <= c && c <= 'z' || ('A' <= c && c <= 'Z')) {
			return true;
		}
		return false;
	}

	public boolean equal(int left, int right) {
		char leftC = sArray[left];
		char rightC = sArray[right];
		if (leftC == rightC) {
			return true;
		} else {
			return Math.abs(leftC - rightC) == ('a' - 'A');
		}
	}
}
