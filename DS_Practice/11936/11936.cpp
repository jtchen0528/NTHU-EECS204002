#include <iostream>
#define INF 1e9

using namespace std;

int* dijsktra_lat_path(int **graph, int v, int bnum, int mood){
    int *d = new int[bnum];
    int *path = new int[bnum];
    bool visit[bnum];

    for(int i=0; i<bnum; i++){
        visit[i] =false;
        d[i] = graph[v][i];
        path[i] = -1;
        if(graph[v][i] != INF){
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
            if(!visit[b] && d[u] + graph[u][b] < d[b]){
                d[b] = d[u] + graph[u][b];
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


int main(){
	int matrixnum;
	cin >> matrixnum;
	for(int i=0; i<matrixnum; i++){
		int v;
		cin >> v;

		int **m = new int *[v];
		for(int j=0; j<v; j++){
			m[j] = new int [v];
			for(int k=0; k<v; k++){
				cin >> m[j][k];
				if(m[j][k]==0) m[j][k]=INF;
			}
		}
		
		int **dlat = new int *[v];
		for(int j=0; j<v; j++){
			dlat[j] = dijsktra_lat_path(m, j, v, 0);
		}

		for(int j=0; j<v; j++){
			for(int k=0; k<v; k++){
				if((dlat[j][k]!=0)&&(dlat[j][k]!=INF)){
					cout << "Cost(" << j << "," << k << "):" << dlat[j][k] << endl;
				}
			}
		}
		if(i!=matrixnum-1){
			cout << endl;
		}
	}
}
