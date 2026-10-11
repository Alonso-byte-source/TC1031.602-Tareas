#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>
#include <queue>
#include <algorithm>

template <class T> class BST;

template <class T>
class Node{
    private: 
        T value;
        Node *left, *right;
        Node<T>* predecesor();
    public:
        Node(T);
        Node(T, Node<T>*, Node<T>*);
        bool find(T);
        void add(T);
        void preOrder(std::stringstream&) const;
        void inOrder(std::stringstream&) const;
        void postOrder(std::stringstream&) const; 
        void levelOrder(std::stringstream&) const;
        void ancestors(std::stringstream&, T&) const; 
        int height() const;
        int whatlevelamI(T) const;
        void removeChilds();
        friend class BST<T>;
};

template <class T>
Node<T>::Node(T val): value(val), left(0), right(0){}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri): value(val), left(le), right(ri) {} 

template <class T>
bool Node<T>::find(T val){
    if(val == value){
        return true;
    } else if(val < value){
        return(left != 0 && left->find(val));
    } else if(val > value){
        return(right != 0 && right->find(val));
    }
    return false;
}

template <class T>
void Node<T>::ancestors(std::stringstream &aux, T &val) const{
    if(val == value){
        return;
    } else if(val < value){
        aux << value << " ";
        return(left->ancestors(aux, val));
    } else if(val > value){
        aux << value << " ";
        return(right->ancestors(aux, val));
    }
}

template <class T>
void Node<T>::add(T val){
    if(val < value){
        if(left != 0){
            left->add(val);
        } else{
            left = new Node<T>(val);
        }
    } else{
        if(right != 0){
            right->add(val);
        } else{
            right = new Node<T>(val);
        }
    }
}

template <class T>
void Node<T>::preOrder(std::stringstream &aux) const{
    aux << value;
    if(left != 0){
        aux << " ";
        left->preOrder(aux);
    }
    if(right != 0){
        aux << " ";
        right->preOrder(aux);
    }
}

template <class T>
void Node<T>::inOrder(std::stringstream &aux) const{
    if(left != 0){
        left->inOrder(aux);
        aux << " ";
    }
    
    aux << value;
	
    if(right != 0){
        aux << " ";
        right->inOrder(aux);   
    }
}

template <class T>
void Node<T>::postOrder(std::stringstream &aux) const{
    if(left != 0){
        left->postOrder(aux);
        aux << " ";
    }
    if(right != 0){        
        right->postOrder(aux);
        aux << " ";
    }
    aux << value;
}

template <class T>
void Node<T>::levelOrder(std::stringstream &aux) const{
    std::queue<const Node<T>*> q;
    q.push(this);

    while(!q.empty()){
        const Node<T>* current = q.front();
        q.pop();

        aux << current->value;
        if(current->left != 0){
            q.push(current->left);
        }

        if(current->right != 0){
            q.push(current->right);
        }

        if(!q.empty()){
            aux << " ";
        }
    }
}

template <class T>
int Node<T>::height() const{
    if(right == 0 && left == 0) return 1;

    int h_left = 0; 
    int h_right = 0;

    if(left != 0){
        h_left = left->height();
    }

    if(right != 0){
        h_right = right->height();
    }

    return std::max(h_left, h_right) + 1;
}

template <class T>
int Node<T>::whatlevelamI(T val) const{
    int level = 0;
    if(val == value){
         return 1;
    } else if(val < value){
        return 1 + left->whatlevelamI(val);
    } else{
        return 1 + right->whatlevelamI(val);
    }
}

template <class T>
void Node<T>::removeChilds(){
    if(left != 0){
        left->removeChilds();
        delete left;
        left = 0;
    }
    if(right != 0){
        right->removeChilds();
        delete right;
        right = 0;
    }
}

template <class T>
class BST{
    private: 
        Node<T> *root;
    public:
        BST();
        ~BST();
        bool empty() const;
        bool find(T) const;
        void add(T);
        std::string visit() const;
        int height() const;
        std::string ancestors(T) const;
        int whatlevelamI(T) const;
        void removeAll();
};

template <class T>
BST<T>::BST(): root(0) {}

template <class T>
BST<T>::~BST<T>(){
    removeAll();
}

template <class T>
bool BST<T>::empty() const{
    return(root == 0);
}

template <class T>
bool BST<T>::find(T val) const{
    if(root != 0){
        return root->find(val);
    } else{
        return false;
    }
} 

template <class T>
void BST<T>::add(T val){
    if(root != 0){
        if(!root->find(val)){
            root->add(val);
        }
    } else{
        root = new Node<T>(val);
    }
}

template <class T>
std::string BST<T>::visit() const{
    std::stringstream aux;
    
    if(!empty()){
        aux << "[";
        root->preOrder(aux);
        aux << "]" << "\n";
    
        aux << "[";
        root->inOrder(aux);
        aux << "]" << "\n";

        aux << "[";
        root->postOrder(aux);
        aux << "]" << "\n";

        aux << "[";
        root->levelOrder(aux);
        aux << "]";
    }
    
    return aux.str();
}

template <class T>
int BST<T>::height() const{
    if(empty()) return -1;
    return root->height();
}

template <class T>
std::string BST<T>::ancestors(T val) const{
    std::stringstream aux;
    aux << "[";
    if(find(val)){
        root->ancestors(aux, val);
        std::string str = aux.str();
        str.pop_back();
        aux.str("");
        aux.clear();
        aux << str;
    }
    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const{
    if(find(val)){
        return root->whatlevelamI(val);
    }
    return -1;
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

#endif