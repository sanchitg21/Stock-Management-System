#include <bits/stdc++.h>
#include "Product.cpp"
#include "User.cpp"
#include "Worker.cpp"
#include "Purchase.cpp"
#include "Sales.cpp"

using namespace std;

// ALL STL DATA STRUCTURES ARE IN Data.cpp file
// ALL the methods alter the data in both the corresponding  tree and corresponding Map
// Methods in UserMangement are declared in Product.cpp,PurchaseMangement in Purchase.cpp, UserMangement in Users.cpp, Workers in Worker.cpp
void usermanagement();
void loadStocks();
void loadStocksOfWorkers();
void ProductMethods();
void Purchasemanagement();
void Workermanagement();
void sales_mgmt();
void loadWorkers();

const regex mobilepattern("[0-9]{10}");

int main()
{

    string password = "stockmanagement";
    string inp;
    while (true)
    {
        cout << "Enter password: ";
        cin >> inp;
        if (inp == "-1")
        {
            return 0;
        }
        if (inp == password)
        {
            break;
        }
        cout << "Wrong Password! Try again" << endl;
    }

    // loads data from stocks.txt file
    loadStocks();  // Loads all the stocks into tree and Map
    loadWorkers(); // Loads all workers in the file Worker.txt into the tree and Map
    cout << "***********STOCK MANAGEMENT***********" << endl;
    while (true)
    {
        cout << "1. PRODUCT MANAGEMENT" << endl;
        cout << "2. PURCHASE MANAGEMENT" << endl;
        cout << "3. SALES MANAGEMENT" << endl;
        cout << "4. USER MANAGEMENT" << endl;
        cout << "5. WORKER MANAGEMENT" << endl;
        cout << "6. EXIT" << endl;
        int n;
        cin >> n;
        switch (n)
        {
        case 1:
        {
            ProductMethods();
        }
        break;
        case 2:
        {
            Purchasemanagement();
        }
        break;
        case 3:
        {
            sales_mgmt();
        }
        break;
        case 4:
        {
            usermanagement();
        }
        break;
        case 5:
        {
            Workermanagement();
        }
        break;
        default:
        {
            return 0;
        }
        break;
        }
    }

    return 0;
}

void loadWorkers()
{
    ifstream inp("Worker.txt");
    int num;
    inp >> num;
    for (int i = 0; i < num; i++)
    {
        string a;
        int b;
        string c;
        inp >> b;
        inp >> a;
        inp >> c;
        insertworker(&Wroot, b, a, c);
        Worker *newworker = new Worker(b, a, c);
        WorkerMap.emplace(b, newworker);
    }
    // for(auto x:WorkerMap)
    // {
    //     cout<<"ID "<<x.first<<" Name "<<x.second->name<<endl;
    // }
}
// all the methods under USER MANAGEMENT
// All the methods essentially alter both the tree and Map as well
void usermanagement()
{
    cout << "USER MANAGEMENT" << endl;
    while (true)
    {
        cout << "1. Add user" << endl;
        cout << "2. List User by id and name" << endl;
        cout << "3. List  Users" << endl;
        cout << "4. Return" << endl;
        int n;
        cin >> n;

        if (n == 1)
        {
            int id;
            string name, mobilenum;
            cout << "Enter User ID: ";
            cin >> id;
            if (ispresentuserid(id))
            {
                cout << "There is a user with that id" << endl;
                continue;
            }
            cout << "Enter User Name: ";
            cin >> name;
            cout << "Enter Mobile Number: ";
            cin >> mobilenum;
            while (!regex_match(mobilenum, mobilepattern))
            {
                cout << "Enter a valid Mobile Number: ";
                cin >> mobilenum;
                if (mobilenum == "-1")
                {
                    return;
                }
            }

            insertuser(&Uroot, id, name, mobilenum);
            User *us = new User(id, name, mobilenum);
            UserMap.emplace(id, us);
        }
        else if (n == 2)
        {
            string nm;
            int idd;
            cout << "Name of the Person: ";

            cin >> nm;
            cout << "ID of the User";
            cin >> idd;
            User *userr = searchInUbst(Uroot, idd, nm);
            if (!userr)
            {
                cout << "There is no such User" << endl
                     << endl;
            }
            else
            {
                cout << "------USER DETAILS-----" << endl
                     << endl;
                cout << "ID: " << userr->id << endl;
                cout << "Name: " << userr->name << endl;
                cout << "Mobile: " << userr->mobilenum << endl;
                cout << endl;
            }
        }
        else if (n == 3)
        {
            if (Uroot == NULL)
            {
                cout << "No Users are present" << endl
                     << endl;
                return;
            }
            cout << endl
                 << "<------USER DETAILS------->" << endl
                 << endl;
            displayusers(&Uroot);
        }

        else
        {
            return;
        }
    }
    cout << endl;
}

