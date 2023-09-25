#include<bits/stdc++.h>
#include "piece.h"
using namespace std;
const int hei=22;
const int colsz=10;
int lg[65536];
int colh(int v){
	if(v<65536) return lg[v]+1;
	else return 16+lg[v>>16]+1;
}
struct step{
	int pid;int rot;int pos;//piece id, rot, horizontal position
};
struct board{
	
	int gar;//number of garbage lines left
	int col[colsz];
	step last_move;
	int hold;
	board(){
		gar=1000;
	}
	ll hash(){
		const ll b1=1e6+17,b2=1e7+17;
		const ll m1=998244353,m2=1e9+7;
		ll h1=(gar*b1+hold)%m1,h2=(gar*b2+hold)%m2;
		for(int i=0; i<colsz ;i++){
			h1=(h1*b1+col[i])%m1;
			h2=(h2*b2+col[i])%m2;
		}
		return h1*m2+h2;
	}
	board clone(){
		board newi;
		newi.gar=gar;
		for(int i=0; i<colsz ;i++) newi.col[i]=col[i];
		newi.last_move=last_move;
		newi.hold=hold;
		return newi;
	}
	pair<bool,board> place(rot x,int pos,int new_hold,int use,int rr){//returns {if possible to place,resulting board}
		int w=x.in.size();
		
		//cout << "hello " << pos << ' ' << new_hold << ' ' << w << endl;
		if(pos+w>colsz){
			return {false,clone()};
		}
		int xh=0;
		for(int i=0; i<w ;i++) xh=max(xh,colh(col[pos+i])-x.in[i]);
		board newi=clone();
		newi.last_move={use,rr,pos};
		newi.hold=new_hold;
		for(int i=0; i<w ;i++) newi.col[pos+i]|=x.out[i]<<xh;
		if(xh==gar-1) newi.gar--;//at most one garbage line is cleared
		/*for(int i=0; i<10 ;i++) cout << newi.col[i] << ' ';
		cout << endl;*/
		while(true){
			int full=(1<<hei)-1;
			for(int i=0; i<colsz ;i++) full&=newi.col[i];
			if(full==0) break;
			full=full&-full;
			for(int i=0; i<colsz ;i++){
				int down=newi.col[i]&(full-1);
				newi.col[i]=newi.col[i]^full^down^(down<<1);
				newi.col[i]>>=1;
			}
		}
		return {true,newi};
	}
	double score(){//evaluates current board
		double res=0;
		{
			if(gar==0) res-=100000;
			res+=gar*20;
		}
		{
			int bad=0;
			for(int i=0; i<colsz ;i++){
				int high_hole=(col[i]+1)&(-col[i]-1);
				int tmp=col[i]^(col[i]&(high_hole-1));
				int free=col[i];
				free&=(free<<1);
				free&=(free<<2);
				bad|=tmp^(tmp&free);
			}
			int bc=__builtin_popcount(bad);
			res+=bc*20;
			res+=(bc-gar+1)*10;
		}
		{
			int bad=0;
			for(int i=1; i<colsz ;i++){
				int diff=colh(col[i-1])-colh(col[i]);
				bad+=diff*(diff+1)/2;
			}
			res+=bad*2;
		}
		//cout << "score = " << res << endl;
		return res;
		
	}
	vector<board>gen_moves(int pid){
		//cout << "gen moves " << hold << ' ' << pid << endl;
		vector<board>ret;
		if(pid!=hold){
			int rr=0;
			for(auto c:pieces[pid].rots){
				for(int i=0; i<10 ;i++){
					auto tmp=place(c,i,hold,pid,rr);
					if(tmp.fi) ret.push_back(tmp.se);
				}
				rr++;
			}
		}
		{
			int rr=0;
			for(auto c:pieces[hold].rots){
				for(int i=0; i<10 ;i++){
					auto tmp=place(c,i,pid,hold,rr);
					if(tmp.fi) ret.push_back(tmp.se);
				}
				rr++;
			}
		}
		return ret;
	}
};
void view(board &b){
	for(int i=hei-1; i>=0 ;i--){
		for(int j=0; j<colsz ;j++){
			if((b.col[j]>>i)&1) cout << 'X';
			else cout << '.';
		}
		cout << endl;
	}
	cout << "Garbage: " << b.gar << endl;
}
board gen_garbage(int lines,int hold,int seed){
	srand(seed);
	board ret;
	vector<int>v(lines);
	for(int i=0; i<colsz ;i++){
		ret.col[i]=(1<<lines)-1;
	}
	for(int i=0; i<lines ;i++){
		if(i==0) v[i]=rand()%colsz;
		else{
			v[i]=rand()%(colsz-1);
			if(v[i]>=v[i-1]) v[i]++;
		}
		ret.col[v[i]]^=1<<i;
	}
	ret.gar=lines;
	ret.last_move={0,0,0};
	ret.hold=hold;
	return ret;
}
board gen_garbage_fixed(vector<int>fixed,int lines,int hold,int seed){
	srand(seed);
	board ret;
	vector<int>v(lines);
	for(int i=0; i<colsz ;i++){
		ret.col[i]=(1<<lines)-1;
	}
	for(int i=0; i<lines ;i++){
		v[i]=fixed[i];
		ret.col[v[i]]^=1<<i;
	}
	ret.gar=lines;
	ret.last_move={0,0,0};
	ret.hold=hold;
	return ret;
}
void init_boardh(){
	init_pieceh();
	lg[0]=-1;
	for(int i=2; i<(1<<16) ;i++) lg[i]=lg[i/2]+1;
}
