#include <iostream>
#include <cstdlib>
using namespace std;


//class Item----------------------------------------
class Item
{
private:
    int ID;
    static int serialOfItems; //counter of items
    string name;
    int quantity;
    double price;

public:
    //default constructor---------
    Item()
    {
        ID=serialOfItems++; //initialize ID for each item
        name="";
        quantity=0;
        price=0.0;


    }
    //default constructor--------




    //parameterized constructor---
    Item(string n,int q,double p)
    {
        ID=serialOfItems++;  //initialize ID for each item
        name=n;
        quantity=q;
        price=p;

    }
    //parameterized constructor----





    //copy constructor-----
    Item(const Item& obj)
    {
        ID=obj.serialOfItems;
        name=obj.name;
        quantity=obj.quantity;
        price=obj.price;
    }
    //copy constructor-----





    //setter and getter for name----
    void setName(string n)
    {
        name=n;
    }
    string getName()
    {
        return name;
    }
    //setter and getter for name----





    //setter and getter for quantity----
    void setQuantity(int q)
    {
        quantity=q;
    }
    int getQuantity()
    {
        return quantity;
    }
    //setter and getter for quantity----





    //setter and getter for price-----
    void setPrice(double p)
    {
        price=p;
    }
    double getPrice()
    {
        return price;
    }
    //setter and getter for price-----



    //Getter for static ID---------
    static int getID()
    {
        return serialOfItems;
    }
    //Getter for static ID---------





    //Operator overloading for the (==)operator
    bool operator ==(const Item &obj)
    {

        if(name==obj.name)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    //Operator overloading for the (==)operator




    //Operator overloading for the (+=)operator
    Item operator +=(const Item& obj2)
    {
        Item obj3;
        obj3.quantity=quantity+obj2.quantity;

        return obj3;
    }
    //Operator overloading for the (+=)operator





    //Operator overloading for the (-=)operator
    Item operator -=(int q)
    {
        Item obj3;
        obj3.quantity=quantity- q;

        return obj3;
    }
    //Operator overloading for the (-=)operator





    //Operator overloading for the (<<)operator
    friend ostream& operator<<(ostream& os, Item& obj)
    {
        os<<"["<<"Item's ID: "<<obj.ID<<" ,Item's Name: "<<obj.getName()<<" ,Item's Quantity: "<<obj.getQuantity();
        os<<" ,Item's Price: "<<obj.getPrice()<<"]";

        return os;
    }
    //Operator overloading for the (<<)operator






    //Operator overloading for the (>>)operator
    friend istream& operator>>(istream& is, Item& obj)
    {
        is>>obj.name>>obj.quantity>>obj.price;
        return is;
    }
    //Operator overloading for the (>>)operator





    friend class Seller;   //class seller a friend of class item


};





//class seller-----------------------------------
class Seller
{
private:
    int numOfItems; //count number of Items actually
    string name;
    string email;
    Item * item;
    int maxItems;
public:

    //parameterized constructor
    Seller(string n,string m,int MX):numOfItems(0)
    {

        name=n;
        email=m;
        maxItems=MX;
        item=new Item[maxItems];
        item[0].serialOfItems-=maxItems;  //subtract ID from capacity

    }
    //parameterized constructor



    Seller():numOfItems(0)
    {

    }


    //Operator overloading for the (<<)operator
    friend ostream& operator<<(ostream& os, Seller& obj)
    {
        os<<endl<<"Your Name is: "<<obj.name<<endl<<"Your Email is: "<<obj.email<<endl;
        return os;
    }
    //Operator overloading for the (<<)operator





    //AddItem Function-----------------
    bool addItem(const Item &obj)
    {
        bool status=false;



        for(int i=0;i<numOfItems;i++)
        {
            //if item actually exist
            if(item[i].name == obj.name)
            {
                item[i].quantity+=obj.quantity;
                status=true;
                break;

            }


        }
        //if item actually not exist
        if (status==false)
        {
            item[numOfItems++]=obj;
            status=true;
        }


        return status;
    }
    //AddItem Function-----------------






