
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <queue>
#include <time.h>
#include <iomanip>
#include <fstream>

#define rep(index, from, to) for(int index = from; index < to; index++)
#define all(v) v.begin(),v.end()
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define MP make_pair


void solve(vector<vector<pair<int, int>>> &v, int c, vector<int> &dis, int dist, vector<bool> &vis) {
	if (dis[c] < dist) return;
	dis[c] = dist;
	trav(it, v[c]) {
		if (!vis[it->first]) {
			vis[it->first] = 1;
			solve(v, it->first, dis, dist + it->second, vis);
			vis[it->first] = 0;
		}
	}
}

double trivialAlghoritm(int n, vector<vector<pair<int,int>>> &v, int src) {
	time_t time = clock();
	vector<int> dis(n, 1e8);
	vector<bool> vis(n);
	solve(v, src, dis, 0, vis);
	//Shortest distance from source to node X is located in dist[X] (or 10^8 if there is no path)
	return clock() - time;
}


double dijkstrasAlghoritm(int n, vector<vector<pair<int, int>>> &v, int src) {
	time_t time = clock();
	priority_queue<pair<int, int>> pq;
	vector<int> dist(n, 1e8);
	vector<bool> vis(n);
	pq.push(MP(0, src));
	dist[src] = 0;
	while (!pq.empty()) {
		int c = pq.top().second;
		pq.pop();
		if (vis[c]) continue;
		vis[c] = 1;
		trav(it, v[c]) {
			if (dist[it->first] > dist[c] + it->second) {
				dist[it->first] = dist[c] + it->second;
				pq.push(MP(-dist[it->first], it->first));
			}
		}
	}
	//Shortest distance from source to node X is located in dist[X] (or 10^8 if there is no path)
	return clock() - time;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	ifstream file;
	file.open("Graph.txt");
	file >> n >> m;
	vector<vector<pair<int, int>>> a(n, vector<pair<int,int>>());
	for (int i = 0; i < m; i++)
	{
		int u, v, c;
		file >> u >> v >> c;
		a[u].push_back(MP(v, c));
		a[v].push_back(MP(u, c));
	}
	cout << setprecision(15) << fixed;
	cout << "Trivial alghoritm time used: " << trivialAlghoritm(n, a, 0) / CLOCKS_PER_SEC << endl;
	cout << "Dijkstras alghoritm time used: " << dijkstrasAlghoritm(n, a, 0) / CLOCKS_PER_SEC << endl;
	system("pause");
}
