package DP;

import java.util.*;

public class Equal {

    public static int compute(int n) {
        return n/5 + (n%5 / 2) + ((n%5) %2);
    }
    
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int t = s.nextInt();
        for (int i = 0; i < t; i++) {
            int n = s.nextInt();
            int[] arr = new int[n];
            int min = Integer.MAX_VALUE;
            for (int j = 0; j < n; j++) {
                arr[j] = s.nextInt();
                min = Math.min(min, arr[j]);
            }
            
            int res = Integer.MAX_VALUE;
            for (int j = 0; j < 5; j++) {
                int count = 0;
                for (int k = 0; k < n; k++) {
                    count += compute(arr[k] - (min - j));
                }
                res = Math.min(count, res);
            }
            System.out.println(res);
        }
        s.close();
    }
}