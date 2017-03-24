
import java.util.*;

public class Queue_reconstruction_406 {
	// Approach 1: Presort
    public int[][] reconstructQueue(int[][] people) {
        ArrayList<Pair> list = new ArrayList<Pair>();
        for (int i = 0; i < people.length; i++) {
            list.add(new Pair(people[i][0], people[i][1]));
        }
        Collections.sort(list);
        Node dummy = new Node(null);
        Node temp, prev;
        
        for (int i = 0; i < list.size(); i++) {
            prev = dummy;
            temp = dummy.next;
            Pair p = list.get(i);
            Node newNode = new Node(p);
            int seen = 0;
            
            while (seen < p.n || (seen == p.n && temp!= null && p.h > temp.pair.h)) {
                if (temp.pair.h >= p.h) seen++;
                prev = temp;
                temp = temp.next;
            }
            newNode.next = prev.next;
            prev.next = newNode;
        }
        
        int[][] res = new int[people.length][2];
        Node head = dummy.next;
        int i = 0;
        while (head != null) {
            res[i][0] = head.pair.h;
            res[i][1] = head.pair.n;
            i++;
            head = head.next;
        }
        return res;
    }
    
    class Pair implements Comparable<Pair> {
        int h;
        int n;
        
        public Pair(int h, int n) {
            this.h = h;
            this.n = n;
        }
        
        public int compareTo(Pair p) {
            if (this.n < p.n) return -1;
            else if (this.n > p.n) return 1;
            else {
                if (this.h < p.h) return -1;
                else if (this.h > p.h) return 1;
                else return 0;
            }
        }
    }

    class Node {
        Pair pair;
        Node next;
        
        public Node(Pair p) {
            pair = p;
        }
    }
}

