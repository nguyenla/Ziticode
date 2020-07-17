#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class UnionFind {
  private:
    vector<int> parents;
    vector<int> sets;
    vector<int> size;
    vector<long> sum;

  public:
    UnionFind(const int num_elements) {
        parents.push_back(0);
        sets.push_back(0);
        sum.push_back(0);
        size.push_back(0);
        for (int i = 1; i <= num_elements; ++i) {
            parents.push_back(i);
            sets.push_back(i);
            sum.push_back(i);
            size.push_back(1);
        }
    }

    int find_parent(const int a) {
        int cur = sets[a];
        while (cur != parents[cur]) {
            // parents[cur] = parents[parents[cur]];
            cur = parents[cur];
        }
        sets[a] = cur;
        return cur;
    }

    bool isConnected(const int a, const int b) {
        return find_parent(a) == find_parent(b);
    }

    void connect(const int a, const int b) {
        int parent_a = find_parent(a);
        int parent_b = find_parent(b);
        if (parent_a == parent_b) return;

        // Make node with larger tree the parent of node with smaller tree
        if (size[parent_a] < size[parent_b]) {
            parents[parent_a] = parent_b;
            sets[a] = parent_b;
            size[parent_b] += size[parent_a];
            sum[parent_b] += sum[parent_a];
            
        }
        else {
            parents[parent_b] = parent_a;
            sets[b] = parent_a;
            size[parent_a] += size[parent_b];
            sum[parent_a] += sum[parent_b];
        }
    }

    void move(const int a, const int b) {
        int parent_a = find_parent(a);
        int parent_b = find_parent(b);
        if (parent_a == parent_b) return;

        sets[a] = parent_b;
        ++size[parent_b];
        --size[parent_a];
        sum[parent_b] += a;
        sum[parent_a] -= a;
    }

    void print(int a) {
        int parent_a = find_parent(a);
        cout << size[parent_a] << " " << sum[parent_a] << "\n";
    }

    void print() {
        cout << "Parents: \n";
        for (int i = 1; i < parents.size(); ++i) {
            cout << parents[i] << " ";
        }
        cout << "\nSets: \n";
        for (int i = 1; i < sets.size(); ++i) {
            cout << sets[i] << " ";
        }
        cout << "\nSize: \n";
        for (int i = 1; i < size.size(); ++i) {
            cout << size[i] << " ";
        }
        cout << "\nSum: \n";
        for (int i = 1; i < sum.size(); ++i) {
            cout << sum[i] << " ";
        }
        cout << "\n---------------\n";
    }
};

int main() {
    int num_elements, num_queries, op, a, b;
    while (cin >> num_elements >> num_queries) {
        UnionFind uf(num_elements);

        while (num_queries--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &a, &b);
                uf.connect(a, b);
            }
            else if (op == 2) {
                scanf("%d%d", &a, &b);
                uf.move(a, b);
            }
            else if (op == 3) {
                scanf("%d", &a);
                uf.print(a);
            }
        }
    }
    return 0;
}
