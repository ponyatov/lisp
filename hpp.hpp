#ifndef _H_HPP
#define _H_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string tag,val;
	Sym(string,string); Sym(string);
	vector<Sym*> nest; void push(Sym*);
	virtual string dump(int=0); virtual string head(); string pad(int);
	virtual Sym* eval();
	virtual Sym* apply(Sym*);
	virtual Sym* mul(); virtual Sym* mul(Sym*);
};

extern Sym* nil;

struct Num: Sym { Num(string); Num(int); };

struct Op: Sym { Op(string); Sym*apply(Sym*); };

struct Cons: Sym { Cons(Sym*,Sym*); string head(); Sym*eval(); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
