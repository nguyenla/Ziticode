import java.math.BigInteger;
import java.util.Arrays;

public class Pegs {
    public static int[] f(int[] numbers) {
        int[] res = {-1, -1};
        if (numbers.length == 2) {
            int diff = numbers[1] - numbers[0];
            if (diff <= 2) {
                return res;
            }
            else if (diff % 3 != 0) {
                res[0] = diff * 2;
                res[1] = 3;
                return res;
            }
            else {
                res[0] = diff * 2 / 3;
                res[1] = 1;
                return res;
            }
        }

        boolean possible = true;
        boolean add = true;
        int last_gear = 0;

        for (int i = 0; i < numbers.length - 1; ++i) {
            int diff = numbers[i + 1] - numbers[i];
            last_gear = add ? last_gear + diff : last_gear - diff;
            add = !add;
        }

        // Backtrack to verify it is possible
        double last = last_gear;
        if (numbers.length % 2 == 0) last_gear /= 3;
        if (last < 1) return res;

        int cur_i = numbers.length - 1;
        double cur_gear = last;
        while (cur_i >= 1) {
            double next_gear = numbers[cur_i] - numbers[cur_i - 1] - cur_gear;
            if (next_gear < 1) {
                possible = false;
                break;
            }
            else {
                cur_gear = next_gear;
                --cur_i;
            }
        }

        if (possible) {
            if (numbers.length % 2 == 0) {
                if (last_gear % 3 == 0) {
                    res[0] = last_gear * 2 / 3;
                    res[1] = 1;
                    return res;
                }
                else {
                    res[0] = last_gear * 2;
                    res[1] = 3;
                    return res;
                }
            }
            else {
                res[0] = last_gear * 2;
                res[1] = 1;
            }
        }
        return res;
    }

    public static void print(int[] arr) {
        System.out.println(arr[0] + " " + arr[1]);
    }

	public static void main(String[] args) {
        int[] test1 = {4, 17, 50};
        int[] res1 = f(test1);
        print(res1);

        int[] test2 = {4, 30, 50};
        int[] res2 = f(test2);
        print(res2);

        int[] test3 = {1, 7, 9, 12, 16};
        int[] res3 = f(test3);
        print(res3);

        int[] test4 = {1, 7, 15, 25, 32};
        int[] res4 = f(test4);
        print(res4);

        int[] test5 = {1, 4, 5};
        int[] res5 = f(test5);
        print(res5);

        int[] test6 = {1, 7};
        int[] res6 = f(test6);
        print(res6);

        int[] test7 = {1, 6};
        int[] res7 = f(test7);
        print(res7);

        int[] test8 = {1, 7, 15, 23};
        int[] res8 = f(test8);
        print(res8);

        int[] test9 = {1, 7, 15, 21};
        int[] res9 = f(test9);
        print(res9);

	}
}

