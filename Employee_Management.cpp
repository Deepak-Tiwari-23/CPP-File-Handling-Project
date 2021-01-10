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
	void set_data();
	void show_data();

	// File handling functions

	void add_employee();
	void show_all_data();
	bool search_employee(char*);
	void delete_employee(char*);
	void update_employee(char*);
};

void Employee::set_data()
{
	cout<<"Enter code of employee : "<<endl;
	cin>>code;
	cin.ignore();
	cout<<"Enter name of employee : "<<endl;
	cin.getline(name,19);
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
	std::fstream file;
	file.open("Employee_Data.txt",std::ios::binary|std::ios::app);
	if(!file)
	{
		cout<<"File not found !"<<endl;
		file.close();
		return;
	}
	file.write((char*)this,sizeof(*this));
	file.close();
	cout<<endl<<"Employee added successfully !"<<endl<<endl;
}

void Employee::show_all_data()
{
	ifstream in;
	in.open("Employee_Data.txt",ios::binary|ios::in);
	if(!in)
	{
		cout<<"File not found !"<<endl;
		in.close();
	}
	else
	{
		cout<<endl<<"             List of all employee !"<<endl<<endl;
		in.read((char*)this,sizeof(*this));
		while(!in.eof())
		{
			show_data();
			cout<<endl;
			in.read((char*)this,sizeof(Employee));
		}
		in.close();
	}
}

bool Employee::search_employee(char* t)
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
			if(strcmp(t,this->name)==0)
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
	bool ans = search_employee(t);
	if(ans == false)
		return;
	ifstream in;
	ofstream out;
	in.open("Employee_Data.txt",ios::in);	
	out.open("temp_file.txt",ios::binary|ios::out);
	in.read((char*)this,sizeof(*this));
	while(!in.eof())
	{
		if(strcmp(t,this->name)!=0)
		{
			out.write((char*)this,sizeof(*this));
		}
		in.read((char*)this,sizeof(*this));
	}
	cout<<endl<<"             Employee deleted successfully !"<<endl<<endl;
	in.close();
	out.close();
	remove("Employee_Data.txt");
	rename("temp_file.txt","Employee_Data.txt");
	
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
		int loc = file.tellg();
		file.read((char*)this,sizeof(*this));
		if(strcmp(t,this->name)==0)
		{
			set_data();
			file.seekp(loc);
			file.write((char*)this,sizeof(*this));
			break;
		}
	}
	file.close();
	cout<<endl<<"             Employee updated successfully !"<<endl<<endl;
}

int menu()
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
	Employee emp;
	char name[20];
	while(1)
	{
		system("cls");
		switch(menu())
		{
			case 1:
			{
				emp.add_employee();
				break;
			}
			case 2:
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
			case 4:
			{
				cout<<"Enter employee name : "<<endl;
				cin.ignore();
				cin.getline(name,19);
				emp.delete_employee(name);
				break;
			}
			case 5:
			{
				cout<<"Enter employee name : "<<endl;
				cin.ignore();
				cin.getline(name,19);
				emp.update_employee(name);
				break;
			}
			case 6:
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
					break;
				}
				else
					continue;
			}
			default:
			{
				cout<<"Invalid Choice !"<<endl;
			}
		}
		system("pause");
	}
	return 0;
}