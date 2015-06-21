#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

int how_many = 0;
vector <string> pattern;
vector <string> data_table;
int pattern_h, pattern_w, table_h, table_w;

//#define DEBUG(ARGS...) { printf(ARGS); }
#define DEBUG(...) { }

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

  DEBUG("\n");
}

void check_naive(int first_row, int first_char){
  DEBUG("In check rest \n");

  for(int i=0; i<pattern_h; ++i){
    string substring = data_table[first_row + i].substr(first_char, pattern_w);

    DEBUG("%d substring: %s pattern: %s\n", i, substring.c_str(), pattern[i].c_str());

    if(substring != pattern[i]){

      DEBUG("Diffrent!\n");

      return;
    }
  }

  how_many++;

  DEBUG("Wynik: %d\n", how_many);
}

void find_pattern(){
  for(int i=pattern_h-1; i<data_table.size(); ++i){
    size_t start = 0;

    DEBUG("Wiersz: %s \n", data_table[i].c_str());

    while(start != string::npos ){
      start = data_table[i].find(pattern[pattern_h-1], start);

      if(start != string::npos) {
        DEBUG("True\n");

        check_naive(i-pattern_h+1, start);
        start++;
      }
    }


    DEBUG("\n");
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
