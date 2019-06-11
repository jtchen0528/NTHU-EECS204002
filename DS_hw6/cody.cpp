#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int freq, key;
    char val;
    shared_ptr<Node> left, right;
    Node(int c, int v, int k)
        : freq(c), val(v), key(k), left(nullptr), right(nullptr) {}
    Node(int c, int k, shared_ptr<Node>& l, shared_ptr<Node>& r)
        : freq(c), key(k), left(l), right(r) {}
};

using node_ptr = shared_ptr<Node>;

void dfs(node_ptr x, vector<bool>& his, vector<vector<bool>>& decode) {
    if (x == nullptr) return;
    if (x->val != '\0') {
        decode[x->val - 'a'] = his;
        return;
    }
    his.push_back(0);
    dfs(x->left, his, decode);
    his.pop_back();
    his.push_back(1);
    dfs(x->right, his, decode);
    his.pop_back();
}

int main() {
    int n, cur_key = 1;
    char c;
    string s;
    cin >> n >> c >> s;
    
	auto cmp = [](node_ptr& a, node_ptr& b) -> bool {
        if (a->freq == b->freq) {
            return a->key > b->key;
        }
        return a->freq > b->freq;
    };

    priority_queue<node_ptr, vector<node_ptr>, decltype(cmp)> pq(cmp);

    vector<int> cnt(26), appear(26, -1);
    while (c = cin.get(), ~c) {
        if (c == ' ' || c == '\n') continue;
        cnt[c - 'a']++;
        if (appear[c - 'a'] == -1) appear[c - 'a'] = cur_key++;
    }
    
	for (int i = 0; i < 26; i++) {
        if (cnt[i] == 0) continue;
        pq.push(make_shared<Node>(cnt[i], 'a' + i, appear[i]));
    }

    while (pq.size() > 1) {
        auto tmp1 = pq.top();
        pq.pop();
        auto tmp2 = pq.top();
        pq.pop();
        pq.push(
            make_shared<Node>(tmp1->freq + tmp2->freq, cur_key++, tmp1, tmp2));
    }

    vector<bool> his;
    vector<vector<bool>> decode(26);
    dfs(pq.top(), his, decode);

    for (char i : s) {
        for (bool j : decode[i - 'a']) cout << j;
    }
    cout << endl;
}
