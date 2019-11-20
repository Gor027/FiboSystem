#include <iostream>
#include <vector>
#include "fibo.h"
#include <algorithm>
#include <cassert>

using namespace std;


Fibo::Fibo() {
    this->value.push_back(false);
}

Fibo::Fibo(int a) {
    static vector<int> calculated_fibonacci = {1, 2};

    size_t vec_size = calculated_fibonacci.size();
    if (calculated_fibonacci[vec_size - 1] < a) {
        size_t i = vec_size - 1;
        while (calculated_fibonacci[i] < a) {
            calculated_fibonacci.push_back(calculated_fibonacci[i] + calculated_fibonacci[i - 1]);
            i++;
        }
    }

    vector<size_t> indexes;
    int suma = a;

    while (suma > 0) {
        auto found = upper_bound(calculated_fibonacci.begin(), calculated_fibonacci.end(), suma);
        int index = found - 1 - calculated_fibonacci.begin();
        indexes.push_back(index);
        suma -= calculated_fibonacci[index];
    }

    vec_size = indexes.size();
    if (vec_size == 0) {
        this->value.push_back(false);
    } else {
        this->value.resize(indexes[0] + 1, false);

        for (size_t i = 0; i < vec_size; i++) {
            this->value[indexes[i]] = true;
        }
    }
}


Fibo::Fibo(const Fibo &f) {
    for (bool i : f.value) {
        this->value.push_back(i);
    }
}

size_t Fibo::length() {
    return this->value.size();
}

void Fibo::normalize() {
    value.push_back(false);
    size_t m = value.size();
    size_t n = m - 2;

    for (size_t i = n; i > 0; --i) {
        if (value[i] == true && value[i - 1] == true) {
            value[i] = false;
            value[i - 1] = false;
            value[i + 1] = true;
            size_t j = i + 2;
            while (j < m && value[j] == value[j - 1]) {
                value[j] = false;
                value[j - 1] = false;
                value[j + 1] = true;
                j += 2;
            }
        }
    }

    if (value[m - 1] == false)
        value.pop_back();
}

Fibo::Fibo(string str) {
    size_t n = str.size();

    for (size_t i = n; i > 0; i--) {
        if (str[i - 1] == '0')
            value.push_back(false);
        else
            value.push_back(true);
    }

    n--;
    while (n > 0 && value[n] == false) {
        value.pop_back();
        n--;
    }

    normalize();
}

ostream &operator<<(ostream &output, const Fibo &fibo) {
    size_t n = fibo.value.size();
    for (size_t i = n; i > 0; --i) {
        output << fibo.value[i - 1];
    }
    return output;
}

///move constructor
Fibo::Fibo(Fibo &&that) : value(move(that.value)) {}

const Fibo &Zero() {
    static const Fibo ret;
    return ret;
}

const Fibo &One() {
    static const Fibo ret(1);
    return ret;
}

Fibo &Fibo::operator=(const Fibo &fibo) {
    this->value = fibo.value;
    return *this;
}

Fibo &Fibo::operator+=(const Fibo &rhs) {
    Fibo fibo;
    fibo.value.clear();

    size_t i = 0;
    for (i = 0; i < (this->value.size() >= rhs.value.size() ? rhs.value.size() : this->value.size()); ++i) {
        if (this->value[i] == 1 && rhs.value[i] == 1) {
            fibo.value.push_back(false);
            fibo.value.push_back(true);
        } else {
            // Here at least one of the values is 0(maybe both).
            fibo.value.push_back(this->value[i] + rhs.value[i]);
        }
    }

    for (; i < this->value.size(); i++)
        fibo.value.push_back(this->value[i]);

    for (; i < rhs.value.size(); i++)
        fibo.value.push_back(rhs.value[i]);

    fibo.normalize();
    *this = fibo;

    return *this;
}

Fibo &Fibo::operator+=(int a) {
    Fibo rhs(a);
    return *this += rhs;
}

Fibo operator+(Fibo lhs, const Fibo &rhs) {
    lhs += rhs;
    return lhs;
}

Fibo operator+(Fibo lhs, int rhs) {
    lhs += rhs;
    return lhs;
}

