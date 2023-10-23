/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#8
* Dictionary.cpp 
* C source code for Dictionary ADT program
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

//#define nil_key "\0"
//#define nil_val -1

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = -1;
}

/********************* HEAPLER FUNCTIONS **************************/
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R->key != N->key && R != nil){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R){
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        this->num_pairs--;
        delete R;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if((R == nil) || (R->key == k)) {
		return R;
	}
	else if(R->key < k) {
		return search(R->right, k);
	}
	else {
		return search(R->left, k);
	}
}

Dictionary::Node* Dictionary::findMin(Node* R){
    if(R == nil){
        return R;
    }
    while(R->left != nil){
        R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    if(R == nil){
        return R;
    }
    while(R->right != nil){
        R = R->right;
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N){
    if(N->right != nil){
        return findMin(N->right);
    }
    else{
        Node* P = N->parent;
        Node* M  = N;
        
        while(P != nil && M == P->right){
            M = P;
            P = P->parent;
        }
        return P;
    }
}

Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N->left != nil){
        return findMax(N->left);
    }
    else{
        Node* P = N->parent;
        Node* M = N;
        while(P != nil && M == P->left){
            M = P;
            P = P->parent;
        }
        return P;
    }
}

void Dictionary::Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v != nil){
        v->parent = u->parent;
    }
}

// RBT Helper Functions (Optional) -----------------------------------------

void Dictionary::LeftRotate(Node* N) {
	Node* A = N->right;

	N->right = A->left;
	if(A->left != this->nil) {
		A->left->parent = N;
	}
	A->parent = N->parent;
	if(N->parent == this->nil) {
		this->root = A;
	}
	else if(N == N->parent->left) {
		N->parent->left = A;
	}
	else{
		N->parent->right = A;
	}
	A->left = N;
	N->parent = A;
}

void Dictionary::RightRotate(Node* N) {
	Node *A = N->left;

	N->left = A->right;
	if(A->right != this->nil) {
		A->right->parent = N;
	}
	A->parent = N->parent;
	if(N->parent == this->nil) {
		this->root = A;
	}
	else if(N == N->parent->right) {
		N->parent->right = A;
	}
	else{
		N->parent->left = A;
	}
	A->right = N;
	N->parent = A;
}

