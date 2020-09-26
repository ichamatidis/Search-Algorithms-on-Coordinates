#include <fstream>
#include "search_algorithms.h"
using namespace std;

//Global Variables used by stat function to keep 
//count of all the solving algorithm steps
double solve_steps=0, solve_len=0,solve_km=0,solve_time=0;

//Templated function for getting the 
//posstion of an element in a vector
template<class T>
int get_poss(vector<T> s, T c){
    int poss=0;
    for(int i=0;i<s.size();i++){
        if(s[i]==c) poss=i;
    }
    return poss;
}

//Best first search implementation
void best_first_search(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times){

        int start_poss = get_poss(city_names,from_poss);
        node start = node(city(from_poss,latitude[start_poss],londitude[start_poss]),0);
        
        int end_poss= get_poss(city_names,to_poss);
        node end = node(city(to_poss,latitude[end_poss],londitude[end_poss]),0);

        int num_children = get_num_children(from_city,start.c.name);
        node* root = new node(num_children);
        *root = start;
        vector<int> visited;
        for(int i=0; i<from_city.size(); i++){
            visited.push_back(0);
        }
        root->children = add(root,end,city_names,road_names,from_city,to_city,latitude,londitude,visited);
        // root->print_tree();
        priority_queue<node*,vector<node*>,compare_nodes> pq;
        pq.emplace(root);
        int steps=0;
        node* u = new node(10);
        while(!pq.empty()){
            steps++;
            u = pq.top();
            pq.pop();
            if(u->c.name==end.c.name) break;
            else{
                for(int i=0;i<u->children.size();i++){
                    if(u->children[i]->visited==false){
                        u->children[i]->visited=true;
                        pq.emplace(u->children[i]);
                    }
                }
                u->visited=true;
            }
        }
        solve_steps+=steps;
        cout<<"Best FS("<<steps<<"): ";
        print_path(u,from_city,to_city,road_names,kilos,times,solve_km,solve_len,solve_time);
}

//A* with KM heuristic implementation
void a_star_km(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times){
        int start_poss = get_poss(city_names,from_poss);
        node start = node(city(from_poss,latitude[start_poss],londitude[start_poss]),0);
        
        int end_poss= get_poss(city_names,to_poss);
        node end = node(city(to_poss,latitude[end_poss],londitude[end_poss]),0);

        int num_children = get_num_children(from_city,start.c.name);
        node* root = new node(num_children);
        *root = start;
        vector<int> visited;
        for(int i=0; i<from_city.size(); i++){
            visited.push_back(0);
        }
        root->children = add(root,end,city_names,road_names,from_city,to_city,latitude,londitude,visited);

        vector<node*> open,close;
        node* u = new node(10);
        node* q = new node(10);
        node* goal = new node(10);
        goal->c.name = end.c.name;
        int q_poss = 0;
        u = root;
        int steps =0;
        open.push_back(u);
        while(!open.empty()){
            q = find_min(open);
            q_poss = min_poss(open);
            if(q->c.name == goal->c.name){
                goal=q;
                break;
            }
            open.erase( open.begin()+q_poss );
            for(int i=0;i < q->children.size() ;i++){
                steps++;
                if(q->children[i]->c.name == end.c.name){
                    goal = q->children[i];
                    break;
                }
                q->children[i]->h += distance(q->children[i]->c.latitude, q->children[i]->c.londitude,q->c.latitude,q->c.londitude);
                int d = get_real_distance(from_city,to_city,q->c.name, q->children[i]->c.name,kilos);
                q->children[i]->g += d;
                q->children[i]->f = q->children[i]->g + q->children[i]->h;
            }
            if(goal->c.name == end.c.name) break;
            node* temp = new node(10);
            temp->f = INT32_MAX;
            for (int i=0;i<q->children.size();i++){
                if(temp->f < q->children[i]->f) temp = q->children[i];
            }
            q = temp;
            open.push_back(q);
            close.push_back(q);
        }
        solve_steps+=steps;
        cout<<"\nA* KM("<<steps<<"): ";
        print_path(goal,from_city,to_city,road_names,kilos,times,solve_km,solve_len,solve_time);
}

