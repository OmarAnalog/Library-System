#include <bits/stdc++.h>

using namespace std;
const int mxbooks=10;
const int mxusers=10;
bool ids_of_books[mxbooks+1][mxusers+1];
struct BOOKS
{
    int id=-1,quantity=0;
    string name="";
    int borrowed=0;
};
BOOKS book[mxbooks];
int added=0;
void add_book()
{
    cout<<"Enter book info: id & name & total quantity: ";
    cin>>book[added].id>>book[added].name>>book[added].quantity;
    added++;
}
void search_books_by_prefix()
{
    cout<<"Enter your name prefix: ";
    string prefix;
    cin>>prefix;
    int cnt=0;
    for(int indx=0; indx<added; indx++)
    {
        if ( (int)prefix.size()>(int) book[indx].name.size()   )
            continue;
        if ( book[indx].name.substr(0,(int)prefix.size())==prefix)
        {
            cout<<book[indx].name<<endl;
            cnt++;
        }
    }
    if (!cnt)
    {
        cout<<"There is no such book with such prefix"<<endl;
    }
}
void print_books()
{
    for(int indx=0; indx<added; indx++)
    {
        cout<<"id = "<<book[indx].id<<" name = "<<book[indx].name<<" total_quantity "<<book[indx].quantity<<
            " total_borrowed "<<book[indx].borrowed<<endl;
    }
}
int find_book_indx_by_name(string &name)
{
    for(int i=0; i<added; i++ )
    {
        if (name==book[i].name)
            return i;
    }
    return -1;
}
bool sort_by_id(BOOKS &fbook, BOOKS &sbook)
{
    if (fbook.id!=sbook.id)
        return fbook.id<sbook.id;
    return  fbook.name<=sbook.name;
}
print_library_by_id()
{
    sort(book,book+added,sort_by_id);
    print_books();
}
bool sort_by_name(BOOKS &fbook, BOOKS &sbook)
{
    if (fbook.name!=sbook.name)
        return fbook.name<sbook.name;
    return  fbook.id<=sbook.id;
}
print_library_by_name()
{
    sort(book,book+added,sort_by_name);
    print_books();
}
// Users Sections
struct USERS
{
    string name="";
    int national_id=-1;
    int borrowed_books_by_user[mxbooks];
    int len=0;
};
USERS users[mxusers];
int clients=0;
int is_borrowed(int user_id, int book_id)
{
    for(int i=0; i<users[user_id].len; i++)
    {
        if (book_id==users[user_id].borrowed_books_by_user[i])
            return i;
    }
    return -1;
}
void add_user()
{
    cout<<"Enter user name & national id: ";
    cin>>users[clients].name>>users[clients].national_id;
    clients++;
}
int find_user_indx_by_name(string &name)
{
    for(int i=0; i<clients; i++ )
    {
        if (name==users[i].name)
            return i;
    }
    return -1;
}
void user_borrow_book()
{
    cout<<"Enter user's name and book's name: ";
    string name,book_name;
    cin>>name>>book_name;
    int user_indx=find_user_indx_by_name(name);
    int book_indx=find_book_indx_by_name(book_name);
    if (user_indx==-1)
    {
        cout<<"Invalid user's name, please try again \n";
        return;
    }
    if (book_indx==-1)
    {
        cout<<"Invalid book, please try again \n";
        return;
    }
    int book_id = book[book_indx].id;
    int book_index_in_borrowed=is_borrowed(user_indx,book_id);
    if (book_index_in_borrowed!=-1)
    {
        cout<<"You borrowed this book before"<<endl;
        return;
    }
    if(users[user_indx].len==mxbooks)
    {
        cout<<"You can't borrow more books, as you exceeded the maximum number for borrowed books"<<endl;
        return;
    }
    users[user_indx].borrowed_books_by_user[users[user_indx].len++]=book_id;
    book[book_indx].borrowed++;
}
void shifting_left(int &deleted,int user_indx)
{
    int length=users[user_indx].len;
    for(int i=deleted+1;i<length;i++)
    {
        users[user_indx].borrowed_books_by_user[i-1]=users[user_indx].borrowed_books_by_user[i];
    }
}
void user_return_book()
{
    cout<<"Enter user's name and book's name: ";
    string name,book_name;
    cin>>name>>book_name;

    int user_indx=find_user_indx_by_name(name);
    int book_indx=find_book_indx_by_name(book_name);
    if (user_indx==-1)
    {
        cout<<"Invalid user's name, please try again \n";
        return;
    }
    if (book_indx==-1)
    {
        cout<<"Invalid book, please try again \n";
        return;
    }
    int user_id= users[user_indx].national_id;
    int book_id = book[book_indx].id;
    int book_index_in_borrowed=is_borrowed(user_indx,book_id);
    if (book_index_in_borrowed==-1)
    {
        cout<<"User "<<name<<" never borrowed this book"<<endl;
        return;
    }
    shifting_left(book_index_in_borrowed,user_indx);
    users[user_indx].len--;
    book[book_indx].borrowed--;
}
void print_users()
{
    cout<<"\n";
    for (int i = 0; i < clients; ++i)
    {
        cout << "user " << users[i].name << " id " << users[i].national_id << " borrowed books ids: ";
        for(int j=0;j<users[i].len;j++)
        {
            cout<<users[i].borrowed_books_by_user[j]<<" ";
        }
        cout<<endl;
    }
}


