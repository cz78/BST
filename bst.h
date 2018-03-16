#include "cmpt_error.h"
#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Your task for this assignment is to implement all of the methods of the BST
// class given below, subject to a few important constraints.
//
// Here are the things your implementation **cannot** do:
//
// - You **cannot** use recursion anywhere in any of the methods you write.
//   All the methods must be implemented iteratively, i.e. using loops.
//
// - You **cannot** add new variables to the BST class, public or private. You
//   cannot add any global variables.
//
// - You **cannot** #include any other files. If you borrow code or ideas from
//   any other source, be sure to cite the source (e.g. as a comment in your
//   code).
//
// - You **cannot** use arrays or vectors or any other pre-made data
//   structure. As mentioned below, you may only use data structures that you
//   implement yourself.
//
// Here are the things your implementation **can** do:
//
// - You **can** add helper methods, either public or private, to BST. You may
//   also add helper functions outside of BST. Of course, any extra
//   methods/functions you add must follow the "cannot" rules above.
//
// - You **can** add helper classes, either in BST or outside of BST. For
//   instance, you could implement your own stack class.
//
// Put all the code necessary to implement BST correct inside a3.h, and then
// submit just this file when you are done. Put your testing code in a3.cpp.
//
// In the specification of the methods for BST, these variables are used:
//
// - n is the number of nodes in the BST
// - h is the height of the BST
// - T refers to the tree immediately before a method is called
// - T' refers to the tree immediately after the method is finished
//
///////////////////////////////////////////////////////////////////////////////


class BST {
private:
    struct Node {
        string value;
        Node* left;
        Node* right;
    };

    Node* head;

public:
    //Helper class called stack with all of its functions
    class Stack
    {
        private:
        struct SL_Node
        {
            Node * BinNode;
            SL_Node * next;
        };
        SL_Node * headS;

        public:
        Stack()
        {
            headS = nullptr;
        }
        ~Stack()
        {
            while(headS != nullptr)
            {
                SL_Node * p = headS->next;
                delete headS;
                headS = p;
            }
        }
        void push(Node * p)
        {
            SL_Node * newNode = new SL_Node{p,nullptr};
            if (headS == nullptr)
            {
                headS = newNode;
            }
            else
            {
                newNode->next = headS;
                headS = newNode;
            }
        }
        Node * pop()
        {
            if (isEmpty())
            {
                cmpt::error("add: Space detected");
                return nullptr;
            }
            else
            {
                SL_Node * p = headS;
                headS = headS->next;
                Node * s = p->BinNode;
                delete p;
                return s;
            }
        }
        Node * top()
        {
            return headS->BinNode;
        }
        int size() const
        {
            int size = 0;
            SL_Node * p = headS;
            while(p != nullptr)
            {
                p = p->next;
                size++;
            }
            return size;
        }
        bool isEmpty()
        {
            if(headS == nullptr)
            {
                 return true;
            }
            return false;
        }
    };
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new empty BST
    // Constraints:
    //    O(1) performance
    BST();

    // Pre-condition:
    //    none
    // Post-condition:
    //    deletes all the nodes in this BST
    // Constraints:
    //    O(n) performance
    ~BST();

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of string in this tree (i.e. n)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    int size() const;

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the height of this tree
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    // Note:
    //    The height of a BST is the number of links in the longest
    //    root-to-leaf path in the tree. An empty tree is height 0,
    //    and a tree with a single node is also height 0.
    int height() const;

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if s is in this tree, and false otherwise
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    bool contains(const string& s) const;

    // Pre-condition:
    //    none
    // Post-condition:
    //    T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is already in T, then insert(s) does nothing.
    void insert(const string& s);

    // Pre-condition:
    //    none
    // Post-condition:
    //    !T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is not in T, then remove(s) does nothing.
    void remove(const string& s);

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in pre-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_preorder() const;

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in in-order order
    //    (i.e. alphabetical order)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_inorder() const;

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in post-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_postorder() const;
}; // class BST


BST::BST()
{
    head = nullptr;
}

BST::~BST()
{
    //If tree is empty, return
    if (head == nullptr)
    {
        return;
    }
    //Make a new stack and a scanner to root
    //push the root to the stack
    Stack newstack;
    Node * scan = head;
    newstack.push(scan);
    while (newstack.isEmpty() == false)
    {
        //pop stack
        scan = newstack.pop();
        //continue travel push the nodes onto the stack
        //push the right node on the stack before the left node
        //in order to print in preorder
        //as stack works in Last In First Out order
        if (scan->right != nullptr)
        {
            newstack.push(scan->right);
        }
        if (scan->left != nullptr)
        {
            newstack.push(scan->left);
        }
        //delete scan after push the left and right node
        delete scan;
    }
}