// //A* with MINUTES heuristic implementation
void a_star_min(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times){
        int start_poss = get_poss(city_names,from_poss);
        node start = node(city(from_poss,latitude[start_poss],londitude[start_poss]),0);
        
        double max_speed=0;
        for(int i=0;i<from_city.size();i++){
            if(kilos[i]/times[i] > max_speed ) max_speed =kilos[i]/times[i]; 
        }//Calculate max real speed for the heuristic

        int end_poss= get_poss(city_names,to_poss);
        node end = node(city(to_poss,latitude[end_poss],londitude[end_poss]),0);

        int num_children = get_num_children(from_city,start.c.name);
        node* root = new node(num_children);
        *root = start;
        vector<int> visited;
        for(int i=0; i<from_city.size(); i++){
            visited.push_back(0);
        }
        root->children = add(root,end,city_names,road_names,from_city,to_city,latitude,londitude,visited);

        vector<node*> open,close;
        node* u = new node(10);
        node* q = new node(10);
        node* goal = new node(10);
        goal->c.name = end.c.name;
        int q_poss = 0;
        u = root;
        int steps=0;
        open.push_back(u);
        while(!open.empty()){
            q = find_min(open);
            q_poss = min_poss(open);
            if(q->c.name == goal->c.name){
                goal=q;
                break;
            }
            open.erase( open.begin()+q_poss );
            for(int i=0;i < q->children.size() ;i++){
                steps++;
                if(q->children[i]->c.name == end.c.name){
                    goal = q->children[i];
                    break;
                }
                q->children[i]->h += distance(q->children[i]->c.latitude, q->children[i]->c.londitude,q->c.latitude,q->c.londitude)/max_speed;
                int d = get_real_time(from_city,to_city,q->c.name, q->children[i]->c.name,kilos);
                q->children[i]->g += d;
                q->children[i]->f = q->children[i]->g + q->children[i]->h;
            }
            if(goal->c.name == end.c.name) break;
            node* temp = new node(10);
            temp->f = INT32_MAX;
            for (int i=0;i<q->children.size();i++){
                if(temp->f < q->children[i]->f) temp = q->children[i];
            }
            q = temp;
            open.push_back(q);
            close.push_back(q);
        }
        solve_steps+=steps;
        cout<<"\nA* MIN("<<steps<<"): ";
        print_path(goal,from_city,to_city,road_names,kilos,times,solve_km,solve_len,solve_time);
        cout<<endl;
}

// //BFS implementation
void BFS(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times){
        
        int start_poss = get_poss(city_names,from_poss);
        node start = node(city(from_poss,latitude[start_poss],londitude[start_poss]),0);
        
        int end_poss= get_poss(city_names,to_poss);
        node end = node(city(to_poss,latitude[end_poss],londitude[end_poss]),0);

        int num_children = get_num_children(from_city,start.c.name);
        node* root = new node(num_children);
        *root = start;
        vector<int> visited;
        for(int i=0; i<from_city.size(); i++){
            visited.push_back(0);
        }
        root->children = add(root,end,city_names,road_names,from_city,to_city,latitude,londitude,visited);
        queue<node*> queue;
        queue.push(root);
        node* t= new node(10);
        string s,e;
        double total_km=0,total_min=0;
        vector<string> r;
        int steps=0;
        cout<<"BFS: ";
        while (!queue.empty()){
            t = queue.front();
            cout<<t->c.name;
            if(t->c.name==end.c.name) break;
            if(!queue.empty() == true) cout<<" -> ";
            else cout<<endl;
            queue.pop();
            for(int i=0;i<t->children.size();i++){
                solve_steps++;
                steps++;
                if(t->children[i]->visited == false ){
                    t->children[i]->visited =true;
                    s=t->c.name;
                    e=t->children[i]->c.name;
                    queue.push(t->children[i]);
                    solve_km += distance(t->c.latitude,t->c.londitude,t->children[i]->c.latitude,t->children[i]->c.londitude);
                    solve_time += distance(t->c.latitude,t->c.londitude,t->children[i]->c.latitude,t->children[i]->c.londitude)/1.4545; //Max KM/MIN
                    solve_len++;
                }
            }
            total_km += get_real_distance(from_city,to_city,s,e,kilos);
            total_min += get_real_time(from_city,to_city,s,e,times);
            r.push_back(get_road_name(from_city,to_city,s,e,road_names));
        }
        cout<<endl;
        solve_len +=r.size();
        for(int i=0;i<r.size();i++){
            cout<<"\t Using road: "<<r[i]<<endl;
        }
        cout<<"Total KM("<<steps<<"): "<<total_km<<" km"<<", total_time= "<<total_min<<" minutes\n\n";
}

