#include "partition_sets.hpp"
#include "UnionFind2D.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
using namespace std;


bool compare_oime(pair<int, pair<int,int> > a, pair<int, pair<int,int> > b)
{
	return a.first < b.first;
}




void partition_to_sets(std::vector<std::vector<bool> > &input, std::vector<std::vector<pair<int,int> > > &sets)
{
	int num_row=input.size();
	int num_col=input[0].size();
	UnionFind2D find(num_row,num_col);
	for(int i=0;i<num_row;i++){
		for(int j=0;j<num_col;j++){
			if(input[i][j]){
				if((i != num_row - 1) && input[i+1][j]) find.unite(i,j,i+1,j);
				if((j != num_col - 1) && input[i][j+1]) find.unite(i,j,i,j+1);
			}
		}
	}
	//cout<<"after job done"<<endl;
    sets.clear();
    vector<pair<int,pair<int,int> > > val;
    val.resize(num_col*num_row);
    for(int i=0;i<num_row;i++){
    	int k=i*num_col;
    	for(int j=0;j<num_col;j++){
    		val[k].second=make_pair(i,j);
    		val[k++].first=find.root(i,j);
    	}
    }
    sort(val.begin(),val.end(),compare_oime);
    int current_id=-1;
    for(int i=0;i<val.size();i++){
    	if(current_id != val[i].first) {
    		current_id=val[i].first;
    		if(input[val[i].second.first][val[i].second.second]){
    			sets.push_back(vector< pair<int,int> >());
    			sets.back().push_back(val[i].second);
    		}
    	}
    	else{
    		sets.back().push_back(val[i].second);
    	}
    }
}













