#include <bits/stdc++.h>
#include <fstream>
#include "Data.cpp"
#include "Product.cpp"
using namespace std;

const regex mpattern("[0-9]{10}");
void sale_product()
{
    int num, amount = 0, qty = 0, cost = 0, re_amount = 0, total_qty = 0, total_cost = 0, quantity = 0;
    string purchaser_id, name, phone_num, product_name;
    int re_quantity;
    cout << "Enter sales number" << endl;
    cin >> num;
    while (sales[num].size())
    {
        cout << "This sales number has already been used! Try a different number" << endl;
        cin >> num;
    }
    cout << "Enter user details making purchasement" << endl;

    // if user does not exist, add it in in user management
    // quantity updation

    cout << "Enter id" << endl;
    cin >> purchaser_id;
    cout << "Enter name" << endl;
    cin >> name;

    while (true)
    {
        cout << "Enter phone number: ";
        cin >> phone_num;
        // To ensure phone number entered is of 10 digits
        if (regex_match(phone_num, mpattern))
        {
            break;
        }
    }
    vector<vector<pair<string, string>>> a;
    vector<pair<Product *, int>> v;
    map<string, int> mp;

    while (true)
    {
        vector<pair<string, string>> b;
        cout << "Enter product name" << endl;
        cin >> product_name;
        //Retrieving root of Product BST
        Product *node = searchInBst(&Proot, product_name);
        if (node == NULL)
        {
            cout << "Product not exists in our stock. Enter another product." << endl;
            continue;
        }
        else if (node->quantity == 0)
        {
            cout << "Product is not available in stocks. Please order this item after some time. Enter another product." << endl;
            continue;
        }
        int flag = 0;
        while (true)
        {
            cout << "Enter quantity" << endl;
            cin >> quantity;
            flag = 0;
            if (quantity == 0)
            {
                flag = 2;
            }
            else if (node->quantity < quantity)
            {
                cout << "Quantity present in stock: " << node->quantity << endl;
                cout << "Requested quantity not available! Enter another quantity" << endl;
                flag = 1;
            }
            if (!flag)
            {
                // update quantity in both data struture as well as in Product BST
                re_quantity = node->quantity - quantity;
                node->quantity = (re_quantity);
                ProductMap[node->id]->quantity = (re_quantity);
                mp[product_name] += quantity;
                break;
            }
            if (flag == 2)
            {
                break;
            }
        }
        if (flag == 2)
        {
            // If quantity is 0, we are ensuring it does not get into the bill
            continue;
        }
        cost = quantity * (node->price);
        b.resize(4);
        b = {{"Product name", product_name}, {"Price per unit", to_string(node->price)}, {"Quantity demanded", to_string(quantity)}, {"Total cost", to_string(cost)}};
        a.push_back(b);
        total_cost += cost;
        cout << "1. Add one more Item?" << endl;
        cout << "2. No" << endl;
        int ch;
        cin >> ch;
        if (ch != 1)
        {
            break;
        }
    }
    // If total cost is 0, it implies no items are bought
    if (!total_cost)
    {
        cout << "No item bought" << endl;
        return;
    }

    // If discount is available and customer coming to retrieve the discount has not appeared before to retrieve the discount with the
    // registered mobile number, he gets the discount.
    string coupon;
    if (discount && !customers[phone_num])
    {
        customers[phone_num] = 1;
        coupon = q.front();
        q.pop();
        // If queue's size is 0, it means all the coupons are used.
        if (!q.size())
        {
            discount = 0;
            customers.clear();
        }
    }
    cout << "Total cost: " << total_cost - discount * total_cost / 100 << endl;
    cout << "Enter money received" << endl;
    cin >> amount;
    int flag = 0;
    
    // This loop executes when entered amount by user is less than the actual amount he has to pay
    while (amount < total_cost - discount * total_cost / 100)
    {
        cout << "Insufficient amount entered" << endl;
        cout << "Amount to be paid: " << total_cost - discount * total_cost / 100 << endl;
        for (auto it = mp.begin(); it != mp.end(); ++it)
        {
            Product *node = searchInBst(&Proot, it->first);
            node->quantity += (it->second);
            ProductMap[node->id]->quantity += (it->second);
        }
        // if purchaser wants to discontinue the purchasement in between, he would like to escape from the transaction.
        cout << "If purchaser wants to discontinue, Press 1, else Press 0." << endl;
        cin >> flag;
        if (flag)
        {
            return;
        }
        else
        {
            cout << "Enter money received" << endl;
            cin >> amount;
        }
    }
    // Re_amount is remaining amount to be paid back to the purchaser/user.
    re_amount = amount - (total_cost - total_cost * discount / 100);

    // Printing the receipt
    cout << "--------------BILL--------------" << endl;
    cout << "ID: " << purchaser_id << endl;
    cout << "Purchaser Name: " << name << endl;
    cout << "Phone Number: " << phone_num << endl;
    cout << endl;

    sales[num].push_back({{"ID: ", purchaser_id}, {"Purchaser Name: ", name}, {"Phone Number: ", phone_num}});
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            cout << a[i][j].first << " " << a[i][j].second << endl;
        }
        sales[num].push_back(a[i]);
        cout << endl;
    }
    cout << "Intial cost: " << total_cost << endl;
    cout << "Discount: " << discount << endl;
    if (coupon.size())
    {
        cout << "Coupon code: " << coupon << endl;
    }
    cout << "Total cost: " << total_cost - discount * total_cost / 100 << endl;
    cout << "Amount received: " << amount << endl;
    cout << "Amount returned: " << re_amount << endl;
    cout << "---------------------------------" << endl;

    sales[num].push_back({{"Intial cost: ", to_string(total_cost)}, {"Discount: ", to_string(discount)}, {"Total cost: ", to_string(total_cost - discount * total_cost / 100)}, {"Amount received: ", to_string(amount)}, {"Amount returned: ", to_string(re_amount)}});
    return;
}

void enable_discount()
{
    cout << "Enter discount(in %)" << endl;
    cin >> discount;
    // i is the coupon number
    cout << "Enter the number of coupons" << endl;
    int n;
    cin >> n;
    // Pushing coupon code numbers into the queue.
    // QUEUE -> FIFO ~ First come first serve
    for (int i = 1; i <= 5; i++)
    {
        q.push(to_string(i));
    }
}

void disable_discount()
{
    discount = 0;
    customers.clear();
    while (q.size())
    {
        q.pop();
    }
}

void list_sales(int num)
{
    if (!sales[num].size())
    {
        cout << "No receipt of this entered sales number!" << endl;
    }
    for (int i = 0; i < sales[num].size(); i++)
    {
        for (int j = 0; j < sales[num][i].size(); j++)
        {
            cout << sales[num][i][j].first << " " << sales[num][i][j].second << endl;
        }
        cout << endl;
    }
    cout << endl;
    return;
}