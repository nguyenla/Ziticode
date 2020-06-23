import java.util.Arrays;
import java.lang.StringBuilder;

public class Sieve {
public static String f(int index) {
    boolean[] isPrime = new boolean[100001];
    Arrays.fill(isPrime, true);
    StringBuilder bd = new StringBuilder();

    for (int i = 2; i < isPrime.length; ++i) {
        if (!isPrime[i]) continue;
        bd.append(Integer.toString(i));
        for (int j = i * 2; j < isPrime.length; j+=i) {
            isPrime[j] = false;
        }
    }
    String primeString = bd.toString();
    return primeString.substring(index, index + 5);
}

	public static void main(String[] args) {
        System.out.println(f(0));
        System.out.println(f(1));
        System.out.println(f(2));
        System.out.println(f(3));
        System.out.println(f(10000));

	}
}

