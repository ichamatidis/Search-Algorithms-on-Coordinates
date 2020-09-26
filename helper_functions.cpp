#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <queue>
#include "helper_functions.h"
using namespace std;

//Loading file with cities and roads
void load_file( vector<double> &latitude, vector<double> &londitude, vector<double> &kilos, vector<double> &time, 
    vector<string> &from_city, vector<string> &to_city, vector<string> &city_names, vector<string> &road_names){
    
    ifstream myfile;
    //Change to be in the same path as the exe.
    string filename="roads.txt";
    cout<<"Give filename: ";
    cin>>filename;
    myfile.open (filename,std::ios_base::in);
    
    string input;
    getline(myfile,input);
    int n_cities = stoi(input);
    for(int i=0;i<n_cities;i++){
        getline(myfile,input);
        city_names.push_back( input);
        getline(myfile,input);
        latitude.push_back(stod(input));
        getline(myfile,input);
        londitude.push_back(stod(input));
    }
    getline(myfile, input);
    int n_roads = stoi(input);
    for(int i=0;i<n_roads;i++){
        getline(myfile,input);//Reading road name
        road_names.push_back( input);
        getline(myfile,input);//Reading Starting city
        from_city.push_back( input);
        getline(myfile,input);//Reading destination city
        to_city.push_back( input);
        getline(myfile,input);
        kilos.push_back( stod(input));//Readind distance in KM
        getline(myfile,input);
        time.push_back( stod(input));//Reading time in minutes
    }
    // print_roads(n_roads,road_names,from_city,to_city,kilos,time);
    cout<<"The are: "<<n_cities<<" in this file\n";
    cout<<"And are: "<<n_roads<<" in this file\n";
    myfile.close();
}

//Printing city names with coordinates
void print_cities( vector<string> city_names, vector<double> latitude, vector<double> londitude){
    for(int i=0;i<city_names.size();i++){
        cout<<city_names[i]<<": ("<<latitude[i]<<", "<<londitude[i]<<")\n";
    }
}


//Print road names, diastance time and starting and anding points.
void print_roads(vector<string> road_names, vector<string> from_city, vector<string> to_city, vector<double> kilos, vector<double> time){
    for(int i=0;i<road_names.size();i++){
        cout<<"-----------------------------------------------------------------"<<endl;
        cout<<"From: "<<from_city[i]<<"-->"<<to_city[i]<<endl;
        cout<<"Road: "<<road_names[i]<<" it is: "<<kilos[i]<<" (Km)."<<endl;
        cout<<"\tAnd you'll need about:"<<time[i]<<" minutes."<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;

    }
}

//Save file to a .txt in the same directory
void save_file( vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> time, 
    vector<string> from_city, vector<string> to_city, vector<string> city_names, vector<string> road_names){
    
    ofstream myfile;
    myfile.open("roads2.txt",std::ios_base::out);
    myfile<<city_names.size()<<"\n";
    for(int i=0;i<city_names.size();i++){
        myfile<<city_names[i]<<"\n";
        myfile<<latitude[i]<<"\n";
        myfile<<londitude[i]<<"\n";
    }
    myfile<<road_names.size()<<"\n";
    for(int i=0;i<road_names.size();i++){
        myfile<<road_names[i]<<"\n";
        myfile<<from_city[i]<<"\n";
        myfile<<to_city[i]<<"\n";
        myfile<<kilos[i]<<"\n";
        myfile<<time[i]<<"\n";
    }
    myfile.close();
}

//Adds city to the existing loaded cities
void add_city(vector<double> &latitude, vector<double> &londitude, vector<string> &city_names){
    cout<<"What's the name of the city:";
    string input;
    cin>>input;
    city_names.push_back(input);
    cout<<"Give latitude:";
    cin>>input;
    latitude.push_back(stod(input));
    cout<<"Give londitude:";
    cin>>input;
    londitude.push_back(stod(input));
    cout<<"City added successfully"<<endl;
}

//Adds road to the exiting loaded roads
void add_road(vector<string> &road_names, vector<string> &from_city, vector<string> &to_city,vector<double> &kilos, vector<double> &time){
    cout<<"What's the name of the road:";
    string input;
    cin>>input;
    road_names.push_back(input);
    cout<<"Give starting point:";
    cin>>input;
    from_city.push_back(input);
    cout<<"Give destination:";
    cin>>input;
    to_city.push_back(input);
    cout<<"Give Kilometers:";
    cin>>input;
    kilos.push_back(stod(input));
    cout<<"Give time:";
    cin>>input;
    time.push_back(stod(input));
    cout<<"Road added successfully"<<endl;
}

//Search if a city exists in the data
void search_city(vector<string> &city_names, string city){
    bool found=false;
    for(int i=0;i<city_names.size();i++){
        if(city_names[i]==city) found=true;
    }
    if(found) cout<<"City: "<<city<<", is a valid entry\n";
    else cout<<"City: "<<city<<", is an invalid entry\n";
}

//Search if a road exists in the data
void search_road(vector<string> &road_names, string road){
    bool found=false;
    for(int i=0;i<road_names.size();i++){
        if(road_names[i]==road) found=true;
    }
    if(found) cout<<"City: "<<road<<", is a valid entry\n";
    else cout<<"City: "<<road<<", is an invalid entry\n";
}

