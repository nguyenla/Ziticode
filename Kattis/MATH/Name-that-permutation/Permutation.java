import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class Permutation {
    static BigInteger[] factorials = new BigInteger[51];

    public static ArrayList<Integer> getKthPermutation(int n, String k_order) {
        ArrayList<Integer> res = new ArrayList<>();
        ArrayList<Integer> numbers = new ArrayList<>();
        for (int i = 1; i <= n; ++i) {
            numbers.add(i);
        }

        // Keep reducing to find next number
        int num = n - 1;
        BigInteger k = new BigInteger(k_order);
        while (num >= 0) {
            BigInteger[] output = k.divideAndRemainder(factorials[num--]);
            // System.out.println(output[0].toString());
            // System.out.println(output[1].toString());
            int pos = output[0].intValue();
            res.add(numbers.get(pos));
            numbers.remove(pos);
            k = output[1];
        }
        return res;
    }

	public static void main(String[] args) {
        // Populate factorials
        factorials[0] = BigInteger.ONE;
        for (int i = 1; i <= 50; ++i) {
            factorials[i] = factorials[i - 1].multiply(new BigInteger(i + ""));
        }

        Scanner sc = new Scanner(System.in);
        String line;
        while (sc.hasNext()) {
            line = sc.nextLine();
            String[] input = line.split(" ");
            // System.out.println(input[0] + " " + input[1]);
            ArrayList<Integer> permutation = getKthPermutation(Integer.parseInt(input[0]), input[1]);
            for (int i = 0; i < permutation.size() - 1; ++i) {
                System.out.print(permutation.get(i) + " ");
            }
            System.out.println(permutation.get(permutation.size() - 1));
        }

	}
}

