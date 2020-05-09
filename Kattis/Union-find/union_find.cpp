#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
  private:
    vector<int> roots;
    vector<int> size;

  public:
    UnionFind(const int num_elements) {
        for (int i = 0; i < num_elements; ++i) {
            roots.push_back(i);
            size.push_back(1);
        }
    }

    int find_root(const int a) {
        int cur = a;
        while (roots[cur] != cur) {
            // improvement: make every other node in path point to its grandparent
            roots[cur] = roots[roots[cur]];
            cur = roots[cur];
        }
        return cur;
    }

    bool isConnected(const int a, const int b) {
        return find_root(a) == find_root(b);
    }

    void connect(const int a, const int b) {
        int root_a = find_root(a);
        int root_b = find_root(b);
        if (root_a == root_b) return;

        // Make node with larger tree the root of node with smaller tree
        if (size[root_a] < size[root_b]) {
            roots[root_a] = root_b;
            size[root_b] += size[root_a];
        }
        else {
            roots[root_b] = root_a;
            size[root_a] += size[root_b];
        }
    }

    void print() {
        cout << "Roots: \n";
        for (int i = 0; i < roots.size(); ++i) {
            cout << roots[i] << " ";
        }
        cout << "\nSize: \n";
        for (int i = 0; i < size.size(); ++i) {
            cout << size[i] << " ";
        }
        cout << "\n---------------\n";
    }
};

int main() {
    int num_elements, num_queries, a, b;
    char c[2];
    scanf("%d%d",&num_elements,&num_queries);
    UnionFind uf(num_elements);

    while (num_queries--){
        scanf("%2s%d%d", c, &a, &b);
        if (c[0] == '=') uf.connect(a, b);
        else if (uf.isConnected(a,b)) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