//Helping function to print the contents of the priority queue
void print_pq(priority_queue<double> pq){
    priority_queue<double> p = pq;
    cout<<"Priority Queue(size="<<p.size()<<"):";
    while (!p.empty()){
        cout<<"\t"<<p.top();
        p.pop();
    }
    cout<<endl;
}

//Calculate the distance in KM given the latitude and londitude of 2 points
double distance(double latA, double londA, double latB, double londB){
    const double R = 6371e3;
    const double PI = 3.141592;
    double f1 = latA * PI/180;
    double f2 = latB * PI/180;
    double Df = (latB-latA) * PI/180;
    double Dl = (londB-londA) * PI/180;

    double a = sin(Df/2) * sin(Df/2) + cos(f1) * cos(f2) * sin(Dl/2) * sin(Dl/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return ((R * c)/1000); // Return in Km
}

//Templated function that returns the index of an element 
//from a vector
template<class T>
int get_poss(vector<T> s, T c){
    int poss=0;
    for(int i=0;i<s.size();i++){
        if(s[i]==c) poss=i;
    }
    return poss;
}

//Returns the number of children a node has
int get_num_children(vector<string> from_city, string city_name){
    int sum=0;
    for(int i=0;i<from_city.size();i++){
        if(from_city[i]==city_name) sum++;
    }
    return sum;
}

//Prints the path from a node to the root
void print_path(node* n, vector<string> from_city, vector<string> to_city, vector<string> road_names, vector<double> kilos, vector<double> times, double &solve_km,double &solve_len,double &solve_time){
    vector<string> city;
    node* temp = new node(0);
    temp = n;
    while(temp->parent!=NULL){
        city.push_back(temp->c.name);
        temp = temp->parent;
    }
    city.push_back(temp->c.name);
    int size = city.size();
    int sum=0;
    for(int i=size-1;i>=0;i--){
        cout<<city[i];
        if(i==0) cout<<endl;
        else cout<<"->";
    }
    temp = n;
    double total_km=0, total_time=0;
    while (temp->parent!=NULL){
        string t = temp->c.name;
        string f = temp->parent->c.name;
        for(int i=0;i<from_city.size();i++){
            if(from_city[i]==f && to_city[i]==t){
                solve_len++;
                solve_km += kilos[i];
                solve_time += times[i];
                total_km+=kilos[i];
                total_time+=times[i];
                cout<<"\tUsing road "<<i<<": "<<road_names[i]<<endl;
            }
        }
        temp = temp->parent;
    }
    cout<<"Total KM: "<<total_km<<" KM, total time: "<<total_time<<" minutes."<<endl;  
} 

//Construct the tree recursively
vector<node*> add(node* start, node& end, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude,vector<int> &visited){
        vector<node*> temp ;
        int num_children = get_num_children(from_city,start->c.name);
        vector<int> p;
        for(int i=0;i<from_city.size();i++){
            if(from_city[i]==start->c.name ){
                visited[i]=1;//Makrs pair as visited
                int poss = get_poss(city_names,to_city[i]);
                node* t = new node(city(to_city[i],latitude[poss],londitude[poss]),0);
                t->dist = distance(start->c.latitude, start->c.londitude, t->c.latitude, t->c.londitude);
                t->parent = start;
                temp.push_back(t);
                for(int j=0;j<from_city.size();j++){
                    if(from_city[j]==t->c.name && visited[j]==0) t->children = add(t,end,city_names,road_names,from_city,to_city,latitude,londitude,visited);
                }
            }
        }
        return temp;
    }

//Returns the possition of the node with the minimum cost
//from a vector
int min_poss(vector<node*> n){
    double min=INT32_MAX;
    int m = 0;
    for(int i=0;i<n.size();i++){
        if(n[i]->f < min ) m = i;
    }
    return m;
}

//Returns the real distance of 2 points from the loaded data
double get_real_distance(vector<string> from_city, vector<string>  to_city, string from_c, string to_c, vector<double> kilos){
    double d=0;
    for(int i=0;i<from_city.size();i++){
        if(from_city[i] == from_c && to_city[i] == to_c ) d= kilos[i];
    }
    return d;
}

//Returns the real time need to go from one point to another
double get_real_time(vector<string> from_city, vector<string>  to_city, string from_c, string to_c, vector<double> times){
    double d=0;
    for(int i=0;i<from_city.size();i++){
        if(from_city[i] == from_c && to_city[i] == to_c ) d= times[i];
    }
    return d;
}

//Returns the name of a road given 2 cities
string get_road_name(vector<string> from_city, vector<string>  to_city, string from_c, string to_c, vector<string> road_names){
    string d;
    for(int i=0;i<from_city.size();i++){
        if(from_city[i] == from_c && to_city[i] == to_c ) d= road_names[i];
    }
    return d;
}

//returns the node with the smallest heuristic cost
node* find_min(vector<node*> n){
    double min=INT32_MAX;
    node* m =new node(10);
    for(int i=0;i<n.size();i++){
        if(n[i]->f < min ) m = n[i];
    }
    return m;
}