// //Global variabled for tracking recursion steps on 
// //DFS
double tk=0,tt=0;
vector<string> rr;
int steps_dfs=0;

// //Recursive function for DFS
void DFS_util(node* s, node end, vector<string> from_city, vector<string> to_city, vector<double> kilos, vector<double> times, vector<string> road_names){//Fix recursion
    s->visited=true;
    cout<<s->c.name<<" -> ";
    if(s->c.name==end.c.name) return;
    for(int i=0;i<s->children.size();i++){
        solve_steps++;
        tk += get_real_distance(from_city,to_city, s->c.name,s->children[i]->c.name,kilos);
        tt += get_real_time(from_city,to_city,s->c.name,end.c.name,times);
        rr.push_back(get_road_name(from_city,to_city,s->c.name,s->children[i]->c.name,road_names));
        steps_dfs++;
        solve_km += distance(s->c.latitude,s->c.londitude,s->children[i]->c.latitude,s->children[i]->c.londitude);
        solve_time += distance(s->c.latitude,s->c.londitude,s->children[i]->c.latitude,s->children[i]->c.londitude)/1.4545; //Max KM/MIN
        solve_len++;
        if(s->children[i]->c.name == end.c.name) {
            cout<<s->children[i]->c.name;
            break;
        }
        DFS_util(s->children[i],end, from_city,to_city,kilos,times,road_names);
    }
}

// //DFS implementation
void DFS(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times){
        
    int start_poss = get_poss(city_names,from_poss);
    node start = node(city(from_poss,latitude[start_poss],londitude[start_poss]),0);
    
    int end_poss= get_poss(city_names,to_poss);
    node end = node(city(to_poss,latitude[end_poss],londitude[end_poss]),0);

    int num_children = get_num_children(from_city,start.c.name);
    node* root = new node(num_children);
    *root = start;
    vector<int> visited;
    for(int i=0; i<from_city.size(); i++){
        visited.push_back(0);
    }
    root->children = add(root,end,city_names,road_names,from_city,to_city,latitude,londitude,visited);
    cout<<"\nDFS: ";
    DFS_util(root, end, from_city,to_city,kilos,times,road_names);
    for(int i=0;i<rr.size();i++){
        cout<<"\tUsing road: "<<rr[i]<<endl;
    }
    tk=0;tt=0;
    rr.clear();
    steps_dfs=0;
    cout<<"Total KM("<<steps_dfs<<"): "<<tk<<" KM, total minutes: "<<tt<<" minutes.\n"<<endl;
}

//Uniform implementation
void uniform(string from_poss, string to_poss, vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times){

        int start_poss = get_poss(city_names,from_poss);
        node start = node(city(from_poss,latitude[start_poss],londitude[start_poss]),0);
        
        int end_poss= get_poss(city_names,to_poss);
        node end = node(city(to_poss,latitude[end_poss],londitude[end_poss]),0);

        int num_children = get_num_children(from_city,start.c.name);
        node* root = new node(num_children);
        *root = start;
        vector<int> visited;
        for(int i=0; i<from_city.size(); i++){
            visited.push_back(0);
        }
        root->children = add(root,end,city_names,road_names,from_city,to_city,latitude,londitude,visited);

        vector<node*> queue;
        node* u = new node(10);
        node* q = new node(10);
        node* goal = new node(10);
        goal->c.name = to_poss;
        int q_poss = 0;
        u = root;
        int steps =0;
        queue.push_back(u);
        while(!queue.empty()){
            q = find_min(queue);
            q_poss = min_poss(queue);
            if(q->c.name==to_poss){
                goal=q;
                break;
            }
            queue.erase( queue.begin()+q_poss );
            for(int i=0;i < q->children.size() ;i++){
                steps++;
                if(q->children[i]->c.name == end.c.name){
                    goal = q->children[i];
                    break;
                }
                q->children[i]->f += distance(q->children[i]->c.latitude, q->children[i]->c.londitude,q->c.latitude,q->c.londitude);
            }
            if(goal->c.name == end.c.name) break;
            node* temp = new node(10);
            temp->f = INT32_MAX;
            for (int i=0;i<q->children.size();i++){
                if(temp->f < q->children[i]->f) temp = q->children[i];
            }
            q = temp;
            queue.push_back(q);
        }
        solve_steps+=steps;
        cout<<"\nUniform ("<<steps<<"): ";
        print_path(goal,from_city,to_city,road_names,kilos,times,solve_km,solve_len,solve_time);
}

