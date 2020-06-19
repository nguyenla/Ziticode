import java.math.BigInteger;
import java.util.Scanner;

public class Catalan {

	public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int cases = sc.nextInt();

        BigInteger[] catalan = new BigInteger[10001];
        BigInteger cur = BigInteger.ONE;
        catalan[0] = cur;
        catalan[1] = cur;

        for (int i = 2; i <= 10000; ++i) {
            cur = cur.multiply(new BigInteger(Integer.toString(2 * (2 * i - 1))));
            cur = cur.divide(new BigInteger(Integer.toString(i + 1)));
            catalan[i] = cur;
        }

        StringBuffer bf = new StringBuffer("");
        for (int i = 0; i < cases; ++i) {
            int n = sc.nextInt();
            bf.append(catalan[n]);
            if (i < cases - 1) bf.append("\n");
        }

        System.out.println(bf.toString());
	}
}

