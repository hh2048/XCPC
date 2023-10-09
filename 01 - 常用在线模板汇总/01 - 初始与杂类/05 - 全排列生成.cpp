int n;
cin >> n;
vector<int> a(n);
// iota(a.begin(), a.end(), 1);
for (auto &it : a) {
    cin >> it;
}
sort(a.begin(), a.end());

do {
    for (auto it : a) {
        cout << it << " ";
    }
    cout << endl;
} while (next_permutation(a.begin(), a.end()));