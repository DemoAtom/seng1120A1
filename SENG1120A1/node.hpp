/*
* Node.hpp
* Written by : SENG1120 Staff (c1234567)
* Modified by  : Oskar Peters C3437787
*
* This class represents the template implementation for a Node class.
* This file should be used in conjunction with Assignment 1 for SENG1120.
*/ 

template <typename T>
Node<T>::Node() 
{ 
    next = nullptr;
    prev = nullptr;
}

template <typename T>
Node<T>::Node(const T& new_data)
{ 
    data = new_data;
    next = nullptr;
    prev = nullptr;
}


template <typename T>
Node<T>::~Node() 
{

}

// ---- Mutators --------
template <typename T>
void Node<T>::set_data(T& new_data) //setting data of current node
{
    data = new_data;
}


template <typename T>
void Node<T>::set_next(Node<T>* const new_next) //seting pointer to next node
{
    next = new_next;
}


template <typename T>
void Node<T>::set_prev(Node<T>* const new_prev) //setting pointer to previous node
{
    prev = new_prev;
}


// ---- Accessors -------- retrieving data
template <typename T>
Node<T>* Node<T>::get_next() 
{
    return next;
}


template <typename T>
Node<T>* Node<T>::get_prev() 
{
    return prev;
}


template <typename T>
T& Node<T>::get_data() 
{
    return data;
}


template <typename T>
const Node<T>* Node<T>::get_next() const 
{
    return next;
}


template <typename T>
const Node<T>* Node<T>::get_prev() const 
{
    return prev;
}


template <typename T>
const T& Node<T>::get_data() const 
{
    return data;
}