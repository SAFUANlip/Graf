#include <iostream>
#include <vector>
using namespace std;

enum color
{
    white,
    gray,
    black
};

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

bool find_cycle_directed_dfs(const vector<vector<int>>& g, vector<color>& colors, int v)
{
    cout << "* in" << v << endl;
    colors[v] = gray;
    for (int u : g[v])
        if (colors[u] == gray || (colors[u] == white && find_cycle_directed_dfs(g, colors, u)))
            return true;
    colors[v] = black;
    cout << "** out" << v << endl;
    return false;
}

bool find_directed_cycle(const vector<vector<int>>& g)
{
    vector<color> colors(g.size(), white);
    for (int v = 0; v < g.size(); ++v)
        if (colors[v] == white && find_cycle_directed_dfs(g, colors, v))
            return true;
    return false;
}

bool find_cycle_dfs(const vector<vector<int>>& g, vector<color>& colors, int p, int v) //p-родитель, завели для неоргафа, чтобы мы не взяли за цикл 0-1 1-0
{
    cout << '* in' << v << endl;
    colors[v] = gray;
    for (int u : g[v])
        if (u != p && (colors[u] == gray || (colors[u] == white && find_cycle_dfs(g, colors, v, u))))
            return true;
    colors[v] = black;
    cout << "** out" << v << endl;
    return false;
}

bool find_cycle(const vector<vector<int>>& g)
{
    vector<color> colors(g.size(), white);
    for (int v = 0; v < g.size(); ++v)
        if (colors[v] == white && find_cycle_dfs(g, colors, -1, v))
            return true;
    return false;

}

void topologcy_sort_dfs(const vector<vector<int>>& g, vector<int>& res, vector<bool>& visited, int v)
{
    visited[v] = true;
    for (int u : g[v])
        if (!visited[u])
            topologcy_sort_dfs(g, res, visited, u);
    res.push_back(v);
}


void topologcy_sort(const vector<vector<int>>& g, vector<int>& res)
{
    vector<bool> visited(g.size());
    for (int v = 0; v < g.size(); ++v)
        if (!visited[v])
            topologcy_sort_dfs(g, res, visited, v);
    reverse(res.begin(), res.end()); //переворачиваем т.к. в начале нужны вершины, от которых исходят рёбра
}

int main()
{
    //неорграф
    int n, first, second, k;
    cin >> n >> k; //k-кол рёбер
    vector<vector<int>> g(n);
    for (int i = 0; i < k; ++i) {
        cin >> first >> second;
        g[first].push_back(second);
        //g[second].push_back(first); //теперь неориентированный
    }
    //cout << find_cycle(g);
    //cin >> first >> second;
    //cout << is_connected(v, first, second);
    /*vector<vector<int>> comp = components(v);
    for (int i = 0; i < comp.size(); ++i)
        for (int j = 0; j < comp[i].size(); ++j)
            cout << "comp " << i << " vertex " << comp[i][j] << endl;*/
    cout<<find_directed_cycle(g);
    //    for(auto x: v)
    //    {
    //        for(int s: x)
    //            cout << s << " ";
    //        cout << endl;
    //     }
    return 0;    
    
}

