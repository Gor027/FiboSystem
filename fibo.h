#ifndef __FIBO_H__
#define __FIBO_H__

#include <vector>

using namespace std;

class Fibo {
    vector<bool> value;

    void normalize();

    void aux_case2(vector<bool> &, int);

public:
    Fibo();

    Fibo(const string);

    Fibo(const char *);

    Fibo(int);

    Fibo(unsigned int) = delete;

    Fibo(long) = delete;

    Fibo(long long) = delete;

    Fibo(unsigned long) = delete;

    Fibo(unsigned long long) = delete;

    Fibo(float) = delete;

    Fibo(double) = delete;

    Fibo(bool) = delete;

    Fibo(char) = delete;

    ~Fibo();

    Fibo(const Fibo &);

    Fibo(Fibo &&);

    size_t length() const;

    Fibo &operator=(const Fibo &);

    Fibo &operator=(Fibo &&) noexcept;

    Fibo &operator+=(const Fibo &);

    Fibo &operator+=(int);

    Fibo &operator&=(const Fibo &);

    Fibo &operator&=(int);

    Fibo &operator^=(const Fibo &);

    Fibo &operator^=(int);

    Fibo &operator|=(const Fibo &);

    Fibo &operator|=(int n);

    Fibo &operator<<=(int);

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

    friend ostream &operator<<(ostream &, const Fibo &);
};

Fibo operator+(Fibo, const Fibo &);

Fibo operator+(Fibo, int);

Fibo operator+(int, const Fibo &);

Fibo operator&(Fibo, const Fibo &);

Fibo operator&(Fibo, int);

Fibo operator&(int, const Fibo &);

Fibo operator^(Fibo, const Fibo &);

Fibo operator^(Fibo, int);

Fibo operator^(int, const Fibo &);

Fibo operator|(Fibo, const Fibo &);

Fibo operator|(Fibo, int);

Fibo operator|(int, const Fibo &);

Fibo operator<<(Fibo, int);

const Fibo &Zero();

const Fibo &One();


#endif //__FIBO_H__