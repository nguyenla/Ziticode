package DP;
import java.util.*;

public class Coin_change {

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        int m = s.nextInt();
        int[] coins = new int[m];
        for (int i = 0; i < m; i++) {
            coins[i] = s.nextInt();
        }
        
        long[] res = new long[n+1];
        res[0] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 1; j <= n; j++) {
                if (j - coins[i] >= 0) {
                    res[j] += res[j-coins[i]];
                }
            }
        }
        System.out.println(res[n]);
        s.close();
    }
}