// //Functions that runs all algorithms on all cities to keep some stats
// //Outputs stats in .txt file in the same directory as the .exe
void solve(vector<string> city_names,vector<string> road_names, vector<string> from_city, vector<string> to_city,
    vector<double> latitude, vector<double> londitude, vector<double> kilos, vector<double> times){
   
    double total = from_city.size();
    ofstream myfile;
    myfile.open("stats.txt",std::ios_base::out);
    myfile<<"Stats for all possible routes\n";

    //Best FS
    solve_km=0;solve_len=0;solve_steps=0;solve_time=0;
    for(int i=0;i<from_city.size();i++){
        string from_poss= from_city[i],to_poss=to_city[i];
        best_first_search(from_poss,to_poss,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
    }
    myfile<<"BestFirstSearch: Average steps= "<<(solve_steps/total)<<", ave.KM= "<<(solve_km/total)<<", ave.time= "
        <<(solve_time/total)<<", ave.length= "<<(solve_len/total)<<endl;

    //A* KM
    solve_km=0;solve_len=0;solve_steps=0;solve_time=0;
    for(int i=0;i<from_city.size();i++){
        string from_poss= from_city[i],to_poss=to_city[i];
        a_star_km(from_poss,to_poss,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
    }
    myfile<<"A* KM: Average steps= "<<(solve_steps/total)<<", ave.KM= "<<(solve_km/total)<<", ave.time= "
        <<solve_time/total<<", ave.length= "<<solve_len/total<<endl;

    //A* MIN
    solve_km=0;solve_len=0;solve_steps=0;solve_time=0;
    for(int i=0;i<total;i++){
        string from_poss= from_city[i],to_poss=to_city[i];
        a_star_min(from_poss,to_poss,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
    }
    myfile<<"A* MIN: Average steps= "<<(solve_steps/total)<<", ave.KM= "<<(solve_km/total)<<", ave.time= "
        <<solve_time/total<<", ave.length= "<<solve_len/total<<endl;

    //BFS
    solve_km=0;solve_len=0;solve_steps=0;solve_time=0;
    for(int i=0;i<total;i++){
        string from_poss= from_city[i],to_poss=to_city[i];
        BFS(from_poss,to_poss,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
    }
    myfile<<"BFS: Average steps= "<<(solve_steps/total)<<", ave.KM= "<<(solve_km/total)<<", ave.time= "
        <<solve_time/total<<", ave.length= "<<solve_len/total<<endl;

    //DFS
    solve_km=0;solve_len=0;solve_steps=0;solve_time=0;
    for(int i=0;i<total;i++){
        string from_poss= from_city[i],to_poss=to_city[i];
        DFS(from_poss,to_poss,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
    }
    myfile<<"DFS: Average steps= "<<(solve_steps/total)<<", ave.KM= "<<(solve_km/total)<<", ave.time= "
        <<solve_time/total<<", ave.length= "<<solve_len/total<<endl;

    //Uniform
    solve_km=0;solve_len=0;solve_steps=0;solve_time=0;
    for(int i=0;i<total;i++){
        string from_poss= from_city[i],to_poss=to_city[i];
        uniform(from_poss,to_poss,city_names,road_names,from_city,to_city,latitude,londitude,kilos,times);
    }
    myfile<<"Uniform: Average steps= "<<(solve_steps/total)<<", ave.KM= "<<(solve_km/total)<<", ave.time= "
        <<solve_time/total<<", ave.length= "<<solve_len/total<<endl;
    
    //Output to file
    cout<<"\n\n Stats saved to output: stats.txt in the same directiry as the .exe\n\n";
    solve_km=0;solve_len=0;solve_steps=0;solve_time=0;
}

