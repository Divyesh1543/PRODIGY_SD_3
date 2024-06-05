#include<iostream>
#include<conio.h>
#include<fstream>

using namespace std;

class contact{
private:
    char fName[50], lName[50], address[50], email[50];
    long long phoneNo;

public:
    void createContacts(){
        cout<<"Enter First Name:";
        cin>>fName;

        cout<<"Enter Last Name:";
        cin>>lName;
        
        cout<<"Enter Phone Number:";
        cin>>phoneNo;
        
        cout<<"Enter Address:";
        cin>>address;
        
        cout<<"Enter Email:";
        cin>>email;
        
    }

    void showContact()
    {
        cout<<"Name: "<<fName<<" "<<lName<<endl;
        cout<<"Contact Number: "<<phoneNo<<endl;
        cout<<"Address: "<<address<<endl;
        cout<<"Email: "<<email<<endl;
    }

    void writeOnFile()
    {
        char ch;
        ofstream file1;
        file1.open("CMS.dat", ios::binary | ios::app);

        do{
            createContacts();
            file1.write(reinterpret_cast<char*>(this), sizeof(*this));
            cout<<"Another Details to Enter? (y/n)";
            cin>>ch;
        }while(ch=='y');

        cout<<"Contact has been saved...";
        file1.close();
    }
    
     void readFromFile(){
        ifstream file2;
        file2.open("CMS.dat", ios::binary);

        cout<<"\n************************\n";
        cout<<"List of Contacts :";
        cout<<"\n************************\n";


        while(!file2.eof())
        {
            if(file2.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                showContact();
                cout<<"\n**********************************\n";
            }
        }

        file2.close();
     }   

    void searchOnFile()
    {
        ifstream file3;
        long long phone;
        cout<<"Enter phone number :";
        cin>>phone;
        file3.open("CMS.dat", ios::binary);

        while(!file3.eof())
        {
            if(file3.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(phone==phoneNo)
                {
                    showContact();
                    return;
                }
            }
        }

        cout<<"No Contact has been Found....";
        file3.close();
    }

    void deleteFromFile()
    {
        long long phone;
        int flag=0;
        ofstream file4;
        ifstream file5;

        file5.open("CMS.dat", ios::binary);
        file4.open("temp.dat", ios::binary);

        cout<<"Enter phone number to delete from contacts :";
        cin>>phone;

        while(!file5.eof())
        {
            if(file5.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(phoneNo != phone)
                {
                    file4.write(reinterpret_cast<char*>(this), sizeof(*this));
                }

                else flag==1;
            }
        }

        file5.close();
        file4.close();
        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");

        flag == 1 ?
        cout<<"\t Contact Removed Successfully....":
        cout<<"\t Contact Not Found...";
    }

    void editContact()
    {
        long long phone;
        fstream file6;

        cout<<"Edit Contacts";
        cout<<"Enter Phone Number to Edit: ";
        cin>>phone;

        file6.open("CMS.dat", ios::binary|ios::out|ios::in);

        while(!file6.eof())
        {
            if(file6.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {   
                if(phone==phoneNo)
                {
                    cout<<"Enter new Record to add\n";
                    createContacts();

                    int pos= -1*sizeof(*this);
                    file6.seekp(pos, ios::cur);
                    file6.write(reinterpret_cast<char*>(this), sizeof(*this));
                    cout<<endl<<endl<<"\tContact Updated Successfully....";
                    return;
                }
            }
        }
        cout<<"\n\n No Record is Found";
        file6.close();
    }
};


int main()
{
    system("cls");
    system("Color 3F");

    cout<<"\n\n\n\n\n\t\t * Welcome to the Contact Management Sytem *";
    getch();

    while(1)
    {
        contact c1;
        int choice;

        system("cls");
        system("Color 03");

        cout<<"\n Contact Management System";
        cout<<"\n Main Menu";
        cout<<"\n*************************\n";
        cout<<"1. Add a new Contact\n";
        cout<<"2. List all Contacts\n";
        cout<<"3. Search for a Contact\n";
        cout<<"4. Delete a Contact\n";
        cout<<"5. Edit a Contact\n";
        cout<<"0. Exit\n";
        cout<<"\n*************************\n";
        cout<<"Enter your Choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
            system("cls");
            c1.writeOnFile();
            break;

            case 2:
            system("cls");
            c1.readFromFile();
            break;

            case 3:
            system("cls");
            c1.searchOnFile();
            break;

            case 4:
            system("cls");
            c1.deleteFromFile();
            break;

            case 5:
            system("cls");
            c1.editContact();
            break;

            case 0:
            system("cls");
            cout<<"\n\n\t\tThank You for Using CMS...."<<endl<<endl;
            exit(0);
            break;

            default:
            continue;
        }

        int option;
        cout<<"Enter the Choice:\n [1] Main Menu\t\t[0] Exit\n";
        cin>>option;

        switch(option)
        {
             case 0:
            system("cls");
            cout<<"\n\n\t\tThank You for Using CMS...."<<endl<<endl;
            exit(0);
            break;

            default:
            continue;
        }

    }

    return 0;
}