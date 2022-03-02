/*
 * @brief SECTION 8 CSCI 1300 PROJECT (LIBRARY MANAGEMENT SYSTEM)
 * Group Members:
 * Mohamad Syafiq Asyraf Bin Bharudin 2116239
 * Mohamad Faris Aiman Bin Mohd Faizal 2111809
 * Qasdina Azlin Binti Azhar 2117040
 * Maryam Siddiqui 2115928

  File format (with example data):
    > libr_rec.dat
      Format:
        LibrID  Password
        LibrName
      Example:
        2111111 qwertyui
        Ali Bin Abu
    > stud_rec.dat
      Format:
        StudID  Password
        StudName
      Example:
        2111111 asdfghjk
        Halim Siddiq
*/

#include <iostream>
#include <istream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

struct Books
{
	string bookname;
	string bookid;
	string author;
};

struct Student
{
	string name;
	string password;
	string ID;
	string bookname;
};

Student st;

const int MAX = 1;

//int sentinelBorrow = 0, sentinelAvailable=0;

void mainMenu(); // Main page
void librarian(int); // Login and librarian dashboard
void student(int); // Login and student dashboard
void insertRecord(); // Inserting new records for librarian
void deleteRecord(); // Delete books
void viewRecord(); // View books
string logLibr(string, string); // Check the existing records of librarians in the file named libr_rec.dat
string logStud(string, string); // Check the existing records of students in the file named stud_rec.dat
void borrowBooks(); //Borrow bookss from library
void updateRecord(); //update books records (bookID, title & author)
void searchRecord(); //search for any books in the record
void availableBooks(); //display all available books in the records

int main()
{
	mainMenu(); // Call the mainMenu() func
	  
	cout << "Thank you for using our system." << endl;

	return 0;
}

//  Programmer: Mohamad Syafiq Asyraf Bin Bharudin 
void mainMenu()
{
	cout << setw(60) << right << "~ WELCOME TO IIUM LIBRARY MANAGEMENT SYSTEM ~" << endl;
	
	cout << "Please choose : " << endl;
	cout << "[1] Login as a librarian" << endl
		 << "[2] Login as a student" << endl
	 	 << "[3] Exit program" << endl;
	cout << endl;
	
	int response;
	cout << "Response : ";
	cin >> response;
	cin.ignore();
	cout << endl;
	
	while (response != 1 && response != 2 && response != 3)
	{
		cout << "Invalid response! Please try again.." << endl;
		cout << "Response : ";
		cin >> response;
		cout << endl;
	}
	
	switch (response)
	{
		case 1:
			librarian(response);
			break;
		case 2:
			student(response);
		case 3:
			break;
	}
}

//  Programmer: Mohamad Syafiq Asyraf Bin Bharudin
void librarian(int option) // Receive a copy of response from caller func
{
	string ID, password, result;
	int nav;
	  
	cout << "Please enter your verification ID : ";
	getline(cin >> ws, ID);
	
	cout << "Please enter your password : ";
	getline(cin >> ws, password);
	
	result = logLibr(ID, password);
	
	while (result == "fail")
	{
		cout << "Invalid credentials!" << endl;
		cout << "Please enter your verification ID : ";
		getline(cin >> ws, ID);
		
		cout << "Please enter your password : ";
		getline(cin >> ws, password);
		
		result = logLibr(ID, password);
	}
	while (nav != 6)
	{
		if (result != "fail")
		{
			cout << "\nWelcome back, " << result << "!" << endl;
			cout << endl;
			
			cout << "What do you want to do? Please choose : " << endl;
			cout << "[1] Insert new record(s)" << endl
				 << "[2] Delete old record(s)" << endl //TBD
				 << "[3] Update record(s)" << endl //TBD
				 << "[4] View all record(s)" << endl // Use ofstream, display all records, append into the global struct, sort
				 << "[5] Search record(s)" << endl
				 << "[6] Logout" << endl;
			cout << endl;
			
			cout << "Response : ";
			cin >> nav;
			cout << endl;
			
			switch (nav)
			{
				case 1:
					insertRecord();
					break;
				case 2:
					deleteRecord();
					break;
				case 3:
					updateRecord();
					break;
				case 4:
					viewRecord();
					break;
				case 5:
					searchRecord();
					break;
				case 6:
					mainMenu();
					break;
			}
		}
	}
}   

