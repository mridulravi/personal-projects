#ifndef HILBERT_HH
#define HILBERT_HH
#include<iostream>
#include<utility>
#include<vector>
#include<string>
#include<sys/wait.h>
using namespace std;

class wff
{
public:
	char val;
//	bool atomic;
	wff * lhs;
	wff * rhs;
	void implement_dt();
	void print();
	
	wff(wff * a, wff *b, char c);
	
};

void apply_modus_ponens(wff* a, wff* b,int i1,int i2);
void check_if_proved();
void print_modus_ponens(int i1, int i2);
pair<int,int> check_modus_ponens(); 
bool wff_equals(wff* a, wff* b);
bool is_in_vector(wff * a);
bool try_axiom1_1();
bool try_axiom1_2();
bool try_axiom2();
bool try_axiom3();
bool try_axiom3_2();
void ask_human_help();
wff* string_to_wff(string s);
bool check_if_valid_char(char a);
wff * helper(string str);
int find_matching(string str);
bool in_axiom_vec(int i);
bool in_rhs_axiom2 ( wff * w);
bool try_brute_force();
bool in_vec(wff *a , vector<wff *> & vec);
vector<wff *> * extract_out_literals(wff * a);
vector<wff *> * extract_wff_of_depth_one(wff *a);
#endif
