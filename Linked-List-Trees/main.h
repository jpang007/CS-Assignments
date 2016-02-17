#ifndef ASSN4_H
#define ASSN4_H

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>   

using namespace std;

 
class Fraction
{
    int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
    int n, d;
 public:
    Fraction() {
      n = 0;
      d = 0;
    }
    Fraction(int n, int d = 1) : n(n/gcd(n,d)), d(d/gcd(n,d)) {}
    int num() const { return n; }
    int den() const { return d; }
    Fraction& operator*=(const Fraction& rhs) {
        int new_n = n*rhs.n / gcd(n*rhs.n, d*rhs.d);
        d = d*rhs.d / gcd(n*rhs.n, d*rhs.d);
        n = new_n;
        return *this;
    }
};
ostream& operator<<(std::ostream& out, const Fraction& f){
   return out << f.num() << '/' << f.den() ;
}
bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return ((lhs.num() * rhs.den()) == (rhs.num() * lhs.den()));
}
bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() < rhs.num() * lhs.den());
}
bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() > rhs.num() * lhs.den());
}
Fraction operator*(Fraction lhs, const Fraction& rhs)
{
    return lhs *= rhs;
}

struct node
{
  int key_value;
  Fraction nodeit;
  node *left;
  node *right;

};

class obtree
{
    public:
        obtree() {
          root = NULL;
        }
        ~obtree() {
            destroy_tree();
        }
        obtree(list<Fraction> a);
        void insertf(list<Fraction>::iterator a) {
          if (root != NULL) {
            insertf(a, root);
          }
          else {
            root = new node;
            root->nodeit = *a;
            root->left = NULL;
            root->right = NULL;
          }
        }
        void insert(int value) {
            if (root != NULL) {
                insert(value, root);
            }
            else {
                root = new node;
                root->key_value=value;
                root->left=NULL;
                root->right=NULL;
            }
        }
        void destroy_tree() {
          destroy_tree(root);
        }
        void print_postorder() {
          print_postorder(root);
        }
        void print_postorderf() {
          print_postorderf(root);
        }
        void print_inorderf() {
          print_inorderf(root);
        } 
        void print_inorder() {
          print_inorder(root);
        }
        void sortf(list<Fraction> &a) {
          sortf(a,root);
        }
        
    private:
        void destroy_tree(node *leaf) {
          if(leaf!=NULL) {
            destroy_tree(leaf->left);
            destroy_tree(leaf->right);
            delete leaf;
            }
          }
        void insertf(list<Fraction>::iterator a, node *leaf) {
          srand(time(NULL));
          if (*a < leaf->nodeit) {
                if (leaf->left != NULL) {
                    insertf(a, leaf->left);
                }
                else {
                    leaf->left = new node; 
                    leaf->left->nodeit = *a;
                    leaf->left->left = NULL;
                    leaf->left->right = NULL;
                }
            }
            else if (*a > leaf->nodeit) {
                if (leaf->right != NULL) {
                    insertf(a, leaf->right);
                }
                else {
                    leaf->right = new node;
                    leaf->right->nodeit = *a;
                    leaf->right->left = NULL;
                    leaf->right->right = NULL;
                }
            }
            else if(*a == leaf->nodeit) {
                if (rand() < RAND_MAX/2) {
                    if (leaf->left != NULL) {
                    insertf(a, leaf->left);
                }
                else {
                    leaf->left = new node; 
                    leaf->left->nodeit= *a;
                    leaf->left->left = NULL;
                    leaf->left->right = NULL;
                }
                }
                else {
                    if (leaf->right != NULL) {
                    insertf(a, leaf->right);
                }
                else {
                    leaf->right = new node;
                    leaf->right->nodeit = *a;
                    leaf->right->left = NULL;
                    leaf->right->right = NULL;
                }
                }
            }
        }
        void insert(int value, node *leaf) {
            srand(time(NULL));
            if (value < leaf->key_value) {
                if (leaf->left != NULL) {
                    insert(value, leaf->left);
                }
                else {
                    leaf->left = new node; 
                    leaf->left->key_value = value;
                    leaf->left->left = NULL;
                    leaf->left->right = NULL;
                }
            }
            else if (value > leaf->key_value) {
                if (leaf->right != NULL) {
                    insert(value, leaf->right);
                }
                else {
                    leaf->right = new node;
                    leaf->right->key_value = value;
                    leaf->right->left = NULL;
                    leaf->right->right = NULL;
                }
            }
            else if(value == leaf->key_value) {
                if (rand() < RAND_MAX/2) {
                    if (leaf->left != NULL) {
                    insert(value, leaf->left);
                }
                else {
                    leaf->left = new node; 
                    leaf->left->key_value = value;
                    leaf->left->left = NULL;
                    leaf->left->right = NULL;
                }
                }
            else {
                if (leaf->right != NULL) {
                  insert(value, leaf->right);
                }
                else {
                    leaf->right = new node;
                    leaf->right->key_value = value;
                    leaf->right->left = NULL;
                    leaf->right->right = NULL;
                }
                }
            }
        }
        void print_postorder(node *leaf) {
          if (leaf != NULL) {
            if (leaf->left) print_postorder(leaf->left);
            if(leaf->right) print_postorder(leaf->right);
            cout << " " << leaf->key_value << " ";
          }
          else {
            return;
          }
          
        }
        void print_postorderf(node *leaf) {
          if (leaf != NULL) {
            if (leaf->left) print_postorderf(leaf->left);
            if(leaf->right) print_postorderf(leaf->right);
            cout << " " << leaf->nodeit << " ";
          }
          else {
            return;
          }
        }
        void print_inorder(node *leaf) {
          if(leaf != NULL) {
        		if(leaf->left) print_inorder(leaf->left);
        		cout<<" "<<leaf->key_value<<" ";
        		if(leaf->right) print_inorder(leaf->right);
	        }
	       else return;
        }
        void print_inorderf(node *leaf) {
          if(leaf != NULL) {
        		if(leaf->left) print_inorderf(leaf->left);
        		cout<<" "<<leaf->nodeit<<" ";
        		if(leaf->right) print_inorderf(leaf->right);
	        }
	       else return;
        }
        void sortf(list<Fraction> &a, node *leaf){ 
	    list<Fraction>::iterator itr = a.begin();
	    if(leaf-> left != 0){
		    sortf(a, leaf->left);	
		}
	    a.push_back((leaf->nodeit));
	    if(leaf-> right != 0){
		    sortf(a, leaf->right);	
	    }
                    
        }
        
        
        node *root;
};


#endif
