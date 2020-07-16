import java.math.BigInteger;
import java.util.Scanner;

public class beautiful_primes {

	public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int cases = sc.nextInt();

        BigInteger[] beautiful = new BigInteger[1001];
        String[] res = new String[1001];

        BigInteger two = new BigInteger("2");
        BigInteger three = new BigInteger("3");
        BigInteger five = new BigInteger("5");
        BigInteger eleven = new BigInteger("11");

        BigInteger cur = new BigInteger("2");
        String cur_s = "";
        beautiful[0] = cur;
        beautiful[1] = cur;
        cur = cur.multiply(five);
        beautiful[2] = cur;
        res[1] = "2";
        res[2] = "2 5";

        for (int i = 3; i <= 1000; ++i) {
            cur = cur.multiply(eleven);
            if (cur.toString().length() != i) {
                cur = cur.divide(eleven);
                cur = cur.multiply(two);
                res[i] = res[i - 1] + " 2";
            }
            else {
                res[i] = res[i - 1] + " 11";
            }
            beautiful[i] = cur;
        }

        StringBuffer bf = new StringBuffer("");
        for (int i = 0; i < cases; ++i) {
            int n = sc.nextInt();
            bf.append(res[n]);
            if (i < cases - 1) bf.append("\n");
        }

        System.out.println(bf.toString());
	}
}

