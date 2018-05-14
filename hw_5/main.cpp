// C Program for Floyd Warshall Algorithm
#include <cstdio>
#include <iostream>
#include <cstring>

#define INF 99999
using namespace std;
int dist[105][105];
int graph[105][105];
int passNode[105][105] = {};
int cntVectrix;

void getPath(int i, int j) {
    if (i == j) { return; }
    if (passNode[i][j] == -1) { printf("->%d", j); }
    else {
        getPath(i, passNode[i][j]);
        getPath(passNode[i][j], j);
    }

}

void floydWarshall() {
    int i, j, k;
    for (i = 0; i < cntVectrix; i++) {
        for (j = 0; j < cntVectrix; j++) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = graph[i][j];
            }
        }
    }

    for (k = 0; k < cntVectrix; k++) {
        for (i = 0; i < cntVectrix; i++) {
            for (j = 0; j < cntVectrix; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    passNode[i][j] = k;
                }
            }
        }
    }
}

int main() {
    cin >> cntVectrix;
    memset(passNode, 0xffffffff, sizeof(passNode));
    for (int i = 0; i < cntVectrix; i++) {
        for (int j = 0; j < cntVectrix; j++) {
            cin >> graph[i][j];
        }
    }
    floydWarshall();
    for (int i = 0; i < cntVectrix; i++) {
        for (int j = 0; j < cntVectrix; j++) {
            if (i == j) {
                continue;
            }
            if (dist[i][j] < INF) {
                cout << "Path(" << i << "," << j << "):";
                cout << i;
                getPath(i, j);
                cout << endl;
                cout << "Cost:" << dist[i][j] << endl;

            }
        }
    }


    return 0;
}
