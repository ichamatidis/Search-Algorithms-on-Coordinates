#include <vector>
#include <string>
#include <queue>
#include <iostream>
using namespace std;

//Adds city from user input
void add_city(vector<double> &latitude, vector<double> &londitude, vector<string> &city_names);

//Adds road from user input
void add_road(vector<string> &road_names, vector<string> &from_city, vector<string> &to_city,vector<double> &kilos, vector<double> &time);

//Saves file to .txt
void save_file( vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> time, 
    vector<string> from_city, vector<string> to_city, vector<string> city_names, vector<string> road_names);

//Loads file
void load_file( vector<double> &latitude, vector<double> &londitude, vector<double> &kilos, vector<double> &time, 
    vector<string> &from_city, vector<string> &to_city, vector<string> &city_names, vector<string> &road_names);

//Prints available cities
void print_cities( vector<string> city_names, vector<double> latitude, vector<double> londitude);

//Prints available roads
void print_roads(vector<string> road_names, vector<string> from_city, vector<string> to_city, vector<double> kilos, vector<double> time);

//search if a city exists in the data loaded
void search_city(vector<string> &city_names, string city);

//search if a road exists in the data loaded
void search_road(vector<string> &road_names, string road);

//Helper function, prints contents of pq
void print_pq(priority_queue<double> pq);

//Converts coordinates to KM
double distance(double latA, double londA, double latB, double londB);

//Helper function prints number of childreb of one road
int get_num_children(vector<string> from_city, string city_name);

//Definition of class city
/*
Contains city name, latitude and londitude and 
and the appropriate constructors
*/
class city{
    public:
        string name;
        double latitude;
        double londitude;
        city(){
            name="";
            latitude=0;
            londitude=0;
        }
        city(string name,double latitude, double londitude){
            this->name=name;
            this->latitude=latitude;
            this->londitude=londitude;
        }
        city(const city &n){//Copy constructor
            this->name=n.name;
            this->latitude=n.latitude;
            this->londitude=n.londitude;
        }
        void print(){
            cout<<"City: "<<name<<", lat="<<latitude<<", londitude="<<londitude<<endl;
        }
};

//node class, refer to manual for explanation
class node{
    public:
    city c;
    bool visited;
    double dist;
    double g;
    double h;
    double f;
    node* parent;
    vector<node*> children;

    node(int num_children)
    :children(num_children,0)
    {//Default constructor
        this->c = city();
        this->visited=false;
        this->dist=0;
        this->parent=NULL;
        g=0;
        h=0;
        f=0;
    }

    node(city n,int num_children)
    :children(num_children,0)
    {//Constructor
        this->c.name = n.name;
        this->c.latitude = n.latitude;
        this->c.londitude = n.londitude;
        this->visited=false;
        this->dist=0;
        this->parent=NULL;
        g=0;
        h=0;
        f=0;
    }

    void add_child(node* child){
        this->children.push_back(child);
    }

    void print(){
        cout<<"----------------------------------------------\n";
        cout<<"Node name:";
        c.print();
        cout<<"Childred:\n";
        if(children.size()==0) cout<<"-\n";
        else{
            for(int i=0; i<children.size() ;i++){
                children[i]->c.print();
            }
        }
        cout<<"----------------------------------------------\n";

    }

    void print_tree(){
        print();
        for(int i=0;i<children.size() ;i++){
            node* n = next(i);
            n->print_tree();
            
        }
    }

    node* next(int i){
        return children[i];
    }
};

//functor operator used to compare nodes in the priority queue dara structure
struct compare_nodes{
    bool operator()(node const *n1, node const *n2){
        return (n1->dist < n2->dist);
    }
};

//Adds node to tree
vector<node*> add(node* start, node& end, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude,vector<int> &visited);

// //Prints the path from one node to another
void print_path(node* n, vector<string> from_city, vector<string> to_city, vector<string> road_names, vector<double> kilos, vector<double> time, double &solve_km,double &solve_len,double &solve_time);

//Finds minimum node in a vector
node* find_min(vector<node*> n);

//Returns the minimum possition in the vector of the node
int min_poss(vector<node*> n);

//Returns the real distance between 2 points
double get_real_distance(vector<string> from_city, vector<string>  to_city, string from_c, string to_c, vector<double> kilos);

//Returns the real time between 2 points
double get_real_time(vector<string> from_city, vector<string>  to_city, string from_c, string to_c, vector<double> times);

//Returns the road name between 2 points
string get_road_name(vector<string> from_city, vector<string>  to_city, string from_c, string to_c, vector<string> road_names);

//Return a pointer to a vector 
node* find_min(vector<node*> n);