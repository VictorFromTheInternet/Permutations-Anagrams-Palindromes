#ifndef H_orderedListType
#define H_orderedListType
 
#include "LinkedList.h"
 
using namespace std; 
 
template <class Type>
class orderedLinkedList: public linkedListType<Type>
{
public:
    bool search(const Type& searchItem) const; 
      //Function to determine whether searchItem is in the list.
      //Postcondition: Returns true if searchItem is in the 
      //               list, otherwise it returns false.

    void insert(const Type& newItem);
      //Function to insert newItem in the list.
      //Postcondition: first points to the new list, newItem 
      //               is inserted at the proper place in the
      //               list, and count is incremented by 1.

    void insertFirst(const Type& newItem);
      //Function to insert newItem in the list.
      //Because the resulting list must be sorted, newItem is 
      //inserted at the proper in the list.
      //This function uses the function insert to insert newItem.
      //Postcondition: first points to the new list, newItem is
      //               inserted at the proper in the list,
      //               and count is incremented by 1.

    void insertLast(const Type& newItem);
      //Function to insert newItem in the list.
      //Because the resulting list must be sorted, newItem is 
      //inserted at the proper in the list.
      //This function uses the function insert to insert newItem.
      //Postcondition: first points to the new list, newItem is
      //               inserted at the proper in the list,
      //               and count is incremented by 1.

    void deleteNode(const Type& deleteItem);
      //Function to delete deleteItem from the list.
      //Postcondition: If found, the node containing 
      //               deleteItem is deleted from the list;
      //               first points to the first node of the 
      //               new list, and count is decremented by 1.
      //               If deleteItem is not in the list, an
      //               appropriate message is printed.
};


template <class Type>
bool orderedLinkedList<Type>::
                 search(const Type& searchItem) const
{
    bool found = false;
    nodeType<Type> *current; //pointer to traverse the list

    current = this -> first;  //start the search at the first node
	
	// keep going as long as current pointer doesn't equal nullptr, at the end
	// and current isnt equal to search item
    while (current != nullptr && !found)
        if (current->info >= searchItem) // checking to see if current passed where it would have been
            found = true;	// if search item is found, set bool val found to "true"
        else
            current = current->link;
 
    if (found) 
       found = (current->info == searchItem); //testing the values of nodes

    return found;
}//end search


template <class Type>
void orderedLinkedList<Type>::insert(const Type& newItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent = nullptr; //pointer just before current
    nodeType<Type> *newNode;  //pointer to create a node

    bool  found;

    newNode = new nodeType<Type>; //create the node
    newNode->info = newItem;  //store newItem in the node
    newNode->link = nullptr;  //set the link field of the node
                              //to nullptr

    //Case 1, list is empty
	if (this ->first == nullptr)  
    {
        this->first = newNode;
        this ->last = newNode;
        this ->count++;
    }
    
    // not empty
    else
    {
        current = this ->first;
        found = false;

        while (current != nullptr && !found) // start traversing the list to find the insert location
           if (current->info >= newItem)	 // check to see if the current node is the insertion location
               found = true;
           else								 // else advance to the next node				
           {
               trailCurrent = current;
               current = current->link;
           }
 		
 		// case 2, list was not empty and the insert loc is at the beggining
        if (current == this ->first)      
        {
            newNode->link = this ->first; // point new node to 1st
            this ->first = newNode;       // point first to the new node
            this ->count++;
        }
        //Case 3, list is not empty  and insert loc is somewhere other than beg
        else                       
        {
        	// connect the new node to the list
            trailCurrent->link = newNode;
            newNode->link = current;
			
			// check to see if the insert loc is at the end
            if (current == nullptr)
                this ->last = newNode;	// if so, point last to new node

            this ->count++;
        }
    }//end else
}//end insert

template<class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem)
{
    insert(newItem);
}//end insertFirst

template<class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem)
{
    insert(newItem);
}//end insertLast

template<class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent = nullptr; //pointer just 
                                            //before current
    bool found;
    
    
	//Case 1, list is empty 
    if (this ->first == nullptr) 
        cout << "Cannot delete from an empty list." << endl;
    
    // the list is not empty, begin search
	else
    {
        current = this ->first;
        found = false;
		
		// search until end or search item is reached
        while (current != nullptr && !found)  
            if (current->info >= deleteItem)	// comparing value of current node
                found = true;
            
			else	// if item looked at isnt search item, advance to next node
            {
                trailCurrent = current;
                current = current->link;
            }
		
		//Case 4, searched the entire list but deleteItem is not in the last
        if (current == nullptr)   // if end is reached
            cout << "The item to be deleted is not in the " 
                 << "list." << endl;
        
		// else, search did not reach the end of the list
		else
            if (current->info == deleteItem) // check to see if deleteItem was found
            {
            	// Case 2, deleteItem is the first node
                if (this ->first == current)       
                {
                    this ->first = this ->first->link;

                    if (this ->first == nullptr) // check to see if there was only one node in the list
                        this ->last = nullptr;   // if so point first + last at the node

                    delete current;
                }
                
				//Case 3, deleteItem is somewhere in the list but not the first node (middle or last)
				else                         
                {
                    trailCurrent->link = current->link; // connecting previous node to node after deleteItem

                    if (current == this ->last) // check to see if the deleteItem was at the end
						this -> last = trailCurrent; // if so point last to item before deleteItem

                    delete current; // delete item
                }
                this -> count--; // decrement the count of nodes
            }
            //Case 4, search passed where deleteItem should have been
            else                            
                cout << "The item to be deleted is not in the "
                     << "list." << endl;
    }
}//end deleteNode


#endif