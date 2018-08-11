#include <bits/stdc++.h>
#define si set<int>

using namespace std;

map<int,int> all_items;
int num_transactions;
double min_sup_trans;
map<int,int> name_change;

typedef struct node
{
	int item; 
	int count; 
	map<int, node *> child;
	node *parent;
}node;

void debug_set(si sett){
	for(si::iterator it=sett.begin();it!=sett.end();++it){
		cout << *it << " ";
	}
	cout << endl;
}

void debug_map(map<int,int> mapp){
	for(map<int,int>::iterator it=mapp.begin(); it!=mapp.end(); ++it){
		cout << it->first << " " << it->second<<", ";
	}
	cout << endl;
}




node* make_node(int item, int count){
	node *new_node = new node;
	new_node->item = item;
	new_node->count = 0;
	return new_node;
}

void first_pass(string file_name, double supp_thresh){
	ifstream in(file_name);
	while(in) {
		string line;
    	getline(in,line);
    	istringstream words(line);
    	for(int item; words >> item; ){
    		if(all_items.count(item)>0)
    			all_items[item] +=1;
    		else
    			all_items[item] = 1;
    	}
    	num_transactions+=1;
  	}
  	min_sup_trans = supp_thresh * num_transactions;
  	in.close();
  	vector <pair<int,int> > sorted_items;  	
	for (map<int,int>::iterator it=all_items.begin(); it!=all_items.end(); ++it){
		if(it->second >= min_sup_trans){
			sorted_items.push_back(make_pair(it->second,it->first));
		}
	}
	sort(sorted_items.begin(),sorted_items.end(),greater<>());
	for(int i=0;i<sorted_items.size();i++){
		name_change[sorted_items[i].second] = (i+1);
	}
}



int main(int argc,char* argv[]){
	string file_name = argv[1];
	double supp_thresh = atof(argv[2])/100.0;
	first_pass(file_name, supp_thresh);
	// make_tree(file_name);

}