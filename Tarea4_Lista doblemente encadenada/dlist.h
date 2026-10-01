#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink{
    private:
        DLink(T);
        DLink(T, DLink<T>*, DLink<T>*);
        DLink(const DLink<T>&);
        
        T value;
        DLink<T> *previous;
        DLink<T> *next;

        friend class DList<T>;
        friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val): value(val), previous(0), next(0){}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink *nxt): value(val), previous(prev), next(nxt){} 

template <class T>
DLink<T>::DLink(const DLink<T> &source): value(source.value), previous(source.previous), next(source.next){}

template <class T>
class DList{
    public:
        DList();
        DList(const DList<T>&);
        ~DList();

        void insertionFirst(T);
        void insertion(T);
        int length() const;
        bool empty() const;
        int search(T);
        void update(int, T);
        void deleteAt(int);
        void deleteAtFirst();
        void deleteAtEnd();
        void clear();

        std::string toStringForward() const;
        std::string toStringBackward() const;

    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;
};

template <class T>
DList<T>::DList(): head(0), tail(0), size(0){}

template <class T>
DList<T>::~DList(){
    clear();
}

template <class T>
bool DList<T>::empty() const{
    return(head == 0 && tail == 0);
}

template <class T>
int DList<T>::length() const{
    return size;
}

template <class T>
void DList<T>::insertionFirst(T val){
    DLink<T> *newLink = new DLink<T>(val);
    newLink->next = head;
    head = newLink;
    size++;
}

template <class T>
void DList<T>::insertion(T val){
    DLink<T> *newLink, *temp;
    newLink = new DLink<T>(val);
    if(empty()){
        head = newLink;
        tail = newLink;
    } else{
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
int DList<T>::search(T val){
    DLink<T> *p;
    int i = 0;
    p = head;
    while(p != 0){
        if(p->value == val){
            return i;
        }
        i++;
        p = p->next;
    }
    return -1;
}

template <class T>
void DList<T>::update(int it, T val){
    if(it < 0 || it >= size) return;
    DLink<T> *p;
    int mid = size/2;
    int i;
    if(it <= mid){
        i = 0;
        p = head;
        while(i < it){
            p = p->next;
            i++;
        }
        p->value = val;
    } else{
        p = tail;
        i = size-1;
        while(i > it){
            p = p->previous;
            i--;
        }
        p->value = val;
    }
}

template <class T>
void DList<T>::deleteAtFirst(){
    DLink<T> *p = head;

	if(head == tail){
		head = 0;
		tail = 0;
	} else{
		head = p->next;
		p->next->previous = 0;
	}
	delete p;
	size--;
}

template <class T>
void DList<T>::deleteAtEnd(){
    DLink<T> *p = tail;

    if(head == tail){
		head = 0;
		tail = 0;
	} else{
		tail = p->previous;
		p->previous->next = 0;
	}
    delete p;
    size--;
}


template <class T>
void DList<T>::deleteAt(int it){
    if(empty()){
        return;
    } else if(it == 0){
        deleteAtFirst();
        return;
    } else if(it == size-1){
        deleteAtEnd();
        return;
    }
    
    DLink<T> *p, *q;
    p = head;
    int i = 0;
    while(p->next != 0){
        if(it = i+1){
            q = p->next;
            p->next = p->next->next;
            p->next->previous = p;
            q->next = 0;
            q->previous = 0;
            delete q;
            size--;
            return;
        }
        i++;
        p = p->next;
    }

}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

// Incluye estas funciones en tu dlist.h para poder imprimir tus respuestas
// en formatos compatibles con el main

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

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
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}


#endif