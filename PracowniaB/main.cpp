#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool func(int i, int j) { return (i>j); }

pair<int, int> pair_max(pair<int,int> a, pair<int, int> b)
{
  if(a.first> b.first) return a;
  if(a.first == b.first && a.second > b.second) return a;
  return b;
}

int main(){
  unsigned int num, tmp;
  unsigned int suffix_sum = 0;
  vector<int> odwiedzone;
  pair<int, int> zerowa = make_pair(0,0);
  scanf("%d", &num);
  vector<int> lego(num);
  for(int i=0; i<num; ++i) {
    scanf("%d", &tmp);
    lego[i] = tmp;
    suffix_sum += tmp;
  }
  sort(lego.begin(), lego.end(), func);
  vector<pair<int,int> > reszta(suffix_sum, make_pair(0,0));
  odwiedzone.reserve(suffix_sum);
  odwiedzone.push_back(0);
  for(int i=0; i<lego.size(); ++i)
  {
    vector<pair<int, int> > new_lego;
    new_lego.reserve(int(odwiedzone.size())*2);
    for(int j=0; j<odwiedzone.size(); ++j)
    {
      new_lego.push_back(make_pair(reszta[odwiedzone[j]].first + lego[i],
            reszta[odwiedzone[j]].second));
      if(reszta[odwiedzone[j]].second + lego[i] > reszta[odwiedzone[j]].first)
      {
        new_lego.push_back(make_pair( reszta[odwiedzone[j]].second + lego[i],
              reszta[odwiedzone[j]].first ) );
      } else {
        new_lego.push_back(make_pair( reszta[odwiedzone[j]].first
              , reszta[odwiedzone[j]].second + lego[i] ) );
      }
    }

    for(int k=0; k<new_lego.size(); ++k) {
      tmp = new_lego[k].first - new_lego[k].second;
      if(reszta[tmp] == zerowa && tmp != 0) {odwiedzone.push_back(tmp);}
      if(tmp < suffix_sum) {
        reszta[tmp] = pair_max(new_lego[k], reszta[tmp]);
      }
    }
    // suffix_sum -= lego[i];
    new_lego.clear();
  }
  for(int i=0; i<reszta.size(); ++i) {
    if(reszta[i] != zerowa) {
      tmp = i;
      break;
    } 
  }
  if(tmp == 0){
    printf("TAK\n%d\n", reszta[0].first);
    return 0;
  }
  printf("NIE\n%d\n", tmp);
  return 0;
}

