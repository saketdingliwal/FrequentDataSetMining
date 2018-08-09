#include <bits/stdc++.h>
#define si set<int>

using namespace std;

map<int,int> all_items;
int num_transactions;
double min_sup_trans;
vector <vector<si> > frequentItemSet; 


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
	vector<si> f1;
	for (map<int,int>::iterator it=all_items.begin(); it!=all_items.end(); ++it){
		if(it->second >= min_sup_trans){
			si cand_set;
			cand_set.insert(it->first);
			f1.push_back(cand_set);
		}
	}
	frequentItemSet.push_back(f1);
}


int main(int argc,char* argv[]){
	string file_name = argv[1];
	double supp_thresh = atof(argv[2])/100.0;
	first_pass(file_name, supp_thresh);
	


}