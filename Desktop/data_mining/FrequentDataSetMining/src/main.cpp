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

void debug_set(si sett){
	for(si::iterator it=sett.begin();it!=sett.end();++it){
		cout << *it << " ";
	}
	cout << endl;
}

bool each_subset(si cand_set, map<si,bool> set_map){
	si subset = cand_set;
	si::iterator last_it;
	for(si::iterator it=cand_set.begin(); it!=cand_set.end(); ++it){
		subset.erase(*it);
		if(it!=cand_set.begin()){
			subset.insert(*last_it);
		}
		if(set_map.count(subset)==0)
			return false;
		last_it = it;
	}
	return true;
}

vector<si> cand_gen(vector<si> fkminus1){
	map<si,bool> set_map;
	for(int i=0;i<fkminus1.size();i++){
		set_map[fkminus1[i]] = 1;
	}

	vector <si> cand_set_vect;
	for(int i=0;i<fkminus1.size();i++){
		for(int j=i+1;j<fkminus1.size();j++){
			si fbar = fkminus1[i];
			si fbardash = fkminus1[j];
			if(fbar.size()>=2){
				int i1 = *fbar.begin();
				si::iterator endd = fbar.end();
				endd--;
				endd--;
				int ikminus2 = *endd;

				int i1dash = *fbardash.begin();
				endd = fbardash.end();
				endd--;
				endd--;
				int ikminus2dash = *endd;
				if(i1!=i1dash || ikminus2!=ikminus2dash)
					break;
			}
			si cand_set = fbar;
			si::iterator endd = fbardash.end();
			endd--;
			cand_set.insert(*endd);
			if(each_subset(cand_set,set_map)){
				cand_set_vect.push_back(cand_set);
			}
		}
	}
	return cand_set_vect;
}


int main(int argc,char* argv[]){
	string file_name = argv[1];
	double supp_thresh = atof(argv[2])/100.0;
	first_pass(file_name, supp_thresh);

	vector <si> fkminus1 = frequentItemSet[0];
	while(fkminus1.size()!=0){
		vector <si> cand_set_vect = cand_gen(fkminus1);
		vector <int> cand_set_count;
		cand_set_count.resize(cand_set_vect.size());
		ifstream in(file_name);
		while(in) {
			string line;
			getline(in,line);
			istringstream words(line);
			si t_set;
			for(int item; words >> item; ){
				t_set.insert(item);
			}
			for(int i=0;i<cand_set_vect.size();i++){
				si cand_set = cand_set_vect[i];
				int flag = 0;
				for(si::iterator it=cand_set.begin(); it!=cand_set.end(); ++it){
					if(t_set.find(*it)==t_set.end()){
						flag = -1;
						break;
					}
				}
				if(flag==0)
					cand_set_count[i]+=1;
			}
		}
	  	in.close();
		vector <si> fk;
		for(int i=0;i<cand_set_vect.size();i++){
			if(cand_set_count[i]>=min_sup_trans){
				// debug_set(cand_set_vect[i]);
				fk.push_back(cand_set_vect[i]);
			}
		}
		frequentItemSet.push_back(fk);	
		fkminus1 = fk;
  	}
  	// for(int i=0;i<frequentItemSet.size();i++){
  	// 	for(int j=0;frequentItemSet[i].size();j++){
  	// 		debug_set(frequentItemSet[i][j]);
  	// 	}
  	// }
}