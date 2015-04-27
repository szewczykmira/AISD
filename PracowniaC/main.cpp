#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

int num;
vector<pair <int, int> > list_of_points;

bool func_x(const pair<int, int>& a, const pair<int, int>& b){
  return a.first < b.first;
}

bool func_y(const pair<int, int>& a, const pair<int, int>& b){
  return a.second < b.second;
}

float get_distance(const pair<int, int>& a, const pair<int, int>& b) {
  float a1 = a.first, a2 = a.second;
  float b1 = b.first, b2 = b.second;
  float d1 = (a1 - b1), d2 = (a2 - b2);
  return sqrt(d1*d1 + d2*d2);
}


void get_points(){
  int tmp1, tmp2;
  scanf("%d", &num);
  for(int i=0; i<num; ++i){
    scanf("%d %d", &tmp1, &tmp2);
    list_of_points.push_back(make_pair(tmp1, tmp2));
    //printf("%d: %d %d\n", i, tmp1, tmp2);
  }
  sort(list_of_points.begin(), list_of_points.end(), func_x);
}

pair<int, int> brutus(int id_from, int id_to){
  float min_distance = get_distance(list_of_points[id_from], list_of_points[id_to]);
  pair<int, int> result;
  result.first = id_from;
  result.second = id_to;
  for(int i=id_from; i< id_to; ++i){
    for(int j=i+1;  j<=id_to; ++j){
      float tmp = get_distance(list_of_points[i], list_of_points[j]);
      if(min_distance > tmp) {
        result.first = i;
        result.second = j;
      }
    }
  }
  return result;
}

pair<int,int> stripped[10010];
pair<int, int> handle_points(int id_from, int id_to){
  //printf("\n id_from: %d \t id_to: %d \n", id_from, id_to);
  pair<int, int> result;
  int how_many = id_to - id_from + 1;
  //printf("How many: %d \n", how_many);
  // what if there is two points in our list
  if(how_many == 2){
   // printf("Two!\n");
    result.first = id_from;
    result.second = id_to;
    return result;
  }
  // three points handled using brute force! May the force be with you :)
  if(how_many == 3){
    //printf("Three!\n");
    result = brutus(id_from, id_to);
    return result;
  }
  // And what if list is longer? Divide!
  int mid_point = id_from + ceil(how_many / 2);
  //printf("Mid point id: %d \n", mid_point);
  pair<int, int> res_left = handle_points(id_from, mid_point - 1);
  pair<int, int> res_right = handle_points(mid_point, id_to);
  float dist_left = get_distance(list_of_points[res_left.first], list_of_points[res_left.second]);
  float dist_right = get_distance(list_of_points[res_right.first], list_of_points[res_right.second]);
  float min_dist = min(dist_left, dist_right);
  if(min_dist == dist_left) {
    result = res_left;
  } else {
    result = res_right;
  }
  // Check points in between!

  int in_stripped = 0;
  for(int i=id_from; i< mid_point; ++i){
    int dist = abs(list_of_points[i].first - list_of_points[mid_point].first);
    if( dist <= min_dist) {
      stripped[in_stripped] = list_of_points[i];
      ++in_stripped;
    }
  }
  int mid_stripped = in_stripped;
  for(int i=mid_point; i<=id_to; ++i){
    int dist = abs(list_of_points[i].first - list_of_points[mid_point].first);
    if( dist <= min_dist) {
      stripped[in_stripped] = list_of_points[i];
      ++in_stripped;
    }
  }
  sort(stripped+mid_stripped, stripped+in_stripped, func_y);
  //printf("[ ");
  int resi = -1,
      resj = -1;
  for(int i = 0; i < mid_stripped; ++i) {
    //printf("(%d, %d) ", stripped[i].first, stripped[i].second);
    pair<int, int> stripped_i(stripped[i].first, stripped[i].second - min_dist);
    pair<int,int>* start_ptr = lower_bound(stripped+mid_stripped, stripped+in_stripped, stripped_i, func_y);
    for(int j = start_ptr - stripped; j < in_stripped; ++j) {

      if(stripped[j].second > stripped[i].second + min_dist) break;

      float temp_dist = get_distance(stripped[i], stripped[j]);
      if(temp_dist < min_dist){
        //printf("Found better min! %f %f\n", temp_dist, min_dist);
        resi = i;
        resj = j;
        min_dist = temp_dist;
      }
    }
  }
  //printf("]\n %d %d\n", resi, resj);
  if(resi == -1) return result;
  for (int i = id_from; i <= id_to; i++) {
    if(list_of_points[i] == stripped[resi]) result.first = i;
    if(list_of_points[i] == stripped[resj]) result.second = i;
  }
  //printf("%d %d\n", result.first, result.second);
  return result;
}

int main(){
  get_points();
  pair<int, int> result = handle_points(0,num - 1);
  printf("%d %d \n", list_of_points[result.first].first, list_of_points[result.first].second);
  printf("%d %d \n", list_of_points[result.second].first, list_of_points[result.second].second);
  //printf("Diff: %f\n", get_distance(list_of_points[result.first], list_of_points[result.second]));
  return 0;
}