void loadStocks()
{
    // fetches all the stock data from Stocks.txt file and loads them into stocks tree with root Proot and map ProductMap
    ifstream fin("stocks.txt");
    int nos;
    fin >> nos;
    for (int i{}; i < nos; i++)
    {
        int id;
        fin >> id;
        string name;
        fin >> name;
        int quan;
        fin >> quan;
        int price;
        fin >> price;
        string cat;
        fin >> cat;
        if (i == 0)
        {
            // todo: to insert
            ProductMap.emplace(id, new Product(id, name, quan, price, cat));
            Proot = new Product(id, name, quan, price, cat);
        }
        else
        {
            // todo: to insert
            Product *temp = new Product(id, name, quan, price, cat);
            ProductMap.emplace(id, new Product(id, name, quan, price, cat));
            insertAtBsT(&Proot, &temp);
        }
    }
}
/////// Sales  Management
///
////
///

void sales_mgmt()
{
    cout << "1. Sell Items" << endl;
    cout << "2. Print receipt of particular sales id number" << endl;
    cout << "4. Enable Discount" << endl;
    cout << "5. Disable Discount" << endl;
    cout << "6. Back (Main Menu)" << endl;
    int n;
    cin >> n;
    if (n == 1)
    {
        sale_product();
    }
    else if (n == 2)
    {
        cout << "Enter sale number" << endl;
        int num;
        cin >> num;
        list_sales(num);
        return;
    }
    else if (n == 3)
    {
        enable_discount();
        return;
    }
    else if (n == 4)
    {
        disable_discount();
        return;
    }
    else
    {
        return;
    }
};

