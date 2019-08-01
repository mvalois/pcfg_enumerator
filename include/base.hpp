#ifndef BASE_H
#define BASE_H

#include <utility>
#include <ostream>
#include <fstream>

// i.e. L8, D4, S2
class Base: public std::pair<char, int> {
public:
	char type = this->first;
	unsigned int len = this->second;

	friend std::ostream& operator<<(std::ostream& os, const Base& b);
	friend std::ifstream& operator>>(std::ifstream& ifs, Base& b);
	bool operator==(const Base &lhs);
	bool operator!=(const Base &lhs);
};

namespace std {
	template<>
	struct hash<Base> : public unary_function<Base, size_t> {
		size_t operator()(const Base& b) const {
			return (hash<char>()(b.type)
				^ (hash<int>()(b.len)<<1) >> 1);
		}
	};
}

#endif