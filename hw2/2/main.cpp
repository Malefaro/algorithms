#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <class T>
class IsLess
{
public:
    bool operator() ( const T& o1, const T& o2)
    { return o1 <= o2; }
};

template<class T = int, class Comparator = IsLess<T>>
class BinaryTree
{
private:
    class Node
    {
    public:
        Node() : val( T() ), left(nullptr), right(nullptr){}
        Node(T& obj):val (obj), left(nullptr), right(nullptr){}
        Node(T& obj,Node* l, Node* r):val (obj), left(l), right(r){}
        ~Node() {delete left; delete right;}
        T val;
        Node* left;
        Node* right;

    };

public:
    BinaryTree():root(nullptr) {}
    explicit BinaryTree(Node* obj) : root(obj){}
    ~BinaryTree() {
        queue<Node *> tmp;
        if (root != nullptr) {
            tmp.push(root);
        }

        while (!tmp.empty()) {
            Node *cur = tmp.front();
            if (cur->left != nullptr) {
                tmp.push(cur->left);
            }
            if (cur->right != nullptr) {
                tmp.push(cur->right);
            }

            delete cur;
            tmp.pop();
        }
    }
    void Add(T& obj);
    void pre_order_print(Node* root);
    Node* root;
    Comparator cmp;
};


template<class T, class Comparator>
void BinaryTree<T,Comparator>::Add(T &obj) {
    if (root == nullptr){
        root = new Node(obj);
        return;
    }
    Node* ptr = root;
    while(1){
        if ( !cmp(obj, ptr->val) ){

            if(ptr->right == nullptr){
                Node* tmp = new Node(obj);
                ptr->right = tmp;
                return;
            }
            ptr = ptr->right;

        }
        else {

            if(ptr->left == nullptr){
                Node* tmp = new Node(obj);
                ptr->left = tmp;
                return;
            }
            ptr = ptr->left;

        }
    }
}




template<class T, class Comparator>
void BinaryTree<T,Comparator>::pre_order_print(BinaryTree::Node *root) {
    if (!root) return;

    stack<Node *> s;
//    stack<Node *> s2;
    s.push(root);

    while (!s.empty()) {
        Node * tmp = s.top();
        s.pop();
        //s2.push(tmp);
        cout << tmp->val << ' ';
        if (tmp->right != nullptr)
            s.push(tmp->right);
        if (tmp->left != nullptr)
            s.push(tmp->left);
    }

//    while (!s2.empty()) {
//        cout <<  s2.top()->val << " ";
//        s2.pop();
//    }
}

int main() {
    int n = 0;
    cin >> n;
    BinaryTree<int> tree;
    for (int i = 0; i < n; ++i){
        int obj = 0;
        cin >> obj;
        tree.Add(obj);
    }
    tree.pre_order_print(tree.root);
    return 0;
}