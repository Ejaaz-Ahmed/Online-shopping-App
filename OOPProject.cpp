#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include<sstream>
using namespace std;
//ejaz's code
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    scrn.X = cpos;
    scrn.Y = rpos;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, scrn);
}
void sleep(int milliseconds)
{
    Sleep(milliseconds);
}
void drawBox(int top, int left, int width, int height)
{
    for (int i = 0; i <= width; ++i)
    {
        gotoRowCol(top, left + i);
        cout << (i == 0 ? '+' : (i == width ? '+' : '-'));
        gotoRowCol(top + height, left + i);
        cout << (i == 0 ? '+' : (i == width ? '+' : '-'));
    }
    for (int i = 1; i < height; ++i)
    {
        gotoRowCol(top + i, left);
        cout << '|';
        gotoRowCol(top + i, left + width);
        cout << '|';
    }
}
void displayDigitalMerchantsInBox()
{
    string name = "Digital Merchants";
    int nameLength = name.length();
    int boxWidth = nameLength + 4;
    int boxHeight = 3;
    int startRow = 2;
    int startCol = 10;
    drawBox(startRow, startCol, boxWidth, boxHeight);
    gotoRowCol(startRow + 1, startCol + 2);
    cout << name;
}
const int max_size = 100;
const int MAX_CUSTOMERS = 100;
//raza's code
class Customer
{
private:
    string username;
    string password;
    string name;
    string email;
public:
    Customer() {}
    void setData(const string& username, const string& password, const string& name, const string& email) {
        this->username = username;
        this->password = password;
        this->name = name;
        this->email = email;
    }
    string getUsername() const
    {
        return username;
    }
    string getPassword() const
    {
        return password;
    }
    string getName() const
    {
        return name;
    }
    string getEmail() const
    {
        return email;
    }
    void saveToFile()
    {
        ofstream file("customers.txt", ios::app);
        if (file.is_open())
        {
            file << username << "," << password << "," << name << "," << email << endl;
            file.close();
        }
        else
        {
            cerr << "Error: Unable to open file 'customers.txt' for writing." << endl;
        }
    }
    static Customer* login(const string& username, const string& password)
    {
        ifstream file("customers.txt");
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file 'customers.txt' for reading." << endl;
            return nullptr;
        }
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string savedUsername, savedPassword;
            getline(iss, savedUsername, ',');
            getline(iss, savedPassword, ',');
            if (savedUsername == username && savedPassword == password)
            {
                string savedName, savedEmail;
                getline(iss, savedName, ',');
                getline(iss, savedEmail);
                Customer* customer = new Customer();
                customer->setData(savedUsername, savedPassword, savedName, savedEmail);
                file.close();
                return customer;
            }
        }
        file.close();
        return nullptr;  // Login failed
    }
    static void getAllCustomers()
    {
        ifstream file("customers.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << "Customer: " << line << endl;
            }
            file.close();
        }
        else
        {
            cerr << "Error: Unable to open file 'customers.txt' for reading." << endl;
        }
    }
};
class CustomerSupportChat
{
private:
    string customerName;
    string response;
public:
    CustomerSupportChat() {}
    void setResponse(const string& customerName, const string& response)
    {
        this->customerName = customerName;
        this->response = response;
    }
    void saveToFile()
    {
        ofstream file("responses.txt", ios::app);
        if (file.is_open())
        {
            file << customerName << ": " << response << endl;
            file.close();
        }
        else
        {
            cerr << "Error: Unable to open file 'responses.txt' for writing." << endl;
        }
    }
    static void getAllResponses()
    {
        ifstream file("responses.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cerr << "Error: Unable to open file 'responses.txt' for reading." << endl;
        }
    }
};
//ejaz's code
class Product
{
public:
    string name;
    double price;
    float rating;
    int numberofreviews;
    Product()
    {
        name = "0";
        price = 0.0;
        rating = 0.0;
        numberofreviews = 0;
    }
   Product(string productname, double productprice)
   {
        name = productname;
        price = productprice;
        rating = 0.0;
        numberofreviews = 0;
   }
   string getproduct()
    {
        return name;
    }
   double getprice()
    {
        return price;
    }
   float getrating()
    {
        return rating;
    }
   void addreview(double ratingvalue)
    {
        rating = (rating * numberofreviews + ratingvalue) / (numberofreviews + 1);
        numberofreviews++;
    }
   void display()
    {
        cout << name << " " << price << " " << rating << " " << numberofreviews << endl;
    }
};
//sabeeh's code
//Both of these functions are used for sorting in the next functions.
bool compareByName(Product a, Product b)
{
    return a.getproduct() < b.getproduct();
}
bool compareByPrice(Product a, Product b)
{
    return a.getprice() < b.getprice();
}
bool compareByRating(Product a,Product b)
{
    return a.getrating()<b.getrating();
}
//ejaz's code
class OnlineShoppingSystem
{
public:
    Product products[max_size];
    int numofproducts;
    OnlineShoppingSystem()
    {
        numofproducts = 0;
    }
  void addproduct(Product product)
{
    if (numofproducts < max_size)
    {
        products[numofproducts] = product;
        numofproducts++;
    }
}
   void sellproduct(string productname, double productprice)
   {
        if (numofproducts < max_size)
        {
            Product newproduct(productname, productprice);
            addproduct(newproduct);
            cout << "The product is: " << productname << " and its price is: " << productprice << endl;
        }
        else
        {
            cout << "Maximum number of products reached." << endl;
        }
    }
   void buyproduct(string productname)
   {
        for (int i = 0; i < numofproducts; i++)
            {
            if (products[i].getproduct() == productname)
            {
                cout << "You have purchased product: " << productname << " for the price of " << products[i].getprice() << endl;
                cout << endl;
                cout << "your bill is " << products[i].getprice() << endl;
                return;
            }
            }
        cout << "Product " << productname << " is not available in the store." << endl;
    }
  void reviewproduct(string productname, double ratingvalue)
    {
        for (int i = 0; i < numofproducts; i++)
            {
            if (products[i].getproduct() == productname)
            {
                products[i].addreview(ratingvalue);
                cout << "You have reviewed the product: " << productname << " with the rating of " << ratingvalue << endl;
                return;
            }
            }
        cout << productname << " is not available in the store." << endl;
    }

