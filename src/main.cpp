/********************   PROJECT 8    **********************/
/*   Use this as your main program for Project 8.
     You will have to write the code for the Bag ADT (on bag.h)
     and the Item ADT, on item.h                            */

#include <iostream>
#include <string>
using namespace std;
#include "item.h"
#include "bag.h"

int main() {
  // declarations
  string anItem;
  Bag groceries;

  // testing
  cout << "==== TEST1: Adding Items ====\n\n";
  groceries.add("milk");
  groceries.add("meat");
  groceries.add("bread");
  groceries.add("lottery tickets");
  groceries.display();

  cout << "\n==== TEST2: Removing Last Item ====\n";
  groceries.remove("lottery tickets");
  groceries.display();

  cout << "\n==== TEST3: isEmpty() ====\n";
  if (groceries.isEmpty())
    cout << "The list is empty\n";
  else
    cout << "The list is not empty\n";

  cout << "\n==== TEST4: getSize() ====\n";
  cout << "The list has " << groceries.getSize() << " items\n";

  cout << "\n==== TEST5: clear() ====\n";
  groceries.clear();
  cout << "The list has " << groceries.getSize() << " items\n";

  cout << "\n==== TEST6: add list items() ====\n";
// while loop to enter items
  cout << "Enter an item ";
  getline(cin, anItem);
  while (anItem != "quit") {
    groceries.add(anItem);
    cout << "Enter another item ";
    getline(cin, anItem);
  }
  groceries.display();

  cout << "\n==== TEST7: contains() ====\n";
  cout << "Search for an item that is NOT in the list: " ;
  getline(cin, anItem);
  if ( groceries.contains(anItem) ) 
    cout << "list contains " << anItem << endl;
  else
    cout << "list does not contain " << anItem << endl;

  cout << "\n==== TEST8: contains() ====\n";
  cout << "Search for an item that is in the list: " ;
  getline(cin, anItem);
  if ( groceries.contains(anItem) ) 
    cout << "list contains " << anItem << endl;
  else
    cout << "list does not contain " << anItem << endl;

  cout << "\n==== TEST9: getFrequencyOf() ====\n";
  cout << anItem << " is in the list " << groceries.getFrequencyOf(anItem) 
          << " times. "<< endl;
}