//  Programmer: Mohamad Syafiq Asyraf Bin Bharudin
void student(int option) // Receive a copy of response from caller func
{
	string ID, password, result;
	ofstream rec;
	int nav;
	char dashboardOpt;
	
	cout << "Verification Menu" << "\n\n"
		 << "[R] Register as a new user" << "\n"
		 << "[P] Proceed to login" << "\n\n"
		 << "Response : ";
		 
	cin >> dashboardOpt;
	cin.ignore();
	dashboardOpt = toupper(dashboardOpt);
	cout << endl;
	
	while (dashboardOpt != 'R' && dashboardOpt != 'P')
	{
		cout << "Invalid input!" << endl;
		cout << "Please re-enter your response : ";
		cin >> dashboardOpt;
		dashboardOpt = toupper(dashboardOpt);
		cin.ignore();
	}

	switch (dashboardOpt)
	{
		case 'R':
			cout << "Enter your name : ";
			getline(cin >> ws, st.name);
			cout << "Enter your studentID : ";
			getline(cin >> ws, st.ID);
			cout << "Enter your password : ";
			getline(cin >> ws, st.password);
			
			result = logStud(st.ID, st.password); // Check the data if they're already in the rec or not
			
			if (result != "fail")
			{
				cout << "User already exists in the record! Please proceed to login." << endl;
				cout << endl;
				student(1); 
			}
			else 
			{
				rec.open("stud_rec.dat", ios::app);
				if (rec.fail())
				{
					cout << "Failed to register! Please try again later." << endl;
					student(1);
				}
					rec << st.ID << " " << st.password << "\n" << st.name << "\n";
					rec.close();
					cout << "Successfully registered! Please login." << endl;
					cout << endl;
					student(1);
			}
			break;
			
    case 'P':
      cout << "Please enter your student ID : ";
      getline(cin >> ws, ID);
      cout << "Please enter your password : ";
      getline(cin >> ws, password);
      
      result = logStud(ID, password);
      
      while (result == "fail")
      {
        cout << "Invalid credentials" << endl;
        cout << "Please enter your student ID : ";
        getline(cin >> ws, ID);
        cout << "Please enter your password : ";
        getline(cin >> ws, password);
        result = logStud(ID, password);
      }
      
      while (nav != 3)
      {
        if (result != "fail")
        {
          cout << "\nWelcome back, " << result << "!" << endl;
          cout << endl;
          
          // Programmer: Maryam Siddiqui, Mohamad Syafiq Asyraf Bin Bharudin
          cout << "What do you want to do? Please choose:  " << endl;
          cout << "[1] Borrow books" << endl
        	   << "[2] Search for available books" << endl
               << "[3] Logout" << endl;
          cout << endl;
          
          cout << "Response : ";
          cin >> nav;
          cout << endl;
          
          switch (nav)
          {
            case 1: 
              borrowBooks();
              break;
            case 2:
              availableBooks();
              break;
            case 3:
              mainMenu();
              break;
          }
        }
      }
	    break; 
	}  
}

//  Programmer: Mohamad Syafiq Asyraf Bin Bharudin 
string logLibr(string ID, string password)
{
	ifstream inf;
	string foundID, foundPassword, foundName;
	
	inf.open("libr_rec.dat"); //  Open a file names "libr_rec.dat"
	
	if (inf.fail()) //  Check the connection between the file and this program
	{
		cout << "Sorry, the file can't be accessed at this moment. Please try again later.";
		mainMenu();
	}
	
	//  Look through the file to check whether the passed values are exist in the file
	while (!inf.eof())
	{
		inf >> foundID >> foundPassword; // Check the ID and password format
		getline(inf >> ws, foundName); // Check the name format
		
		if (foundID == ID && foundPassword == password) //  If the passed values exist in the file, return the name of the user
		{
			inf.close();
			return foundName;
			break;
		}
	}
	return "fail"; // If the passed values are not exist in the file, return fail to the calling func
}