    void displayproducts()
    {
        for (int i = 0; i < numofproducts; i++)
        {
            products[i].display();
        }
    }
    //sabeeh's code
// here i will simply pass that functions as a comparator, it is allowed because of the algorithm library i have added in the top
    void sortProductsByName()
    {
        sort(products, products + numofproducts, compareByName);
    }//matlab mne products[0] se start kia ha aur products[numofproducts] pe end kia ha
   void sortProductsByPrice()
   {
        sort(products, products + numofproducts, compareByPrice);
   }
   void searchProduct(string productName)
   {
        for (int i = 0; i < numofproducts; i++)
            {
            if (products[i].getproduct() == productName)
            {
                cout << "Product found: ";
                products[i].display();
                return;
            }
            }
        cout << "Product not found." << endl;
    }
    void suggestProductsBasedOnRating()
    {
        sort(products,products+numofproducts,compareByRating);
        cout<<"Top 3 products based on ratings are: "<<endl;
        for(int i=0; i<3; i++)
            {
            if(i<numofproducts)
            {
                products[i].display();
            }
            }
    }
};
void saveproductinfile(Product products[], int numofproducts, string filename){
    ofstream file(filename.c_str());
    if (file.is_open()){
        for (int i = 0; i < numofproducts; i++)
            {
            file << products[i].name << " " << products[i].price << endl;
            }
        file.close();
        cout << "Products are saved in " << filename << endl;}
    else
        {
        cout << "Unable to open file " << filename << endl;
        }
}
void loadproductsfromfile(OnlineShoppingSystem& shop, const string& filename)
{
    ifstream file(filename.c_str());
    if (file.is_open())
        {
        string productname;
        double productprice;
        while (file >> productname >> productprice){
            Product newproduct(productname, productprice);
            shop.addproduct(newproduct);}
        file.close();
        cout << "Products are successfully loaded from file." << endl;
        }
    else
        {
        cout << "Unable to open file " << filename << endl;
        }
}
//nayar's code
class bank_card
{
private:
    string card_number;
    string card_holder_name;
    string expiry_date;
    string cvv;
public:
    void configure_bank_card()
    {
        cout << endl;
        cout << "enter the card number: ";
        cin >> card_number;
        cout << "enter card holder name: ";
        cin >> card_holder_name;
        cout << "enter expiry date (MM/YY): ";
        cin >> expiry_date;
        cout << "enter CVV: ";
        cin >> cvv;
        cout << endl;
    }
    void display_bank_card_info()
    {
        int a;
        cout << "here are the bank card details:" << endl;
        cout << endl;
        cout << "card number: " << card_number << endl;
        cout << "card holder name: " << card_holder_name << endl;
        cout << "expiry date: " << expiry_date << endl;
        cout << "CVV: " << cvv << endl;
        cout << endl;
        cout << "for configuration, press 1 to confirm your payment: ";
        cin >> a;
        if(a == 1)
        {
            cout << endl;
            cout << "payment done!" << endl;
            save_payment_info();
        }
        else
        {
            cout << endl;
            cout << "payment not confirmed" << endl;
            cout << "enter the information again" << endl;
            configure_bank_card();
        }
        cout << endl;
    }
    void save_payment_info()
    {
        ofstream outfile("payments.txt", ios::app);
        if (outfile.is_open())
        {
            outfile << "bank card payment" << endl;
            outfile << "card number: " << card_number << endl;
            outfile << "card holder name: " << card_holder_name << endl;
            outfile << "expiry date: " << expiry_date << endl;
            outfile << "CVV: " << cvv << endl;
            outfile << "--------------------------" << endl;
            outfile.close();
        }
        else
        {
            cout << "unable to open file to save payment information." << endl;
        }
    }
};
class other_methods
{
private:
    string name;
    int a;
    int amount;
public:
    void configure_other_method()
    {
        cout << endl;
        cout << "select your choice from above: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            name = "PayPal";
            break;
        case 2:
            name = "cash on delivery";
            break;
        case 3:
            name = "Jazz Cash";
            break;
        case 4:
            name = "Easy Paisa";
            break;
        default:
            cout << "invalid choice ... please select a valid payment method" << endl;
            configure_other_method();
            return;
        }
        cout << endl;
        cout << "Payment method selected: " << name << endl;
        cout << endl;
        cout << "please enter the amount: ";
        cin >> amount;
        cout << endl;
        cout << "for configuration, press 1 to confirm your payment: ";
        cin >> a;
        if(a == 1)
        {
            cout << endl;
            cout << "payment done!" << endl;
            cout << endl;
            save_payment_info();
        }
        else
        {
            cout << "payment not confirmed" << endl;
            cout << "enter the information again" << endl;
            configure_other_method();
        }
    }
    void display_info()
    {
        cout << "here is your payment info!" << endl;
        cout << "your total amount is: " << amount << endl;
        cout << endl;
    }
    void save_payment_info()
    {
        ofstream outfile("payments.txt", ios::app);
        if (outfile.is_open())
        {
            outfile << "other method payment" << endl;
            outfile << "payment method: " << name << endl;
            outfile << "amount: " << amount << endl;
            outfile << "--------------------------" << endl;
            outfile.close();
        }
        else
        {
            cout << "unable to open file to save payment information" << endl;
        }
    }
};
class payment
{
private:
    bank_card b;
    other_methods o;
    int type;
public:
    void display_options()
    {
        cout << "select a payment method type:" << endl;
        cout << "1. Bank Card" << endl;
        cout << "2. Other Methods" << endl;
    }
    void configure_payment()
    {
        cout << "enter your choice: ";
        cin >> type;
        if (type == 1)
        {
            cout << endl;
            cout << "you have selected to pay VIA Bank Card!" << endl;
            b.configure_bank_card();
        }
        else if (type == 2)
        {
            cout << endl;
            cout << "you have these options" << endl;
            cout << "1. PayPal" << endl;
            cout << "2. Cash on Delivery" << endl;
            cout << "3. Jazz Cash" << endl;
            cout << "4. Easy Paisa" << endl;
            cout << endl;
            o.configure_other_method();
        }
        else
        {
            cout << "invalid choice ... please select a valid payment method type ..." << endl;
            configure_payment();
        }
    }
    void display_info()
    {
        if (type == 1)
        {
            b.display_bank_card_info();
        }
        else if (type == 2)
        {
            o.display_info();
        }
        else if (type == 3)
        {
            display_previous_payments();
        }
        else
        {
            cout << "no valid payment method selected ..." << endl;
            display_options();
        }
    }
    void display_previous_payments()
    {
        ifstream infile("payments.txt");
        if (infile.is_open())
        {
            string line;
            cout << "previous payments:" << endl;
            while (getline(infile, line))
            {
                cout << line << endl;
            }
            infile.close();
        }
        else
        {
            cout << "no previous payments" << endl;
        }
    }
};
class Delivery
{
private:
    int a;
    string name,number,gmail,address,city,p1,p2,province;
public:
    void info()
    {
        cout << "please enter the delivery information ..." << endl;
        cout << endl;
        cout << "enter your name: ";
        cin >> name;
        cout << "enter your phone number: ";
        cin >> number;
        cout << "enter your gmail: ";
        cin >> gmail;
        cout << "enter your home address: ";
        cin >> address;
        cout << "enter your city: ";
        cin >> city;
        cout << "enter your province: ";
        cin >> province;
    }
    void password()
    {
        cout << "enter password: ";
        cin >> p1;
        cout << "re-type password: ";
        cin >> p2;
        if(p1 == p2)
        {
            cout << endl;
            cout << "password saved!" << endl;
        }
        else
        {
            cout << endl;
            cout << "password not same, confirm it again!" << endl;
            password();
        }
    }
    void show()
    {
        cout << endl;
        cout << "here is the delivery information" << endl;
        cout << endl;
        cout << "your name: " << name << endl;
        cout << "your phone number: " << number << endl;
        cout << "your gmail: " << gmail << endl;
        cout << "your address: " << address << endl;
        cout << "your city: " << city << endl;
        cout << "your province: " << province << endl;
        cout << endl;
        cout << "for configuration, press 1 to confirm the delivery information: ";
        cin >> a;
        if(a == 1)
        {
            cout << endl;
            cout << "information saved!" << endl;
            cout << endl;
        }
        else
        {
            cout << endl;
            cout << "information not saved!" << endl;
            cout << "enter the information again ..." << endl;
            info();
        }
    }
};
int main()
{
    //ejaz's code
    system("cls");
    int h;
    displayDigitalMerchantsInBox();
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                Welcome!"<<endl;
    cout<<endl;
    cout<<endl;
    //raza's code
    CustomerSupportChat supportChat;
    while (true)
        {
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Support Chat" << endl;
        cout << "4. Display login Information" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1:
                {
                string username, password, name, email;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                Customer customer;
                customer.setData(username, password, name, email);
                customer.saveToFile();
                cout << endl;
                cout << "Account created successfully! " << endl;
                break;
                }
            case 2:
                {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                Customer* customer = Customer::login(username, password);
                if (customer != nullptr)
                {
                    cout << endl;
                    cout << "Login successful. Welcome, " << customer->getName() << "!" << endl;
                    delete customer;
                    break;
                }
                else
                {
                    cout << endl;
                    cout << "Invalid username or password. Login failed." << endl;
                    cout << endl;
                    cout << "select choice again!" << endl;
                    cout << endl;
                    cout << "loading ..." << endl;
                    sleep(2000);
                    main();
                }
                break;
                }
            case 3:
                {
                string customerName, response;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "Enter your response/message: ";
                getline(cin, response);
                supportChat.setResponse(customerName, response);
                supportChat.saveToFile();
                cout << "Response saved successfully!" << endl;
                cout << endl;
                cout << "loading ..." << endl;
                sleep(2000);
                main();
                break;
                }
            case 4:
                cout << endl;
                cout << "Customers:" << endl;
                cout << endl;
                Customer::getAllCustomers();
                cout << endl;
                cout << "Responses:" << endl;
                cout << endl;
                CustomerSupportChat::getAllResponses();
                int v;
                cout << endl;
                cout << "press 1 to go back to front page: ";
                cin >> v;
                if(v == 1)
                {
                cout << "loading ..." << endl;
                sleep(2000);
                main();
                }
                break;
            case 5:
                cout << endl;
                cout << "ALLAH HAFIZ ..." << endl;
                return 0;
            default:
                cout << endl;
                cout << "Please select a valid option ..." << endl;
                cout << endl;
                sleep(2000);
                main();
        }
        cout << endl;
        break;
            }
    OnlineShoppingSystem shop;
    loadproductsfromfile(shop,"Digitalshop.txt");
    //sabeeh's code
    shop.addproduct(Product("Laptop", 80000));
    shop.addproduct(Product("Mobile", 50000));
    shop.addproduct(Product("PC", 150000));
    shop.addproduct(Product("Graphic_card", 25000));
    shop.addproduct(Product("Charger", 2500));
    shop.addproduct(Product("RAM", 8000));
    shop.addproduct(Product("HDD", 9000));
    shop.addproduct(Product("SSD", 5500));
    shop.addproduct(Product("Cables", 3000));
    shop.addproduct(Product("Keyboard", 2000));
    //ejaz's code
    cout << endl;
    int a;
    char p;
    int i=0;
    cout<<"(Make sure to write Words in their proper case) "<<endl;
    do{
    int z;
    cout << endl;
    cout << "main menu" << endl;
    cout<<"Press 1 to sell the products: "<<endl;
    cout<<"Press 2 to buy the products: "<<endl;
    cout<<"Press 3 to review the products: "<<endl;
    //nayar's work
    cout<<"Press 4 to move to the product payment and delivery: "<<endl;
    //sabeeh's work
    cout << "Press 5 to Sort products by name: " << endl;
    cout << "Press 6 to Sort products by price: " << endl;
    cout << "Press 7 to Search for a product: " << endl;
    //ejaz's work
    cout << "Press 8 to See product suggestions: " << endl;
    cout<<"Press 9 to exit: "<<endl;
    cout << "enter your choice: ";
    cin>>a;
    switch (a)
    {
    case 1:
        do{
            cout<<endl;
            cout<<"Enter the product you are going to Sell with Price: ";
            string s;
            double d;
            cin>>s>>d;
            shop.sellproduct(s,d);
            cout<<endl;
            cout<<"your product is added to the list and here is the list of all Products: "<<endl;
            cout << endl;
            shop.displayproducts();
            int q;
            cout<<endl;
            cout<<"Press 1 to add more products in store and 0 to return to main menu: ";
            cin>>q;
            if(q==1)
            {
            string Name;int Price;
            cout<<endl;
            cout<<"Enter name of product to add: ";
            cin>>Name;
            cout<<"Enter price of product: ";
            cin>>Price;
            Product obj(Name,Price);
            shop.addproduct(obj);
            }
            if(q==0)
            {
                break;
            }
            cout<<endl;
            cout<<"Press 0 to exit or any other digit to continue: "<<endl;
            cin>>z;
        }while(z!=0);
        break;
    case 2:
        do{
        string q;
        cout << endl;
        cout<<"Here is the list of Products you can buy: "<<endl;
        cout << endl;
        shop.displayproducts();
        cout << endl;
        cout<<"Enter the name of product you want to buy: ";
        cin>>q;
        cout << endl;
        shop.buyproduct(q);
        i=1;
        cout << endl;
        cout<<"Press 0 to move to delivery options and any other digit to buy another product: ";
        cin>>z;
        cout << endl;
        }while(z!=0);
        break;
    case 3:
        do{
        string w;
        double r;
        cout << endl;
        shop.displayproducts();
        cout << endl;
        cout<<"Enter the name of product with ratings: ";
        cin>>w>>r;
        shop.reviewproduct(w,r);
        cout << endl;
        cout<<"Press 0 to return to main menu and any other digit to continue: ";
        cin>>z;
        }while(z!=0);
        break;
        //nayar's code
    case 4:
        do{
        cout << endl;
        cout << "please buy a product first!" << endl;
        cout << endl;
        cout<<"Press 0 to return to main menu: ";
        cin>>z;
        }while(z!=0);
        break;
        //sabeeh's code
    case 5:
                shop.sortProductsByName();
                cout << endl;
                cout << "Products sorted by name: " << endl;
                cout << endl;
                shop.displayproducts();
                break;
    case 6:
                shop.sortProductsByPrice();
                cout << endl;
                cout << "Products sorted by price: " << endl;
                cout << endl;
                shop.displayproducts();
                break;
    case 7:
        {
                string productname;
                cout << endl;
                cout << "Enter the name of the product to search: ";
                cin >> productname;
                cout << endl;
                shop.searchProduct(productname);
                break;
        }
    case 8:
                cout << endl;
                shop.suggestProductsBasedOnRating();
                break;
    //ejaz's code
    case 9:
        cout << endl;
        cout << "thank you for visiting!" << endl;
        return 0;
    default:
    {
        do{
        cout << endl;
        cout<<"Wrong choice ...";
        cout << endl;
        cout<<"Press 0 to return to main menu: ";
        cin>>z;
        }while(z!=0);
        break;
    }
    }
    //nayar's work
    if(i==1)
    {
    int x;
    payment pa;
    Delivery d;
    d.info();
    d.password();
    d.show();
    pa.display_options();
    pa.configure_payment();
    pa.display_info();
    cout << "your parcel will be delivered soon!" << endl;
    cout << "thank you for shopping :)" << endl;
    cout << endl;
    cout << "if you want to do payment again, press 1: " << endl;
    cout << "if you want to check previous payments, press 2: " << endl;
    cin >> a;
    if(a == 1)
    {
        cout << endl;
        main();
    }
    else if(a == 2)
    {
        cout << endl;
        pa.display_previous_payments();
    }
    else
    {
       cout<<"BYE! thanks for coming!"<<endl;
    }
        break;
    }
    cout << endl;
    //ejaz's work
}while(a!=100);
    cout << endl;
    saveproductinfile(shop.products,shop.numofproducts,"Digitalshop.txt");
    return 0;
}
