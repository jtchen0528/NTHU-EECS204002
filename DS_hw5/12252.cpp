#include<iostream>
#include<memory.h>

using namespace std;

struct Node{
	int target;
	int lat;
	int band;
	Node *next; 
};

Node *insert(Node *graph,int id, int target,int lat,int band){
	if(graph == NULL){
		struct Node *new_node = new Node;
		new_node->target = target;
		new_node->lat = lat;
		new_node->band = band;
		graph = new_node;
		return graph;
	}else{
		struct Node *ptr = graph;
		while(graph->next!=NULL){
			graph = graph->next;
		}
		struct Node *new_node = new Node;
		new_node->target = target;
		new_node->lat = lat;
		new_node->band = band;
		graph->next = new_node;
		return ptr;
	}
}

void printlist(Node *graph[], int bnum){
	for(int i=0; i<bnum; i++){
		cout << "graph" << i << endl;
		while(graph[i]!=NULL){
			cout << graph[i]->target << " " << graph[i]->lat << " " << graph[i]->band << endl;
			graph[i] = graph[i]->next;
		}
	}
}

int* dijkstra_lat(Node *graph[], int source, int bnum)
{

	int *d = new int[bnum]; 
	bool visit[bnum]; 
   
  	for (int i=0; i<bnum; i++) visit[i] = false;
    for (int i=0; i<bnum; i++){
		d[i] = 1e9;
	}
 
	struct Node *ptr;
	int lat=1e9;
    
	d[source] = 0;
 
    for (int k=0; k<bnum; k++)
    {
        int a = -1, b = -1, min = 1e9;
        for (int i=0; i<bnum; i++){
            if (!visit[i] && d[i] < min)
            {
                a = i;
                min = d[i];
            }
 		}

        if (a == -1) break;
        visit[a] = true;

        for (b=0; b<bnum; b++){
			ptr = graph[a];
			lat = 1e9;
			while(ptr!=NULL){
				if(ptr->target == b){
					lat = ptr->lat;
				}
//				cout << ptr->lat << endl;
				ptr=ptr->next;
			}
            if (!visit[b] && d[a] + lat < d[b])
            {
                d[b] = d[a] + lat;
            }
		}
    }
	return d;
}

int* dijkstra_band(int **band, int v, int bnum)
{
	int *d = new int[bnum];
	bool visit[bnum];

    for (int i=0; i<bnum; i++){
		visit[i] = false;
		d[i] = band[v][i];
	}
 
	int max;
	int u;
    
	d[v] = 0;
 
    for (int k=0; k<bnum-1; k++)
    {
        int b, i;
		max=-1;
        for (i=0; i<bnum; i++){
            if (!visit[i] && d[i] > max)
            {
                u = i;
                max = d[i];
            }
 		}

        visit[u] = true;

        for (b=0; b<bnum; b++){
            if ((!visit[b])&&(band[u][b]!=-1)){ 
				if(d[b]==-1){
					d[b] = band[u][b];
					if(max<band[u][b]){
               		 	d[b] = max;
					}	
           		}else{
					if((band[u][b] > d[b])){
						d[b] = band[u][b];
						if(max < d[b]){
							d[b] = max;
						}
					}
				}
			}
		}
    }
	return d;
}

void printmatrix(int m[8][8]){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(m[i][j]==1e9){
				cout << "_ ";
			}else{
				cout << m[i][j] << " " ;
			}
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
	int bnum, conn;
	int id, target, lat, band;
	int *dlat, *dband;

	cin >> bnum >> conn;
//	cout << bnum << " " << conn << endl;
	struct Node *graph[bnum];
	int **bands = new int*[bnum];

	for(int i=0; i<bnum; i++){
		graph[i] = NULL;
	}

	for(int i=0; i<bnum; i++){
		bands[i] = new int[bnum];
		for(int j=0; j<bnum; j++){
			bands[i][j] = -1;
		}
	}
	
	while(conn>0){
		cin >> id >> target >> lat >> band;
		graph[id] = insert(graph[id], id, target, lat, band);
		bands[id][target] = band;
		conn--;
	}

//	cout << "start finding min lat"<< endl;
	
	dlat = dijkstra_lat(graph, 0, bnum);

	dband = dijkstra_band(bands, 0, bnum);
	for(int i=1; i<bnum; i++){
		if(dlat[i] == 1e9){
			cout << i << " " << "inf";
		}else{
			cout << i << " " << dlat[i];
		}
		if(dband[i]==-1){
			cout << " " << "0" << endl;
		}else{
			cout << " " << dband[i] << endl;
		}
	}

//	printlist(graph, bnum);
	
}
