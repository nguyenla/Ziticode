import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

public class AnagramCounting {

    public static BigInteger factorial(int n) {
        BigInteger res = new BigInteger("1");
        BigInteger cur = new BigInteger("1");
        BigInteger des = new BigInteger("" + (n+1));
        BigInteger one = new BigInteger("1");

        while (!cur.equals(des)) {
            res = res.multiply(cur);
            cur = cur.add(one);
        }
        return res;
    }

    public static String compute(String word) {
        HashMap<Character, Integer> map = new HashMap<Character, Integer>();
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (map.containsKey(c)) {
                map.put(c, map.get(c) + 1);
            }
            else {
                map.put(c, 1);
            }
        }
        BigInteger res = new BigInteger("1");
        res = res.multiply(factorial(word.length()));
        for (char c : map.keySet()) {
            res = res.divide(factorial(map.get(c)));
        }
        return res.toString();
    }


    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        while (s.hasNext()) {
            String word = s.next();
            System.out.println(compute(word));
        }
        s.close();
    }
}
