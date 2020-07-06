#include<conio.h>
#include<iostream>
#include<vector>
#include<iterator>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
int flag=1;
vector<int> code;
vector<string> stock_name;
vector<int> price;
vector<int> quantity;
vector<int> minimun_stock;
int line_no;
int total_bill=0;
int y=0;
void getdata();
void newstock();
void sales();
void purchase();
void showallstocks();
void edit();
void store();
void gst()
{
    float b,r;
    cout<<"Enter GST rates: ";
    cin>>r;
    b=total_bill*(r/100);
    cout<<"GST amount is: "<<b<<"\n Total Bill is: "<<total_bill+b;
}

void start()
{
    int a;
    cout<<"\nChoose from following:"<<endl;
    cout<<"1.Add new item"<<endl;
    cout<<"2.Sale"<<endl;
    cout<<"3.Purchase"<<endl;
    cout<<"4.Show all stock"<<endl;
    cout<<"5.Edit item details"<<endl;
    cout<<"6.Exit"<<endl;
    cin>>a;
    switch(a)
    {
    case 1:
        {
            newstock();
            break;
        }
    case 2:
        {
            sales();
            break;
        }
    case 3:
        {
            purchase();
            break;
        }
    case 4:
        {
            showallstocks();
            break;
        }
    case 5:
        {
            edit();
            break;
        }
    case 6:
        {
            flag=0;
            store();
            break;

        }
    }
}

void cheak(fstream &z)
{
    if(z.is_open())
    {
    }
    else
    {
        cout<<"couldn't open file";
        //loop to start again
    }
}

void store()
{
    {
    fstream codef("code.txt");
    ostream_iterator<int> output_iterator(codef,"\n");
    copy(code.begin(), code.end(), output_iterator);
    }
    {
    fstream name("name.txt");
    ostream_iterator<string> output_iterator(name,"\n");
    copy(stock_name.begin(), stock_name.end(), output_iterator);
    }
    {
        fstream pricef("price.txt");
        ostream_iterator<int> output_iterator(pricef,"\n");
        copy(price.begin(), price.end(), output_iterator);
    }
    {
        fstream qun("quantity.txt");
        ostream_iterator<int> output_iterator(qun,"\n");
        copy(quantity.begin(), quantity.end(), output_iterator);
    }
    {
        fstream mini("minimum.txt");
        ostream_iterator<int> output_iterator(mini,"\n");
        copy(minimun_stock.begin(), minimun_stock.end(), output_iterator);
    }
    if(flag==1)
    start();
    else
    {
        exit(0);
        _getch();
    }
}

void getdata()
{
    string s;
    int no;
    fstream codef("code.txt");
    cheak(codef);
    fstream name("name.txt");
    cheak(name);
    fstream quantityf("quantity.txt");
    cheak(quantityf);
    fstream pricef("price.txt");
    cheak(pricef);
    fstream mini("minimum.txt");
    cheak(mini);
    while(codef>>no)
    {
        code.push_back(no);
    }
    while(getline(name,s))
    {
        stock_name.push_back(s);
    }
    while(pricef>>no)
    {
        price.push_back(no);
    }
    while(quantityf>>no)
    {
        quantity.push_back(no);
    }
    while(mini>>no)
    {
        minimun_stock.push_back(no);
    }

}

void newstock()
{
    string new_name;
    cout<<"Enter Name of new item : ";
    cin>>new_name;
    stock_name.push_back(new_name);
    cout<<"Enter Price of item : ";
    int new_price;
    cin>>new_price;
    price.push_back(new_price);
    cout<<"Enter the quantity : ";
    int new_quantity;
    cin>>new_quantity;
    quantity.push_back(new_quantity);
    cout<<"Enter the minimum quantity : ";
    int new_min_quantity;
    cin>>new_min_quantity;
    minimun_stock.push_back(new_min_quantity);
    cout<<"Enter the code : ";
    int new_code;
    cin>>new_code;
    code.push_back(new_code);
    cout<<"new stock added succesfully"<<endl;
    store();
}

