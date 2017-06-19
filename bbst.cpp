#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
 
int te;   //gobal function used in inrange function

struct node {      // Structure created for node, consisting of id, count, color, left child address, right child address and parent address
	int id;
        int count;
	char color;
	node *left;
	node *right;
	node *parent;
};
 
typedef struct node *nod;
struct node empty;
nod empty_pointer = &empty;

nod minimum(nod root) {          //function is used to find out the node with the minimum value
	while (root->left != empty_pointer)
		root = root->left;
	return root;
}
 
nod maximum(nod root) {         // function is used to find out the node with the maximum value
	while (root->right != empty_pointer)
		root = root->right;
	return root;
}
 
nod search(nod root, int k) {     // This function takes root and the values of node to be searches as an argument.
	if (root == empty_pointer || root->id == k)
		return root;      // return root node is the root is null or the node to be searched is root node itself.
	if (k < root->id)
		return search(root->left, k);   // recursive calling of the function search
	else
		return search(root->right, k);
}
 
 
void rotate_left(nod *root, nod x) {   //In order to satisfy the conditions of red black tree, we use rotate_left function. 
	nod y = x->right;
	x->right = y->left;
	if (y->left != empty_pointer)   // Rotating the node, taking its parent as a center point and rotating it towards left side
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == empty_pointer)
		*root = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;                // making the node as a parent now
	x->parent = y;              // Previous parent is now the right child of the new parent
}
 
void rotate_right(nod *root, nod y) {    //In order to satisfy the conditions of red black tree, we use rotate_right function.
	nod x = y->left;
	y->left = x->right;
	if (x->right != empty_pointer)    // Rotating the node, taking its parent as a center point and rotating it towards right side
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == empty_pointer)
		*root = x;
	else if (y->parent->left == y)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;              // making the node as a parent now
	y->parent = x;              // Previous parent is now the left child of the new parent
}
 
void insert_fix(nod *root, nod z) {                  // after inserting each node, we have to check whether the tree is satisfying the conditions of red black tree.
	while (z->parent->color == 'r') {
		if (z->parent == z->parent->parent->left) {
			nod y = z->parent->parent->right;
			if (y->color == 'r') {
				z->parent->color = 'b';
				y->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					rotate_left(root,z);
				}
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rotate_right(root,z->parent->parent);
			}
		}
		else {                                   // both the child of a red node is black
			nod y = z->parent->parent->left;
			if (y->color == 'r') {
				z->parent->color = 'b';
				y->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rotate_right(root,z);
				}
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rotate_left(root,z->parent->parent);
			}
		}
	}
	(*root)->color = 'b';  // root node is always black
}
 
void insert_tree(nod *root, char *s) {     // taking root node and file name as an argument
        int n1,i;
	int n=0,j=0;
	int n3;
	ifstream myfile;         // using ifstream function for file handling
	myfile.open(s);           // s is the name of the file
	if(myfile.is_open())
	{
	   while(myfile >> n1)
	   {
	     if(n == 0)
	     {
	       n3=n1;    // n3 is the number of the input in the input file
	       n++;
	    }
	    else
	    {
	      for(i=0; i<n3; i++)     // keep inserting the node till n3 nodes are inserted into the red black
	      {
		    nod Z = (nod) malloc(sizeof(struct node));
	Z->id = n1;
	myfile >> n1;
	Z->count = n1;
	myfile >> n1;
	nod y = empty_pointer;
	nod x = *root;
	while (x != empty_pointer) {
		y = x;
		if (Z->id < x->id)
			x = x->left;
		else
			x = x->right;
	}
	Z->parent = y;
	if (y == empty_pointer)
		*root = Z;
	else if (Z->id < y->id)
		y->left = Z;
	else
		y->right = Z;
	Z->left = empty_pointer;    // intially make the left, right and parent pointer of the new node null
	Z->right = empty_pointer;
	Z->color = 'r';
	insert_fix(root,Z);   // after the insertion, new node should satify the conditions of the red black tree.
	      }
	    }
	  }
	}
	
}
 
