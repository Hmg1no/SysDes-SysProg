// File:    LL.cpp
// Author:  Hazael Magino
// Date:    5/1/2023
// Section: Section 12
// E-mail:  hazaelm1@umbc.edu
// Description: This program is templated linked list. Although it can take in almost any type of data, in this project we 
// use strings. In this we have a templated node struct as well. Other than that the program utilizes the rule of 3 by having an 
//an overloaded [], overloaded= , and a copy constructor incase the user wants to copy old data to a new variable.  


#include <string>

#include <iostream>

#include <iomanip>

#include <cmath>

using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template < class T >
  class Node {
    public: Node(const T & data); //Node Constructor - Assume each quan
    pair < T,
    int > & GetData(); //Node Data Getter
    void SetData(const pair < T, int > & ); //Node Data Setter
    Node < T > * GetNext(); //Node m_next getter
    void SetNext(Node < T > * next); //Node m_next setter
    private: pair < T,
    int > m_data; //Holds templated data
    Node < T > * m_next; //Pointer to next node
  };

template < class T >
  Node < T > ::Node(const T & data) {
    m_data = make_pair(data, 1);
    m_next = nullptr;
  }

template < class T >
  pair < T, int > & Node < T > ::GetData() {
    return m_data;
  }

template < class T >
  void Node < T > ::SetData(const pair < T, int > & data) {
    m_data = data;
  }

template < class T >
  Node < T > * Node < T > ::GetNext() {
    return m_next;
  }

template < class T >
  void Node < T > ::SetNext(Node < T > * next) {
    m_next = next;
  }

//Templated Linked List class
template < class T >
  class LL {
    public:
      // Name: LL() (Linked List) - Default Constructor
      // Desc: Used to build a new linked list
      // Preconditions: None
      // Postconditions: Creates a new linked list where m_head points to nullptr
      LL();
    // Name: ~LL() - Destructor
    // Desc: Used to destruct a LL
    // Preconditions: There is an existing LL with at least one node
    // Postconditions: A LL is deallocated (including dynamically allocated nodes)
    //                 to have no memory leaks!
    ~LL();
    // Name: LL (Copy Constructor)
    // Desc: Creates a copy of existing LL
    //       Requires a LL - REQUIRED to be implemented even if not used
    // Preconditions: Source LL exists
    // Postconditions: Copy of source LL
    LL(const LL & );
    // Name: operator= (Overloaded Assignment Operator)
    // Desc: Makes two LL of the same type have identical number of nodes and values
    // Preconditions: Requires two linked lists of the same templated type
    //                REQUIRED to be implemented even if not used
    // Postconditions: Two idenetical LL
    LL < T > & operator = (const LL & );
    // Name: Find
    // Desc: Iterates through LL and returns node if data found
    // Preconditions: LL Populated
    // Postconditions: Returns nullptr if not found OR Node pointer if found
    Node < T > * Find(const T & data);
    // Name: Insert
    // Desc: Either inserts a node to the linked list OR increments frequency of first
    //       Takes in data. If "first" (of pair) NOT in list, adds node
    //       If "first" (of pair) is already in list, increments quantity
    //       Inserts "first" in order with no duplicates
    // Preconditions: Requires a LL.
    // Postconditions: Node inserted in LL based on first value (or quantity incremented)
    void Insert(const T & );
    // Name: RemoveAt
    // Desc: Removes a node at a particular position based on data passed (matches first)
    // Preconditions: LL with at least one node. 
    // Postconditions: Removes first node with passed value (in first)
    void RemoveAt(const T & );
    // Name: Display
    // Desc: Display all nodes in linked list
    // Preconditions: Outputs the LL
    // Postconditions: Displays the pair in each node of LL 
    void Display();
    // Name: GetSize
    // Desc: Returns the size of the LL
    // Preconditions: Requires a LL
    // Postconditions: Returns m_size
    int GetSize();
    // Name: operator<< (Overloaded << operator)
    // Desc: Returns the ostream of the data in each node
    // Preconditions: Requires a LL
    // Postconditions: Returns an ostream with the data from each node on different line
    template < class U >
    friend ostream & operator << (ostream & output,
      const LL < U > & );
    // Name: Overloaded [] operator
    // Desc: When passed an integer, returns the data at that location
    // Precondition: Existing LL
    // Postcondition: Returns pair from LL using []
    pair < T,
    int > & operator[](int x); //Overloaded [] operator to pull data from LL
    private: Node < T > * m_head; //Node pointer for the head
    int m_size; //Number of nodes in queue
  };
