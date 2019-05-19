#include<iostream>
#include<queue>
#include<vector>
#define INF 1e9

using namespace std;

struct edge{
	int dst, lat, band;
};

void printgraph(vector<vector<edge> > graph){
	for(int i=0; i<graph.size(); i++){
		for(int j=0; j<graph[i].size(); j++){
			cout <<" ("<< graph[i][j].dst << "," << graph[i][j].lat << "," <<graph[i][j].band<< ") ";
		}
		cout << endl;
	}
}

void printgraph2(edge **graph, int bnum){
	for(int i=0; i<bnum; i++){
		for(int j=0; j<bnum; j++){
			cout <<" ("<< graph[i][j].dst << "," << graph[i][j].lat << "," <<graph[i][j].band<< ") ";
		}
		cout << endl;
	}
}

vector<int > findminpath(vector<vector<edge> > graph, vector<int> d, int bnum){
	d = vector<int > (bnum, INF);
	d[0] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push({0, 0});
	while (!pq.empty()){
		auto tmp = pq.top();
		pq.pop();
		int u = tmp.second;
		if(tmp.first != d[u]) continue;
		for(int i=0; i<graph[u].size(); i++){
			edge &e = graph[u][i];
			if(d[e.dst] > d[u] + e.lat){
				d[e.dst] = d[u] + e.lat;
				pq.push(make_pair(d[e.dst], e.dst));
			}
		}
	}
	return d;
}

vector<int > findmaxband(vector<vector<edge> > graph, vector<int> d, int bnum){
	d = vector<int > (bnum, 0);
	d[0] = INF;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	pq.push({INF, 0});
	while (!pq.empty()){
		auto tmp = pq.top();
		pq.pop();
		int u = tmp.second;
		if(tmp.first != d[u]) continue;
		for(int i=0; i<graph[u].size(); i++){
			edge &e = graph[u][i];
			if(d[e.dst] < min(d[u], e.band)){
				d[e.dst] = min(d[u], e.band);
				pq.push(make_pair(d[e.dst], e.dst));
			}
		}
	}
	return d;
}

int* dijsktra_lat_path(edge **graph, int v, int bnum, int mood){
	int *d = new int[bnum];
	int *path = new int[bnum];
	bool visit[bnum];

	for(int i=0; i<bnum; i++){
		visit[i] =false;
		d[i] = graph[v][i].lat;
		path[i] = -1;
		if(graph[v][i].lat != INF){
			path[i] = v;
		}
	}

	int min, u=-1;
	d[v] = 0;

	for(int k=0; k<bnum; k++){
		int b, i;
		min=INF;
		for(i=0; i<bnum; i++){
			if(!visit[i] && d[i] < min){
				u=i;
				min=d[i];
			}
		}
		
		visit[u] = true;
		for(b=0; b<bnum; b++){
			if(!visit[b] && d[u] + graph[u][b].lat < d[b]){
				d[b] = d[u] + graph[u][b].lat;
				path[b] = u;
			}
		}
	}
	if(mood==0){
		return d;
	}else{
		return path;
	}
}

int* dijsktra_band_path(edge **graph, int v, int bnum, int mood){
	int *d = new int[bnum];
	int *path = new int[bnum];
	bool visit[bnum];

	for(int i=0; i<bnum; i++){
		visit[i] =false;
		d[i] = graph[v][i].band;
		path[i]=-1;
		if(graph[v][i].band!=-1){
			path[i] = v;
		}
	}

	int max, u;
	d[v] = 0;

	for(int k=0; k<bnum-1; k++){
		int b, i;
		max=-1;
		for(i=0; i<bnum; i++){
			if(!visit[i] && d[i] > max){
				u=i;
				max=d[i];
			}
		}
		visit[u] = true;
		for(b=0; b<bnum; b++){
			if((!visit[b])&&(graph[u][b].band!=-1)){
				if(d[b]==-1){
                    d[b] = graph[u][b].band;
					path[b]=u;
                    if(max<graph[u][b].band){
                        d[b] = max;
						path[b]=u;
                    }
                }else{
                    if((graph[u][b].band > d[b])){
                        d[b] = graph[u][b].band;
						path[b]=u;
                        if(max < d[b]){
                            d[b] = max;
							path[b]=u;
                        }
                    }
				}
			}
		}
	}
	if(mood==0){
		return d;
	}else{
		return path;
	}
}