void sales()
{
    int j=0;
    cout<<"Enter customer name: ";
    string coustmer_name;
    cin>>coustmer_name;
    cout<<"Enter details of items "<<coustmer_name<<" purchased?";
    for(int i=0;i>=0;i++)
    {
        cout<<"\n Enter Item Code or Q to quit: ";
        string item_code;
        cin>>item_code;
        if(item_code=="Q")
        {
            if(j==0)
            {
                start();
            }
            else
            {
                break;
            }
        }
        else
        {
            j=1;
            stringstream g(item_code);
            int c=0;
            g>>c;
            vector<int>::const_iterator search_code= find(code.begin(), code.end(), c);
            if (search_code != code.end())
            {
                cout << "Code " << c <<" found " ;
                line_no =  search_code - code.begin() ;
            }
            else
                cout << "Element not found.\n\n";
            cout<<"You selected "<<stock_name[line_no]<<"\n\tPriced at "<<price[line_no]<<endl;
            cout<<"Enter Quantity : ";
            int get_quantity;
            cin>>get_quantity;
            if(get_quantity>quantity[line_no])
            {
                cout<<"Not enough stock";
                start();
            }
            else
            {
                quantity[line_no]=quantity[line_no]-get_quantity;
            }
            total_bill=total_bill+(price[line_no]*get_quantity);
        }

    }
    cout<<"Bill of "<<coustmer_name<<" is "<<total_bill;
    gst();
    store();
}

void purchase()
{
    int j=0;
    cout<<"Enter details of items you purchased?";
    for(int i=0;i>=0;i++)
    {
        cout<<"\n Enter Item Code or Q to quit: ";
        string item_code;
        cin>>item_code;
        if(item_code=="Q")
        {
            if(j==0)
            {
                start();
            }
            else
            {
                break;
            }
        }
        else
        {
            stringstream g(item_code);
            int c=0;
            g>>c;
            vector<int>::const_iterator search_code= find(code.begin(), code.end(), c);
            if (search_code != code.end())
            {
                cout << "Code " << c <<" found " ;
                line_no =  search_code - code.begin() ;
            }
            else
                cout << "Element not found.\n\n";
            cout<<"You selected "<<stock_name[line_no]<<"\n\tPriced at "<<price[line_no]<<endl;
            cout<<"Enter Quantity you purchased :";
            int get_quantity;
            cin>>get_quantity;
            quantity[line_no]=quantity[line_no]+get_quantity;
            total_bill=total_bill+(price[line_no]*get_quantity);
        }

    }
    cout<<"Bill of items you purchased is "<<total_bill;
    gst();
    store();
}

void showallstocks()
{
    cout<<"SL.NO\tCODE\t\tNAME\t\tQUANTITY\tPRICE\t\tMINIMUM STOCK"<<endl;
    for(int i=0;i<code.size();i++)
    {
        if(quantity[i]>minimun_stock[i])
        {
            cout<<i+1<<"\t"<<code[i]<<"\t\t"<<stock_name[i]<<"\t\t"<<quantity[i]<<"\t\t"<<price[i]<<"\t\t"<<minimun_stock[i]<<endl;
        }
        else
        {
            cout<<i+1<<"\t"<<code[i]<<"\t\t"<<stock_name[i]<<"\t\t"<<quantity[i]<<"\t\t"<<price[i]<<"\t\t"<<minimun_stock[i]<<"    low stock"<<endl;
        }
    }
    if(y==0)
    start();
}

void edit()
{
    y=1;
    showallstocks();
    y=0;
    cout<<"Enter line number you want to edit : ";
    cin>>line_no;
    cout<<"1.CODE"<<endl;
    cout<<"2.NAME"<<endl;
    cout<<"3.QUANTITY"<<endl;
    cout<<"4.PRICE"<<endl;
    cout<<"5.MINIMUM QUANTITY"<<endl;
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:
        {
            cout<<"Enter new CODE : ";
            cin>>choice;
            code[line_no-1]=choice;
            break;
        }
    case 2:
        {
            cout<<"Enter new NAME : ";
            string edit_name;
            cin>>edit_name;
            stock_name[line_no-1]=edit_name;
            break;
        }
    case 3:
        {
            cout<<"Enter new QUANTITY : ";
            cin>>choice;
            quantity[line_no-1]=choice;
            break;
        }
    case 4:
        {
            cout<<"Enter new PRICE : ";
            cin>>choice;
            price[line_no-1]=choice;
            break;
        }
    case 5:
        {
            cout<<"Enter new MINIMUM QUANTITY : ";
            cin>>choice;
            minimun_stock[line_no-1]=choice;
            break;
        }
    }
    store();
}

int main()
{
   getdata();
    start();
    _getch();
}