int BST::size() const
{
    //If tree is empty, return
    if (head == nullptr)
    {
        return 0;
    }
    //Make a new stack and a scanner to root
    //push the root to the stack
    Stack newstack;
    Node * scan = head;
    newstack.push(scan);
    int size = 0;
    while (newstack.isEmpty() == false)
    {
        //pop stack and increment size by 1
        scan = newstack.pop();
        size++;
        //continue travel push the nodes onto the stack
        //push the right node on the stack before the left node
        //in order to print in preorder
        //as stack works in Last In First Out order
        if (scan->right != nullptr)
        {
            newstack.push(scan->right);
        }
        if (scan->left != nullptr)
        {
            newstack.push(scan->left);
        }
    }
    return size;
}

int BST::height() const
{
    //if tree is empty, return 0
    if ((head == nullptr) || (head->left == nullptr && head->right == nullptr)
    {
        return 0;
    }
    //Make a new stack and
    //initialize a pointer to scan the tree
    //Since traveling in preorder traversal
    //Initialize variables to keep track of the number of nodes
    //in current height level
    //and another to reset tracking variable
    //both of these can't be greater than 2
    //because a root can have only up to 2 children
    Stack newstack;
    Node * scan = head;
    newstack.push(scan);
    int height = 0;
    int NodeInStack = 1;
    int NodeCounter = 0;
    while (newstack.isEmpty() == false)
    {
        //pop stack and print the value
        scan = newstack.pop();
        NodeInStack--;
        //continue travel push the nodes onto the stack
        //push the right node on the stack before the left node
        //in order to print in preorder
        //as stack works in Last In First Out order
        //update the counter each time we push a node on to the stack
        if (scan->right != nullptr)
        {
            newstack.push(scan->right);
            NodeCounter++;
        }
        if (scan->left != nullptr)
        {
            newstack.push(scan->left);
            NodeCounter++;
        }
        //If already visited 2 child of a subtree at current height
        //move onto the subtree of the child and update the height
        if (NodeInStack == 0)
        {
            height++;
            NodeInStack = NodeCounter;
            NodeCounter = 0;
        }
    }
    return height;
}

bool BST::contains(const string& s) const
{
    Node * search = head;
    while (search != nullptr)
    {
        if (s.compare(search->value) < 0)
        {
            search = search->left;
        }
        else if (s.compare(search->value) > 0)
        {
            search = search->right;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void BST::insert(const string& s)
{
    //If tree is empty create a new node and make it
    //the root
    if (head == nullptr)
    {
        Node * newNode = new Node;
        newNode->value = s;
        newNode->left = nullptr;
        newNode->right = nullptr;
        head = newNode;
        return;
    }
    Node * search = head;
    //search the tree for insertion point
    while (search != nullptr)
    {
        //If input value less than current node value
        //Check to see if the left of currrent node is null
        //if it is, create a new node and put it there
        //Otherwise travese further left
        if (s.compare(search->value) < 0)
        {
            if (search->left == nullptr)
            {
                Node * newNode = new Node;
                search->left = newNode;
                newNode->value = s;
                newNode->left = nullptr;
                newNode->right = nullptr;
                return;
            }
            search = search->left;
        }
        //If input value bigger than current node value
        //Check to see if the right of currrent node is null
        //if it is, create a new node and put it there
        //Otherwise travese further right
        else if (s.compare(search->value) > 0)
        {
            if (search->right == nullptr)
            {
                Node * newNode = new Node;
                search->right = newNode;
                newNode->value = s;
                newNode->left = nullptr;
                newNode->right = nullptr;
                return;
            }
            search = search->right;
        }
        //If found identical return
        else
        {
            return;
        }
    }
}

void BST::remove(const string& s)
{
    if (head == nullptr)
    {
        return;
    }
    Node * parent = nullptr;
    Node * search = head;
    Node * child;
    Node * newparent;
    Node * swap;
    int movement = 0; // 1 if going left, 0 for right
    while (search != nullptr)
    {
        //If found node then break
        if (s.compare(search->value) == 0)
        {
            break;
        }
        //If target value is less than current
        //value then traverse left
        else if (s.compare(search->value) < 0)
        {
            parent = search;
            movement = 1;
            search = search->left;
        }
        //If target value is greater than current
        //value then traverse right
        else
        {
            parent = search;
            movement = 0;
            search = search->right;
        }
    }
    //If node is not in tree then return
    if (search == nullptr)
    {
        return;
    }
    /*
    Search has found the node that need to be remove
    Three Cases:
    1) It is leaf node
    2) It has one child
    3) It has two children
    */
    // Case 1: search is a leaf
    if ((search->left == nullptr) && (search->right == nullptr))
    {
        // Check to see if the searched node is the root
        if (parent == nullptr)
        {
            delete search;
            head = nullptr;
        }
        else
        {
            delete search;
            //check to see if search is in the left or right
            //in order to reset the parent's link
            if (movement == 1)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }
    }
    else
    {
        // Case 2: search has one child
        if ((search->left == NULL) || (search->right == NULL))
        {
            //check to see where its child is located
            if (search->left != NULL)
            {
                child = search->left;
            }
            else
            {
                child = search->right;
            }
            //if search is the root
            //make the child the new head
            if (parent == nullptr)
            {
                head = child;
                delete search;
            }
            //if search is not the root
            //make the parent of search adopt its child
            else
            {
                if (movement == 1)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }
                delete search;
            }
        }
        // Case 3: search has two children
        // Need to find a replacement for the two children
        // the replacement will be the largest of the left subtree
        else
        {
            newparent = search;
            swap = search->left;
            movement = 1;
            //Search for the largest value of the left subtree
            while (swap->right != nullptr)
            {
                newparent = swap;
                swap = swap->right;
                movement = 0;
            }
            //Update new value to the root
            search->value = swap->value;
            //Two cases to link the 2 nodes
            //1)Replacement is left child of ptr
            //  (and could be having 0 or 1 children)
            if (movement == 1)
            {
                search->left = swap->left;
                delete swap;
            }
            //2)Replacement is right (grand)child of ptr->left
            else
            {
                newparent->right = swap->left;
                delete swap;
            }
        }
    }
}

void BST::print_preorder() const
{
    //If tree is empty, return
    if (head == nullptr)
    {
        return;
    }
    //Make a new stack and a scanner to root
    //push the root to the stack
    Stack newstack;
    Node * scan = head;
    newstack.push(scan);
    while (newstack.isEmpty() == false)
    {
        //pop stack and print the value
        scan = newstack.pop();
        cout << scan->value << " ";
        //continue travel push the nodes onto the stack
        //push the right node on the stack before the left node
        //in order to print in preorder
        //as stack works in Last In First Out order
        if (scan->right != nullptr)
        {
            newstack.push(scan->right);
        }
        if (scan->left != nullptr)
        {
            newstack.push(scan->left);
        }
    }
    cout << endl;
}

/*
1. Start from root, let's call it scan.
2. If scan is not NULL, push the node on to stack.
3. Move to left child of scan, scan=scan->left.
  3.1 Go to step 2.
4. If scan is NULL and stack is not empty, pop node from the stack.
5. Print node value
6. Move to right child of scan, scan=scan->right
   6.1 Go to step 2.
*/
void BST::print_inorder() const
{
    //If tree is empty, return;
    if (head == nullptr)
    {
        return;
    }
    //Create a pointer to root and a new stack
    Node * scan = head;
    Stack newstack;
    //While the stack is not empty or scan is not null
    while ((newstack.isEmpty() == false) || (scan != nullptr))
    {
        //if current node is not null then put onto the stack
        //and move left
        if (scan != nullptr)
        {
            newstack.push(scan);
            scan = scan->left;
        }
        //if the current node is null then pop the stack,
        //output the popped node value
        //move right of the popped node
        else
        {
            scan = newstack.pop();
            cout << scan->value << " ";
            scan = scan->right;
        }
    }
    cout << endl;
}

void BST::print_postorder() const
{
    //if tree is empty, return
    if (head == nullptr)
    {
        return;
    }
    //Make a new stack and
    //initialize a pointer to scan the tree
    //Make a pointer to keep track of the parent of
    //each node when scanning
    //Make a popping node to receive the node when
    //pop from stack and output answer
    Stack newstack;
    Node * scan = head;
    newstack.push(scan);
    Node * prevscan = head;
    Node * popping = nullptr;
    while (newstack.isEmpty() == false)
    {
        scan = newstack.top();
        //Moving down the tree
        if ((scan == prevscan) || (scan == prevscan->left) || (scan == prevscan->right))
        {
            //Moving down the tree to the left
            if (scan->left != nullptr)
            {
                newstack.push(scan->left);
            }
            //Moving down the tree to the right
            else if (scan->right != nullptr)
            {
                newstack.push(scan->right);
            }
            else
            {
                popping = newstack.pop();
                cout << popping->value << " ";
            }
        }
        //Moving back up the tree from the left child
        else if (scan->left == prevscan)
        {
            //If exist a right node push onto stack
            if (scan->right != nullptr)
            {
                newstack.push(scan->right);
            }
            //else pop stack and print the value
            else
            {
                popping = newstack.pop();
                cout << popping->value << " ";
            }
        }
        //If top of stack is a leaf then pop
        //and print output
        else if (scan->right == prevscan)
        {
            popping = newstack.pop();
            cout << popping->value << " ";
        }
        prevscan = scan;
    }
    cout << endl;
}