void Dictionary::RB_InsertFixUp(Node* N) {
	while(N->parent->color == 1) {
		if(N->parent == N->parent->parent->left) {
			Node* y = N->parent->parent->right;
			if(y->color == 1) {
				N->parent->color = 0;
				y->color = 0;
				N->parent->parent->color = 1;
				N = N->parent->parent;
			}
			else{
				if(N == N->parent->right) {
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = 0;
				N->parent->parent->color = 1;
				RightRotate(N->parent->parent);
			}
		}
		else{
            Node* y = N->parent->parent->left;
			if(y->color == 1) {
				N->parent->color = 0;
				y->color = 0;
				N->parent->parent->color = 1;
				N = N->parent->parent;
			}
			else{
				if(N == N->parent->left) {
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = 0;
				N->parent->parent->color = 1;
				LeftRotate(N->parent->parent);
			}
		}
	}
	this->root->color = 0;
}

void Dictionary::RB_Transplant(Node *u, Node *v){
    if(u->parent == this->nil){
        this->root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
	while(N != root && N->color == 0){
		if(N == N->parent->left) {
			Node* W = N->parent->right;
			if(W->color == 1) {
				W->color = 0;
				N->parent->color = 1;
				LeftRotate(N->parent);
				W = N->parent->right;
			}
			if(W->left->color == 0 && W->right->color == 0) {
				W->color = 1;
				N = N->parent;
			}
			else{
				if(W->right->color == 0) {
					W->left->color = 0;
					W->color = 1;
					RightRotate(W);
					W = N->parent->right;
				}
				W->color = N->parent->color;
				N->parent->color = 0;
				W->right->color = 0;
				LeftRotate(N->parent);
				N = this->root;
			}
		}
		else{
			Node* W = N->parent->left;
			if(W->color == 1) {
				W->color = 0;
				N->parent->color = 1;
				RightRotate(N->parent);
				W = N->parent->left;
			}
			if(W->right->color == 0 && W->left->color == 0) {
				W->color = 1;
				N = N->parent;
			}
			else{
				if(W->left->color == 0) {
					W->right->color = 0;
					W->color = 1;
					LeftRotate(W);
					W = N->parent->left;
				}
				W->color = N->parent->color;
				N->parent->color = 0;
				W->left->color = 0;
				RightRotate(N->parent);
				N = this->root;
			}
		}
	}
	N->color = 0;
}

void Dictionary::RB_Delete(Node* N) {
    Node* x;
	Node* y = N;
	int y_original_color = y->color;
	
	if(N->left == nil) {
		x = N->right;
		RB_Transplant(N, N->right);
	}
	else if(N->right == nil) {
		x = N->left;
		RB_Transplant(N, N->left);
	}
	else{
		y = findNext(N);
		y_original_color = y->color;
		x = y->right;
		if(y->parent == N) {
			x->parent = y;
		}
		else{
			RB_Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		RB_Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
		y->color = N->color;
	}
	if(y_original_color == 0) {
		RB_DeleteFixUp(x);
	}
}

/********************* HEAPLER FUNCTIONS **************************/

Dictionary::Dictionary(){
    nil = new Node("\0", -1);
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->color = 0;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("\0", -1);
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->color = 0;
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, nil);
}

Dictionary::~Dictionary(){
    postOrderDelete(root);
    root = nullptr;
    current = nullptr;
    Node* N = nil;
    delete N;
}

int Dictionary::size() const{
    return(num_pairs);
}

bool Dictionary::contains(keyType k) const{
    bool exist = true;
    Node* N = search(this->root, k);
    //std::cout << "exist:" << exist << std::endl;
    if(N == nil){
        exist = false;
    }
    //std::cout << "exist:" << exist << std::endl;
    return exist;
}

valType& Dictionary::getValue(keyType k) const{
    bool exist = contains(k);
    //std::cout << "k:" << k << "     exist:" << exist << std::endl;
    if(exist == false){
        throw std::logic_error("Dictionary: getValue(): key \""+ k +"\" does not exist");
    }
    else{
        Node* N = search(root, k);
        return N->val;
    }
}

bool Dictionary::hasCurrent() const{
    if(current == nil){
        return false;
    }
    else{
        return true;
    }
}

keyType Dictionary::currentKey() const{
    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    else{
        return current->key;
    }
}

valType& Dictionary::currentVal() const{
    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    else{
        return current->val;
    }
}

void Dictionary::clear(){

    postOrderDelete(this->root);    
    this->root = nil;
    this->current = nil;
    this->num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
	Node* A = nil;
	Node* B = this->root;
	while(B != nil) {
		A = B;
		if(k < B->key) {
			B = B->left;
		}
		else if(k == B->key) {
			B->val = v;
			return;
		}
		else{
			B = B->right;
		}
	}

	Node *C = new Node(k, v);

	C->parent = A;
	C->left = nil;
	C->right = nil;
	
	if(A == nil) {
		root = C;
	}
	else if(C->key < A->key) {
		A->left = C;
	}
	else {
		A->right = C;
	}
    num_pairs++;
    C->left = nil;
    C->right = nil;
    C->color = 1;
    RB_InsertFixUp(C);
}

void Dictionary::remove(keyType k){
    if(contains(k) == false){
        throw std::logic_error("Dictionary: remove(): key \""+ k +"\" does not exist");
    }
    else if(current->key == k){
        current = nil;
    }
    Node* z = search(root, k);
    RB_Delete(z);
    num_pairs--;
    delete z;
}

void Dictionary::begin(){
    if(num_pairs != 0){
        current = findMin(this->root);
    }
}

void Dictionary::end(){
    if(num_pairs != 0){
       current = findMax(this->root);
    }
}

void Dictionary::next(){
    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    else{
        current = findNext(current);
    }
}

void Dictionary::prev(){
    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

std::string Dictionary::to_string() const{
    std::string out = "";
    inOrderString(out, this->root);
    return out;
}

std::string Dictionary::pre_string() const{
    std::string pre = "";
    preOrderString(pre, this->root);
    return pre;
}

bool Dictionary::equals(const Dictionary& D) const{
    Dictionary A = *this;
    Dictionary B = D;
    
    A.begin();
    B.begin();
    bool eq = true;
    eq = (B.num_pairs == num_pairs);
    while(eq && A.hasCurrent()){
        if(A.currentKey() != B.currentKey()){
            eq = false;
        }
        if (A.currentVal() != B.currentVal()){
            eq = false;
        }
        B.next();
        A.next();
    }
    return (eq);
    /*    bool eq = true;
    eq = (this->num_pairs == D.num_pairs);
    if(eq){
        eq = (this->pre_string() == D.pre_string());
    }
    if(eq){
        eq = (this->to_string() == D.to_string());
    }
    return (eq);*/
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D){
    return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D){
   if(this != &D){
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
   }
   return *this;
}