void printpath(int *path, int dst, int bnum){
	cout << dst << "->";
	if(path[dst]==0){
		cout << path[dst];
	}else if(path[dst]==-1){

	}else{
		printpath(path, path[dst], bnum);
	}
}

void BFS(edge **graph, int bnum){
    queue<int> q;
	bool visit[bnum];
    for (int i=0; i<bnum; i++){
        visit[i] = false;
 	}
    for (int k=0; k<bnum; k++){
        if (!visit[k]){
            q.push(k);
            visit[k] = true;
            while (!q.empty()){
                int i = q.front(); q.pop();
				cout << i;
 
                for (int j=0; j<bnum; j++){
                    if (graph[i][j].lat!=INF && !visit[j]){
                        q.push(j);
                        visit[j] = true;
                    }
				}
            }
        }
	}
	cout << endl;
}

bool *visitDFS;	
void DFS(edge **graph, int i, int bnum)
{
    if (visitDFS[i]) return;
    visitDFS[i] = true;
	cout << i;

    for (int j=0; j<bnum; j++){
        if (graph[i][j].lat != INF){
            DFS(graph, j, bnum);
		}
	}	
}

void DFStraversal(edge **graph, int bnum)
{
	visitDFS = new bool[bnum];
    for (int i=0; i<bnum; i++){
        visitDFS[i] = false;
	}
    for (int i=0; i<bnum; i++){
        DFS(graph, i, bnum);
	}
	cout << endl;
}

int main() {
	int bnum, conn;
	cin >> bnum >> conn;

//	vector<vector<edge> > graph(bnum);

	edge **graph2 = new edge *[bnum];
	for(int i=0; i<bnum; i++){
		graph2[i] = new edge[bnum];
		for(int j=0; j<bnum; j++){
			graph2[i][j].dst=-1;
			graph2[i][j].lat=INF;
			graph2[i][j].band=-1;
		}
	}

	for(int i=0; i<conn; i++){
		int id, dst, lat, band;
		cin >> id >> dst >> lat >> band;
//		graph[id].push_back({dst, lat, band});
		graph2[id][dst] = {dst, lat, band};
	}

//	printgraph(graph);
//	printgraph2(graph2, bnum);
/*
	vector<int > dlat;
	dlat = findminpath(graph, dlat, bnum);
	
	vector<int > dband;
	dband = findmaxband(graph, dband, bnum);
*/
	int *dlat2, *dband2;
	dlat2 = dijsktra_lat_path(graph2, 0, bnum, 0);
	dband2 = dijsktra_band_path(graph2, 0, bnum, 0);

	int *dlatpath, *dbandpath;
	dlatpath = dijsktra_lat_path(graph2, 0, bnum, 1);
	dbandpath = dijsktra_band_path(graph2, 0, bnum, 1);
/*
	BFS(graph2, bnum);
	DFStraversal(graph2, bnum);
*/	
	for(int i=1; i<bnum; i++){
		cout << i << " ";
/*
		dlat[i] == INF ? cout << "inf" : cout << dlat[i];
		cout << " " << dband[i];
*/
		dlat2[i] == INF ? cout << "inf" : cout << dlat2[i];
		dband2[i] == -1 ? cout << " 0" : cout <<" "<< dband2[i];
/*
		cout << " lat_path: ";
		printpath(dlatpath, i, bnum);
		cout << " band_path: ";
		printpath(dbandpath, i, bnum);
*/		
		cout << endl;
	}	

}
