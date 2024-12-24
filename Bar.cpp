// File:    Bar.cpp
// Author:  Hazael Magino
// Date:    5/1/2023
// Section: Section 12
// E-mail:  hazaelm1@umbc.edu
// Description: The goal of this program is to succesfuly read in file input from a text file and then accordingly sort data. 
// The user can choose to remove certain types of data from the file. Then after being read from the user can export the file with 
// a certain name. 

#include "Bar.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <string>
#include <map> 
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;

    // Name: Bar (Default Constructor) (not used)
   // Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
   // Preconditions: Input file has correctly formatted input
   // Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar() {

    m_fileName = "Random.txt"; // Set the file name to the given file name

    m_data = new LL < string > (); // Allocate memory for m_data and initialize it as an empty linked list
}

// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename) {

    m_fileName = filename; // Set the file name to the given file name

    m_data = new LL < string > (); // Allocate memory for m_data and initialize it as an empty linked list
}

// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar() {

    delete m_data; // Deallocate the memory allocated for m_data

    m_data = nullptr; // Set m_data to nullptr to avoid dangling pointer issues
}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start() {

    LoadFile(); // Load data from the file

    RemoveCommon(); // Remove common words from the data

    RemoveSingles(); // Remove words with a frequency of 1 from the data

    SortData(); // Sort the data based on frequency

    DisplayBars(); // Display the data as bars

    Export(); // Export the data to a file
}

//   // Name: LoadFile()
//   // Desc: Loads a file (everything as a string although could be anything stringlike)
//   //       Calls RemovePunct as each item is loaded
//   //       Each input file is an unknown length
//   // Preconditions: m_fileName is populated with good data
//   // Postconditions: m_data is populated
void Bar::LoadFile() {

    int count = 0; // Initialize a counter to keep track of the number of items loaded

    ifstream filestream; // Declare an input file stream object

    filestream.open(m_fileName); // Open the file with the given file name

    string rInput; // Declare a string variable to store the input from the file

    // Check if the file was opened successfully
   if (filestream.is_open()) {

        // Read input from the file until the end of the file is reached
         while (filestream >> rInput) {

            RemovePunct(rInput); // Remove punctuation from the input

            m_data -> Insert(rInput); // Insert the word into m_data

            count++; // Increment the counter
         }

      filestream.close(); // Close the input file stream
   }

    cout << count << " loaded" << endl; // Output the number of items loaded
}

// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string & string) {

    //convert to lowercase string if uppercase
   for (string::iterator it = string.begin(); it != string.end(); ++it) {

        * it = tolower( * it);

   }

   // Remove punctuation from the beginning of the string
   while (!string.empty() && ispunct(string[0])) {

      string.erase(string.begin());

   }
   // Remove punctuation from the end of the string
   while (!string.empty() && ispunct(string[string.length() - 1])) {

      string.pop_back();

   }

}

// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon() {

   string choice; // Declare a string variable to store the user's choice

   // Declare a string variables to store an alternative choices

   string choice1 = "yes";

   string choice2 = "y";

   string choice3 = "YES";

   string choice4 = "Y";

    cout << "Would you like to remove all common words (Only use with essays)?" << endl; // Prompt the user for their choice

    cin >> choice; // Read the user's input

    // Check if the user's choice is "yes" or "y"
   if ((choice == choice1) || (choice == choice2) || (choice == choice3) || (choice == choice4)) {

        // Iterate through each item in EXCLUDE_LIST
         for (vector < string > ::const_iterator it = EXCLUDE_LIST.begin(); it != EXCLUDE_LIST.end(); ++it) {

            m_data -> RemoveAt( * it); // Remove the current item from m_data
         }

        cout << "All common words removed " << endl; // Output a message indicating that all common words have been removed
   }
}

// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles() {

    int count = 0; // Initialize a counter to keep track of the number of items removed

    string choice; // Declare a string variable to store the user's choice

    // Declare a string variables to store an alternative choices

   string choice1 = "yes";

   string choice2 = "y";

   string choice3 = "YES";

   string choice4 = "Y";

    cout << "Would you like to remove all words with a frequency of 1?" << endl; // Prompt the user for their choice

    cin >> choice; // Read the user's input

   // Check if the user's choice is "yes" or "y"
   if ((choice == choice1) || (choice == choice2) || (choice == choice3) || (choice == choice4)) {

      // Iterate through each item in m_data
      for (int i = 0; i < m_data -> GetSize(); i++) {

            pair < string, int > temp = ( * m_data)[i]; // Get the current item

            // Check if the frequency of the current item is 1
            if (temp.second == 1) {

                m_data -> RemoveAt(temp.first); // Remove the current item from m_data

                count++; // Increment the counter

                i--; // Decrement the loop counter to account for the removed item
            }
      }

        cout << count << " Removed" << endl; // Output the number of items removed
   }
}

// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData() {

    if (m_data -> GetSize() == 0) { // Check if m_data is empty

        cout << "No data to sort" << endl; // Output a message indicating that there is no data to sort

        return; // Exit the function
   }

    // Iterate through each item in m_data
   for (int i = 0; i < m_data -> GetSize(); i++) {

        // Insert the item into m_dataSorted using the frequency as the key and the label as the value
        m_dataSorted.insert(make_pair(( * m_data)[i].second, ( * m_data)[i].first));
   }

}

// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars() {

    int const labelWidth = 15; // Set a fixed width for the labels

    // Iterate through the multimap in reverse order
   for (multimap < int, string > ::reverse_iterator rit = m_dataSorted.rbegin(); rit != m_dataSorted.rend(); ++rit) {

        cout << setw(labelWidth) << right << rit -> second << ":"; // Output the label with fixed width and right alignment

        // Output the bar character for the number of times specified by the key
         for (int i = 0; i < rit -> first; i++) {

            cout << barChar;
         }

        cout << endl; // Move to a new line
   }

}

// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export() {

    string nametxt; // Declare a string variable to store the name of the export file

    cout << "What would you like to call the export file? " << endl; // Prompt the user for the name of the export file

    cin >> nametxt; // Read the user's input

    ofstream outputCont(nametxt); // Create an output file stream object with the given file name

    if (outputCont.is_open()) { // Check if the file was opened successfully

        int labelWidth = 15; // Set a fixed width for the labels

        // Iterate through the multimap in reverse order
         for (multimap < int, string > ::reverse_iterator rit = m_dataSorted.rbegin(); rit != m_dataSorted.rend(); ++rit) {

            outputCont << setw(labelWidth) << right << rit -> second << ":"; // Output the label with fixed width and right alignment

            // Output the bar character for the number of times specified by the key
            for (int i = 0; i < rit -> first; i++) {

               outputCont << barChar;
            }

            outputCont << endl; // Move to a new line
         }
   }
   cout << "Output to exportFile " << nametxt << endl;
   
   outputCont.close(); // Close the output file stream



}