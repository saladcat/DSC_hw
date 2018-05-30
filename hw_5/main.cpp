
// similar with HDOJ 1385 floyd-warshell
#include <cstdio>
#include <iostream>
#include <cstring>


const int INF = 0x3f3f3f3f;
using namespace std;
int dist[105][105];
int graph[105][105];
int nxtVectrix[105][105];// nxtVectrix[i][j] from i to j the next vectrix is
int numVectrix;

void prtPath(int i, int j) {
    if (nxtVectrix[i][j] == -1) {
        return;
    }
    printf("Path(%d,%d):", i, j);
    cout << i;
    while (i != j) {
        i = nxtVectrix[i][j];
        cout << "->" << i;
    }
    cout << endl;
}

int main() {
    cin >> numVectrix;
    for (int i = 0; i < numVectrix; i++) {
        for (int j = 0; j < numVectrix; j++) {
            cin >> graph[i][j];
        }
    }
    for (int i = 0; i < numVectrix; i++) {
        for (int j = 0; j < numVectrix; ++j) {
            if (graph[i][j] == 0) {
                dist[i][j] = INF;
                nxtVectrix[i][j] = -1;
            } else {
                dist[i][j] = graph[i][j];
                nxtVectrix[i][j] = j;
            }
        }
    }

    for (int k = 0; k < numVectrix; k++) {
        for (int i = 0; i < numVectrix; ++i) {
            for (int j = 0; j < numVectrix; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxtVectrix[i][j] = nxtVectrix[i][k];
                } else if (dist[i][k] + dist[k][j] == dist[i][j] && nxtVectrix[i][k] < nxtVectrix[i][j]) {
                    nxtVectrix[i][j] = nxtVectrix[i][k];
                }
            }
        }
    }
    for (int i = 0; i < numVectrix; ++i) {
        for (int j = 0; j < numVectrix; ++j) {
            if (i != j && nxtVectrix[i][j] != -1) {
                prtPath(i, j);
                cout << "Cost:" << dist[i][j] << endl;
            }
        }
    }
    return 0;
}



























