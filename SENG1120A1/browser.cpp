
// Modified by  : Oskar Peters C3437787
#include "browser.h"

Browser::Browser(const std::string& homepage, int history_limit) 

    : homepage(homepage), history_limit(history_limit) {

    // Initialize the history and bookmarks linked lists
    history = new LinkedList<std::string>();
    bookmarks = new LinkedList<std::string>();
    this->history_limit = history_limit;

    // Visit the homepage to add it to the history
    visit(homepage);
}



Browser::~Browser() 
{
    // Deallocate memory for the history and bookmarks linked lists
    delete history;
    delete bookmarks;
}


const std::string& Browser::get_current_site()
{
    try {
        // Check if the history list is empty
        if (history->size() < 1) {
            // Throw an exception
            throw std::logic_error("No current site. History is empty.");
        }

        // Return data from currently selected node
        return history->get_current();
    } catch (const std::logic_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
}


void Browser::visit(const std::string& url)
{
    // adds url as a node at the end of the history list and selects it 
    history->push_back(url);
}


void Browser::back(int steps)
{
    for (int i=0; i < steps; i++) {
        history->backward();
    }
}


void Browser::forward(int steps)
{
    for (int i=0; i < steps; i++) {
        history->forward();
    }
}


int Browser::remove(std::string url)
{
    //intialises variable for number of items removed at 0
    int itemsRemoved = 0;

    //loops the search function to find then delete each item which matches the url
    while (history->search(url)) {
        //removes current node after the applicable node has been found
        history->remove();

        //adds to itemsRemoved count
        itemsRemoved++;
    }

    //returns the number of items removed
    return itemsRemoved;
}


void Browser::bookmark_current()
{
    //checks to see if current url is in bookmarks
    if (bookmarks->search(history->get_current())==true) {
        //removes currently selected node/url from bookmarks
        bookmarks->remove();
        std::cout << history->get_current() << " removed from bookmarks" << std::endl;

    } else {
        // if url was not in bookmarks it will be inserted into the list
        bookmarks->push_back(history->get_current());
        std::cout << history->get_current() << " added to bookmarks" << std::endl;
    }
}

void Browser::clear_history()
{
    if (history->empty() == true) {
        //exception
        std::cout << "Invalid. History is already empty." << std::endl;
        return;

    } else {
    // uses "clear" command on history linkedlist
    history->clear();
    visit(homepage);
    }

}


void Browser::print_bookmarks()
{
    if (bookmarks->empty() == true) {
        //exception
        std::cout << "Invalid. Bookmarks is empty.";
        return;

    } else {

        //starts from beginning of list
        bookmarks->begin();

        // a loop to print each node data
        while (bookmarks->get_current() != bookmarks->back()) {

            //prints data
            std::cout << bookmarks->get_current() << std::endl;

            //moves to next node
            bookmarks->forward();
        }

        // prints last non-sentinel node in list
        std::cout << bookmarks->get_current() << std::endl;
    }
}


int Browser::count_history() const
{
    return history->size();
}


int Browser::count_bookmarks() const
{
    return bookmarks->size();
}


void Browser::visit_bookmark(int index)
{
    index = index-1;
    bookmarks->begin();
    if  (index >= 0 && index < bookmarks->size()) {
        for (int i = 0; i < index; ++i) {
            bookmarks->forward();
        }
        std::string url = bookmarks->get_current();
        visit(url);
    } else {
        //exception
        std::cout << "Invalid. Index is not relative to any item in bookmarks";
        return;
    }
}