Fibo &Fibo::operator&=(const Fibo &rhs) {
    while (value.size() > rhs.value.size()) {
        value.pop_back();
    }

    for (size_t i = 0; i < value.size(); i++)
        value[i] = value[i] & rhs.value[i];

    size_t n = value.size() - 1;
    while (n > 0 && value[n] == false) {
        --n;
        value.pop_back();
    }

    return *this;
}

Fibo operator&(Fibo lhs, const Fibo &rhs) {
    lhs &= rhs;
    return lhs;
}

Fibo &Fibo::operator^=(const Fibo &rhs) {
    if (value.size() < rhs.value.size())
        value.resize(rhs.value.size(), false);

    size_t i = 0;
    while (i < rhs.value.size()) {
        value[i] = value[i] != rhs.value[i];
        i++;
    }

    size_t n = value.size() - 1;
    while (n > 0 && value[n] == false) {
        --n;
        value.pop_back();
    }

    normalize();

    return *this;
}

Fibo operator^(Fibo lhs, const Fibo &rhs) {
    lhs ^= rhs;
    return lhs;
}

Fibo &Fibo::operator|=(const Fibo &rhs) {
    if (value.size() < rhs.value.size())
        value.resize(rhs.value.size(), false);

    size_t i = 0;
    while (i < rhs.value.size()) {
        if (rhs.value[i] == true)
            value[i] = true;
        i++;
    }

    normalize();

    return *this;
}

Fibo operator|(Fibo lhs, const Fibo &rhs) {
    lhs |= rhs;
    return lhs;
}

Fibo &Fibo::operator<<=(int n) {
    reverse(value.begin(), value.end());
    int i = 0;
    while (i < n) {
        value.push_back(false);
        ++i;
    }
    reverse(value.begin(), value.end());
}

Fibo operator<<(Fibo lhs, int rhs) {
    lhs <<= rhs;
    return lhs;
}

bool Fibo::operator==(const Fibo &f2) const {
    if (this->value.size() != f2.value.size())
        return false;

    for (size_t i = 0; i < value.size(); i++)
        if (this->value[i] != f2.value[i])
            return false;

    return true;
}

bool Fibo::operator==(int a) {
    Fibo arg(a);
    return *this == arg;
}

bool Fibo::operator<(const Fibo &f2) const {
    if (*this == f2)
        return false;

    if (this->value.size() > f2.value.size())
        return false;
    else {
        for (size_t i = 0; i < this->value.size(); i++) {
            if (this->value[i] > f2.value[i])
                return false;
        }
    }

    return true;
}

bool Fibo::operator<(int a) {
    Fibo arg(a);
    return *this < arg;
}

bool Fibo::operator<=(const Fibo &f2) const {
    return *this == f2 || *this < f2;
}

bool Fibo::operator<=(int a) {
    Fibo arg(a);
    return *this <= arg;
}

bool Fibo::operator!=(const Fibo &f2) const {
    return !(*this == f2);
}

bool Fibo::operator!=(int a) {
    Fibo arg(a);
    return *this != arg;
}

bool Fibo::operator>(const Fibo &f2) const {
    if (*this == f2)
        return false;

    if (this->value.size() < f2.value.size())
        return false;
    else {
        for (size_t i = 0; i < f2.value.size(); i++) {
            if (this->value[i] < f2.value[i])
                return false;
        }
    }

    return true;
}

bool Fibo::operator>(int a) {
    Fibo arg(a);
    return *this > arg;
}

bool Fibo::operator>=(const Fibo &f2) const {
    return *this == f2 || *this > f2;
}

bool Fibo::operator>=(int a) {
    Fibo arg(a);
    return *this >= arg;
}

int main() {

    Fibo f;

    assert(f == Zero());
    assert(Fibo(f) == Zero());

    assert(Zero() < One());
    assert(Fibo("11") == Fibo("100"));
    assert((Fibo("1001") + Fibo("10")) == Fibo("1011"));
    assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
    assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
    assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
    assert((Fibo("101") << 3) == Fibo("101000"));

    f = One();
    f <<= 3;
    assert(f == Fibo("1000"));

    f = One();
    assert(f + Fibo("1") == Fibo("10"));
    assert(f == One());

    Fibo f1("101");
    Fibo f2 = Fibo("101");
    assert(f1 == f2);

    assert(Fibo("11").length() == 3); // 11 == 100

    std::cout << Fibo("11") << std::endl; // prints 100

    return 0;
}