

public class Rotate_image_48 {
	// Approach 1: Rotate in-place using helper method
	// Complicated implementation
    public void rotate(int[][] matrix) {
        int n = matrix.length;
        int r = 0;
        while (r < n-r) {
            for (int c = r; c < n-r-1; c++) {
                int a = r;
                int b = c;
                int temp = matrix[a][b];
                Pair pair = getNext(r, c, n-r*2, r);
                while (pair.x != a || pair.y != b) {
                    int swap = temp;
                    temp = matrix[pair.x][pair.y];
                    matrix[pair.x][pair.y] = swap;
                    pair = getNext(pair.x, pair.y, n-r*2, r);
                }
                matrix[a][b] = temp;
            }
            r++;
        }
    }
    
    // Return the next pair of (x,y) to visit
    public Pair getNext(int x, int y, int n, int r) {
        int diff;
        if (x == r) {
            diff = (r+ n-1) -y;
            y = r + n-1;
            x += n-1 - diff;
        }
        else if (x == r+n-1) {
            diff = y-r;
            y = r;
            x -= n-1 - diff;
        }
        else if (y == r) {
            diff = x - r;
            x = r;
            y += n-1 - diff;
        }
        else if (y == r+n-1) {
            diff = (r + n - 1) - x;
            x = r + n - 1;
            y -= n-1 - diff;
        }
        return new Pair(x,y);
    }
    
    class Pair {
        int x;
        int y;
        
        public Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}

