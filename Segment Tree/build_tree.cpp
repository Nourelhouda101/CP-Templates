#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define ll long long
#define sp " "

void files() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
    #endif
}

vector<ll>segtree;
vector<ll>v;
void build_seg_tree(int n) { //for a sum tree
    // insert the initial array as the leaves of the tree
    for(int i = 0; i < n; i++)
    segtree[n + i] = v[i];

    //parent of node i = tree[i * 2] (+, min, max --> depeneds on your needs) tree[i * 2 + 1] 
    for(int i = n - 1; i >= 1; i--)
    segtree[i] = segtree[i * 2] + segtree[i * 2 + 1];
}

void solve() {
   ll n;
   cin >> n;
   v.resize(n);

   for(int i = 0; i < n; i++)
   cin >> v[i];

   //To make the array with power of 2 size to be able to devide by 2 every time.
   while(__builtin_popcountll(n) != 1) {
      n++;
      //push back something will not affect your result ex: sum --> 0, min --> LLONG_MAX..
      v.push_back(0);
   }

   //The size of the segment tree = 2 * n (n is now power of two)
   segtree.resize(n * 2);
   build_seg_tree(n);

   //Print
    int level_size = 1;
    int i = 1;
    while(i < 2 * n) {

        for(int j = 0; j < level_size && i < 2 * n; j++, i++)
        cout << segtree[i] << sp;

        cout << nl;
        level_size *= 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    files();
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();

        if (t != 0)
        cout << nl;
    }

    return 0;
}