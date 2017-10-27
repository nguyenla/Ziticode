import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

public class SmallestMultiple {
    public static BigInteger gcd(BigInteger a, BigInteger b) {
        if (a.compareTo(b) < 0) return gcd(b, a);
        if (a.mod(b).equals(BigInteger.ZERO)) {
            return b;
        }
        return gcd(b, a.mod(b));
    }

    public static BigInteger lcm(BigInteger a, BigInteger b) {
        BigInteger res = a.multiply(b);
        res = res.divide(gcd(a, b));
        return res;
    }


    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        while (s.hasNextLine()) {
            String[] arr = s.nextLine().split(" ");
            BigInteger[] nums = new BigInteger[arr.length];
            for (int i = 0; i < nums.length; i++) {
                nums[i] = new BigInteger(arr[i]);
            }
            BigInteger res = new BigInteger("1");

            for (int i = 0; i < nums.length; i++) {
                res = lcm(res, nums[i]);
            }
            System.out.println(res.toString());
        }
        s.close();
    }
}
