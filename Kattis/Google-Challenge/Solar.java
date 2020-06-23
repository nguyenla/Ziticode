import java.math.BigInteger;
import java.util.Arrays;

public class Solar {
    public static String f(int[] numbers) {
        if (numbers.length == 1 && numbers[0] < 0) return Integer.toString(numbers[0]);
        Arrays.sort(numbers);
        BigInteger prod = new BigInteger("1");
        int num_zeros = 0;
        int cur_neg = 0;
        int num_pos = 0;
        int num_neg = 0;

        for (int i = 0; i < numbers.length; ++i) {
            if (numbers[i] == 0) {
                ++num_zeros;
            }
            else if (numbers[i] > 0) {
                ++num_pos;
                prod = prod.multiply(new BigInteger(Integer.toString(numbers[i])));
            }
            else {
                ++num_neg;
                if (cur_neg == 0) {
                    cur_neg = numbers[i];
                }
                else {
                    prod = prod.multiply(new BigInteger(Integer.toString(numbers[i] * cur_neg)));
                    cur_neg = 0;
                }
            }
        }

        if (num_pos == 0) {
            if (num_neg >= 2) return prod.toString();
            else return "0";
        }
        if (num_zeros == numbers.length) {
            return "0";
        }
        else {
            return prod.toString();
        }
    }

	public static void main(String[] args) {
        int[] test1 = {2, 0, 2, 2, 0};
        System.out.println(f(test1));

        int[] test2 = {0, 0, 0, 0, 0, 0, -3};
        System.out.println(f(test2));

        int[] test3 = {-2, -3, 4, -5};
        System.out.println(f(test3));

        int[] test4 = {-1000 };
        System.out.println(f(test4));

        int[] test5 = {-1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000 ,-1000, -1000, -1000, -1000, -1000, -1000, -1000 };
        System.out.println(f(test5));

        int[] test6 = {-1, -1, -1, 0 };
        System.out.println(f(test6));

        int[] test7 = {-1, 0 };
        System.out.println(f(test7));

        int[] test8 = {-1, 0, 10};
        System.out.println(f(test8));

        int[] test9 = {0};
        System.out.println(f(test9));

	}
}

