#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
using namespace std;

const int MAXSUM=1000001;
int suffix_sum = 0;
int pierwsza_niezerowa = MAXSUM;
vector<int> lego;
map<int, int> reszta;
map<int, int> buffer;

bool func(int i, int j)
{
    return (i>j);
}

void read_data()
{
    int num, tmp;
    scanf("%d", &num);
    for(int i=0; i<num; ++i) {
        scanf("%d", &tmp);
        lego.push_back(tmp);
        suffix_sum += tmp;
    }
}

void buffer_push(const int a, const int b)
{
    const int mi = min(a,b);
    const int mx = max(a,b);
    const int tmp = mx - mi;
    if(tmp < suffix_sum + pierwsza_niezerowa) {
      if(buffer.find(tmp) != buffer.end()){
        buffer[tmp] = max(mx, buffer[tmp]);
      } else {
        buffer[tmp] = mx;
      }
    }
}

void flush_buffer()
{
  for(map<int, int>::iterator i=buffer.begin(); i != buffer.end(); ++i) {
      int key = i->first;
      reszta[key] = max(i->second, reszta[key]);
      if(reszta[key] - key != 0 && key < pierwsza_niezerowa) {
          pierwsza_niezerowa = key;
      }
  }
  buffer.clear();
}

void crunch_data()
{
    sort(lego.begin(), lego.end(), func);
    reszta[0] = 0;
    for(int i=0; i<lego.size(); ++i) {
        for(map<int, int>::iterator j=reszta.begin(); j != reszta.end(); ++j) {
            int higher = j->second;
            int lower = j->second - j->first;
            buffer_push( higher + lego[i],
                            lower);

            buffer_push( lower + lego[i],
                           higher);
        }
        flush_buffer();
        suffix_sum -= lego[i];
    }
}

void output_solution()
{
  int tmp;
    for(map <int, int>::iterator i=reszta.begin(); i != reszta.end(); ++i) {
        if((i->second - i->first) != 0) {
            tmp = i->first;
            break;
        }
    }
    if(tmp == 0) {
        printf("TAK\n%d\n", reszta[0]);
        exit(0);
    }
    printf("NIE\n%d\n", tmp);
    exit(0);
}

int main()
{
    read_data();
    crunch_data();
    output_solution();
}

