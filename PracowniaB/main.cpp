#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
using namespace std;

const int MAXSUM=1000001;
int suffix_sum = 0, max_sum = 0;
int pierwsza_niezerowa = MAXSUM;
vector<int> lego;
vector<int> reszta(MAXSUM+1, 0);
vector<int> buffer(MAXSUM+1, 0);

bool func(int i, int j)
{
    return (i<j);
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
    if(tmp <= suffix_sum + pierwsza_niezerowa) {
      buffer[tmp] = max(mx, buffer[tmp]);
    }
}

void flush_buffer()
{
  for(int key=0; key != buffer.size(); ++key) {
      reszta[key] = max(buffer[key], reszta[key]);
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
        for(int j=0; j != reszta.size(); ++j) {
            int higher = reszta[j];
            int lower = higher - j;
            if(lower >= 0 && j <= suffix_sum + pierwsza_niezerowa && j <= max_sum) {
                printf("j: %d h: %d l: %d i: %d\n", j, higher, lower, lego[i]);
                buffer_push( higher + lego[i],
                            lower);

                buffer_push( lower + lego[i],
                           higher);
            }
        }
        flush_buffer();
        printf("ms: %d ss: %d\n", max_sum, suffix_sum + pierwsza_niezerowa);
        suffix_sum -= lego[i];
        max_sum += lego[i];
    }
}

void output_solution()
{
  int tmp;
    for(int i=0; i != reszta.size(); ++i) {
        if((reszta[i] - i) != 0) {
            tmp = i;
            printf("%d - %d\n", i, reszta[i]);
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

