#ifndef __FIBO_H__
#define __FIBO_H__

#include <vector>

using namespace std;

class Fibo {

public:
	vector<bool> value;
	friend ostream &operator<<(ostream &, const Fibo &);
	Fibo(Fibo&& that);

	void normalize();

	Fibo();

	Fibo(string);

	Fibo(int);

	Fibo(const Fibo &);

	size_t length();

	Fibo& operator=(const Fibo &);

	Fibo &operator+=(const Fibo &);

	Fibo &operator+=(int);

	Fibo& operator&=(const Fibo &);

	Fibo& operator^=(const Fibo &);

	Fibo& operator|=(const Fibo &);

	Fibo& operator<<=(int);

	bool operator==(const Fibo &) const;

	bool operator==(int);

	bool operator<(const Fibo &) const;

	bool operator<(int);

	bool operator<=(const Fibo &) const;

	bool operator<=(int);

	bool operator!=(const Fibo &) const;

	bool operator!=(int);

	bool operator>(const Fibo &) const;

	bool operator>(int);

	bool operator>=(const Fibo &) const;

    bool operator>=(int);
};

Fibo operator+(Fibo, const Fibo &);

Fibo operator+(Fibo, int);

Fibo operator&(Fibo, const Fibo &);

Fibo operator^(Fibo, const Fibo &);

Fibo operator|(Fibo, const Fibo &);

Fibo operator<<(Fibo, const Fibo &);

const Fibo &Zero();

const Fibo &One();


#endif //__FIBO_H__
