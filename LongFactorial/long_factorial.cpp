/*
author: s.aparajith@live.com
date: 22.11.2020
*/
#include <bits/stdc++.h>
using namespace std;
class BigInteger 
{
std::string value;
bool sign = 0;
public:
BigInteger()
{
    value = "0";
}
BigInteger(const std::string&s)
{
    unsigned long start = s.find_first_not_of("0-");
    if (!std::strcmp(&s[start],"")) {
    std::strcpy(&value[0], "0");
    }
    if(s[0] == '-') {
    sign = 1;
    }
    value = &s[start];
}
BigInteger(long int a)
{
    sign =0;
    if (a < 0)
    {
        sign = 1;
        a *= -1;
    }
   value = std::to_string(a);
}
BigInteger operator=(long int a)
{
    return *new BigInteger(a);
}
std::string getValue() const
{
    return value;
}
bool getSign() const
{
    return sign;   
}
BigInteger operator+(const BigInteger & a) const{
    //a + (-b) = a - b
    if (!getSign() && a.getSign()) {
    BigInteger * temp = new BigInteger(a.value);
    return *this - *temp;
    }

    //(-a) + b = b - a
    if (getSign() && !a.getSign()) {
    //temp is positive. temp = -a
    BigInteger * temp = new BigInteger(value);
    return a - *temp;
    }

    //a + b = b + a
    if (value.length() < a.length())
    return a.operator+(*this);

    std::string result = this->add(a);

    //(-a) + (-b) = -(a + b)
    if (getSign() && a.getSign())
    return *new BigInteger('-' + result);

    return *new BigInteger(result);
}

BigInteger operator-(const BigInteger& a) const
{
   if (length() == 0)
    return a * *new BigInteger(-1);
    if (a.length() == 0)
    return *this * *new BigInteger(-1);
    //both positive
    if (!getSign() && !a.getSign()) {
    if (*this > a)
        return *new BigInteger(this->subtract(a));

    // a - b = -(b - a)
    BigInteger * result = new BigInteger(a.subtract(*this));
    result->setSign(true);
    return *result;
    }

    //a - (-b) = a + b
    if (!getSign() && a.getSign())
    return *new BigInteger(this->add(a));

    //(-a) - b = - (a + b)
    if (getSign() && !a.getSign()) {
    BigInteger result = this->add(a);
    result.setSign(true);
    return result;
    }

    //(-a) - (-b) = b - a
    BigInteger temp1 = *new BigInteger(value);
    BigInteger temp2 = *new BigInteger(a.value);
    return temp2 - temp1;
}

BigInteger operator*(const BigInteger& a) const
{
    BigInteger final = 0;
    std::string result;
    BigInteger* temp;


    int carry;
    int current;

    //fast mult algorithm. the same we were taught in elementary.
    for(long i=length() - 1;i >= 0; i--)
    {
    carry = 0;
    result = "";
    for (long j=a.length() - 1; j >= 0; j--)
    {
        current = (value[i] - '0') * (a.value[j] - '0') + carry;
        result = (char)(current % 10 + '0') + result;
        carry = current / 10;
    }

    if (carry > 0)
        result = (char)(carry + '0') + result;

    temp = new BigInteger(result);
    final += *new BigInteger(temp->alignLeft(length() - i - 1));
    }

    final.setSign(sign ^ a.sign);
    return final;
}
void operator+=(const BigInteger& a){
    BigInteger temp = *this + a;
    value = temp.value;
    sign = temp.sign;
}

void operator-=(const BigInteger& a){
    BigInteger temp = *this - a;
    value = temp.value;
    sign = temp.sign;
}
bool operator==(const BigInteger& a) const
{
    if (length() == 0 && a.length() == 0)
    return true;

    //if the signs are not the same
    if (getSign() ^ a.getSign())
    return false;

    if (length() != a.length())
    return false;

    for(long i = 0; i < length(); i++){
    if (value[i] != a.value[i])
        return false;
    }

    return true;
}
void operator--()
{
    *this= *this - 1;
}

bool operator<(const BigInteger& a) const{
    if (getSign() && !a.getSign())
    return true;
    if (!getSign() && a.getSign())
    return false;

    unsigned long l1 = length(), l2 = a. length();

    //both positive
    if (!getSign() && !a.getSign()) {
    if (l1 > l2)
        return false;

    if (l1 < l2)
        return true;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return false;

        if (value[i] < a.value[i])
            return true;
    }
    }

