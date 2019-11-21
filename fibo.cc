#include <iostream>
#include <vector>
#include "fibo.h"
#include <algorithm>
#include <cassert>

using namespace std;


Fibo::Fibo() : Fibo(0) {}

Fibo::Fibo(int a) {
    assert(a >= 0);

    static vector<int> calc_fibo = {1, 2};

    size_t vec_size = calc_fibo.size();
    if (calc_fibo[vec_size - 1] < a) {
        size_t i = vec_size - 1;
        while (a - calc_fibo[i] >= calc_fibo[i - 1]) {
            calc_fibo.push_back(calc_fibo[i] + calc_fibo[i - 1]);
            i++;
        }
    }

    vector<size_t> indexes;
    int suma = a;

    while (suma > 0) {
        auto found = upper_bound(calc_fibo.begin(), calc_fibo.end(), suma);
        int index = found - 1 - calc_fibo.begin();
        indexes.push_back(index);
        suma -= calc_fibo[index];
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

Fibo::Fibo(const Fibo &f) : value(f.value) {}

size_t Fibo::length() const {
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

bool string_correctnes(string str) {
    bool ret = true;
    size_t i = 0;
    if (str.empty() || (str[0] == '0' && str.size() > 1))
        ret = false;
    while (i < str.size() && ret) {
        if (str[i] != '0' && str[i] != '1')
            ret = false;
        i++;
    }
    return ret;
}

Fibo::Fibo(const string str) {
    assert(string_correctnes(str));

    size_t n = str.size();

    for (size_t i = n; i > 0; i--) {
        value.push_back(str[i - 1] != '0');
    }

    n--;
    while (n > 0 && value[n] == false) {
        value.pop_back();
        n--;
    }

    normalize();
}

Fibo::Fibo(const char *str) : Fibo(string(str)) {
    assert(str != nullptr);
}

ostream &operator<<(ostream &output, const Fibo &fibo) {
    size_t n = fibo.value.size();
    for (size_t i = n; i > 0; --i) {
        output << fibo.value[i - 1];
    }
    return output;
}

Fibo::Fibo(Fibo &&that) : value(move(that.value)) {}

const Fibo &Zero() {
    static const Fibo ret;
    return ret;
}

const Fibo &One() {
    static const Fibo ret(1);
    return ret;
}

Fibo &Fibo::operator=(const Fibo &f) {
    this->value = f.value;
    return *this;
}

Fibo &Fibo::operator=(Fibo &&f) noexcept {
    value = move(f.value);
    return *this;
}

void Fibo::aux_case2(vector<bool> &value, int i) {
    size_t j = i;

    if (j >= 2) {
        while (j >= 2) {
            j -= 2;
            //case type: 0201
            if (value[j] == true) {
                value[j] = false;
                value[j + 1] = true;
                if (j == 1) {
                    assert(value[0] == false);
                    value[0] = true;
                }
            }
                //case type: 0200
            else {
                if (j > 0) {
                    if (value[j - 1] == true) {
                        value[j - 1] = false;
                        value[j] = false;
                        value[j + 1] = true;
                    } else {
                        value[j] = true;
                    }
                } else {
                    value[j] = true;
                }
                j = 0;
            }
        }
    } else if (j == 1) {
        value[j - 1] = true;
    }
}

Fibo &Fibo::operator+=(const Fibo &rhs) {
    if (value.size() < rhs.value.size())
        value.resize(rhs.value.size(), false);

    int surplus = 0, sum;
    sum = (int) value[0] + (int) rhs.value[0];
    if (sum == 1) {
        value[0] = true;
    } else if (sum == 2) {
        value[0] = false;
        surplus = 1;
    }

    for (size_t i = 1; i < value.size(); i++) {
        sum = (int) value[i] + surplus;
        if (i < rhs.value.size()) {
            sum += (int) rhs.value[i];
        }

        if (sum == 0) {
            //nothing to do
        } else if (sum == 1) {
            if (value[i - 1] == false) {
                value[i] = true;
                surplus = 0;
            } else {
                value[i] = false;
                value[i - 1] = false;
                surplus = 1;
            }
        } else if (sum == 2) {
            if (value[i - 1] == true) {
                value[i - 1] = false;
                value[i] = true;
                surplus = 1;
            }
                //0201 or 0200
            else {
                surplus = 1;
                value[i] = false;
                aux_case2(value, i);
            }
        } else {
            value[i] = true;
            surplus = 1;

            aux_case2(value, i);

            if (value[i - 1] == true) {
                value[i - 1] = false;
                value[i] = false;
                surplus = 2;
            }
        }
    }

    if (surplus == 1) {
        if (value.size() > 0 && value.back() == true) {
            value.back() = false;
            value.push_back(false);
            value.push_back(true);
        } else {
            value.push_back(true);
        }
    }
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
    lhs += Fibo(rhs);
    return lhs;
}

Fibo operator+(int lhs, const Fibo &rhs) {
    Fibo lhs_fibo(lhs);
    lhs_fibo += rhs;
    return lhs_fibo;
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

Fibo &Fibo::operator&=(int n) {
    *this &= Fibo(n);
    return *this;
}

Fibo operator&(Fibo lhs, const Fibo &rhs) {
    lhs &= rhs;
    return lhs;
}

Fibo operator&(int n, const Fibo &rhs) {
    Fibo f(n);
    f &= rhs;
    return f;
}

Fibo operator&(Fibo lhs, int n) {
    Fibo f(n);
    return lhs &= f;
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

Fibo &Fibo::operator^=(int n) {
    *this ^= Fibo(n);
    return *this;
}

Fibo operator^(Fibo lhs, const Fibo &rhs) {
    lhs ^= rhs;
    return lhs;
}

Fibo operator^(Fibo lhs, int n) {
    return lhs ^= Fibo(n);
}

Fibo operator^(int n, const Fibo &rhs) {
    Fibo f(n);
    return f ^= rhs;
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

Fibo &Fibo::operator|=(int n) {
    *this |= Fibo(n);
    return *this;
}

Fibo operator|(Fibo lhs, const Fibo &rhs) {
    lhs |= rhs;
    return lhs;
}

Fibo operator|(Fibo lhs, int n) {
    return lhs |= Fibo(n);
}

Fibo operator|(int n, const Fibo &rhs) {
    Fibo f(n);
    return f |= rhs;
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

Fibo::~Fibo() {}

int main() {

        

    return 0;
}