void tree_transplant(nod *root, nod u, nod v) {   // after deletion, this function is used to fix the broken links between the nodes 
	if (u->parent == empty_pointer)
		*root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}
 
void delete_fix(nod *root, nod x) {         // after deletion of a node, we have to check whether the tree is satisfying the conditions of red black tree.
	while (x != *root && x->color == 'b') {
		if (x == x->parent->left) {
			nod w = x->parent->right;
			if (w->color == 'r') {
				w->color = 'b';
				x->parent->color = 'r';
				rotate_left(root,x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				x = x->parent;
			}
			else {
			 	if (w->right->color == 'b') {
					w->left->color = 'b';
					w->color = 'r';
					rotate_right(root,w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->right->color = 'b';
				rotate_left(root,x->parent);
				x = *root;
			}
		}
		else {
			nod w = x->parent->left;
			if (w->color == 'r') {
				w->color = 'b';
				x->parent->color = 'r';
				rotate_right(root,x->parent);
				w = x->parent->left;
			}
			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				x = x->parent;
			}
			else {
				if (w->left->color == 'b') {
					w->right->color = 'b';
					w->color = 'r';
					rotate_left(root,w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->left->color = 'b';
				rotate_right(root,x->parent);
				x = *root;
			}
		}
	}
	x->color = 'b';
}
 
void delete_tree(nod *root, int z) { // takes root node and value of the node to be deleted as an argument
	nod Z = search(*root, z); // returns the node with id equal to z
	if (Z == empty_pointer) {
		return;
	}
	nod y = Z;
	char yoc = y->color;
	nod x;
	if (Z->left == empty_pointer) {
		x = Z->right;
		tree_transplant(root,Z,Z->right);
	}
	else if (Z->right == empty_pointer) {
		x = Z->left;
		tree_transplant(root,Z,Z->left);
	}
	else {
		y = minimum(Z->right);         // returns the node with the minimum value
		yoc = y->color;
		x = y->right;
		if (y->parent == Z)
			x->parent = y;
		else {
			tree_transplant(root,y,y->right);
			y->right = Z->right;
			y->right->parent = y;
		}
		tree_transplant(root,Z,y);
		y->left = Z->left;
		y->left->parent = y;
		y->color = Z->color;
	}
	if (yoc == 'b')
		delete_fix(root,x); // in order to check and correct all the conditions of red black tree, we use delete_fix function
}
 
nod quick_add(nod *root, int i, int c)     // use this function with increase function
{
        nod Z = (nod) malloc(sizeof(struct node));
	Z->id = i;
	Z->count = c;
	nod y = empty_pointer;
	nod x = *root;
	while (x != empty_pointer) {
		y = x;
		if (Z->id < x->id)
			x = x->left;
		else
			x = x->right;
	}
	Z->parent = y;
	if (y == empty_pointer)
		*root = Z;
	else if (Z->id < y->id)
		y->left = Z;
	else
		y->right = Z;
	Z->left = empty_pointer;
	Z->right = empty_pointer;
	Z->color = 'r';
	insert_fix(root,Z);         // in order to check and correct all the conditions of red black tree, we use insert_fix function
	return Z;
}
  
 
 
void increase(nod *root, int i, int c)
{
      nod Z = search(*root, i);     // return the node with id value equal to i
      if(Z == empty_pointer)
      {
	Z = quick_add(root, i, c);    // if the node is not present, then add new node
	cout<<Z->count<<endl;
      }
      else
      {
	Z->count = Z->count + c;         // increase th count of the node by value c
	cout<<Z->count<<endl;
      }
} 
 
 
void reduce(nod *root, int i, int c)
{
      nod Z = search(*root, i);      // return the node with id value equal to i
      if(Z == empty_pointer)
      {
	cout<<"0"<<endl;            // print "0" if node is not present or removed
      }
      else
      {
	Z->count = Z->count - c;     // reduce the value of the node by c
	if(Z->count <= 0)
	{ 
	  cout<<"0"<<endl;
	  delete_tree(root, i);      // if the value of count becomes equal to or less than zero, then delete that node from the tree
	}
	else
	{
	  cout<<Z->count<<endl;
	}
      }
}
 
void count(nod *root, int i)
{
      nod Z = search(*root, i);     // return the node with id value equal to i
      if(Z == empty_pointer)
      {
	cout<<"0"<<endl;        // print "0" if node is not present or removed
      }
      else
      {
	  cout<<Z->count<<endl;    // print the count of the node
      }
}


void inrange(nod root, int i, int c)
{
  if(root == empty_pointer)
    return;
  if(root->id >= i && root->id <= c)
    te = te + root->count;         // call the function recursively and add the count value of each node to the global variable that satisfies the condition
  inrange(root->left, i, c);
  inrange(root->right, i, c);
}
 
 
nod next(nod root, int i)
{
        nod temp = search(root, i);      // return the node with id value equal to i
	if (temp == empty_pointer) {
		return temp;
	}
	if (temp->right != empty_pointer)
		return minimum(temp->right);
	nod y = temp->parent;
	while (y != empty_pointer && temp == y->right) {
		temp = y;
		y = y->parent;
	}
	return y;          // return the lowest value node greater than node with value i
}
 
 
nod previous(nod root, int i) {
	nod temp = search(root, i);    // return the node with id value equal to i
	if (temp == empty_pointer) {
		return temp;
	}
	if (temp->left != empty_pointer)
		return maximum(temp->left);
	nod y = temp->parent;
	while (y != empty_pointer && temp == y->left) {
		temp = y;
		y = y->parent;
	}
	return y;       // return the highest value node less than the node with value i
}
 
int main(int argc, char *argv[])
{
	empty.left = empty.right = empty.parent = empty_pointer;
	empty.color = 'b';
	nod tree = empty_pointer;
	int n,i,c,j=0;
	string s;                   
	insert_tree(&tree, argv[1]);     // calling the insert function ; passing the name of the input file
	te = 0;
	while(j == 0)   // comparing string and calling each functions 
	{
	     
	cin >> s;
	     if(s == "increase")
            {
                cin >> i;
                cin >> c;
                increase(&tree, i, c);
           }
    
          else if(s == "reduce")
           {
                cin >> i;
                cin >> c;
                reduce(&tree, i, c);
           }
    
          else if(s == "count")
           {
                cin >> i;
                count(&tree, i);
           }
    
          else if(s == "inrange")
           {
                cin >> i;
                cin >> c;
                inrange(tree, i, c);
                cout<<te<<endl;
                te=0;
            }
    
          else if(s == "next")
           {
               cin >> i;
               nod t = search(tree, i);
	       if(t == empty_pointer)
	       {
		 t = quick_add(&tree, i ,7);
		 t = next(tree, i);
		 cout<<t->id<<" "<<t->count<<endl;
		 delete_tree(&tree, i);
		 
	      }
	      else
	      {
		   nod t = next(tree, i);
		   cout<<t->id<<" "<<t->count<<endl;
	      }
           }
    
          else if(s == "previous")
           {
               cin >> i;
               nod t = search(tree, i);
	       if(t == empty_pointer)
	       {
		 t = quick_add(&tree, i ,7);
		 t = previous(tree, i);
		 cout<<t->id<<" "<<t->count<<endl;
		 delete_tree(&tree, i);
		 
	      }
	      else
	      {
		   nod t = previous(tree, i);
		   cout<<t->id<<" "<<t->count<<endl;
	      }
           }
    
    
          else if(s == "quit")
          { 
	     j++;
             break;
           }
	}
	
	
	return 0;
}
