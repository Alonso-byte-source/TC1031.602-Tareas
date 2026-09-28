#ifndef LIST
#define LIST
#include <string>
#include <sstream>
#include <iostream>

template <class T> class List;

template <class T>
class Link{
    private:
        Link(T);
        Link(T, Link<T>*);
        T value;
        Link<T> *next;

        friend class List<T>;
};

template <class T>
Link<T>::Link(T val): value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt): value(val), next(nxt) {}

template <class T>
class List{
    public: 
        List();
        List(const List<T>&);
        ~List();

        void insertion(T);
        void insertionFirst(T);
        int search(T);
        void update(int, T);
        void deleteAt(int);
        void deleteAtFirst();
        void clear();
        bool empty() const;
        std::string toString() const;

    private:
        Link<T> *head;
        int size;
};

template <class T>
List<T>::List(): head(0), size(0) {}

template <class T>
List<T>::~List(){
    clear();
}

template <class T>
bool List<T>::empty() const{
    return(head == 0);
}


template <class T>
void List<T>::insertionFirst(T val){
    Link<T> *newLink;
    newLink = new Link<T>(val);
    newLink->next = head;
    head = newLink;
    size++;
}

template <class T>
void List<T>::insertion(T val){
    if(empty()){
        insertionFirst(val);
        return;
    }
    Link<T> *p, *newLink;
    newLink = new Link<T>(val);
    p = head;

    while(p->next != 0){
        p = p->next;
    }

    newLink->next = 0;
    p->next = newLink;
    size++;
}

template <class T>
int List<T>::search(T val){
    if(empty()) return -1;
    
    Link<T> *p;
    p = head;
    int it = 0;
    
    while(p != 0){
        if(p->value == val) return it;
        it++;
        p = p->next;
    }
    
    return -1;
}

template <class T>
void List<T>::update(int it, T val){
    Link<T> *p;
    p = head;
    int i = 0;
    while(p != 0){
        if(it == i){
            p->value = val;
            break;
        }
        p = p->next;
        i++;
    }
}

template <class T>
void List<T>::deleteAtFirst(){
    if(empty()) return;

    Link<T> *p = head;
    head = p->next;
    delete p;
    size--;
}

template <class T>
void List<T>::deleteAt(int it){
    if(it == 0){
        deleteAtFirst();
        return;
    }
    
    Link<T> *p, *q;
    p = head;
    int i = 0;
    while(p->next != 0){
        if(it == i+1){
            q = p->next;
            p->next = p->next->next;
            q->next = 0;
            delete q;
            size--;
            return;
        }
        i++;
        p = p->next;
    }
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

#endif