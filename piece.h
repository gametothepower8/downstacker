#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
struct rot{//a piece with fixed rotation
	vector<int>in;
	vector<int>out;
};
struct piece{
	int id;
	char name;
	vector<rot>rots;//list of possible rotations
	piece(int _id,char _name){
		id=_id,name=_name;
	}
	void addrot(rot x){
		rots.push_back(x);
	}
};
vector<piece>pieces;
int piece_char_to_id[226];
void init_pieceh(){
	rot i0={{0,0,0,0},{1,1,1,1}};
	rot i1={{0},{15}};
	rot o0={{0,0},{3,3}};
	
	rot j0={{0,0,0},{3,1,1}};
	rot j1={{0,2},{7,4}};
	rot j2={{1,1,0},{2,2,3}};
	rot j3={{0,0},{1,7}};
	
	rot l0={{0,0,0},{1,1,3}};
	rot l1={{0,0},{7,1}};
	rot l2={{0,1,1},{3,2,2}};
	rot l3={{2,0},{4,7}};
	
	rot t0={{0,0,0},{1,3,1}};
	rot t1={{0,1},{7,2}};
	rot t2={{1,0,1},{2,3,2}};
	rot t3={{1,0},{2,7}};
	
	rot s0={{0,0,1},{1,3,2}};
	rot s1={{1,0},{6,3}};
	rot z0={{1,0,0},{2,3,1}};
	rot z1={{0,1},{3,6}};
	
	piece i(0,'I');i.addrot(i0);i.addrot(i1);
	piece j(1,'J');j.addrot(j0);j.addrot(j1);j.addrot(j2);j.addrot(j3);
	piece l(2,'L');l.addrot(l0);l.addrot(l1);l.addrot(l2);l.addrot(l3);
	piece o(3,'O');o.addrot(o0);
	piece t(4,'T');t.addrot(t0);t.addrot(t1);t.addrot(t2);t.addrot(t3);
	piece s(5,'S');s.addrot(s0);s.addrot(s1);
	piece z(6,'Z');z.addrot(z0);z.addrot(z1);
	pieces={i,j,l,o,t,s,z};
	piece_char_to_id['I']=0;
	piece_char_to_id['J']=1;
	piece_char_to_id['L']=2;
	piece_char_to_id['O']=3;
	piece_char_to_id['T']=4;
	piece_char_to_id['S']=5;
	piece_char_to_id['Z']=6;
}
