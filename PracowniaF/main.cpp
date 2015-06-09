#include <iostream>
#include <stdio.h>
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
  for(int i=0; i<table_h; ++i){
    getline(cin, row);
    data_table.push_back(row);
  }
  printf("\n");
}

void check_rest(int first_row, int first_char){
  bool works = true;
  printf("In check rest \n");
  for(int i=1; i<pattern_h; ++i){
    string substring = data_table[first_row + i].substr(first_char, pattern_w);
    printf("%d substring: %s pattern: %s\n", i, substring.c_str(), pattern[i].c_str());
    if(substring != pattern[i]){
      printf("Diffrent!\n");
      works = false;
      break;
    }
  }
  if(works){
    how_many++;
    printf("Wynik: %d\n", how_many);
  }
}

void find_pattern(){
  for(int i=0; i<=(data_table.size() - pattern_h); ++i){
    printf("Wiersz: %s \n", data_table[i].c_str());
    for(int j=0; j<=(data_table.size() - pattern.size() + 1); ++j){
      string substring = data_table[i].substr(j, pattern_w);
      printf("j: %d substr: %s pattern: %s \n", j, substring.c_str(), pattern[0].c_str());
      if(substring == pattern[0] ){
        printf("True\n");
        check_rest(i, j);
      }
      printf("\n");
    }
    printf("\n");
  }
}

void return_value(){
  printf("%d\n", how_many);
}

int main(){
  get_data();
  find_pattern();
  return_value();
  return 0;
}
