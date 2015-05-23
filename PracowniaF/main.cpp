#include <iostream>
#include <string>
#include <vector>
using namespace std;

int how_many = 0;
vector <string> pattern;
vector <string> data_table;
int pattern_h, pattern_w, table_h, table_w;

void get_data(){
  string row;
  scanf("%d %d %d %d\n", &pattern_h, &pattern_w, &table_h, &table_w);
  for(int i=0; i<pattern_h; ++i){
    getline(cin, row);
    pattern.push_back(row);
  }
  string wiersz;
  for(int i=0; i<table_h; ++i){
    getline(cin, wiersz);
    data_table.push_back(wiersz);
  }
}

void check_rest(int first_row, int first_char){
}

void find_pattern(){
  for(int i=0; i<data_table.size(); ++i){
    for(int j=0; j<(data_table.size() - pattern.size()); ++j){
      if(data_table[i].substr(j, pattern_w) == pattern[0] ){
        check_rest(j, i);
      }
    }
  }
}

int main(){
  get_data();
  find_pattern();
  return 0;
}
