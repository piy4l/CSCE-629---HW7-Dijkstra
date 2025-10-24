#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, w; };

int main() {
    string filename = "input.txt";
    ifstream fin(filename);
    if (!fin) {
        cerr << "Cannot open file" << filename << endl;
        return 1;
    }

    int n, m;  //vertices, edges
    fin >> n >> m;

    int s;  //source
    fin >> s;

    int k;  // how many destinations to report
    fin >> k;
    vector<int> targets(k);
    for (int i = 0; i < k; ++i) fin >> targets[i];

    // Undirected graph by default (roads are two-way)
    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    fin.close();

    const int INF = 1e9;
    vector<int> dist(n + 1, INF), parent(n + 1, -1);
    vector<char> used(n + 1, 0);
    dist[s] = 0;
    parent[s] = s;

    for(int iter = 0; iter < n; ++iter){
        int u = -1, best = INF;
        for(int v = 1; v <= n; ++v){
           if(!used[v] && dist[v] < best){
                best = dist[v];
                u = v;
            }
        }
        if (u == -1)
            break;
        used[u] = 1;
        for (const auto& e : g[u]) {
            if (!used[e.to] && dist[u] + e.w < dist[e.to]) {
                dist[e.to] = dist[u] + e.w;
                parent[e.to] = u;
            }
        }
    }

    cout << "Source: " << s << endl;
    for (int t : targets) {
        cout << "Destination " << t << ": ";
        if (t < 1 || t > n){
            cout << "invalid id" << endl;
            continue;
        }
        if (dist[t] == INF){
                cout << "unreachable" << endl;
                continue;
        }
        cout << "distance = " << dist[t] << "    path: ";
        vector<int> path;
        for (int cur = t; cur != parent[cur]; cur = parent[cur])
            path.push_back(cur);
        path.push_back(s);
        reverse(path.begin(), path.end());

        for (size_t i = 0; i < path.size(); ++i) {
            if (i) cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }
    return 0;
}
