#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int num, modulo;
// x/1 -> black, ./0 -> white
vector<string> wrong_patterns;
vector<string> list_of_all_patterns(32);
char pos[3] = ".x";

int dynamic(int i, int j){
  return 0;
}

// Define how looks every possible row
void define_patterns(){
  int iter = 0;
  for(int i=0; i<2; ++i){
    for(int j=0; j<2; ++j){
      for(int k=0; k<2; ++k){
        for(int l=0; l<2; ++l){
          for(int m=0; m<2; ++m){
            char permutation[6] = { pos[i], pos[j], pos[k], pos[l], pos[m] };
            list_of_all_patterns[iter] = permutation;
            ++iter;
          }
        }
      }
    }
  }
}

//Generate any possible wrong pattern
void handle_pattern(){
  char pat[10] = "036147258";
  for (int i = 0; i < 3; i++) {
    scanf("%s %s %s", &pat[3*i + 0], &pat[3*i + 1], &pat[3*i + 2]);
  }
  // create all permutation 5x3 with wrong pattern!
  for(int i=0; i<2; ++i){
    for(int j=0; j<2; ++j){
      for(int k=0; k<2; ++k){
        for(int l=0; l<2; ++l){
          for(int m=0; m<2; ++m){
            for(int n=0; n<2; ++n){
              char forbidden_pattern[3][16] = { 
              { pat[0], pat[1], pat[2], pos[i], pos[j], pat[3], pat[4], pat[5], pos[k], pos[l], pat[6], pat[7], pat[8], pos[m], pos[n]},
              { pos[i], pat[0], pat[1], pat[2], pos[j], pos[k], pat[3], pat[4], pat[5], pos[l], pos[m], pos[6], pos[7], pos[8], pos[n]},
              { pos[i], pos[j], pat[0], pat[1], pat[2], pos[k], pos[l], pat[3], pat[4], pat[5], pos[m], pos[n], pat[6], pat[7], pat[8]}
              };
              wrong_patterns.push_back(forbidden_pattern[0]);
              wrong_patterns.push_back(forbidden_pattern[1]);
              wrong_patterns.push_back(forbidden_pattern[2]);
            }
          }
        }
      }
    }
  }
  sort(wrong_patterns.begin(), wrong_patterns.end());
}

//Check how many is permutation which ends on rows drugi trzeci
int ends_with(int drugi, int trzeci){
  int wynik = 0;
  for(int i=0; i<32; ++i){
    string merged_rows = list_of_all_patterns[i] + list_of_all_patterns[drugi] + list_of_all_patterns[trzeci];
    if(binary_search(wrong_patterns.begin(), wrong_patterns.end(), merged_rows)){
      wynik += dynamic(i, drugi);
    }
  }
  return wynik;
}


//Get input
void get_numbers_and_patterns(){
  int patterns;
  scanf("%d %d %d", &num, &patterns, &modulo);
  for(int i=0; i < patterns; ++i){
    handle_pattern();
  }
}

//main function
int main(){
  define_patterns();
  get_numbers_and_patterns();
  return 0;
}
