
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <queue>
#include <time.h>
#include <fstream>

#define rep(index, from, to) for(int index = from; index < to; index++)
#define all(v) v.begin(),v.end()
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)


vector<unordered_set<int>> con;
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	srand(time(NULL));
	int n, m;
	cout << "N ? ";
	cin >> n;
	cout << "M ? ";
	cin >> m;
	ofstream file;
	file.open("graph.txt");
	con.resize(n);
	vector<pair<pair<int, int>, int>> cons;
	int x = 0;
	if (m >= n * (n - 1) / 2) //Fully-connected
	{
		m = n * (n - 1) / 2;
		cons.resize(m);
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				cons[x].first.first = i;
				cons[x].first.second = j;
				cons[x].second = rand() % 1000;
				x++;
			}
		}
	}
	else {
		cons.resize(m);
		for (int i = 0; i < min(n, m); i++)
		{
			while (1) {
				int to = rand() % n;
				if (con[i].find(to) == con[i].end() && to != i) {
					con[i].insert(to);
					con[to].insert(i);
					cons[x].first.first = i;
					cons[x].first.second = to;
					cons[x].second = rand() % 1000;
					x++;
					break;
				}
			}
		}
		for (int i = 0; i < m - min(m, n); i++)
		{
			while (1) {
				int fr = rand() % n;
				int to = rand() % n;
				if (con[fr].find(to) == con[fr].end() && to != fr) {
					con[fr].insert(to);
					con[to].insert(fr);
					cons[x].first.first = fr;
					cons[x].first.second = to;
					cons[x].second = rand() % 1000;
					x++;
					break;
				}
			}
		}
	}
	random_shuffle(all(cons));
	file << n << " " << m << endl;
	trav(it, cons) {
		file << it->first.first << " " << it->first.second << " " << it->second << endl;
	}
	file.close();
#ifdef _DEBUG
	system("pause");
#endif // _DEBUG

}