    //sellItem Function----------------
    bool sellItem(string n,int q)
    {
        bool status=false;
        for(int i=0;i<numOfItems;i++)
        {
            if(item[i].name==n)
            {
                // If the quantity is <= item’s quantity you will decrease it
                if(item[i].quantity>=q)
                {
                    item[i].quantity-=q;
                }
                //else: will print him “There is only {quantity} left for this item”
                else
                {
                    cout<<"There is only "<<item[i].quantity<<" left for this item";
                }
                status=true;
            }

        }
        return status;
    }
    //sellItem Function----------------






    //Print Items function----
    void printItems()
    {
        for(int i=0;i<numOfItems;i++)
        {
            cout<<endl<<item[i]<<" ";
        }
    }
    //Print Items function----




    //Find an Item by ID-----
    Item findItem(int id)
    {
        Item X;
        for (int i=0;i<numOfItems;i++)
        {
            if(id==item[i].ID)
            {
                X=item[i];

            }
        }
        return X;
    }
    //Find an Item by ID-----





    //Destructor-------
    ~Seller()
    {
        delete [] item;
    }
    //Destructor-------

};

int Item::serialOfItems=1;     //set serial ID starting with the first item of ID 1



int main()
{
    string Name,Email;
    int MaxOfItems,choose;

    //Ask the seller to input his details and his store capacity---
    cout<<"Hello,Seller..please Enter your Name: ";
    cin>>Name;
    cout<<"Enter your Email: ";
    cin>>Email;
    cout<<"Enter Your Store capacity: ";
    cin>>MaxOfItems;
    Seller S(Name,Email,MaxOfItems);    //create object from class seller



    while(true) //to display options continuously, and break when the seller enter exit
    {

        //options
        cout<<endl<<"1. Print My Info."<<endl;
        cout<<"2. Add An Item."<<endl;
        cout<<"3. Sell An Item."<<endl;
        cout<<"4. Print Items."<<endl;
        cout<<"5. Find an Item by ID"<<endl;
        cout<<"6. Exit"<<endl;

        cout<<endl<<"Enter your choice: ";
        cin>>choose;


        switch(choose)
        {
        case 1:
            cout<<S; //print Seller's Info
            break;
        case 2:
            {
                string name;
                int quantity;
                double price;

                //The seller enter name,quantity and price for The product to be added
                cout<<"Please Enter name of Item: ";
                cin>>name;
                cout<<"Enter quantity of Item: ";
                cin>>quantity;
                cout<<"Enter price of Item: ";
                cin>>price;


                Item i1(name,quantity,price);  //create object from class Item
                S.addItem(i1);                 //Aggregation --> (Add Items)
                break;
            }

        case 3:
            {

                //The seller enter name,quantity for The product to be sold
                string nameSell;
                int quantitySell;
                cout<<"Enter The Item name you want to sell it: ";
                cin>>nameSell;
                cout<<"Enter the sold quantity: ";
                cin>>quantitySell;


                S.sellItem(nameSell,quantitySell);  // --> (Sell Items)
                break;
            }

        case 4:
            {
                S.printItems();         //Print Items
                break;
            }
        case 5:
            {
                //Find Item by ID
                int ID;
                cout<<"Enter Id: ";
                cin>>ID;
                Item x=S.findItem(ID);
                cout<<x;            //print Item's Info
                break;
            }

        case 6:
            exit(0);            //When seller want to exit from program
        }



    }

    /*Seller S(Name,Email,MaxOfItems);

    cout<<S;
    Item i1("Milk",10,12.5);
    S.addItem(i1);

    S.printItems();

    S.sellItem("Milk",5);
    S.printItems();*/


    /*while (true)
    {
        cout<<"Choose From this list: "<<endl;
        cout<<"\t"<<

    }*/





    return 0;
}
