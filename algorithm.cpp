/*
  Author: Joshua Lee
  Date: 4/6/2015
  Description: Program that will display a menu and allow the user to choose which 
               search or sort algorithm to use until the user quits.
  Algorithm:
    1) Display a menu of the choices the user can choose
    2) From the selection perform the search or sort that they chose
    3) If it is a search function display the book in table format
      a) take in the Book ID and the # of books bought
      b) output the total cost
    4) If it is a sorting function
      a) display the unsorted array of 1,000 random numbers and then sort them
      b) display the sorted array
    5) Continue to loop through the menu until the user chooses to quit
    6) Bonus: add a execution time calculation to both the searching and sorthing 
              and display it to the user
*/
#include<iostream>
#include<string>
#include<iomanip>
// Include for random number
#include<cstdlib>
#include<ctime>

using namespace std;

int displayMenu(){ // Function to display and return the user choice
  int choice;
  cout << "**** SEARCHING & SORTING MENU ****\n\n";
  cout << "\t1. Linear Search\n";
  cout << "\t2. Binary Search\n";
  cout << "\t3. Bubble Sort\n";
  cout << "\t4. Selection Sort\n";
  cout << "\t5. Quit\n\n";
  cout << "PLease enter your choice: ";
  cin >> choice;
  return choice;
}

void display(string *bookTitle, int *bookID, double *bookPrice){
  cout << "**** LINEAR SEARCH ****\n";
  cout << "Book ID\t\t\tTitle\t\t\t\tCost\n";
  for (int i=0; i<10; i++){
    cout << bookID[i] << "\t " << setw(40) << left << bookTitle[i] << "\t$" << bookPrice[i] << "\n";
  }
  cout << endl;
}

int linearSearch(int *bookID, int id){
  for (int i = 0; i<10; i++){
    if (bookID[i] == id){
      return i;
    }
  }
  return -1;
}

int binarySearch(int *bookID, int id){
  int max = 9, mid = 5, min = 0;
  for (int i = 0; i < 10; i++){
    mid = (max + min)/2;
    if (id == bookID[mid]){
      return mid;
    }
    else if (id > bookID[mid]){
      min = mid + 1;
    }
    else{
      max = mid;
    }
  }
  return -1;
}

double calcTotalCost(double *bookPrice, int index, int qty){
  double price = bookPrice[index];
  return price *= qty;
}

void searchOutput(int id, string title, int qty, double cost){
  // Outputing the data to the user
  cout << "Book ID: " << id << endl;
  cout << "Book Title: " << title << endl;
  cout << "Number of books bought: " << qty << endl;
  cout << "Total Cost: $" << setprecision(2) << fixed << cost << endl;
}

void initializeUnsortedArr(int *array, int size){
  // Generate a random seed
  srand (time(NULL));
  for(int i=0;i<size;i++){
    array[i] = rand() % 500 + 1;
  }
}

void displayArray(int *array, int size){
  for(int i=0;i<size;i++){
    cout << array[i] << "\t";
  }
}

void bubbleSort(int *array, int size){
  while (true){
    // having a condition to check if a swap was made, if none then it's sorted
    bool swapped = false;
    for (int i = 0; i < size - 1; i++){
      if (array[i] > array[i+1]){
        // copy must be made so that the value is not lost while swapping
        int copy = array[i];
        array[i] = array[i+1];
        array[i+1] = copy;
        swapped = true;
      }
    }
    if (!swapped) break;
  }
}

void selectionSort(int *array, int size){
  int copy, index;
  for(int i = 0; i< 500;i++){ // It starts the sort at the first position and then moves over one for each iteration b/c the first one is going to be the lowest
    int min = 500;
    for(int j=i;j<500;j++){
      if(array[j] < min){
        min = array[j];
        index = j;
      }
    }
    // copy must be made so that the value is not lost while swapping
    copy = array[i];
    array[i]=min;
    array[index] = copy;
  }
}

void navigateMenu(int choice){
  // Creating the arrays for the searching algorithm
  string bookTitle[] = {"Starting out with C++", "Java Programming", "Software Structures", "Design and Analysis of Algorithms", "Computer Graphics", "Artificial Intelligence: A Modern Approach", "Probability and Statistics", "Cognitive Science", "Modern Information Retrieval", "Speech and Language Processing"};
  int bookID[] = {1101, 1211, 1333, 1456, 1567, 1642, 1699, 1755, 1800, 1999};
  double bookPrice[] = {112.32, 73.25, 54.00, 67.32, 135.00, 173.22, 120.00, 42.25, 32.11, 123.75};
  // Create variables to be used in below functions
  int id = 0, copies = 0, index;
  double totalPrice;


  switch(choice)
  {
    case 1:{
      display(bookTitle, bookID, bookPrice);
      cout << "Please enter the book ID you wish to purchase: ";
      cin >> id;
      cout << "How many copies you wish to purchase: ";
      cin >> copies;
      // Finding the index position of the inputted book ID through linear search
      index = linearSearch(bookID, id);
      // Continue to ask for a book ID until a valid one is provided
      while (index == -1){
        cout << "That is not an existing book ID. Please enter the book ID you wish to purchase: ";
        cin >> id;
        index = linearSearch(bookID, id);
      }
      // Function call to calculate the total cost
      totalPrice = calcTotalCost(bookPrice, index, copies);
      // Outputing the data to the user
      searchOutput(id, bookTitle[index], copies, totalPrice);
      break;
    }
    case 2:{
      display(bookTitle, bookID, bookPrice);
      cout << "Please enter the book ID you wish to purchase: ";
      cin >> id;
      cout << "How many copies you wish to purchase: ";
      cin >> copies;
      // Finding the index position of the inputted book ID through binary search
      index = binarySearch(bookID, id);
      // Continue to ask for a book ID until a valid one is provided
      while (index == -1){
        cout << "That is not an existing book ID. Please enter the book ID you wish to purchase: ";
        cin >> id;
        index = binarySearch(bookID, id);
      }
	    // Function call to calculate the total cost
	    totalPrice = calcTotalCost(bookPrice, index, copies);
      searchOutput(id, bookTitle[index], copies, totalPrice);
      break; 
    }
    case 3:{ // Bubble Sort
      int arr[500];
      // Create the unsorted array
      initializeUnsortedArr(arr, 500);
      cout << "**** BUBBLE SORT ****\n";
      cout << "Unsorted array:\n";
      displayArray(arr, 500);
      cout << endl;
      bubbleSort(arr, 500);
      cout << endl << "Sorted array:\n";
      displayArray(arr, 500);
      cout << endl;
      break;
    }
    case 4:{ // Selection Sort
      int arr[500];
      // Create the unsorted array
      initializeUnsortedArr(arr, 500);
      cout << "**** SELECTION SORT ****\n";
      cout << "Unsorted array:\n";
      displayArray(arr, 500);
      cout << endl;
      selectionSort(arr, 500);
      cout << endl << "Sorted array:\n";
      displayArray(arr, 500);
      cout << endl;
      break;
    }
  }
}

int main(){
  int choice = 0;
  while (choice != 5){ // Continue to display the menu until they choose the quit option
    choice = displayMenu();
    navigateMenu(choice);
  }

  return 0;
}
