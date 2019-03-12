#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string add(string a, string b) {
    if (a.length() < b.length()) swap(a, b);
    auto ra = a.begin(), rb = b.begin();
    int carry = 0;
    string ans;
    while (ra != a.end() && rb != b.end()) {
        int tmp = *ra + *rb + carry - '0' - '0';
        carry = tmp / 10;
        ans += tmp % 10 + '0';
        ra++, rb++;
    }
    while (ra != a.end()) {
        int tmp = *ra + carry - '0';
        carry = tmp / 10;
        ans += tmp % 10 + '0';
        ra++;
    }
    if (carry) ans += "1";
    return ans;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    string roll[3] = {"1", "1"};
    vector<string> table;
    table.push_back("0");
    table.push_back("1");

    int last = 1;
    for (int i = 2; i < 20000; i++) {
        auto& t = roll[i % 3];
        t = add(roll[(i + 2) % 3], roll[(i + 1) % 3]);
        if (t.length() != last) {
            table.push_back(t);
            last = t.length();
        }
    }

    int t, x;
    cin >> t;
    cout << t << endl;
    while (t--) {
        cin >> x;
        cout << x << ' ';
        vector<int> cnt(10);
        for (auto rit = table[x].rbegin(); rit != table[x].rend(); rit++) {
            cnt[*rit - '0']++;
            cout << *rit;
        }
        for (int i = 0; i < 10; i++) {
            cout << ' ' << cnt[i];
        }
        cout << endl;
    }
}
