#include <iostream>
#include <vector>
using namespace std;

bool is_connected_dfs(const vector<vector<int>>& g, vector<bool>& visited, int v, int v1) {
    cout << "Current vertex " << v << endl;

    visited[v] = true;
    if (v == v1) {
        return true;
    }
    for (int u : g[v])
        if (!visited[u] && is_connected_dfs(g, visited, u, v1))
            return true;
    return false;
}

void components_dfs(const vector<vector<int>>& g, vector<int>& c, int v, int ci) {
    c[v] = ci;
    for (int u : g[v])
        if (c[u] == -1)
            components_dfs(g, c, u, ci);
}

vector<vector<int>> components(const vector<vector<int>>& g) {
    vector<int> c(g.size(), -1);
    int ci = 0;
    for (int v = 0; v < g.size(); ++v)
        if (c[v] == -1)
            components_dfs(g, c, v, ci++);
    vector<vector<int>> comp(ci);
    for (int v = 0; v < c.size(); ++v)
        comp[c[v]].push_back(v);

    return comp;
}

bool is_connected(const vector<vector<int>>& v, int first, int second) {
    vector<bool> vis(v.size());
    return is_connected_dfs(v, vis, first, second);
}

int main()
{
    //неорграф
    int n, first, second, k;
    cin >> n >> k; //k-кол рёбер
    vector<vector<int>> v(n);
    for (int i = 0; i < k; ++i) {
        cin >> first >> second;
        v[first].push_back(second);
        v[second].push_back(first); //теперь ориентированный
    }
    //cin >> first >> second;
    //cout << is_connected(v, first, second);
    vector<vector<int>> comp = components(v);
    for (int i = 0; i < comp.size(); ++i)
        for (int j = 0; j < comp[i].size(); ++j)
            cout << "comp " << i << " vertex " << comp[i][j] << endl;
    return 0;
}

