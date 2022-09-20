#include <iostream>
#include <map>
#include <fstream>
#include <sqlite3.h>
#define maxSeat 60
static int ticket_no_original = 2021;
using namespace std;

int count = 0;

struct node
{
    int Ticket_no, Price, Age;
    string Name, Location, Destination;
    node *next;
} * head;
string PUT_LOCATION(int a)
{
    map<int, string> location;
    location[1] = "K.L.E";
    location[2] = "Kalamboli Colony";
    location[3] = "MGM Hospital";
    location[4] = "Asudgown";
    location[5] = "Khanda Colony";
    location[6] = "Garden Hotel";
    location[7] = "St Bus Depo";
    location[8] = "Panvel Station";
    return location[a];
}
string PUT_DESTINATION(int b)
{
    map<int, string> destination;
    destination[1] = "K.L.E";
    destination[2] = "Kalamboli Colony";
    destination[3] = "MGM Hospital";
    destination[4] = "Asudgown";
    destination[5] = "Khanda Colony";
    destination[6] = "Garden Hotel";
    destination[7] = "St Bus Depo";
    destination[8] = "Panvel Station";
    return destination[b];
}
int CHARGE(int age, int a, int b)
{
    int charge;
    if (a == b)
    {
        charge = 0;
    }

    if (a < b)
    {
        if (age < 15)
        {
            if (b == a + 3 || b == a + 2 || b == a + 1)
            {
                charge = 5;
            }
            else if (b == a + 4 || b == a + 5)
            {
                charge = 7;
            }
            else
            {
                charge = 9;
            }
        }
        else
        {
            if (b == a + 3 || b == a + 2 || b == a + 1)
            {
                charge = 7;
            }
            else if (b == a + 4 || b == a + 5)
            {
                charge = 9;
            }
            else
            {
                charge = 11;
            }
        }
    }
    else
    {
        if (age < 15)
        {
            if (b == a - 3 || b == a - 2 || b == a - 1)
            {
                charge = 5;
            }
            else if (b == a - 4 || b == a - 5)
            {
                charge = 7;
            }
            else
            {
                charge = 9;
            }
        }
        else
        {
            if (b == a - 3 || b == a - 2 || b == a - 1)
            {
                charge = 7;
            }
            else if (b == a - 4 || b == a - 5)
            {
                charge = 9;
            }
            else
            {
                charge = 11;
            }
        }
    }

    return charge;
}
void BOOKING(int age, string name, int location, int destination)
{
    count++;
    node *a;
    a = new node();
    a->Age = age;
    a->Name = name;
    a->Location = PUT_LOCATION(location);
    a->Destination = PUT_DESTINATION(destination);
    a->Ticket_no = ticket_no_original;
    ticket_no_original++;
    a->Price = CHARGE(a->Age, location, destination);
    if (head == NULL)
    {
        head = a;
        return;
    }
    else
    {
        node *t;
        t = head;
        while (t->next != NULL)
        {
            t = t->next;
        }
        t->next = a;
        a->next = NULL;
    }
}
void ALL_FILE_PRINT()
{
    fstream fio;
    fio.open("TICKET.txt", ios::app);
    if (head == NULL)
    {
        fio << "No Booking are avaliable to display \n\n";
        return;
    }
    node *t;
    t = head;
    while (t != NULL)
    {
        fio << "Ticket No :-";
        fio << t->Ticket_no << endl;
        fio << "Name :-";
        fio << t->Name << "\t";
        fio << "Age :-";
        fio << t->Age << endl;
        fio << "Location :-";
        fio << t->Location << "\t";
        fio << "Destination:-";
        fio << t->Destination << endl;
        fio << "Price:-";
        fio << t->Price << "\n\n";
        t = t->next;
        fio << "Have a safe Journy\n\n";
    }
    cout << "All data saved";
    fio.close();
}
void PRINT()
{
    if (head == NULL)
    {
        cout << "No Booking are avaliable to display \n\n";
        return;
    }
    node *t;
    t = head;
    while (t != NULL)
    {
        cout << "Ticket No :-" << t->Ticket_no << endl;
        cout << "Name :-" << t->Name << "\t";
        cout << "Age :-" << t->Age << endl;
        cout << "Location :-" << t->Location << "\t";
        cout << "Destination:-" << t->Destination << endl;
        cout << "Price:-" << t->Price << "\n\n";
        t = t->next;
    }
    cout << "Have a safe Journy\n";
}

