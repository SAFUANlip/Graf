﻿#include "Graf.h"
using namespace std;

int main()
{
    
/*Little bit chenges for seting
github working	
*/	


//Second commit, to check pull
//
//
    //неорграф
    int n, m;
    cin >> n >> m; //k-кол рёбер
    UnGraf gr(n, m);
    auto res = gr.find_bridge();
    for (auto e : res) {
        cout << e.first << " " << e.second << endl;
    }
    //cout << find_cycle(g);
    //cin >> first >> second;
    //cout << is_connected(v, first, second);
    /*vector<vector<int>> comp = components(v);
    for (int i = 0; i < comp.size(); ++i)
        for (int j = 0; j < comp[i].size(); ++j)
            cout << "comp " << i << " vertex " << comp[i][j] << endl;*/
            //cout<<find_directed_cycle(g);
            //    for(auto x: v)
            //    {
            //        for(int s: x)
            //            cout << s << " ";
            //        cout << endl;
            //     }
    return 0;

}