//  Programmer: Mohamad Syafiq Asyraf Bin Bharudin 
string logStud(string ID, string password)
{
	ifstream inf;
	string foundID, foundPassword, foundName;
	
	inf.open("stud_rec.dat"); //  Open a file names "stud_rec.dat"
	
	if (inf.fail()) //  Check the connection between the file and this program
	{
		cout << "Sorry, the file can't be accessed at this moment. Please try again later.";
		mainMenu();
	}
	
	//  Look through the file to check whether the passed values are exist in the file 
	while (!inf.eof())
	{
		inf >> foundID >> foundPassword; // Check the ID and password format 
		getline(inf >> ws, foundName); // Check the name format
		
		if (foundID == ID && foundPassword == password) //  If the passed values exist in the file, return the name of the user
		{
			inf.close();
			return foundName;
			break;
		}
	}
	return "fail";  // If the passed values are not exist in the file, return fail to the calling func
}

//  Programmer: Mohamad Faris Aiman Bin Mohd Faizal, Mohamad Syafiq Asyraf Bin Bharudin 
void insertRecord()
{
	Books libr[MAX];
	string refNum;
	
	ofstream outf;
	ifstream inf;
	
	string exist;
	char response;
	int newMax;
	int count = 0;
	
	while (response != 'N') // Loop the process until the user enter 'N' or 'n' to stop the process
	{
		srand(time(NULL)); // Generate random num on each run
		
		cout << "\nInput Guidelines:" << "\n"
			 << "[Book Name] The title of the book that you want to insert into the record" << "\n"
			 << "[Author] The Author of the book (Only one author is required)" << "\n"
			 << "[Reference alphabet] The reference character (R/G) that will be used to identify the book type" << "\n"
			 << "G -> General\nR -> Red Spot\n" << endl;
		
		inf.open("book_rec.dat");
		
		// This is to check how many records are currently in the file
		while (inf.good())
		{
			getline(inf >> ws, exist); // Use this format to read each line including the spaces
			count += 1; // Count the no. of lines that have been read
		}
		
		// The value of count we have received need to be divided by 3 to ignore the author and the ID for each book
		cout << "There are " << count/3 << " records in total currently." << endl; 
		inf.close();
		cout << endl;
		
		count = 0; // Reset the counter
		
		cout << "How many records do you wish to add? : "; // Ask the user if he wants to add specific no. of records
		cin >> newMax; // Store the value in newMax
		
		while (newMax <= 0) // The user should input at least 1 value in order to use this function
		{
			cout << "Invalid! At least one record must be entered" << endl;
			cout << "Enter the number of records: ";
			cin >> newMax;
		}
		
		Books *ptrLibr = new Books[newMax]; // Use a pointer and new func to request for a new size of an array of data struct
		cout << endl;
		
		for (int i = 0; i < newMax; i++) // Iterate the process using newMax limit
		{
			cout << "Enter book name : ";
			getline(cin >> ws, (ptrLibr + i) -> bookname); // Instead of using struct, we can also use single variable name
			
			cout << "Enter author : "; 
			getline(cin >> ws, (ptrLibr + i) -> author); 
			
			refNum = to_string((rand() % 10000) + 10000); // Random value 
			
			cout << "Enter reference alphabet : "; // Get the character from the user (refer to the Input Guidelines above)
			getline(cin >> ws, (ptrLibr + i) -> bookid);
			
			(ptrLibr + i) -> bookid += refNum; // Append the character with the refNum to create an unique ID for each book
			cout << endl;
		}
		
		outf.open("book_rec.dat", ios::app); // Use file based method to store the data and also append mode (ios::app) to add the data into the existing file
		//  Check the conn
		
		if (outf.fail()) // Might need to be removed
		{
			cout << "Sorry, the file can't be accessed at this moment. Please try again later." << endl;
			system ("pause");
			exit(1);
		}
		
		for (int i = 0; i < newMax; i++) // Paste the collected data into the file by using these specific format
		{
			outf << (ptrLibr + i) -> bookname << "\n"
				 << (ptrLibr + i) -> author << "\n"
				 << (ptrLibr + i) -> bookid << "\n";
		}
		
		cout << endl;
		outf.close();
		
		cout << "Book was successfully added into the record!" << endl;
		inf.open("book_rec.dat"); // Calculate the no. of records in the file after the appending process has been done
		
		while (inf.good())
		{
			getline(inf >> ws, exist);
			count += 1;
		}
		
		cout << count/3 << " records in total." << endl; // Display the current total of records
		inf.close();
		
		cout << "Do you wish to add more records? [Y/N] : "; // Ask the user if he wants to continue using this function (insertRecord)
		cin >> response;
		response = toupper(response); // Get the input from the user ('Y' or 'N'), if user enter lowercase letter ('n' or 'y'), toupper will replace it with uppercase letter 
		cout << endl;
		
	    while (response != 'Y' && response != 'N')
	    {
	      cout << "Invalid response. Only Y or N are allowed!" << endl;
	      cout << "Please re-enter : ";
	      cin >> response;
	      response = toupper(response);
	      cout << endl;
	    }
	}
}

