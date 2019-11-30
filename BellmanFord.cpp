#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
#define forn(i, n) for (ll i = 0; i < n; i++)
#define forn1(i, n) for (ll i = 1; i <= n; i++)
#define EPS 1e-9
#define pb push_back
#define sortx(x) sort(x.begin(), x.end())

const int MAX{1010}, oo{1000000010};
int dist[MAX], soldados[MAX];

double bellman_ford(ll saida, ll chegada, ll n_estradas, ll n_balas, double probabilidade, const vector<pair<ll, ll>> arestas)
{
    for (int i = 1; i <= n_estradas; ++i)
    {
        dist[i] = oo;
    }

    dist[saida] = soldados[saida];

    for (int i = 1; i <= n_estradas - 1; i++)
    {
        bool atualizou = false;

        for (const auto &[u, v] : arestas)
        {
            // cout << "ARESTA u = " << u << " v = " << v << endl;
            if (dist[v] > dist[u] + soldados[v])
            {
                // cout << "dist[ " << v << " ] = " << dist[v] << " > dist[ " << u << " ] = " << dist[u] << " + soldados[ " << v << " ] = " << soldados[v] << endl;
                dist[v] = dist[u] + soldados[v];
                atualizou = true;
            }
        }
        if(not atualizou)
            break;
    }
    if (dist[chegada] > n_balas)
        return 0.0;
    
    return pow(probabilidade, dist[chegada]);
}

int main()
{
    ios::sync_with_stdio(0);

    ll n_pontos_estrategicos, n_estradas, n_balas;
    double probabilidade_de_matar;

    while (cin >> n_pontos_estrategicos >> n_estradas >> n_balas >> probabilidade_de_matar)
    {
        vector<pair<ll, ll>> estradas_peso;
        memset(soldados, 0, sizeof(soldados));

        ll ponto1, ponto2;
        forn(i, n_estradas)
        {
            cin >> ponto1 >> ponto2;
            estradas_peso.pb({ponto1, ponto2});
            estradas_peso.pb({ponto2, ponto1});
        }
        ll n_soldados;
        cin >> n_soldados;

        ll pos;
        forn(i, n_soldados)
        {
            cin >> pos;
            soldados[pos]++;
        }

        ll ponto_partida, ponto_chegada;
        cin >> ponto_partida >> ponto_chegada;
        auto resposta = bellman_ford(ponto_partida, ponto_chegada, n_pontos_estrategicos, n_balas, probabilidade_de_matar, estradas_peso);
        cout.precision(3);
        cout << fixed << resposta << '\n';

    }
    return 0;
}
