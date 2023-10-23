/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#6
* BigInteger.cpp 
* C++ source code for BigInteger program
*********************************************************************************/

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include "BigInteger.h"

#define BASE 1000000000 
#define power 9 

BigInteger::BigInteger(){
   signum = 0;
   List L;
   digits = L;
}

BigInteger::BigInteger(std::string s) {
	if (s.length() == 0) {
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	if(s.length() == 1 && (s[0] == '-' || s[0] == '+')) {
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}
	for(unsigned long i = 0; i < s.length(); i++) {
		if(s[0] == '-' || s[0] == '+') {
			continue;
		}
		if(std::isdigit(s[i]) == 0) {
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}
	std::string string = s;
	signum = 1;
	if(string[0] == '+') {
		string.erase(0,1);
	}
	else if(string[0] == '-') {
		signum = -1;
		string.erase(0,1);
	}
	string.erase(0, string.find_first_not_of('0'));

	if(string.length() % power != 0) {
		int len = (string.length() % power);
		std::string e = string.substr(0, len);

		ListElement E1 = std::stol(e);

		digits.insertBefore(E1);
		string.erase(0, len);
	}

	while(string.length() > 0) {
		std::string e = string.substr(0, (power));
		ListElement E2 = std::stol(e);

		digits.insertBefore(E2);
		string.erase(0, (power));
	}
}

BigInteger::BigInteger(const BigInteger& N){
   signum = N.signum;
   digits = N.digits;
}


int BigInteger::sign() const{
   return signum;
}


int BigInteger::compare(const BigInteger& N) const {
    if(this->signum == -1){
        if(N.signum != -1){
            return -1;
        }
    }
    else if(N.signum == -1){
        if(this->signum != -1){
            return 1;
        }
    }

    int comp = 0;

    if(this->signum != -1 && N.signum != -1){
        if(this->digits.length() > N.digits.length()){
            return 1;
        }
        else if(this->digits.length() < N.digits.length()){
            return -1;
        }
        else{
            List L1 = this->digits;
            List L2 = N.digits;
            L1.moveFront();
            L2.moveFront();
            while(L1.position() < L1.length() && L2.position() < L2.length()){
                int d1 = L1.moveNext();
                int d2 = L2.moveNext();
                if(d1 < d2){
                    comp = -1;
                    break;
                }
                else if(d1 > d2){
                    comp = 1;
                    break;
                }
            }
        }
    }
    else if(this->signum == -1 && N.signum == -1){
        if(this->digits.length() > N.digits.length()){
            return -1;
        }
        else if(this->digits.length() < N.digits.length()){
            return 1;
        }
        else{
            List L1 = this->digits;
            List L2 = N.digits;
            L1.moveFront();
            L2.moveFront();
            while(L1.position() < L1.length() && L2.position() < L2.length()){
                int d1 = L1.moveNext();
                int d2 = L2.moveNext();
                if(d1 < d2){
                    comp = 1;
                    break;
                }
                else if(d1 > d2){
                    comp = -1;
                    break;
                }
            }
        }
    }
    return comp;
}

void BigInteger::makeZero(){
   signum = 0;
   digits.clear();
}

void BigInteger::negate(){
   if(signum != 0){
      signum *= -1;
   }
}


void negateList(List &L){
   if(L.length() > 0){
        L.moveFront();
        while( L.position() < L.length()){
            L.setAfter(L.peekNext() * -1);
            L.moveNext();

        }
   }
}

void sumList(List &S, List A, List B, int sign){
    S.clear();
    A.moveBack();
    B.moveBack();
    S.moveBack();
    if(A.length() != 0 && B.length() == 0){
        S = A;
        return;
    } 
    else if (A.length() == 0 && B.length() != 0){
        S = B;
        return;
    }
    
    while(A.position() != 0 && B.position() != 0){
        S.insertAfter(A.peekPrev() + (sign * B.peekPrev()));
        B.movePrev();
        A.movePrev();
    }
    while(B.position() != 0){
        S.insertAfter(sign * B.peekPrev());
        B.movePrev();
    }
    while(A.position() != 0){
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }

    if(S.front() == 0){
        S.moveFront();
        while(S.moveNext() == 0 && S.position() < S.length()){
            S.eraseBefore();
        }
        if( S.length() == 1 && S.front() == 0){
            S.clear();
        }
    }
}


int normalizeList(List &L){
    if(L.length() == 0){
        return 0;
    }

    L.moveBack();  
    while(L.position() > 0){
        L.movePrev();
        ListElement E = L.peekNext();
        if(E < 0){
            ListElement factor = (-1 * floor(E / BASE)) == 0 ? 1 : (-1 * (E / BASE)); 

            if(L.front() == E){
                negateList(L);
                normalizeList(L);
                return -1;
            }

            L.setAfter( E + (factor * BASE));
            if(L.position() == 0){
                L.insertBefore(factor);
                return -1;
            } 
            else{
                ListElement E1 = L.peekPrev();
                L.setBefore(E1 - factor);
            }
        }
        else if(E >= BASE){
            ListElement factor = floor(E / BASE);
            L.setAfter(E - (factor * BASE));

            if(L.position() == 0){
                L.insertBefore(factor);
                return 1;
            } 
            else{
                ListElement E1 = L.peekPrev();
                L.setBefore(E1 + factor);
            }
        } 
    }
    return 1;
}


    void shiftList(List& L, int p) {
    L.moveBack();
    for(int i = 0; i < p; i++) {
        L.insertBefore(0);
    }
}


void scalarMultiList(List &L, ListElement m){
    if(m == 0){
      L.clear();
      return;
    }
    if(m != 1){
        L.moveBack();
        while (L.position() > 0) {
            long element = L.movePrev();
            L.setAfter(m * element);
        }
    }
}

BigInteger BigInteger::add(const BigInteger& N) const {
    List L1 = this->digits;
    List L2 = N.digits;
    List L3;
    BigInteger A;

    if (this->sign() == 1 && N.sign() == 1) {
        sumList(L3, L1, L2, 1);
        
        A.signum = normalizeList(L3);
        A.digits = L3;
    }
    else if (this->sign() == -1 && N.sign()== -1) {
        negateList(L1);
        negateList(L2);

        sumList(L3, L1, L2, 1);

        A.signum = normalizeList(L3);
        A.digits = L3;
    }
    else {
        if (this->sign() < 0) {
            negateList(L1);
        }
        if (N.sign() < 0) {
            negateList(L2);
        }
        sumList(L3, L1, L2, 1);

        A.signum = normalizeList(L3);
        A.digits = L3;
    }

    return A;
}


BigInteger BigInteger::sub(const BigInteger &N) const{
    List L1 = this->digits;
    List L2 = N.digits;
    List L3;
    BigInteger A;
    BigInteger B = *this;
    BigInteger C = N; 
    int sgn;

    int comp = this->compare(N);
    if( comp == -1){
        A = N.sub(*this);
        A.signum = -1;
        return A;
    }
    else if(N.signum == -1 && signum == -1){
        C.signum = 1;
        B.signum = 1;
        
        A = C.sub(B);
        return A;
    }
    sumList(L3, L1, L2, -1 * N.signum);
    sgn = normalizeList(L3);

    A.signum = sgn;
    A.digits = L3;

    return A;
}


BigInteger BigInteger::mult(const BigInteger& N) const {
	List L1 = this->digits;
    List L2 = N.digits;
    List L3;
    BigInteger A;

	if(this->signum == -1) {
		negateList(L1);
	}
	
	L2.moveBack();
	int shift = 0;
	while(L2.position() > 0) {
		List list1 = L1;
		ListElement element = (N.signum)*L2.movePrev();
		scalarMultiList(list1, element);
		shiftList(list1, shift);
		normalizeList(list1);

		List list2 = L3;
		sumList(L3, list1, list2, 1);
		normalizeList(L3);

		shift += 1;
	}

    if(L3.length() == 0) {
		A.signum = 0;
	}
	else if((this->signum == -1 && N.signum == 1) || (this->signum == 1 && N.signum == -1)) {
		A.signum = -1;
	} 
    else{
		A.signum = 1;
	}

	A.digits = L3;
	return A;
}

std::string BigInteger::to_string(){
    std::string s = "";
    if(this->signum == 0){
        return "0";
    }
    else if(this->signum == -1){
        s += '-';
    }
    digits.moveFront();
    while(digits.position() < digits.length()){
        ListElement E = digits.moveNext();
        std::string element = std::to_string(E);
        while(digits.position() != 1 && element.length() < power){
            element = '0' + element;
        }
        s += element;   
    }
    return s;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
    bool eq = (A.signum == B.signum);
    if(eq){
        eq = (A.digits == B.digits);
    }
    return eq;
}

bool operator<( const BigInteger& A, const BigInteger& B ){
    bool comp = (A.compare(B) == -1);
    return comp;
}

bool operator<=( const BigInteger& A, const BigInteger& B ){
    bool comp = false;
    if(A.compare(B) == -1 || A.compare(B) == 0){
        comp = true;
    }
    return comp;
}

bool operator>( const BigInteger& A, const BigInteger& B ){
    bool comp = (A.compare(B) == 1);
    return comp;
}

bool operator>=( const BigInteger& A, const BigInteger& B ){
    bool comp = false;
    if(A.compare(B) == 1 || A.compare(B) == 0){
        comp = true;
    }
    return comp;
}

BigInteger operator+(const BigInteger &A, const BigInteger &B){
   return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
   A = A.add(B);
   return A;
}
 
BigInteger operator-(const BigInteger &A, const BigInteger &B){
   return A.sub(B);
}

BigInteger operator-=(BigInteger &A, const BigInteger &B){
   A = A.sub(B);
   return A;
}

BigInteger operator*(const BigInteger &A, const BigInteger &B){
   return A.mult(B);
}

BigInteger operator*=(BigInteger &A, const BigInteger &B){
   A = A.mult(B);
   return A;
}