// Programmer : Mohamad Faris Aiman Bin Mohd Faizal, Mohamad Syafiq Asyraf Bin Bharudin
void deleteRecord()
{
	int counter = 0;
	string id, search, author, line, title;
	char response;
	
	while (response != 'N')
	{
		cout << "Enter refID  of the book that you want delete : ";
		getline(cin >> ws,search); // Reading the inputs of users for name of search
		
		ifstream infile("book_rec.dat"); // Opening search records dat file for reading
		ofstream ofile("tmp.txt", ios::app); // Writing to temporary file before renaming to original file name.
		ofstream dfile("delete_rec.dat", ios::app);    
		
		while(getline(infile >> ws,title))
		{
			getline(infile >> ws, author);
			getline(infile >> ws, id);
			
			if(id == search)
			{ //If line equals to search,author and ID then we can delete the record
				dfile << title << "\n"
					  << author << "\n"
					  << id << "\n";
				dfile.close();
			}
			else
			{
				ofile << title << "\n";
				ofile << author << "\n";
				ofile << id << "\n";
			}
		}
		
		ofile.close();
		infile.close();
		
		remove("book_rec.dat"); // Remove the old file
		rename("tmp.txt", "book_rec.dat"); // Rename the temporary file to the original name.
		
		cout << "Do you want to delete other records? [Y/N] : ";
		cin >> response;
		response = toupper(response); // Get the input from the user ('Y' or 'N'), if user enter lowercase letter ('n' or 'y'), 
									  //toupper will replace it with uppercase letter 
		cout << endl;
		
	    while (response != 'Y' && response != 'N')
	    {
	      cout << "Invalid response. Only Y or N are allowed!" << endl;
	      cout << "Please re-enter : ";
	      cin >> response;
	      response = toupper(response);
	      cout << endl;
	    }
	}
}

// Programmer : Mohamad Faris Aiman Bin Mohd Faizal
void viewRecord() 
{
	string id, book, author, line;
	int counter = 0; // Counting number of rows.
	
	ifstream infile("book_rec.dat"); // Open the book records dat file.
	
	cout << "~ SHOWING ALL RECORDS AVAILABLE ~ : \n" << endl;
	
	while(getline(infile, book)) // I didn't use good() or eof(), it was causing duplicates at the end.
	{ 
		getline(infile, author);
		getline(infile, id);
		
		counter++;
		cout << counter << " | " << id << " | " << book << " | " << author << " | " << endl;
	}
	infile.close();
}

