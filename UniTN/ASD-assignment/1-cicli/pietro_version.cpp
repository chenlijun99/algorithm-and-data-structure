#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <queue>
using namespace std;
using namespace std::chrono;

struct nodo {
	vector <int> vic;
	bool visited;
};

void stampaArray (int arr[], int dim) {
	for (int i=0; i<dim;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
void stampaVertici (vector <nodo> g) {
	for (int i=0; i<g.size(); i++) {
		cout << i << " ";
	}
	cout << endl;
}

void stampaRichieste (vector <vector <int>> rich) {
	for (int i=0; i<rich.size(); i++) {
		cout << rich[i][0] << " " << rich[i][1] << endl;
	}
}

//	using erdos
int percorsoMinimo (vector <nodo> &g, int r, int f) {
	int erdos [g.size()];
	queue <int> q;
	q.push(r);

	for (int u=0; u<g.size(); u++) {
		erdos[u]=-1;
	}
	erdos[r]=0;

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i=0; i<g[u].vic.size(); i++) {
			int v = g[u].vic[i];
			if (erdos[v]==-1) {
				erdos[v]=erdos[u]+1;
				q.push(v);
				if (v==f)
					return erdos[f];
			}
		}
	}

	return 0;
}


int main (int argc, char *argv[]) {

	//auto start = high_resolution_clock::now();
	const char* input="input.txt";
	if (argc == 2) {
		input = argv[1];
	}
	else if (argc != 1) {
		cerr << "usage:: ./a.out [input]" << endl;
	}
	ifstream in(input);
	ofstream out("output.txt");

	vector <nodo> grafo;
	//vector <vector <int>> richieste;

	//---- N:=numero di nodi	M:=numero di archi	Q:= nr richieste
	int N, M, Q;
	in >> N;
	in >> M;
	in >> Q;
	grafo.resize(N);
	//richieste.resize(Q);

	for (int i=0; i<M; i++) {
		int from, to;
		in >> from >> to;
		grafo[from].vic.push_back(to);
		grafo[to].vic.push_back(from);
	}

	int s, f;
	for (int i=0; i<Q; i++) {
		//richieste[i].resize(2);
		//in >> richieste[i][0] >> richieste[i][1];
		in >> s >> f;
		out << percorsoMinimo(grafo, s, f) << endl;
	}

	/*
	for (int i=0; i<richieste.size();i++) {
		out << percorsoMinimo(grafo, richieste[i][0], richieste[i][1]) << endl;
	}
	*/
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << duration.count() << endl;
	return 0;
}