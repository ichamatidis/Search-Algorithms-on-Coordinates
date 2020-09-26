#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <queue>
#include "search_algorithms.h"
using namespace std;


int main(){
    vector<double> latitude,londitude,kilos,times;
    vector<string> city_names,road_names,from_city,to_city;
    int choice = -1;
    while (choice != 0){
        cout<<"\n1.Add City\n";    
        cout<<"2.Add Road\n";    
        cout<<"3.List Cities\n";    
        cout<<"4.List Roads\n";
        cout<<"5.Search City\n";
        cout<<"6.Search Road\n";
        cout<<"7.Save To File\n";
        cout<<"8.Load File\n";    
        cout<<"9.Solve\n";    
        cout<<"10.Stats\n";
        cout<<"0.Quit\n";    
        cout<<"Your choice:";
        cin>>choice;
        cout<<endl;
        if(choice==1) add_city(latitude,londitude,city_names);
        else if(choice==2) add_road(road_names,from_city,to_city,kilos,times);
        else if(choice==3) print_cities(city_names,latitude,londitude);
        else if(choice==4) print_roads(road_names,from_city,to_city,kilos,times);
        else if(choice==5) {
            string city;
            cout<<"What city are you searching for:";
            cin>>city;
            search_city(city_names,city);
        }
        else if(choice==6){
            string road;
            cout<<"What road are you searching for:";
            cin>>road;
            search_road(city_names,road);
        }
        else if(choice==7) save_file(latitude,londitude,kilos,times,from_city,to_city,city_names,road_names);
        else if(choice==8) load_file(latitude,londitude,kilos,times,from_city,to_city,city_names,road_names);
        else if(choice==9) {
            string start, destination;
            cout<<"Give starting point: ";
            cin>>start;
            cout<<"Give destination: ";
            cin>>destination;
            cout<<"-----------------------------------------------------------------------------------"<<endl;
            //Run all algorithms on the given cities
            best_first_search(start,destination,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
            a_star_km(start,destination,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
            a_star_min(start,destination,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
            BFS(start,destination,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
            DFS(start,destination,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
            uniform(start,destination,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
            cout<<"-----------------------------------------------------------------------------------"<<endl;
        }
        else if(choice==10) solve(city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
        else if(choice==0) cout<<"Quiting.\n";
        else{
            cout<<"Invalid input, quiting.\n";
            choice=0;
        }   
    }
    
    return 0;
    
}
//Reverse to roads to double the roads
