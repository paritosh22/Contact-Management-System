#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;
class contact  {
    private: 
        char fname[50] , lname[50] , address[100] , email[50];
        long long phNo;

    public: 
    void createContact() {
        cout<<"Enter your first name: ";
        cin>>fname;

        cout<<"Enter your last name: ";
        cin>>lname;

        cout<<"Enter address: ";
        cin>>address;

        cout<<"Enter email: ";
        cin>>email;

        cout<<"Enter phone nummber: ";
        cin>>phNo;
        cout<<endl;
    }

    void showcontact() {
        cout<<"Name: "<<fname<<" "<<lname<<endl;
        cout<<"Address: "<<address<<endl;
        cout<<"Email :"<<email<<endl;
        cout<<"Phone Number :"<<phNo<<endl;
    }

    void writeonfile() {
        char ch;
        ofstream f1; 
        f1.open("CMS.dat" , ios::binary | ios::app);
        do{
            createContact();
            f1.write(reinterpret_cast<char*>(this), sizeof(*this));
            cout<<"Do you have next data? "<<endl;
            cout<<"(y/n) :";
            cin>>ch;
        }while(ch=='y');

        cout<<"Contact has been Successfully Created....";
        f1.close();
    }

    void readfromfile() {
        ifstream f2;
        f2.open("CMS.dat" , ios::binary);
        cout<<"-------------------------"<<endl;
        cout<<"LIST OF CONTACT"<<endl;
        cout<<"-------------------------"<<endl;

        while(!f2.eof()) {
            if(f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
                showcontact();
                cout<<"-------------------------"<<endl;
            }
        }
        f2.close();
    }

    void seacrhonfile() {
        ifstream f3;
        long long phone;
        cout<<"Enter the Phone Number to search: ";
        cin>>phone;
        f3.open("CMS.dat" , ios::binary);

        while(!f3.eof()) {
            if(f3.read(reinterpret_cast<char*>(this) , sizeof(*this))) {
                if (phone == phNo) {
                    showcontact();
                    return;
                }
            }
        }
        cout<<"No Record Found";
        f3.close();
    }

    void deletefromfile() {
        long long phone;
        int flag = 0;
        ofstream f4;
        ifstream f5;

        f5.open("CMS.dat" , ios::binary);
        f4.open("temp.dat" , ios::binary);

        cout<<"Enter the Phone number to delete: ";
        cin>>phone;

        while(!f5.eof()) {
            if(f5.read(reinterpret_cast<char*>(this) , sizeof(*this))) {
                if (phNo != phone) {
                    f4.write(reinterpret_cast<char*>(this), sizeof(*this));
                }
                else flag = 1;
            }
        }

        f4.close();
        f5.close();
        remove("CMS.dat");
        rename("temp.dat" , "CMS.dat");

        flag == 1 ?
        cout<<"Contact Deleted..."<<endl:
        cout<<"Contact Not Found..."<<endl;
    }

    void editContact() {
    long long phone;
    fstream f6;

    cout << "Edit Contact" << endl;
    cout << "-------------------------" << endl;
    cout << "Enter the phone number to be edited: ";
    cin >> phone;
    cout << endl;
    f6.open("CMS.dat", ios::binary | ios::in | ios::out);

    while (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (phone == phNo) {
            cout << "Contact Found" << endl;
            cout << "Enter New Record " << endl;
            createContact();

            int pos = f6.tellp() - sizeof(*this); 
            f6.seekp(pos); 
            f6.write(reinterpret_cast<char*>(this), sizeof(*this)); 
            cout << endl << endl << "Contact Successfully Updated..." << endl;
            return;
        }
    }

    cout << "No Record Found" << endl;
    f6.close();
}

};

int main(){
   system("cls");
   system("color 40");  //color XY , X = background color , Y = Text Color

   cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t ------- WELCOME TO CONTACT MANAGEMENT SYSTEM -------";
   getch();

   while(1) {
        contact c1;
        int choice;

        system("cls");
        system("color 0D");

        cout<<"CONTACT MANAGEMENT SYSTEM"<<endl;
        cout<<endl;
        cout<<"MAIN MENU"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"[1] Add a New Contact"<<endl;
        cout<<"[2] List ALL Contacts"<<endl;
        cout<<"[3] Search For Contacts"<<endl;
        cout<<"[4] Delete a Contact"<<endl;
        cout<<"[5] Update a Contact"<<endl;
        cout<<"[0] Exit"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>choice;

        switch(choice) {
            case 1:
            system("cls");
            c1.writeonfile();
            break;

            case 2:
            system("cls");
            c1.readfromfile();
            break;

            case 3:
            system("cls");
            c1.seacrhonfile();
            break;

            case 4:
            system("cls");
            c1.deletefromfile();
            break;

            case 5:
            system("cls");
            c1.editContact();
            break;

            case 0:
            system("cls");
            cout<<"\n\n\n\t\t --- Thank You For Using CMS ---"<<endl<<endl;
            exit(0);
            break;

            default: 
            continue;
        }

        int opt;
        cout<<"\n\n Enter the Choice:\n[1] Main Menu\t\t[0]Exit\n";
        cin>>opt;

        switch(opt) {
            case 0:
            system("cls");
            cout<<"\n\n\n\t\t----- Thank You For Using CMS -----"<<endl<<endl;
            exit(0);
            break;

            default: 
            continue;
        }
    }
    return 0;
}