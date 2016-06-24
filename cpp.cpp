#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main(int argc, char *argv[]) { return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V){}
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::head() { return "<"+tag+":"+val+">"; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

Sym* Sym::eval() {
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		(*it) = (*it)->eval();
	return this; }

Sym* Sym::apply(Sym*o) { return nil; }

Sym* Sym::mul(Sym*o) { return nil; }

Num::Num(string V):Sym("num",V){}
Num::Num(int N):Sym("num",""){ ostringstream os; os<<N; val=os.str(); }
Sym* Num::mul(Sym*o) { cerr<<val<<".mul\n";
	if (o->tag!="num") return nil;
	else return new Num(val);//atoi(val.c_str())+atoi(o->val.c_str()));
}

Op::Op(string V):Sym("op",V){}
Sym* Op::apply(Sym*o) { cerr<<val<<".apply\n";
	if (val=="*") return o->nest[0]->mul(o->nest[1]);
	else return this;
}

Cons::Cons(Sym*A,Sym*B):Sym("cons","") { push(A); push(B); }
string Cons::head() { return "."; }
Sym* Cons::eval() { return nest[0]->apply(nest[1]); }

Sym* nil = new Sym("nil","");
