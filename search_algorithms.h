#include <vector>
#include "helper_functions.h"
using namespace std;


//Best first search
void best_first_search(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times);

//A* with KM as cost function
void a_star_km(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times);

//A* with MIN as cost function
void a_star_min(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times);

//BFS
void BFS(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times);

//DFS
void DFS(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times);

//uniform search
void uniform(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times);

//Runs all the algorithms on all the cities to keep some stats
void solve(vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times);