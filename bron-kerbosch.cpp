/*
 *      O algoritmo de Bron-Kerbosch: 
 *
 *  Um algoritmo introduzido por Coen Bron 
 *  e Joep Kerbosch em 1973. Usado para 
 *  encontrar todos os cliques maximais 
 *  em um grafo bidirecional.
 *
 *  Complexidade: O(2^V)
 *
 */

#include <iostream>
#include <vector>
#include <set>
using namespace std;

void bronKerbosch(set<int> P, set<int> R, set<int> X, vector<vector<int>>& grafo){

    // Se o conjunto de P e X está vazio, isso signifca 
    // que não sobram mais candidatos, logo um clique 
    // foi encontrado seus vértices estão em R.
   if(P.size() == 0 and X.size() == 0){
        cout << "Clique encontrado:\n";
        for(const int &x : R )
            cout << x << ' ';
        cout << '\n';
        return;
   }

   // Verifica-se os cliques possíveis de todos os vértices candidatos
   set<int> __P = P;
   for(int p : __P){
       // Criam-se os conjuntos, derivados de P, X, R que irão gerar 
       // um novo clique
        set<int> _P, _X, _R = R;
        for(int adj : grafo[p]){
            if(P.count(adj))
                _P.insert(adj);
            if(X.count(adj))
                _X.insert(adj);
        }
        _R.insert(p);
        X.insert(p);
        bronKerbosch(_P, _R, _X, grafo);
        P.erase(p);
   }
}

int main(){
    cout << "Digite o número de vértices e de arestas no grafo:\n";
    
    // V := número de vértices
    // E := número de arestas
    int V, E; cin >> V >> E;

    // Aqui, o grafo será uma lista de adjacência.
    vector<vector<int>> grafo(V+1);

    cout << "Descreva a(s) aresta(s):\n";

    // Recebe E arestas
    for(int i = 0; i < E; ++i){
        int a, b; cin >> a >> b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    
    // Três conjuntos são criados
    // - Conjunto R: Vértices que são partes de um clique (Começa vazio)
    // - Conjunto P: Vértices candidatos, que têm ligação com todos os vértices de R. (Começa com todos os 
    // vértices do grafo)
    // - Conjunto X: Vértices já analisados ou que não podem ser adicionados em R (Começa vazio)

    set<int> R, X, P;

    // Popula P
    for(int i = 1; i <= V; ++i)
        P.insert(i);

    // Chama a função com todos os vértices do grafo em P 
    // Fazendo com que todos os cliques no grafo sejam 
    // encontrados
    bronKerbosch(P, R, X, grafo);

}
