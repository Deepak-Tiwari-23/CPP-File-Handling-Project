#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Employee
{
	char name[20];
	char address[20];
	int salary;
	int code;
public:
	Employee() //constructor 
	{
		code = 0;
		strcpy(name,"No title");
		salary = 0;
		strcpy(address,"Not found");
	}
	void set_data();  // function to take employee details
	void show_data();  // function to display data

	// File handling functions

	void add_employee();              // function to add a new employee
	void show_all_data();            //  function to show all employees
	bool search_employee(char*);    //   function to search an employee
	void delete_employee(char*);   //    function to delete an employee
	void update_employee(char*);  //     function to update an existing employee
};

void Employee::set_data()
{
	cout<<"Enter code of employee : "<<endl;
	cin>>code;
	cin.ignore();  // to clear the buffer of previous variable
	cout<<"Enter name of employee : "<<endl;
	cin.getline(name,19);  // function to get a string input
	cout<<"Enter salary of employee : "<<endl;
	cin>>salary;
	cin.ignore();
	cout<<"Enter address of employee : "<<endl;
	cin.getline(address,19);
}

void Employee::show_data()
{
	cout<<"Employee Code    : "<<code<<endl;
	cout<<"Employee Name    : "<<name<<endl;
	cout<<"Employee Salary  : "<<salary<<endl;
	cout<<"Employee Address : "<<address<<endl;
}

void Employee::add_employee()
{
	set_data();
	std::fstream file;  // creating an object  of fstream class
	file.open("Employee_Data.txt",std::ios::binary|std::ios::app);
	if(!file)
	{
		cout<<"File not found !"<<endl;
		file.close();
		return;
	}
	file.write((char*)this,sizeof(*this));  // "this" represents current object and write function writes the provided data in the file
	file.close();
	cout<<endl<<"Employee added successfully !"<<endl<<endl;
}

void Employee::show_all_data()
{
	ifstream in;  // creating an object of ifstream class
	in.open("Employee_Data.txt",ios::binary|ios::in);
	if(!in)
	{
		cout<<"File not found !"<<endl;
		in.close();
	}
	else
	{
		cout<<endl<<"             List of all employee !"<<endl<<endl;
		in.read((char*)this,sizeof(*this));  // reading the data from the file in object format
		while(!in.eof())
		{
			show_data();
			cout<<endl;
			in.read((char*)this,sizeof(Employee));
		}
		in.close();
	}
}

bool Employee::search_employee(char* t)  // return true if searched employee is present in the file, else false
{
	int c=0;
	ifstream in;
	in.open("Employee_Data.txt",ios::binary|ios::in);
	if(!in)
	{
		cout<<"File not found !"<<endl;
		in.close();
	}
	else
	{
		in.read((char*)this,sizeof(*this));
		while(!in.eof())
		{
			if(strcmp(t,this->name)==0)  // if the searched name an current object name are same
			{
				cout<<endl<<"             Employee found !"<<endl<<endl;
				show_data();
				cout<<endl;
				c++;
				in.close();
				return true;
			}
			in.read((char*)this,sizeof(*this));
		}
		if(c==0)
			cout<<endl<<"             Employee not found !"<<endl;
		in.close();
		return false;
	}
	return false;
}

void Employee::delete_employee(char* t)
{
	bool ans = search_employee(t);  // first search the employee,if not present then simply exit
	if(ans == false)
		return;
	ifstream in;
	ofstream out;
	in.open("Employee_Data.txt",ios::in);	
	out.open("temp_file.txt",ios::binary|ios::out);  // this creates a new empty text file with name as temp_file
	in.read((char*)this,sizeof(*this));
	while(!in.eof())
	{
		if(strcmp(t,this->name)!=0)  // skipping the employee to be deleted
		{
			out.write((char*)this,sizeof(*this));  // copying the data from main file to the temporary file
		}
		in.read((char*)this,sizeof(*this));
	}
	cout<<endl<<"             Employee deleted successfully !"<<endl<<endl;
	in.close();
	out.close();
	remove("Employee_Data.txt");  // deleting the main file
	rename("temp_file.txt","Employee_Data.txt");  // making the temporary file as main file
	
}

void Employee::update_employee(char* t)
{
	bool ans = search_employee(t);
	if(ans == false)
		return;
	fstream file;
	file.open("Employee_Data.txt",ios::in|ios::out|ios::binary);
	
	while(!file.eof())
	{
		int loc = file.tellg();  // storing the current location of file pointer
		file.read((char*)this,sizeof(*this));
		if(strcmp(t,this->name)==0)
		{
			set_data();
			file.seekp(loc);  // pointing to the desired location by using "loc" variable
			file.write((char*)this,sizeof(*this));  // updating the data
			break;
		}
	}
	file.close();
	cout<<endl<<"             Employee updated successfully !"<<endl<<endl;
}

int menu()  // function to show menu to the user. It returns the selected option number
{
	int select;
	cout<<endl;
	cout<<"                                    --------------------------------------------                                    "<<endl;
	cout<<"                                             EMPLOYEE MANAGEMENT SYSTEM                                             "<<endl;
	cout<<"                                    --------------------------------------------                                    "<<endl;
	cout<<endl;
	cout<<"                                    ============================================                                    "<<endl;
	cout<<"                                                 SELECT YOUR CHOICE                                                 "<<endl;
	cout<<endl<<endl;
	cout<<"                                         1. Add New Employee                                                        "<<endl;
	cout<<"                                         2. Search Employee                                                         "<<endl;
	cout<<"                                         3. Show All Employees                                                      "<<endl;
	cout<<"                                         4. Delete Employee                                                         "<<endl;
	cout<<"                                         5. Update Employee                                                         "<<endl;
	cout<<"                                         6. Exit                                                                    "<<endl;
	cout<<endl<<endl;
	cout<<"                                    ============================================                                    "<<endl;
	cin>>select;
	return select;
}

int main()
{	
	Employee emp;  // creating an object of employee class
	char name[20];
	while(1)  // infinite loop
	{
		system("cls");  // to clear the screen
		switch(menu())  // switch case for selected option
		{
			case 1:  // if user wants to add new employee
			{
				emp.add_employee();
				break;
			}
			case 2:  // if user wants to search an employee
			{
				cout<<"Enter employee name : "<<endl;
				cin.ignore();
				cin.getline(name,19);
				bool ans = emp.search_employee(name);
				break;
			}
			case 3:
			{
				emp.show_all_data();
				break;
			}
			case 4:  // if user wants to delete an employee
			{
				cout<<"Enter employee name : "<<endl;
				cin.ignore();
				cin.getline(name,19);
				emp.delete_employee(name);
				break;
			}
			case 5:  // if user wants to update an employee
			{
				cout<<"Enter employee name : "<<endl;
				cin.ignore();
				cin.getline(name,19);
				emp.update_employee(name);
				break;
			}
			case 6:  // if user wants to exit the program
			{
				cout<<"Thank You For Using This System"<<endl;
				cout<<endl<<"Do you really want to exit ? "<<endl;
				cout<<endl<<"  1.Confirm        2.Cancel "<<endl;
				int c = 0;
				cin>>c;
				if(c==1)
				{ 
					system("cls");
					exit(0);
					break;  // breaking the infinite loop
				}
				else
					continue;
			}
			default:  // if user enter an invalid number in menu
			{
				cout<<"Invalid Choice !"<<endl;
			}
		}
		system("pause");  // halts the main program and ask an input from user to continue
	}
	return 0;
}