void UPDATE(int ticket_no)
{
    node *t;
    if (head == NULL)
    {
        cout << "No Booking are avaliable to Update \n\n";
        return;
    }
    else
    {
        t = head;
        while (t != NULL)
        {
            if (t->Ticket_no == ticket_no)
            {
                int a, b;
                cout << "Enter UPDATED Name :\n";
                cin >> t->Name;
                cout << "Enter UPDATED Age :\n";
                cin >> t->Age;
                cout << "Enter UPDATED Location No.:\n";
                cin >> a;
                t->Location = PUT_LOCATION(a);
                cout << "Enter UPDATED Destination No.:\n";
                cin >> b;
                t->Destination = PUT_DESTINATION(b);
                t->Price = CHARGE(t->Age, a, b);
                cout << endl;
                return;
            }
            t = t->next;
        }
    }
    cout << "Sorry We are unable to find your Booked Ticket !! Make Sure enterd Ticket No is correct !!";
}

void CANCEL(int ticket_no)
{
    count--;

    if (head == NULL)
    {
        cout << "No Booking are avaliable to Cancel ";
        return;
    }
    else if (head->Ticket_no == ticket_no)
    {
        node *t;
        t = head;
        cout << "Ticket has been canceled:\n";
        head = head->next;
        delete t;
        return;
    }
    node *t, *p;
    t = head;
    while (t != NULL)
    {
        p = t;
        t = t->next;
        if (t->Ticket_no == ticket_no)
        {
            if (t->next == NULL)
            {
                p->next = NULL;
                free(t);
                cout << "Ticket has been canceled:\n\n";
                return;
            }
            else
            {
                node *a;
                a = t->next;
                p->next = a;
                delete t;
                cout << "Ticket has been canceled:\n";
                return;
            }
        }
    }
}

int main()
{
    sqlite3 *db;

    cout << "Welcome to Sush Travels\n";
    int age, location, destination;

    string name;
    cout << "We Provides Bus Service Between these Location\nPlease Enter Stop No for Location And Destinantin Same as Display:-\n";
    cout << " 1] K.L.E \n 2] Kamaboli Colony\n 3] MGM Hospital\n 4] Asudgown\n 5] Khanda Colony\n 6] Garden Hotel\n 7] St Bus Depo\n 8] Panvel Station\n";
    cout << "Enter Your Choise -\n";
    int ch, ticket_no;
    do
    {
        cout << "1] BOOK YOUR TICKET -\n";
        cout << "2] CANCEL YOUR TICKET -\n";
        cout << "3] UPDATE YOUR TICKET -\n";
        cout << "4] SHOW ALL BOOKINGS -\n";
        cout << "5] CANCEL PROCESS -\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            if (maxSeat == count)
            {
                cout << "Bus is full, No seat avaliable for booking \n";
            }

            cout << "\n";
            cout << "Enter Your Name :\n";
            cin >> name;
        jump:
            cout << "Enter Your Age :\n";
            cin >> age;
            if (age < 1)
            {
                cout << "Age cant be 0 or Less than 0 :\n";
                goto jump;
            }
        jump1:
            cout << "Enter Your Location No.:\n";
            cin >> location;
            if (location >= 9 || location <= 0)
            {
                cout << "Entered Location No is not correct\nPlease Check again !!\n";
                goto jump1;
            }
        jump2:
            cout << "Enter Your Destination No.:\n";
            cin >> destination;
            if (destination >= 9 || destination <= 0)
            {
                cout << "Entered Destination No is not correct\nPlease Check again !!\n";
                goto jump2;
            }
            BOOKING(age, name, location, destination);
            cout << endl;
            cout << "Your Tecket has been Booked \nHave a safe Journy\n\n\n";
            break;
        case 2:
            if (head == NULL)
            {
                cout << "\nNo Booking are avaliable to Cancel \n\n";
                break;
            }
            cout << "\n";
            cout << "Enter Your Ticket No to Cancel ticket\n";
            cin >> ticket_no;
            CANCEL(ticket_no);

            break;
        case 3:
            if (head == NULL)
            {
                cout << "\nNo Booking are avaliable to Update \n\n";
                break;
            }
            cout << "\n";
            cout << "Enter Your Ticket No to Update ticket\n";
            cin >> ticket_no;
            UPDATE(ticket_no);
            break;
        case 4:
            cout << "\n";
            PRINT();
            cout << endl;
            break;
        case 5:
            goto jump3;
        default:
            cout << "\n";
            cout << "Enter A Valid Input \nTry Again !!\n";
            break;
        }
    } while (true);
jump3:
    cout << "Do you want to Save data into File\nPress 1 for yes:-";
    int ch1;
    cin >> ch1;
    if (ch1 == 1)
    {
        ALL_FILE_PRINT();
    }

    return 0;
}