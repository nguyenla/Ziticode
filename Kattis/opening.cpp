#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num_blocks, bl;
    cin >> num_blocks;
    vector<int> blocks;

    for (size_t i = 0; i != num_blocks; ++i) {
        cin >> bl;
        blocks.push_back(bl);
    }
    sort(blocks.begin(), blocks.end());
    
    return 0;
}