//Programmer Qasdina Azlin, Mohamad Faris Aiman Bin Mohd Faizal
void updateRecord()
{
	string id, search, author, line, title, updatedID, updatedTitle, updatedAuthor;
	char response;
	int input;
	  
	while(response != 'N')
	{
		ifstream infile("book_rec.dat");
		ofstream ofile("tmp.txt");
		    
		cout << "Enter bookID of the book that you want to update : ";
		getline(cin >> ws,search);
		cout << endl;
		
		cout << "Please choose on which component you want to update" << endl
			 << "[1] Update BookID" << endl
			 << "[2] Update Book Title" << endl
			 << "[3] Update Book Author" << endl;
			 
		cout << "Response : ";
		cin >> input;
		cout << endl;
		    
		while(getline(infile >> ws, title))
		{ // .eof() was causing duplicate at end of line.
			getline(infile >> ws, author);
			getline(infile >> ws, id);
			
			if(id == search)
			{
				if(input == 1)
				{
					ofstream ifile("updateID_rec.dat", ios::app);
					
					cout << "Enter updated BookID : "; // Reading input of users.
					getline(cin >> ws, updatedID);
          			cout << author << " " << title << endl;
					
					ifile << title << "\n"; // Writing details of updated to update_rec.dat
					ifile << author << "\n";
					ifile << updatedID << "\n";
					ifile.close(); // Close file so we can read the file. It will be opened when we ask for the response
					        
					ofile << title << "\n"; // Writing updated to tmp before changing to original
					ofile << author << "\n";
					ofile << updatedID << "\n";
				}
				
				else if(input == 2)
				{
					ofstream tfile("updateTitle_rec.dat", ios::app);
							
					cout << "Enter updated title : ";
					getline(cin >> ws, updatedTitle);
					
					tfile << updatedTitle << "\n"; // Writing details of updated to update_rec.dat
					tfile << author << "\n";
					tfile << id << "\n";
					tfile.close(); // Close file so we can read the file. It will be opened when we ask for the response
					        
					ofile << updatedTitle << "\n"; // Writing updated to tmp before changing to original
					ofile << author << "\n";
					ofile << id << "\n";
				}
				
				else if (input == 3)
				{
					ofstream afile("updateAuthor_rec.dat", ios::app);
					
					cout << "Enter update author : ";
					getline(cin >> ws, updatedAuthor);
					
					afile << title << "\n"; // Writing details of updated to update_rec.dat
					afile << updatedAuthor << "\n";
					afile << id << "\n";
					afile.close(); // Close file so we can read the file. It will be opened when we ask for the response
					        
					ofile << title << "\n"; // Writing updated to tmp before changing to original
					ofile << updatedAuthor << "\n";
					ofile << id << "\n";
				}
			}
			
			else
			{
				ofile << title << "\n"; // Other are also written to tmp
				ofile << author << "\n";
				ofile << id << "\n";
			}     
		}
		
		infile.close();
		ofile.close();
		
		remove("book_rec.dat");
		rename("tmp.txt", "book_rec.dat");
		
		cout << "Do you want to update other records? [Y/N] : ";
		cin >> response;
		response = toupper(response);
		cout << endl;
		
	    while (response != 'Y' && response != 'N')
	    {
	      cout << "Invalid response. Only Y or N are allowed!" << endl;
	      cout << "Please re-enter : ";
	      cin >> response;
	      response = toupper(response);
	      cout << endl;
	    }
	}
}
      	
