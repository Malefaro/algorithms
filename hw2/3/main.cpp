#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class T>
class IsLess
{
public:
    bool operator() ( const T& o1, const T& o2)
    { return o1 < o2; }
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
        ~Node(){} //{delete left; delete right;}
        T val;
        Node* left;
        Node* right;


    };

public:
    BinaryTree():root(nullptr) {}
    explicit BinaryTree(Node* obj) : root(obj){}
    void Add(T& obj);
    ~BinaryTree() {
        queue<Node*> tmp;
        if(root != nullptr) {
            tmp.push(root);
        }

        while(!tmp.empty()) {
            Node *cur = tmp.front();
            if(cur->left != nullptr) {
                tmp.push(cur->left);
            }
            if(cur->right != nullptr) {
                tmp.push(cur->right);
            }

            delete cur;
            tmp.pop();
        }
    }
    long Width(Node *root);
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
long BinaryTree<T,Comparator>::Width(BinaryTree::Node *root)
{
    vector<Node*> v1;
    vector<Node*> v2;
    v1.push_back(root);
    long max_width = 0;
    while ( !v1.empty() ){
        for (auto const& obj : v1){
            if ( obj->left )
                v2.push_back(obj->left);
            if ( obj->right)
                v2.push_back(obj->right);
        }
        if ( !v2.empty() ) {
            v1.clear();
            v1 = v2;
            v2.clear();
            if ( v1.size() > max_width )
                max_width = v1.size();
        }
        else
            return max_width;
    }
};


template <class T, class P, class CompT = IsLess<T>, class CompP = IsLess<P>>
class Treap
{
    class Node
    {
    public:
        Node() : val( T() ),priority( P() ), left(nullptr), right(nullptr){}
        Node(T& obj, P& pri):val (obj),priority(pri), left(nullptr), right(nullptr){}
        Node(T& obj,P& pri,Node* l, Node* r):val (obj),priority(pri), left(l), right(r){}
        ~Node(){} //{delete left; delete right;}
        T val;
        P priority;
        Node* left;
        Node* right;
    };
    CompT cmpT;
    CompP cmpP;
    void Split(Node* root, T& key, Node*& left, Node*& right);
public:
    Treap():root(nullptr) {}
    ~Treap() {
        queue<Node*> tmp;
        if(root != nullptr) {
            tmp.push(root);
        }

        while(!tmp.empty()) {
            Node *cur = tmp.front();
            if(cur->left != nullptr) {
                tmp.push(cur->left);
            }
            if(cur->right != nullptr) {
                tmp.push(cur->right);
            }

            delete cur;
            tmp.pop();
        }
    }
    explicit Treap(Node* obj) : root(obj) {}
    void Add(T& obj, P& pri);
    long Width(Node *root);
    Node* root;

};

template <class T, class P, class CompT, class CompP>
void Treap<T,P,CompT,CompP>::Add(T &obj, P &pri)
{
    if (root == nullptr){
        root = new Node(obj,pri);
        return;
    }
    Node* ptr = root;
    Node* prev =nullptr;
    while(1)
    {
        if (cmpP(ptr->priority, pri)){
            Node* left;
            Node* right;
            Split(ptr,obj,left,right);
            Node* tmp = new Node(obj,pri,left,right);
            if(ptr == root){
                root = tmp;
                return;
            }
            if ( !cmpT(tmp->val, prev->val) )
                prev->right = tmp;
            else
                prev->left = tmp;
            return;
        }

        if( !cmpT(obj, ptr->val)){
            if (ptr->right == nullptr){
                Node* tmp = new Node(obj,pri);
                ptr->right = tmp;
                return;
            }
            prev = ptr;
            ptr = ptr->right;
        } else {
            if (ptr->left == nullptr){
                Node* tmp = new Node(obj,pri);
                ptr->left = tmp;
                return;
            }
            prev = ptr;
            ptr = ptr->left;
        }
    }
}



template <class T, class P, class CompT, class CompP>
long Treap<T,P,CompT,CompP>::Width(Treap::Node *root) {
    vector<Node*> v1;
    vector<Node*> v2;
    v1.push_back(root);
    long max_width = 0;
    while ( !v1.empty() ){
        for (auto const& obj : v1){
            if ( obj->left )
                v2.push_back(obj->left);
            if ( obj->right)
                v2.push_back(obj->right);
//            if ( !obj->left && !obj->right )

        }
        if ( !v2.empty() ) {
            v1.clear();
            v1 = v2;
            v2.clear();
            if ( v1.size() > max_width )
                max_width = v1.size();
        }
        else
            return max_width;
    }
}

template <class T, class P, class CompT, class CompP>
void Treap<T,P,CompT,CompP>::Split(Treap::Node *root, T &key, Treap::Node *&left, Treap::Node *&right) {

    {
        if( root == nullptr ) {
            left = nullptr;
            right = nullptr;
        } else if( root->val <= key ) {
            Split( root->right, key, root->right, right );
            left = root;
        } else {
            Split( root->left, key, left, root->left );
            right = root;
        }
    }
}

int main() {
//    int n = 0;
//    cin >> n;
//    BinaryTree<int> tree;
//    for (int i = 0; i < n; ++i){
//        int obj = 0;
//        cin >> obj;
//        tree.Add(obj);
//    }
//    cout << tree.Width(tree.root);
    Treap<int,int> t1;
    BinaryTree<int> t2;
    int n =0;
    cin >> n;
    for (int i = 0; i < n; ++i){
        int x = 0;
        int y = 0;
        cin >> x >> y;
        t1.Add(x,y);
        t2.Add(x);
    }
    //cout << t1.Width(t1.root) << endl;
    cout << t1.Width(t1.root) - t2.Width(t2.root) << endl;
    return 0;
}