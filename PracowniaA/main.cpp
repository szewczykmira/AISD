#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAXSIZE = 200010;
vector<vector<int> > graf(MAXSIZE);
map<pair<int, int>,int> edge_cost;
vector <int> stos;
vector <int> dfs_stos;
vector <bool> odwiedzone(MAXSIZE, false);

void print_solution()
{
  printf("%d \n", int(stos.size()));
  int length, to, from = stos[0];
  for(int i=1; i<stos.size(); i++) {
    to = stos[i];
    length = edge_cost[pair<int,int>(from, to)];
    printf("%d %d %d\n", from, length, to);
    from = to;
  }
  to = 0;
  length = edge_cost[pair<int,int>(from, to)];
  printf("%d %d %d\n", from, length, to);
}

bool ZnajdzCykl()
{
  int aktualny;
  dfs_stos.push_back(0);
  while(!dfs_stos.empty()) {
    aktualny = dfs_stos.back();
    dfs_stos.pop_back();

    if(aktualny == -1) {
      stos.pop_back();
      continue;
    }

    odwiedzone[aktualny] = true;

    stos.push_back(aktualny);
    dfs_stos.push_back(-1);

    for(int i=0; i<graf[aktualny].size(); i++) {
      int next = graf[aktualny][i];
      if(next == 0) {
        print_solution();
        exit(0);
      }
      if(odwiedzone[next] != true ) {
        dfs_stos.push_back(next);
      }
    }
  }
  return false;
}

int main()
{
    int num, l, m, r;
    scanf("%d", &num);
    // Tworzenie listy sąsiedztwa
    for(int i=0; i<num; ++i) {
        scanf("%d %d %d", &l, &m, &r);
        graf[l].push_back(r);
        edge_cost[pair<int,int>(l,r)] = m;
    }
    //Zaczynamy czesc glowna programu
    ZnajdzCykl();
    printf("BRAK\n");
    return 0;
}
