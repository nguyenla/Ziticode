import java.lang.Math;
import java.util.Arrays;
import java.util.ArrayList;

public class Solution {
    public static long gcd(long a, long b) {
        a = Math.abs(a);
        b = Math.abs(b);
        if (a == 0 && b == 0) return 1;
        if (a == 0) return b;
        if (b == 0) return a;
        if (a < b) return gcd(b, a);
        if (a % b == 0) return b;
        return gcd(b, a % b);
    }

    static class Fraction {
        long num;
        long den;

        public Fraction(long a, long b) {
            num = a;
            den = b;
            reduce();
        }

        public long num() { return num; }
        public long den() { return den; }

        public void reduce() {
            long factor = gcd(num, den);
            num /= factor;
            den /= factor;
            if (den < 0) {
                den = -den;
                num = -num;
            }
        }
        
        public boolean isNegative() {
            return num * den < 0;
        }
    } // end of Fraction

    public static Fraction sum(Fraction f1, Fraction f2) {
        long num = f1.num() * f2.den() + f1.den() * f2.num();
        long den = f1.den() * f2.den();
        Fraction s = new Fraction(num, den);
        s.reduce();
        return s;
    }

    // f1 - f2
    public static Fraction subtract(Fraction f1, Fraction f2) {
        Fraction f3 = new Fraction(-1 * f2.num(), f2.den());
        return sum(f1, f3);
    }

    // f1 * f2
    public static Fraction multiply(Fraction f1, Fraction f2) {
        Fraction prod = new Fraction(f1.num() * f2.num(), f1.den() * f2.den());
        prod.reduce();
        return prod;
    }

    // f1 / f2
    public static Fraction divide(Fraction f1, Fraction f2) {
        Fraction quo = new Fraction(f1.num() * f2.den(), f2.num() * f1.den());
        quo.reduce();
        return quo;
    }

    public static Fraction[][] inverse(Fraction input[][]) {
        int n = input.length;
        Fraction one = new Fraction(1, 1);
        Fraction zero = new Fraction(0, 1);

        Fraction[][] augmented = new Fraction[n][2 * n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 2 * n; ++j) {
                if (j < n) {
                    augmented[i][j] = input[i][j];
                }
                else if (i + n == j) {
                    augmented[i][j] = one;
                }
                else {
                    augmented[i][j] = zero;
                }
            }
        }

        // Forward elimination
        for (int i = 0; i < n; ++i) {
            // Find rows with max leading fraction, and swap with row[i]
            int max_i = i;
            for (int k = i; k < n; ++k) {
                Fraction diff = subtract(augmented[k][i], augmented[i][i]);
                if (!diff.isNegative() && diff.num() != 0) max_i = k;
            }

            // Swapping
            for (int j = 0; j < 2 * n; ++j) {
                Fraction temp_f = augmented[i][j];
                augmented[i][j] = augmented[max_i][j];
                augmented[max_i][j] = temp_f;
            }
            
             // Start first row with leading one
            Fraction mult = divide(one, augmented[0][0]);
            for (int j = 0; j < 2 * n; ++j) {
                augmented[0][j] = multiply(augmented[0][j], mult);
            }

            // Elimination
            for (int k = i + 1; k < n; ++k) {
                if (augmented[k][i].num() != 0) {
                    Fraction multiple = divide(augmented[i][i], augmented[k][i]);
                    for (int j = 0; j < 2 * n; ++j) {
                        augmented[k][j] = subtract(augmented[i][j], multiply(multiple, augmented[k][j]));
                    }
                }

                if (augmented[k][i + 1].num() != 0) {
                    Fraction multiple = divide(one, augmented[k][i + 1]);
                    for (int j = 0; j < 2 * n; ++j) {
                        augmented[k][j] = multiply(multiple, augmented[k][j]);
                    }
                }
            }
        }

        // Backward substitution
        for (int i = n - 1; i >= 0; --i) {
            for (int k = i - 1; k >= 0; --k) {
                Fraction multiple = divide(augmented[k][i], augmented[i][i]);
                for (int j = 0; j < 2 * n; ++j) {
                    augmented[k][j] = subtract(augmented[k][j], multiply(multiple, augmented[i][j]));
                }
            }
        }