// All methods for Products
// All the underlying functions in this methods are implemented in the file Product.cpp
void ProductMethods()
{
    while (true)
    {
        cout << "1. Add New Product" << endl;  // Adding new prodcut to the Stocks
        cout << "2. List 1 Product" << endl;   // Displaying info regarding one single product based on name
        cout << "3. List All Product" << endl; // Listing all products
        cout << "4. Update Product" << endl;   // Updating details of a product based on old name
        cout << "5. Delete Product" << endl;   // Deleting a  Product
        cout << "6. Back (Main Menu)" << endl; //  Return to main Flow
        cout << "Enter Your Choice : ";
        int n;
        cin >> n;
        switch (n)
        {
        case 1:
        {
            cout << "Enter Product ID: ";
            int id;
            cin >> id;
            if (!checkValidityOfID(id))
            {
                continue;
            }
            cout << endl
                 << "Enter Name: ";
            string name;
            cin >> name;
            cout << "Enter Quantity: ";
            int q;
            cin >> q;
            cout << "Enter Price: ";
            int p;
            cin >> p;
            cout << "Enter Category: ";
            string c;
            cin >> c;
            Product *temp = new Product(id, name, q, p, c);
            ProductMap.emplace(id, temp); // Adding into Map
            insertAtBsT(&Proot, &temp);   // Inserting into product tree
            cout << endl
                 << "Product Added Successfully!!" << endl;
        }
        break;
        case 2:
        {
            string nnn;
            cout << "Enter name of the Item: ";
            cin >> nnn;
            Product *ans = searchInBst(&Proot, nnn);
            if (!ans)
            {
                cout << "There is no such Product! " << endl;
                return;
            }
            cout << "<---------ITEM DETAILS------->" << endl
                 << endl;
            cout << "ID: " << ans->id << endl;
            cout << "Name: " << ans->name << endl;
            cout << "Price: " << ans->price << endl;
            cout << "Quantity available: " << ans->quantity << endl;
            cout << endl;
        }
        break;
        case 3:
        {
            if (!Proot)
            {
                cout << "No Products" << endl;
                return;
            }
            listAllProducts();
            cout << endl;
        }
        break;
        case 4:
        {
            // updating the product

            cout << "Enter name of the product: ";
            string old_name;
            cin >> old_name;
            // checking if the product is there in the stock or not
            if (!checkValidityOfName(old_name))
            {
                return;
            };
            cout << "Enter the new name of the product: ";
            string new_name;
            cin >> new_name;
            cout << "Enter the new price: ";
            int new_price;
            cin >> new_price;
            cout << "Enter the updated quantity: ";
            int new_q;
            cin >> new_q;
            Product *temp = searchInBst(&Proot, old_name);
            // updating in the map ;
            temp->name = new_name;
            temp->price = new_price;
            temp->quantity = new_q;
            // updating in the binary search tree
            deleteProduct(Proot, old_name);
            insertAtBsT(&Proot, &temp);

            ProductMap.erase(temp->id);
            ProductMap.emplace(temp->id, temp);
            cout << "Updated successfully" << endl
                 << endl;
        }
        break;
        case 5:
        {
            cout << "Name of the product to be deleted: ";
            string name;
            cin >> name;
            if (!checkValidityOfName(name))
            {
                // Product with that name does not exist
                break;
            }
            auto temp = searchInBst(&Proot, name);
            ProductMap.erase(temp->id);
            deleteProduct(Proot, name);
            inorder(Proot);
            cout << "Deleted successfully" << endl;
            ;
        }
        break;
        default:
        {
            cout << "Exiting" << endl;
            return;
        }
        break;
        }
    }
}
// ALL methods under Worker Management
void Workermanagement()
{
    cout << "---------Worker MANAGEMENT-----------" << endl;
    while (true)
    {
        cout << "1. Add a worker" << endl;        // Adding a worker
        cout << "2. Display all Workers" << endl; // Showing the details of all the workers in the store
        cout << "3. Delete a Worker" << endl;     // Deleting a worker based on his name
        cout << "4. Update worker" << endl;       // Updating worker information
        cout << "5. Display a worker" << endl;    // Display the details of a worker
        cout << "6. Exit" << endl;                // Return
        int n;
        cin >> n;
        if (n == 1)
        {
            int id;
            string name, mobilenum;
            cout << "Enter Worker ID: ";
            cin >> id;
            if (ispresentworkerid(id))
            {
                cout << "There is a worker with that id" << endl;
                continue;
            }

            cout << "Enter Worker Name: ";
            cin >> name;

            while (true)
            {
                cout << "Enter Mobile Number: ";
                cin >> mobilenum;
                if (regex_match(mobilenum, mobilepattern))
                {
                    break;
                }
            }

            insertworker(&Wroot, id, name, mobilenum);
            Worker *us = new Worker(id, name, mobilenum);
            WorkerMap.emplace(id, us);
        }
        else if (n == 2)
        {
            if (Wroot == NULL)
            {
                cout << "No Workers exists" << endl
                     << endl;
                return;
            }
            cout << "<--------Workers List --------->" << endl
                 << endl;
            displayWorkers(&Wroot);
        }

        else if (n == 3)
        {
            if (Wroot == NULL)
            {
                cout << "There are no workers to be deleted!" << endl
                     << endl;
                continue;
            }
            string name;
            cout << "Enter the Name of the Worker: ";
            cin >> name;
            int idd = getid(Wroot, name);
            if (idd == -1)
            {
                cout << "There is No such Worker" << endl;
                return;
            }
            WorkerMap.erase(idd);
            Worker *temp = deleteworker(Wroot, name);
        }

        else if (n == 4)
        {
            cout << "Enter name" << endl;
            string name;
            cin >> name;
            if (getid(Wroot, name) == -1)
            {
                cout << "NO such worker exist" << endl;
                return;
            }
            int id = getid(Wroot, name);
            cout << id << endl;
            updateWorker(id);
        }
        else if (n == 5)
        {
            displayworker();
        }
        else
        {
            return;
        }
    }
    cout << endl;
}
// Manages the Purchases being made by the store from the suppliers of products
void Purchasemanagement()
{
    while (true)
    {
        cout << "1. Add purchase" << endl;        // Making a Purchase
        cout << "2. List Purchase by id" << endl; // Display  the Purchase by ID
        cout << "3. List Purchases" << endl;      // Display all the Purchases Made
        cout << "4. EXIT" << endl;                // Return
        int n;
        cin >> n;

        if (n == 1)
        {
            string nn, q, p, cat;
            vector<vector<string>> v;
            int x;
            cout << "Enter Purchase id : ";
            cin >> x;
            if (ispresentid(purchaselist, x))
            {
                cout << "There is a purchase with that id" << endl;
                continue;
            }
            int i = 0;
            vector<string> temp;
            cout << "Enter product name: ";
            cin >> nn;
            temp.push_back(nn);
            cout << "Enter Price: ";
            cin >> p;
            temp.push_back(p);
            cout << "Enter Quantity: ";
            cin >> q;
            temp.push_back(q);

            cout << "Enter Category: ";
            cin >> cat;
            temp.push_back(cat);

            string seller;
            cout << "Enter Seller: ";
            cin >> seller;
            temp.push_back(seller);
            v.push_back(temp);

            Product *te = searchInBst(&Proot, nn);
            if (!te)
            {
                int k;
                cout << "Enter id for this new product: ";
                cin >> k;
                Product *ne = new Product(k, nn, (stoi)(q), (stoi)(p), cat);
                insertAtBsT(&Proot, &ne);
                ProductMap.emplace(k, ne);
            }
            else
            {
                te->quantity += (stoi)(q);
                te->price = (stoi)(p);
                ProductMap[te->id]->quantity += (stoi)(q);
                ProductMap[te->id]->price = (stoi)(p);
            }

            while (true)
            {
                // This loop runs untill we are ok with all the products being purchased from sellers
                cout << "1. Add one more product" << endl;
                cout << "2. RETURN" << endl;
                int y;
                cin >> y;
                if (y != 1)
                {
                    break;
                }
                else
                {
                    string nn, q, p, cat;

                    vector<string> t;

                    cout << "Enter product name: ";
                    cin >> nn;
                    t.push_back(nn);
                    cout << "Enter Price: ";
                    cin >> p;
                    t.push_back(p);
                    cout << "Enter Quantity: ";
                    cin >> q;
                    t.push_back(q);

                    cout << "Enter Category: ";
                    cin >> cat;
                    t.push_back(cat);
                    string seller;
                    cout << "Enter Seller: ";
                    cin >> seller;
                    t.push_back(seller);
                    v.push_back(t);
                    Product *te = searchInBst(&Proot, nn);
                    if (!te)
                    {
                        int k;
                        cout << "Enter id for this new product: ";
                        cin >> k;
                        Product *ne = new Product(k, nn, (stoi)(q), (stoi)(p), cat);
                        insertAtBsT(&Proot, &ne);
                        ProductMap.emplace(k, ne);
                    }
                    else
                    {
                        te->quantity += (stoi)(q);
                        te->price = (stoi)(p);
                        ProductMap[te->id]->quantity += (stoi)(q);
                        ProductMap[te->id]->price = (stoi)(p);
                    }
                }
            }
            for (int i = 0; i < v.size(); i++)
            {
                string nn = v[i][0]; // name of ith stock bought
                string pp = v[i][1]; //  price of ith stock bought
                string qq = v[i][2]; //  quantity of ith stock bought
                string cc = v[i][3]; //  category of ith stock bought
                string ss = v[i][4]; //  supplier name of ith stock bought
                Product *temp = searchInBst(&Proot, nn);

                if (!temp)
                {
                    int k;
                    cout << "Enter id for this new product: ";
                    cin >> k;
                    Product *ne = new Product(k, nn, (stoi)(qq), (stoi)(pp), cc);
                    insertAtBsT(&Proot, &ne);
                    ProductMap.emplace(k, ne);
                }
                else
                {
                    temp->quantity += (stoi)(qq);
                    temp->price = (stoi)(pp);
                    ProductMap[temp->id]->quantity += (stoi)(qq);
                    ProductMap[temp->id]->price = (stoi)(pp);
                }
            }

            if (purchaselist == NULL)
            {

                purchaselist = new Purchase(x, v);
            }
            else
            {

                addPurchase(purchaselist, x, v);
            }
        }
        else if (n == 2)
        {
            int tempid;
            cout << "Enter the purchase id :";
            cin >> tempid;
            Purchase *temp = getpurchase(purchaselist, tempid);
            if (temp == NULL)
            {
                cout << endl
                     << "There is no such Purchase" << endl
                     << endl;
                return;
            }
            else
            {
                cout << "Purchase ID: " << temp->pid << endl;
                cout << endl;
                for (int i = 0; i < (temp->v).size(); i++)
                {
                    cout << "Product Name: " << temp->v[i][0] << endl;
                    cout << "product Price: " << temp->v[i][1] << endl;
                    cout << "Product Quantity: " << temp->v[i][2] << endl;
                    cout << "Product Category: " << temp->v[i][3] << endl;
                    cout << "Product Seller: " << temp->v[i][4] << endl;
                    cout << endl;
                }
            }
        }
        else if (n == 3)
        {
            if (purchaselist == NULL)
            {
                cout << "No Purchases made yet" << endl;
            }

            displaypurchases(purchaselist); // Function implemented in Purchase.cpp
        }
        else
        {
            return;
        }
    }
}
