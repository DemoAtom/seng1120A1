/*
* LinkedList.hpp
* Written by : SENG1120 Staff (c1234567)
* Modified by  : Oskar Peters C3437787
*
* This class represents the template implementation for a LinkedList class.
* This file should be used in conjunction with Assignment 1 for SENG1120. */ 


template <typename T>
LinkedList<T>::LinkedList() {

    // Create sentinel nodes for head and tail
    head = new Node<T>();
    tail = new Node<T>();
    
    // Initialise pointers
    head->set_next(tail);
    tail->set_prev(head);

    // Set current pointer to head
    current = head;
    
    // Initialise count to 0
    count = 0;
}


template <typename T>
LinkedList<T>::~LinkedList() 
{
	clear(); // Call clear() to deallocate memory for all nodes
    delete head; // Delete the head sentinel node
    delete tail; // Delete the tail sentinel node
}


template <typename T>
void LinkedList<T>::push_front(const T& data) 
{
    // Create a new node with the provided data
    Node<T>* newNode = new Node<T>(data);

    // Set the new node's pointers
    newNode->set_next(head->get_next()); // Point new node's prev to the current first node
    newNode->set_prev(head);             // Point new node's prev to head

    // Adjust pointers of adjacent nodes
    head->get_next()->set_prev(newNode); // Point the current last node's next to the new node
    head->set_next(newNode);             // Point head next to the new node

    // Increment the count of nodes
    ++count;
}


template <typename T>
void LinkedList<T>::push_back(const T& data) 
{
Node<T>* newNode = new Node<T>(data); //initialises a new node
    if( count == 0 ) //handles the case when the first song is added
    {
        current = newNode;
        current->set_prev(head);
        current->set_next(tail);
        head->set_next(current);
        tail->set_prev(current);

    } else {
        current = tail->get_prev();
        newNode->set_prev(current);
        newNode->set_next(tail);
        current->set_next(newNode);
        tail->set_prev(newNode);
        current = newNode;
    }
    count++;
}


template <typename T>
void LinkedList<T>::insert(const T& data) {

    // Create a new node with the provided data
    Node<T>* newNode = new Node<T>(data);

    // Update pointers to insert newNode before the current node
    newNode->set_prev(current->get_prev());
    newNode->set_next(current);
    current->get_prev()->set_next(newNode);
    current->set_prev(newNode);

    // Update current pointer to point to the newly inserted node
    current = newNode;

    // Increment the count of nodes
    ++count;

}


template <typename T>

T LinkedList<T>::pop_front() {
    try {
        if (head->get_next() == tail) {
            throw std::logic_error("pop_front() called on an empty list.");
        }
        // Get the first node
        Node<T>* firstNode = head->get_next();

        // Get data from the first node
        T data = firstNode->get_data();

        // Update pointers to remove the first node
        head->set_next(firstNode->get_next());
        firstNode->get_next()->set_prev(head);

        // Delete the first node
        delete firstNode;

        // Decrement the count of nodes
        --count;
        delete data;

    } catch (const std::exception& e) {

        std::cerr << "Exception occurred: " << e.what() << std::endl;
        static T default_value; // Default-constructed value for T
        return default_value;
    }
}


template <typename T>
T LinkedList<T>::pop_back() {
    try {
        if (tail->get_prev() == head) {
            throw std::logic_error("pop_back() called on an empty list.");
        }
        // Get the last node
        Node<T>* lastNode = tail->get_prev();

        // Get data from the last node
        T data = lastNode->get_data();

        // Update pointers to remove the last node
        head->set_prev(lastNode->get_prev());
        lastNode->get_prev()->set_next(tail);

        // Delete the last node
        delete lastNode;

        // Decrement the count of nodes
        --count;

        return data;
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        static T default_value; // Default-constructed value for T
        return default_value;
    }
}


template <typename T>
T LinkedList<T>::remove() {
    try {
        if (head->get_next() == tail || current == head || current == tail) {
            throw std::logic_error("remove() called on a sentinel node.");
        }

        // Get the data from the current node
        T data = current->get_data();

        // Update pointers to remove the current node
        current->get_prev()->set_next(current->get_next());
        current->get_next()->set_prev(current->get_prev());

        // declares & stores a pointer to the current node to delete it later
        Node<T>* nodeToRemove = current;

        // Move the current pointer to the next node
        current = current->get_next();

        // Delete the nodeToRemove
        delete nodeToRemove;

        // Decrement the count of nodes
        --count;

        return data;
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        static T default_value; // Default-constructed value for T
        return default_value;
    }
}


template <typename T>
void LinkedList<T>::clear()
{
	while (head->get_next() != tail) //causes deletetion until no non-sentinel nodes remain
    {
        Node<T>* node_to_remove = head->get_next(); // Get the node to remove (node after head)
        head->set_next(node_to_remove->get_next()); // Set head's next pointer to the next node
        node_to_remove->get_next()->set_prev(head); // Set the next node prev pointer to head
        delete node_to_remove;
        --count; // Decrement the count of nodes
    }
}


template <typename T>
T& LinkedList<T>::front() const {
    try {
        if (head->get_next() == tail) {
            throw std::out_of_range("front() called on an empty list.");
        }
        return head->get_next()->get_data(); // Returns data of the first node after the head sentinel node
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return T();
    }
}


template <typename T>
T& LinkedList<T>::back() const {
    try {
        if (head->get_next() == tail) {
            throw std::out_of_range("back() called on an empty list.");
        }
        // Returns data of the node before the tail sentinel node
        return tail->get_prev()->get_data(); 
    } catch (const std::exception& e) {
        static T default_value; 
        std::cerr << "Exception occurred: " << e.what() << std::endl;

        // Returning a reference to the static default value
        return default_value; 
    }
}


template <typename T>
T& LinkedList<T>::get_current() const {
    if (size()==0) {
        throw std::logic_error("get_current() called on an invalid node.");
    } else if (current==nullptr) {
        throw std::logic_error("get_current() called on an sent node.");
    }
    return current->get_data();
    }


template <typename T>
void LinkedList<T>::begin() 
{
	current = head->get_next();
}


template <typename T>
void LinkedList<T>::end() 
{
	current = tail->get_prev();
}


template <typename T>
void LinkedList<T>::forward() 
{	
	// Check if there's a valid next node
    if (current->get_next() != tail) { 
        // Move current pointer forward
		current = current->get_next();
    }
}


template <typename T>
void LinkedList<T>::backward() 
{	
	// Check if there is a valid next node
    if (current->get_prev() != nullptr) {
        // Move current pointer forward
		current = current->get_prev();

		// Check if current is not tail (sentinel node)
        if (current != tail) {

			// sets pointer to previous node
            current->set_next(current->get_next());
        }
    }
}


template <typename T>
int LinkedList<T>::size() const
{
	// intialise listSize variable to zero
	int listSize = 0;

    // Start from the first node after the head
    Node<T>* current = head->get_next();

    // traverse the list
    while (current != tail) {
		// add to listSize count
		++listSize;

        // move to the next node
        current = current->get_next();
    }
	return listSize;
}


template <typename T>
bool LinkedList<T>::empty() const
{
	if (head->get_next()==tail) {
		return true;
	} else {
	return false;
	}
}


template <typename T>
bool LinkedList<T>::search(const T& target) {
    // Start from the first node after the head
    current = head->get_next();

    // Traverse the list
    while (current != tail) {
        // If the current node contains the target data, return true
        if (current->get_data() == target) {
            current = current;
            return true;
        }
        // Move to the next node
        current = current->get_next();
    }

    // If the target is not found in the list, return false
    return false;
}