        Fraction[][] res = new Fraction[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                res[i][j] = augmented[i][j+n];
            }
        }

        return res;
    }

    public static int[] solution(int[][] numbers) {
        int n = numbers.length;
        // Edge case n = 1
        if (n == 1) {
            int[] res = new int[n + 1];
            res[0] = 1;
            res[1] = 1;
            return res;
        }
        int[] res = new int[n];
        Arrays.fill(res, -1);

        boolean[] terminal = new boolean[n];
        boolean[] unreachable = new boolean[n];
        long[] total = new long[n];
        Arrays.fill(terminal, true);
        Arrays.fill(unreachable, true);
        Arrays.fill(total, 0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (numbers[i][j] != 0) {
                    total[i] += numbers[i][j];
                    if (i != j) terminal[i] = false;
                    unreachable[j] = false;
                }
            }
        }

        ArrayList<Integer> terminals = new ArrayList<Integer>();
        ArrayList<Integer> transients = new ArrayList<Integer>();
        transients.add(0); // Consider state 0 to be transient even if it is unreachable
        int num_unreachable_terminals = 0;
        for (int i = 0; i < n; ++i) {
            if (terminal[i] && unreachable[i] && i != 0) {
                res[i] = 0;
                ++num_unreachable_terminals;
            }
            else if (terminal[i]) terminals.add(i);
            else if (i != 0) transients.add(i);
        }

        // Short circuit if there is no path from 0 to any other state
        if (total[0] == 0) {
            int[] final_res = new int[num_unreachable_terminals + 2];
            Arrays.fill(final_res, 0);
            final_res[0] = 1;
            final_res[num_unreachable_terminals + 1] = 1;
            return final_res;
        }
        int num_terminals = terminals.size();
        int num_transients = transients.size();


        Fraction[][] trans_mat = new Fraction[num_transients][num_transients];
        for (int i = 0; i < transients.size(); ++i) {
            for (int j = 0; j < transients.size(); ++j) {
                trans_mat[i][j] = new Fraction(numbers[transients.get(i)][transients.get(j)], total[transients.get(i)]);
            }
        }

        Fraction[][] trans_ter_mat = new Fraction[num_transients][num_terminals];
        for (int i = 0; i < num_transients; ++i) {
            for (int j = 0; j < num_terminals; ++j) {
                trans_ter_mat[i][j] = new Fraction(numbers[transients.get(i)][terminals.get(j)], total[transients.get(i)]);
            }
        }

        // Subtract trans_mat from identity matrix
        Fraction one = new Fraction(1, 1);
        Fraction zero = new Fraction(0, 1);
        for (int i = 0; i < trans_mat.length; ++i) {
            for (int j = 0; j < trans_mat[0].length; ++j) {
                if (i == j) trans_mat[i][j] = subtract(one, trans_mat[i][j]);
                else trans_mat[i][j] = subtract(zero, trans_mat[i][j]);
            }
        }

        Fraction[][] inverse = inverse(trans_mat);

        // Multiply inverse by trans_ter_mat: inverse has size num_transients * num_terminals
        Fraction[] probs = new Fraction[num_terminals];
        long lcm = 1;
        Arrays.fill(probs, zero);
        for (int i = 0; i < num_terminals; ++i) {
            for (int j = 0; j < num_transients; ++j) {
                probs[i] = sum(probs[i], multiply(inverse[0][j], trans_ter_mat[j][i]));
            }
            lcm = lcm / gcd(lcm, probs[i].den()) * probs[i].den();
        }

        // Populate res, not final answer
        for (int i = 0; i < num_terminals; ++i) {
            res[terminals.get(i)] = (int) (lcm / probs[i].den() * probs[i].num());
        }

        int[] final_res = new int[n - num_transients  + 1];
        int cur = 0;
        for (int i = 0; i < res.length; ++i) {
            if (res[i] != -1) {
                final_res[cur++] = res[i];
            }
        }
        final_res[final_res.length - 1] = (int) lcm;

        return final_res;
    }
}
