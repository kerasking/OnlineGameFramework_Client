//
//  CircleQueue.hpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/9/25.
//
//

#ifndef __Circularqueue_hpp__
#define __Circularqueue_hpp__

#include <cassert>

template <typename T>
class Node {
public:
    Node()
    : _next(nullptr)
    , _last(nullptr) {
        
    }
    
    inline const T& data() {
        return _data;
    }
    
    inline Node<T>* next() {
        return _next;
    }
    
    inline Node<T>* last() {
        return _last;
    }
    
    inline void set_data(const T& data) {
        _data = data;
    }
    
    void set_next(Node* next) {
        this->_next = next;
        next->_last = this;
    }
    
    void set_last(Node* last) {
        this->_last = last;
        last->_next = this;
    }
    
private:
    T _data;
    
    Node<T>* _next;
    Node<T>* _last;
};


template <typename T>
class Circularqueue {
public:
    Circularqueue() : Circularqueue(128) {
        
    }
    
    Circularqueue(int cap) {
        assert(cap > 1 && "cap must > 1");
        
        _size = 0;
        _cap = cap;
        
        _head = _rear = new Node<T>();
        
        for(int i = 1; i < cap; i++) {
            auto node = new Node<T>();
            _rear->set_next(node);
            _rear = node;
        }
        _rear->set_next(_head);
        _rear = _head;
    }
    
    ~Circularqueue() {
        auto start = _head;
        auto cur = _head->next();
        
        while(cur != start) {
            delete _head;
            
            _head = cur;
            cur = cur->next();
        }
        delete _head;
    }
    
    bool enqueue(const T& data) {
        if(this->full()) {
            return false;
        }
        
        _rear->set_data(data);
        _rear = _rear->next();
        _size++;
        
        return true;
    }
    
    T dequeue() {
        T data = _head->data();
        
        _head = _head->next();
        _size--;
        
        return data;
    }
    
    const T& front() {
        return _head->data();
    }
    
    inline bool empty() {
        return _size <= 0;
    }
    
    inline bool full() {
        return _size >= _cap;
    }
    
    inline int size() {
        return _size;
    }
    
    void clear() {
        _size = 0;
        _rear = _head;
    }
    
private:
    Node<T>* _head;
    Node<T>* _rear;
    
    int _size;
    int _cap;
};

#endif /* __Circularqueue_hpp__ */