//*****************************************************************
//Implement LL here

// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head points to nullptr

template < class T >
  LL <T>::LL() {

    // Set the head pointer of the linked list to nullptr
    m_head = nullptr;

    // Set the size of the linked list to 0
    m_size = 0;
  }

// Name: ~LL() - Destructor
// Desc: Used to destruct a LL
// Preconditions: There is an existing LL with at least one node
// Postconditions: A LL is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!

template < class T >
  LL <T>::~LL() {

    // Set curr to point to the head of the linked list
    Node <T> * curr = m_head;

    // Traverse the linked list
    while (curr != nullptr) {

      // Set the head to point to the next node in the list
      m_head = curr -> GetNext();

      // Delete the current node
      delete curr;

      // Set curr to point to the new head of the list
      curr = m_head;
    }
  }

// Name: LL (Copy Constructor)
// Desc: Creates a copy of existing LL
//       Requires a LL - REQUIRED to be implemented even if not used
// Preconditions: Source LL exists
// Postconditions: Copy of source LL

template < class T >
  // Define a copy constructor for the linked list class
  LL <T>::LL(const LL & element) {

    // Initialize the head pointer to nullptr and size to 0
    m_head = nullptr;

    m_size = 0;

    // Set curr to point to the head of the linked list to be copied
    Node <T> * curr = element.m_head;

    // Traverse the linked list to be copied
    while (curr != nullptr) {

      // Create a new node with data from the current node in the linked list to be copied
      Node <T> * copyNode = new Node <T> (curr -> GetData().first);

      // Set the data of the new node
      copyNode -> SetData(curr -> GetData());

      // Set the next pointer of the new node to nullptr
      copyNode -> SetNext(nullptr);

      // Check if the head of the new linked list is null
      if (m_head == nullptr) {

        // Set the head of the new linked list to point to the new node
        m_head = copyNode;
      } else {

        // Set temp to point to the head of the new linked list
        Node <T> * temp = m_head;

        // Traverse the new linked list until reaching the last node
        while (temp -> GetNext() != nullptr) {

          temp = temp -> GetNext();
        }

        // Set the next pointer of temp to point to the new node
        temp -> SetNext(copyNode);
      }

      // Set curr to point to the next node in the linked list to be copied
      curr = curr -> GetNext();

      // Increment the size of the new linked list
      m_size++;
    }

  }

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values
// Preconditions: Requires two linked lists of the same templated type
//                REQUIRED to be implemented even if not used
// Postconditions: Two idenetical LL

template < class T >
  // Define an assignment operator for the linked list class
  LL <T> & LL <T>::operator=(const LL & data) {

    // Check if the current object is not the same as the source object
    if (this != & data) {

      // Deallocate current linked list
      Node <T> * curr = m_head;

      // Traverse the linked list
      while (curr != nullptr) {

        // Set the head of the linked list to point to the next node
        m_head = curr -> GetNext();

        // Delete the current node
        delete curr;

        // Set curr to point to the new head of the linked list
        curr = m_head;
      }

      // Create deep copy of source linked list
      m_head = nullptr;

      curr = nullptr;

      // Set size of linked list to 0
      m_size = 0;

      // Set curr to point to the head of the source linked list
      curr = data.m_head;

      // Traverse the source linked list
      while (curr != nullptr) {

        // Insert data from source linked list into current linked list
        for (int x = 0; x < curr -> GetData().second; x++) {

          Insert(curr -> GetData().first);
        }

        // Set curr to point to the next node in the source linked list
        curr = curr -> GetNext();
      }

    }

    // Return a reference to the current object
    return * this;
  }

// Name: Find
// Desc: Iterates through LL and returns node if data found
// Preconditions: LL Populated
// Postconditions: Returns nullptr if not found OR Node pointer if found

template < class T >
  Node <T> * LL <T>::Find(const T & data) {

    // Set temp to point to the head of the linked list
    Node <T> * temp = m_head;

    // Traverse the linked list
    while (temp != nullptr) {

      // Check if the current node contains the specified data
      if (temp -> GetData().first == data) {

        // If it does, return a pointer to the current node
        return temp;
      }

      // Set temp to point to the next node in the list
      temp = temp -> GetNext();
    }

    // If the data is not found in the list, return nullptr
    return nullptr;
  }

// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first
//       Takes in data. If "first" (of pair) NOT in list, adds node
//       If "first" (of pair) is already in list, increments quantity
//       Inserts "first" in order with no duplicates
// Preconditions: Requires a LL.
// Postconditions: Node inserted in LL based on first value (or quantity incremented)

template < class T >
  void LL <T>::Insert(const T & data) {

    // Set curr to point to the head of the linked list
    Node <T> * curr = m_head;

    // Set prev to nullptr
    Node <T> * prev = nullptr;

    // Traverse the linked list until curr points to a node with data greater than or equal to the specified data
    while ((curr != nullptr) && (curr -> GetData().first < data)) {

      prev = curr;

      curr = curr -> GetNext();
    }

    // Check if curr points to a node with data equal to the specified data
    if ((curr != nullptr) && (curr -> GetData().first == data)) {

      // If it does, increment the second element of the pair stored in the current node
      curr -> GetData().second++;

      return;
    }

    // Create a new node containing the specified data
    Node <T> * newData = new Node <T> (data);

    // Check if prev is nullptr
    if (prev == nullptr) {

      // If it is, set the head of the linked list to point to the new node
      m_head = newData;
    } else {

      // Otherwise, set the next pointer of prev to point to the new node
      prev -> SetNext(newData);
    }

    // Set the next pointer of the new node to point to curr
    newData -> SetNext(curr);

    // Increment the size of the linked list
    m_size++;
  }

// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node. 
// Postconditions: Removes first node with passed value (in first)
// Define a template class for a linked list

// Define a template function to remove a node from a linked list
template <class T>
void LL<T>::RemoveAt(const T& select) {

    // Initialize pointers to keep track of current, previous, and next nodes
    Node<T>* curr = m_head;

    Node<T>* temp = nullptr;

    Node<T>* next = nullptr;

    // Check if the linked list is empty
    if (m_size < 1) {

      cout << "The linked list is empty" << endl;
      return;

    }

    // Check if there is only one node in the linked list
    if (m_size == 1) {

        delete m_head; // Delete the head node

        m_head = nullptr; // Set head pointer to null

        m_size--; // Decrement size of linked list

        return;
    }

    // Traverse the linked list to find the node to be removed
    while (curr != nullptr) {

        if (curr->GetData().first == select) { // Check if current node data matches the data to be removed

            if (temp == nullptr) { // Check if current node is the head node

                m_head = curr->GetNext(); // Set head pointer to next node

            } else {

                temp->SetNext(curr->GetNext()); // Set previous node's next pointer to current node's next pointer

            }
            next = curr->GetNext(); // Set next pointer to current node's next pointer

            delete curr; // Delete current node

            curr = next; // Set current pointer to next pointer

            m_size--; // Decrement size of linked list

        } else {

            temp = curr; // Set previous pointer to current pointer

            curr = curr->GetNext(); // Set current pointer to next pointer
        }
    }

    // Reset pointers to null
    temp = nullptr;

    curr = nullptr;
    
    next = nullptr;
}


// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the LL
// Postconditions: Displays the pair in each node of LL 

template < class T >
  void LL <T>::Display() {

    // Initialize current node to head of linked list
    Node < T > * curr = m_head;

    // Traverse linked list
    while (curr != nullptr) {

      // Print data of current node
      cout << curr -> GetData().first << ":" << curr->GetData().second << '\n';

      // Move to next node in linked list
      curr = curr -> GetNext();
    }

    cout << "END" << endl;
  }

// Name: GetSize
// Desc: Returns the size of the LL
// Preconditions: Requires a LL
// Postconditions: Returns m_size

template < class T >

  int LL <T>::GetSize() {

    // Return the size of the linked list
    return m_size;
  }

// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line

template < class U >
  ostream & operator << (ostream & output, const LL <U> & other) {

    // Overload the << operator to print the contents of the linked list

    Node <U> * curr = other.m_head; // Start at the head of the list

    while (curr != nullptr) { // Traverse the list

      output << curr -> GetData().first << ":" << curr -> GetData().second << '\n'; // Output the data of each node

      curr = curr -> GetNext(); // Move to the next node
    }

    // Indicate the end of the list
    output << "END" << endl;

    return output; // Return the output stream
  }

// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
//Overloaded [] operator to pull data from LL

template < class T >
  pair <T, int> & LL <T>::operator[](int x) {

    // Traverse the linked list to find the node at the specified index
    Node <T> * curr = m_head;

    for (int i = 0; i < x; i++) {

      curr = curr -> GetNext();
    }

    // Return the data of the node at the specified index
    return curr -> GetData();
  }