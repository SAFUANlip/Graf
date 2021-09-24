#include <iostream>
#include <vector>
using namespace std;

class Graf {
    
public:
    Graf(int n, int m) : ver{ n }, ed{ m } { g.resize(ver); };

    bool connect(int first, int second) {
        if (first >= g.size() || second >= g.size()) {
            cout << "The graph has no such vertices";
            return false;
        }
        vector<bool> vis(g.size());
        return(is_connected_dfs(vis, first, second));
    }

    vector<vector<int>> components() {
        vector<int> c(g.size(), -1);
        int ci = 0;
        for (int v = 0; v < g.size(); ++v)
            if (c[v] == -1)
                components_dfs(c, v, ci++);

        return(make_components(c, ci));
    }


private:
    bool is_connected_dfs(vector<bool>& visited, int v, int v1) {
        cout << "Current vertex " << v << endl;

        visited[v] = true;
        if (v == v1) {
            return true;
        }
        for (int u : g[v])
            if (!visited[u] && is_connected_dfs(visited, u, v1))
                return true;
        return false;
    }

    

protected:
    enum color
    {
        white,
        gray,
        black
    };

    int ver, ed;
    vector<vector<int>> g;

    ~Graf() {
        g.clear();
    }
    virtual bool find_cycle() = 0;
    
    void components_dfs(vector<int>& c, int v, int ci) {
        c[v] = ci;
        for (int u : g[v])
            if (c[u] == -1)
                components_dfs(c, u, ci);
    }

    vector<vector<int>> make_components(vector<int> &c, int count)
    {
        vector<vector<int>> comp(count);
        for (int v = 0; v < c.size(); ++v)
            comp[c[v]].push_back(v);
        return comp;
    }
};

class DirGraf : public Graf {

public:
    DirGraf(int n, int m):Graf(n, m) {
        int first, second;
        for (int i = 0; i < ed; ++i) {
            cin >> first >> second;
            g[first].push_back(second);
        }
    }

    void top_sort() {
        if (this->find_cycle()) {
            cout << "in cycle graf can't be top sort";
            return;
        }
        topologcy_sort();
        
    }

    bool find_cycle() override
    {
        vector<color> colors(g.size(), white);
        for (int v = 0; v < g.size(); ++v)
            if (colors[v] == white && find_cycle_directed_dfs(colors, v))
                return true;
        return false;
    }

    /*void find_bridge()
    {

    }*/
 
    vector<vector<int>> kosaraju()
    {
        inverted = invert();
        vector<bool> visited(inverted.size());
        vector<int> out(inverted.size());

        for (int v = 0; v < inverted.size(); ++v)
            if (!visited[v])
                dfs_kos(visited, out, v);
        reverse(out.begin(), out.end());

        vector<int> c(g.size(), -1);
        int ci = 0;
        for (int i = 0; i < g.size(); ++i)
            if (c[out[i]] == -1)
                components_dfs(c, out[i], ci++);
        return(make_components(c, ci));
    }

private:
    vector<int> top_s;
    vector<vector<int>> inverted;

    void dfs_kos(vector<bool> & visited, vector<int>& out, int v)
    {
        visited[v] = true;
        for (int u : inverted[v])
            if (!visited[u])
                dfs_kos(visited, out, u);
        out.push_back(v);
    }

    vector<vector<int>> invert()
    {
        inverted.resize(g.size());
        for (int v = 0; v < g.size(); ++v)
            for (int u : g[v])
                inverted[u].push_back(v);
        return inverted;
    }

    void topologcy_sort()
    {
        vector<bool> visited(g.size());
        for (int v = 0; v < g.size(); ++v)
            if (!visited[v])
                topologcy_sort_dfs(visited, v);
        reverse(top_s.begin(), top_s.end()); //переворачиваем т.к. в начале нужны вершины, от которых исходят рёбра
    }

    void topologcy_sort_dfs(vector<bool>& visited, int v)
    {
        visited[v] = true;
        for (int u : g[v])
            if (!visited[u])
                topologcy_sort_dfs(visited, u);
        top_s.push_back(v);
    }

    bool find_cycle_directed_dfs(vector<color>& colors, int v)
    {
        cout << "* in" << v << endl;
        colors[v] = gray;
        for (int u : g[v])
            if (colors[u] == gray || (colors[u] == white && find_cycle_directed_dfs(colors, u)))
                return true;
        colors[v] = black;
        cout << "** out" << v << endl;
        return false;
    }
};

class UnGraf : public Graf {

public:
    UnGraf(int n, int m) : Graf(n, m) {
        int first, second;
        for (int i = 0; i < ed; ++i) {
            cin >> first >> second;
            g[first].push_back(second);
            g[second].push_back(first); //теперь неориентированный
        }
    }

    bool find_cycle() override
    {
        vector<color> colors(g.size(), white);
        for (int v = 0; v < g.size(); ++v)
            if (colors[v] == white && find_cycle_dfs(colors, -1, v))
                return true;
        return false;
    }

private:
    bool find_cycle_dfs(vector<color>& colors, int p, int v) //p-родитель, завели для неоргафа, чтобы мы не взяли за цикл 0-1 1-0
    {
        cout << "* in " << v << endl;
        colors[v] = gray;
        for (int u : g[v])
            if (u != p && (colors[u] == gray || (colors[u] == white && find_cycle_dfs(colors, v, u))))
                return true;
        colors[v] = black;
        cout << "** out " << v << endl;
        return false;
    }
};