    else {
    if (l1 > l2)
        return true;

    if (l1 < l2)
        return false;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return true;

        if (value[i] < a.value[i])
            return false;
    }
    }

    //equal
    return false;
}

bool operator<=(const BigInteger& a) const{
    if (getSign() && !a.getSign())
    return true;
    if (!getSign() && a.getSign())
    return false;

    unsigned long l1 = length(), l2 = a. length();

    //both positive
    if (!getSign() && !a.getSign()) {
    if (l1 > l2)
        return false;

    if (l1 < l2)
        return true;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return false;

        if (value[i] < a.value[i])
            return true;
    }
    }

    else {
    if (l1 > l2)
        return true;

    if (l1 < l2)
        return false;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return true;

        if (value[i] < a.value[i])
            return false;
    }
    }

    //equal
    return true;
}

bool operator>(const BigInteger& a) const{
    if (getSign() && !a.getSign())
    return false;
    if (!getSign() && a.getSign())
    return true;

    unsigned long l1 = length(), l2 = a. length();

    //both negative
    if (getSign() && a.getSign()) {
    if (l1 > l2)
        return false;

    if (l1 < l2)
        return true;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return false;

        if (value[i] < a.value[i])
            return true;
    }
    }

    else {
    if (l1 > l2)
        return true;

    if (l1 < l2)
        return false;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return true;

        if (value[i] < a.value[i])
            return false;
    }
    }

    //equal
    return false;
}

bool operator>=(const BigInteger& a) const{
    if (getSign() && !a.getSign())
    return false;
    if (!getSign() && a.getSign())
    return true;

    unsigned long l1 = length(), l2 = a. length();

    //both negative
    if (getSign() && a.getSign()) {
    if (l1 > l2)
        return false;

    if (l1 < l2)
        return true;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return false;

        if (value[i] < a.value[i])
            return true;
    }
    }

    else {
    if (l1 > l2)
        return true;

    if (l1 < l2)
        return false;

    for (long i = 0; i < l1; i++) {
        if (value[i] > a.value[i])
            return true;

        if (value[i] < a.value[i])
            return false;
    }
    }

    //equal
    return true;
}

unsigned long length() const
{
    if (value == "0")
    return 0;
    return value.length();
}

private:

std::string subtract(const BigInteger&a) const
{

    if (a.length() > length())
    return a.subtract(*this);
    long numOfZeros = this->length() - a.length();
    std::string aligned = a.align(numOfZeros);
    //now this and a are in the same length

    std::string result = "";
    int x = 0;
    bool carry = 0;

    for (long i = value.length() -1; i>=0; i--){
    x=value[i] - aligned[i] - carry;
    carry = false;
    if (x < 0){
        x+=10;
        carry = true;
    }
    result = (char)(x + 48) + result;
    }

    return result;
}
void setSign(const bool s)
{ 
    sign = s;
}
BigInteger alignLeft(const unsigned long l ) const
{
    std::string newStr = value;
    for (unsigned long i=0; i<l; i++)
    {
        newStr = newStr + "0";
    }
    return newStr;
}
std::string add(const BigInteger & a) const {
    unsigned long numOfZeros = value.length() - a.length();
    std::string aligned = a.align(numOfZeros);
    //now this and a are in the same length

    std::string result;
    int x = 0;
    bool carry = 0;

    for (long i = value.length() -1; i>=0; i--){
    //according to the ascii table '0' = 0 + 48 so subtracting 48 is a more sufficient way to convert
    x=value[i] + aligned[i] - 96 + carry;
    carry = x/10;
    result = (char)(x%10 + 48) + result;
    }

    //in case of "overflow"
    if (carry)
    result = "1" + result;

    return result;
}
std::string align(const unsigned long l) const{
    std::string newStr = value;
    for (unsigned long i=0; i<l; i++){
    newStr = "0" + newStr;
    }
    return newStr;
}
};

std::ostream& operator<<(std::ostream& os, const BigInteger& a)
{
    if (a.length() == 0 || a.getValue()[0] == '0') {
    std::string zero = "0";
    return os << zero;
    }
    if (a.getSign())
    return os << "-" + a.getValue();
    else
    return os<< a.getValue();
}


// Complete the extraLongFactorials function below.
void extraLongFactorials(int n) 
{
BigInteger I(n);
while(n>1)
{
   BigInteger I_1(--n);
   I = I*I_1; 
}
cout<<I;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    extraLongFactorials(n);

    return 0;
}
