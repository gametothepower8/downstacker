#include<bits/stdc++.h>
#include "board.h"
using namespace std;
const int see_next=5;
const int search_width=100;
vector<int> gen_pieces(int seed){//generates random valid sequence of pieces
	srand(seed);
	vector<int>d(7);
	for(int i=0; i<7 ;i++) d[i]=i;
	vector<int>ret;
	for(int i=1; i<=100 ;i++){
		random_shuffle(d.begin(),d.end());
		for(int j=0; j<7 ;j++) ret.push_back(d[j]);
	}
	return ret;
}

vector<int> gen_solver(string s,int seed){//appends random valid piece sequence given  
	srand(seed);
	vector<int>d(7);
	for(int i=0; i<7 ;i++) d[i]=i;
	vector<int>ret;
	int rem=127;
	for(int i=0; i<s.size() ;i++){
		ret.push_back(piece_char_to_id[s[i]]);
		rem^=(1<<piece_char_to_id[s[i]]);
		if(rem==0) rem=127;
	}
	vector<int>dd;
	for(int i=0; i<7 ;i++) if((rem>>i)&1) dd.push_back(i);
	random_shuffle(dd.begin(),dd.end());
	for(auto c:dd) ret.push_back(c);
	for(int i=1; i<=100 ;i++){
		random_shuffle(d.begin(),d.end());
		for(int j=0; j<7 ;j++) ret.push_back(d[j]);
	}
	return ret;
}
typedef pair<double,pair<int,board> >  fun;
bool cmp(fun x,fun y){
	return x.fi<y.fi;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	int seed;cin >> seed;
	string s;cin >> s;
	init_boardh();
	//vector<int>p_seq=gen_pieces(seed);
	vector<int>p_seq=gen_solver(s,seed);
	board b=gen_garbage(10,p_seq[0],seed);
	if(true){
		vector<int>fixed(10);
		for(int i=0; i<10 ;i++){
			int x;cin >> x;fixed[i]=x;
		}
		b=gen_garbage_fixed(fixed,10,p_seq[0],seed);
	}
	int hold=p_seq[0];
	int ptr=1;
	//view(b);
	int used=0;
	while(b.gar>0){
		int ly=see_next+1;//number of moves with full info
		vector<pair<double,pair<int,board> > >layers[ly+1];
		layers[0].push_back({b.score(),{0,b}});
		unordered_map<ll,int>um;
		for(int i=1; i<=ly ;i++){
			int id=0;
			for(auto bb:layers[i-1]){
				auto res=(bb.se.se).gen_moves(p_seq[ptr+i-1]);
				for(auto nb:res){
					ll hsh=nb.hash();
					if(um[hsh]) continue;
					um[hsh]=true;
					layers[i].push_back({nb.score(),{id,nb}});
				}
				id++;
			}
			sort(layers[i].begin(),layers[i].end(),cmp);
			if(layers[i].size()>search_width) layers[i].resize(search_width);
		}/*
		if(layers[ly][0].fi<0){
			cout << "Found " << ptr+ly-1 << "!!!" << endl;
		}
		for(int i=1; i<=ly ;i++){
			cout << layers[i].size() << ' ';
		}
		cout << endl;*/
		int cur=0;
		for(int i=ly; i>=2 ;i--) cur=layers[i][cur].se.fi;
		b=layers[1][cur].se.se;
		if(b.last_move.pid==hold) hold=p_seq[ptr];
		ptr++;used++;
		view(b);
		cout << "Move: " << pieces[b.last_move.pid].name << ' ' << b.last_move.rot << ' ' << b.last_move.pos << endl;	
		cout << "Used: " << used << endl;
		//system("pause");
	}
	cout << "END!!!" << endl;
}
