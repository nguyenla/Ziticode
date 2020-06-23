import java.lang.Math;
import java.util.Arrays;
import java.util.ArrayList; import java.util.HashMap;

public class Solution_draft {
    // Convert integer to binary representation
    public static String toBinary(int i, int len) {
        String bin = Integer.toBinaryString(i);
        return String.format("%" + len + "s", bin).replace(" ", "0");
    }

    public static void print(char[] input) {
        for (int i = 0; i < input.length; ++i) {
            System.out.print(input[i] + " ");
        }
        System.out.println();
    }

    public static void printHashMap(HashMap<String, Integer> map) {
        System.out.println("HashMap from string to integer: ");
        for (String k : map.keySet()) {
            System.out.println(k + " " + map.get(k));
        }
        System.out.println("-----END MAP----------");
    }

    public static void print(HashMap<String, HashMap<String, ArrayList<String>>> map) {
        for (String key : map.keySet()) {
            System.out.println("-----------------");
            System.out.println("Output: " + key);
            HashMap<String, ArrayList<String>> mp = map.get(key);
            for (String k2 : mp.keySet()) {
                ArrayList<String> ls = mp.get(k2);
                String out = k2 + ": ";
                for (int i = 0; i < ls.size(); ++i) {
                    out += ls.get(i) + " ";
                }
                System.out.println(out);
            }
        }
    }

    public static void print2(HashMap<String, HashMap<String, Integer>> map) {
        for (String key : map.keySet()) {
            System.out.println("-----------------");
            System.out.println("Output: " + key);
            HashMap<String, Integer> mp = map.get(key);
            for (String k2 : mp.keySet()) {
                String out = k2 + ": " + mp.get(k2);
                System.out.println(out);
            }
        }
    }
    // ------------------------- End of utility functions ------------------
    
    // Collapse a (m * n) nebula to (m - 1) * (n - 1)
    public static String collapse(String s1, String s2) {
        String output = "";
        char[] s1c = s1.toCharArray();
        char[] s2c = s2.toCharArray();
        for (int i = 0; i < s1c.length - 1; ++i) {
            int total = s1c[i] + s2c[i] + s1c[i + 1] + s2c[i + 1] - 192;
            if (total == 1) output += '1';
            else output += '0';
        }
        return output;
    }

    public static int solution(boolean[][] input) {
        int height = input.length + 1;
        int n = (1 << height) - 1;
        HashMap<String, HashMap<String, ArrayList<String>>> starting = new HashMap<>();
        HashMap<String, HashMap<String, Integer>> ending = new HashMap<>();

        // Preprocessing
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                String s1 = toBinary(i, height);
                String s2 = toBinary(j, height);
                String output = collapse(s1, s2);
                // System.out.println(s1 + " " + s2);
                // System.out.println(output);

                // Update starting
                if (starting.containsKey(output)) {
                    HashMap<String, ArrayList<String>> mp = starting.get(output);
                    ArrayList<String> suffixes = new ArrayList<>();
                    if (mp.containsKey(s1)) {
                        suffixes = mp.get(s1);
                    }
                    suffixes.add(s2);
                    mp.put(s1, suffixes);
                }
                else {
                    HashMap<String, ArrayList<String>> mp = new HashMap<>();
                    ArrayList<String> ls = new ArrayList<String>();
                    ls.add(s2);
                    mp.put(s1, ls);
                    starting.put(output, mp);
                }

                // Update ending
                if (ending.containsKey(output)) {
                    HashMap<String, Integer> mp = ending.get(output);
                    if (mp.containsKey(s2)) {
                        mp.put(s2, mp.get(s2) + 1);
                    }
                    else {
                        mp.put(s2, 1);
                    }
                }
                else {
                    HashMap<String, Integer> mp = new HashMap<>();
                    mp.put(s2, 1);
                    ending.put(output, mp);
                }
            }
        }

        System.out.println("Starting");
        print(starting);
        System.out.println("--------------------------------------");
        System.out.println("Ending");
        print2(ending);
        System.out.println("--------------------------------------");
        // ---------------------- End of preprocessing ------------------------

        // Solving
        // Transform the given matrix to a list of columns
        ArrayList<String> columns = new ArrayList<String>();
        System.out.println("All columns:");
        for (int j = 0; j < input[0].length; ++j) {
            String col = "";
            for (int i = 0; i < input.length; ++i) {
                col += input[i][j] ? '1' : '0';
            }
            System.out.println(col);
            columns.add(col);
        }

        int res = 0;
        System.out.println("First column: " + columns.get(0));
        HashMap<String, Integer> curMap = ending.get(columns.get(0));

        for (int i = 1; i < columns.size(); ++i) {
            String col = columns.get(i);
            System.out.println("Processing col: " + col);
            HashMap<String, Integer> nextMap = new HashMap<>();

            System.out.println("Cur map: ");
            printHashMap(curMap);


            for (String end : curMap.keySet()) {
                // System.out.println("Column: " + col + ", end: " + end);
                ArrayList<String> possibleStarts = starting.get(col).get(end);
                if (possibleStarts == null) continue;
                for (int j = 0; j < possibleStarts.size(); ++j) {
                    String start = possibleStarts.get(j);
                    if (!nextMap.containsKey(start)) {
                        nextMap.put(start, curMap.get(end));
                    }
                    else {
                        nextMap.put(start, nextMap.get(start) + curMap.get(end));
                    }
                }
            }

            curMap = new HashMap<>(nextMap);
        }

        for (String key : curMap.keySet()) {
            res += curMap.get(key);
        }

        return res;
    }

	public static void main(String[] args) {
        System.out.println("Solved");
        boolean[][] input = new boolean[][]{
            {true, false, true},
            {false, true, false},
            {true, false, true}
        };
        System.out.println(solution(input));

        boolean[][] input2 = new boolean[][] {
            {true, false, true, false, false, true, true, true},
            {true, false, true, false, false, false, true, false},
            {true, true, true, false, false, false, true, false},
            {true, false, true, false, false, false, true, false},
            {true, false, true, false, false, true, true, true}
        };
        System.out.println(solution(input2));

        boolean[][] input3 = new boolean[][] {
            {true, true, false, true, false, true, false, true, true, false},
            {true, true, false, false, false, false, true, true, true, false},
            {true, true, false, false, false, false, false, false, false, true},
            {false, true, false, false, false, false, true, true, false, false}
        };
        System.out.println(solution(input3));
    }
}