//Programmer : Qasdina Azlin bt Azhar
void searchRecord()
{
	string id, book, author, line, search;
	char response;
	int counter =0;
		
	while (response != 'N')
	{
		cout << "Enter book ID you wish to search : "; //current book ID
		getline(cin >> ws, search);
		cout << endl;
				
		ifstream infile;
		infile.open("book_rec.dat"); //open book_rec.dat to read the text in the file
		counter = 0;
				
		while(!infile.eof())
		{
			getline(infile >> ws, book);
			getline(infile >> ws, author);
			getline(infile >> ws, id);
			// counter = 0;
				      
			if(id == search) 
			{
				cout << "Book ID " << search << " was found!\n";
				cout << book << " | " << author << " | " << id << endl;
				counter = 1;
				break;
			}
		}
		
		if(counter != 1)
		{
			cout << "Sorry, Book ID" << search << " can not be found!" << endl;
		}
		
		infile.close();
		cout << "\nDo you want to search other records? [Y/N] : ";
		cin >> response;
		response = toupper(response); // Get the input from the user ('Y' or 'N'), if user enter lowercase letter ('n' or 'y'), toupper will replace it with uppercase letter 
		cout << endl;
		
	    while (response != 'Y' && response != 'N')
	    {
	      cout << "Invalid response. Only Y or N are allowed!" << endl;
	      cout << "Please re-enter : ";
	      cin >> response;
	      response = toupper(response);
	      cout << endl;
	    }
	}
}

// Progammer : Mohamad Faris Aiman Bin Mohd Faizal, Maryam Siddiqui
void borrowBooks()
{
	string book, author, id, target, line;
	ofstream ofile;
	char response = 'Y';
		
	while (response != 'N')
	{
		cout << "Enter refID of the book you want to borrow :";
		getline(cin >> ws, target); // Reading the inputs of user for the target ID
		cout << endl;
		ifstream infile("available_rec.dat"); // Opening available_rec.dat to search for available books.
		ofstream ofile("tmp.dat", ios::app); // Writing to temporary file before renaming to original file name.
		ofstream bfile("borrowed_rec.dat", ios::app);  // Borrowed books written here to keep track.
		while(getline(infile >> ws, book))
		{
			getline(infile >> ws, author);
			getline(infile >> ws, id);
			
			if(id == target || author == target || book == target)
			{ //If target is equal to the ID, then it is book we want to borrow.
				cout << " | " << id << " | " << book << " | " << author << " | " << endl;
				
				bfile << book << "\n" // Writes to borrowed_rec.dat
					    << author << "\n"
					    << id << "\n";
				bfile.close();
			}
			else // Others are written to tmp.txt.
			{
				ofile << book << "\n";
				ofile << author << "\n";
				ofile << id << "\n";
			}
		}
    	infile.close();
		ofile.close();
		remove("available_rec.dat");
    	rename("tmp.dat", "available_rec.dat");
    	cout << endl;
    	
		cout << "Do you wish to borrow more books? [Y/N]: ";
		cin >> response;
		response = toupper(response); // Get the input from the user ('Y' or 'N'), if user enter lowercase letter ('n' or 'y'), toupper will replace it with uppercase letter 
		cout << endl;
		
	    while(response != 'N' && response != 'Y')
	    {
	      cout << "Invalid response. Only Y or N are allowed!" << endl;
	      cout << "Please re-enter: ";
	      cin >> response;
	      response = toupper(response);
	      cout << endl;
	    }
	}
}

//Programmer: Maryam Siddiqui & Qasdina Azlin
void availableBooks()
{
	string book, author, id, target, line;
	int counter = 0;
	
	ofstream ofile;
	ifstream ifile;
	
	ifile.open("available_rec.dat");
	while(getline(ifile >> ws, book))
	{ // We didn't use good() or eof(), it was causing duplicates at the end.
		getline(ifile >> ws,author);
		getline(ifile >> ws,id);
		    
		ofile << book << "\n"; //write details in tmp.txt file
		ofile << author << "\n";
		ofile << id << "\n"; 
		    
		counter++; //incrementing the records from one to another
		cout << counter << " | " << id << " | " << book << " | " << author << " | " << endl;
	}
	
	ifile.close();
	ofile.close();
}




