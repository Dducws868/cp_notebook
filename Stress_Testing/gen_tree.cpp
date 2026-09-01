#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <utility>
using namespace std;
int UID(int L, int R) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(L, R)(rng);
}
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên
    freopen("out.txt","w",stdout);
    std::srand(std::time(0));

    // Tạo số ngẫu nhiên n trong khoảng từ 20 đến 30
    int n = 6 + std::rand() % 1;
    std::cout << n << ' ';
    int m = 6 + std::rand() % 1;
    int k = 2;
    std::cout << m << ' ' << k << endl;
    // Tạo cây với n-1 cạnh
    std::vector<std::pair<int, int>> edges;
    std::set<int> connected;
    connected.insert(1); // Bắt đầu với đỉnh 1

    for (int i = 2; i <= n; ++i) {
        int u = i;            // Đỉnh hiện tại
        int v = *std::next(connected.begin(), std::rand() % connected.size()); // Đỉnh đã kết nối ngẫu nhiên
        edges.emplace_back(u, v);
        connected.insert(u);
    }

    // In ra các cạnh của cây

    for (const auto& edge : edges) {
        std::cout << edge.first  <<" "<< edge.second << std::endl;
    }
    cout << UID(0, 1) << ' ' << UID(1, n) << ' ' << UID(1, n);
    return 0;
}