void print_who_borrowed_by_name()
{
    cout<<"Enter book's name: ";
    string name;
    cin>>name;
    int book_indx=find_book_indx_by_name(name);
    int book_id=book[book_indx].id;
    if (book_indx==-1)
    {
        cout<<"Invalid book's name, please try again."<<endl;
        return;
    }
    if (clients==0)
    {
        cout<<"There are no users"<<endl;
        return;
    }
    if(book[book_indx].borrowed==0)
    {
        cout<<"This book is not borrowed by anybody"<<endl;
        return;
    }
   for (int i = 0; i < clients; ++i)
    {
        for(int j=0;j<users[i].len;j++)
        {
            if(users[i].borrowed_books_by_user[j]==book_id)
            {
                cout<<users[i].name<<endl;
                break;
            }
        }
    }

}
void starting_menu()
{
    cout<<"\t\t\t\tWelcome To My Library\n"<<endl;
    cout<<"Library Menu;"<<endl;
    cout<<"1) add_book"<<endl;
    cout<<"2) search_books_by_prefix"<<endl;
    cout<<"3) print_who_borrowed_by_name"<<endl;
    cout<<"4) print_library_by_id"<<endl;
    cout<<"5) print_library_by_name"<<endl;
    cout<<"6) add_user"<<endl;
    cout<<"7) user_borrow_book"<<endl;
    cout<<"8) user_return_book"<<endl;
    cout<<"9) print_users"<<endl;
    cout<<"10) Exit"<<endl;
}
void Libiray_System()
{
    starting_menu();
    while(1)
    {
        cout<<"\nEnter your menu choice [1-10]: ";
        int choice;
        cin>>choice;

        if (choice==1)
        {
            add_book();
        }
        else  if (choice==2)
        {
            search_books_by_prefix();
        }
        else   if (choice==3)
        {
            print_who_borrowed_by_name();
        }
        else   if (choice==4)
        {
            print_library_by_id();
        }
        else   if (choice==5)
        {
            print_library_by_name();
        }
        else  if (choice==6)
        {
            add_user();
        }
        else if (choice==7)
        {
            user_borrow_book();
        }
        else if (choice==8)
        {
            user_return_book();
        }
        else if (choice==9)
        {
            print_users();
        }
        else
        {
            break;
        }
    }
}
int main()
{
    Libiray_System();
    return 0;
}
