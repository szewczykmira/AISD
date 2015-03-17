#include <iostream>
using namespace std;

int main() {
  int begin, end;
  scanf("%d %d", &begin, &end);
  if(begin > end)
  {
    swap(begin, end);
  }
  for(int i = begin; i<=end; i++)
  {
    printf("%d \n", i);
  }
  return 0;
}
