#include "preterm.hpp"

Preterm::Preterm(const Preterm &pt){
	this->proba = pt.proba;
	this->structure = pt.structure;
	this->ordered_rules = pt.ordered_rules;
	this->pivot = pt.pivot;
	this->ruleranks = pt.ruleranks;
}

Preterm::Preterm(double proba, const Structure &structure, Ruledict *ordered_rules){
	this->proba = proba;
	this->structure = structure;
	this->ordered_rules = ordered_rules;
}

bool Preterm::operator[](const unsigned int pivot){
	unsigned int rank = ruleranks[pivot];
	Base &b = structure[pivot];
	if(rank+1 >= (*ordered_rules)[b].size()){
		return false;
	}
	proba /= (*ordered_rules)[b][rank+0].second;
	proba *= (*ordered_rules)[b][rank+1].second;
	ruleranks[pivot]++;
	return true;
}

std::ostream& operator<<(std::ostream& os, Preterm& pt){
	for(unsigned int pivot=0; pivot < pt.structure.size(); pivot++){
		const Base &b = pt.structure[pivot];
		unsigned int rank = pt.ruleranks[pivot];
		Rule r = (*pt.ordered_rules)[b][rank].first;
		os << r.terminal;
	}
	return os;
}

bool operator<(const Preterm &lhs, const Preterm &rhs){
	return lhs.proba < rhs.proba;
}