#include <bits/stdc++.h>
#include "Purchase.h"
using namespace std;
// Purchase is buying n number of goods from suppliers and saving them to our own stock
// Data Structure Used : Linked List
Purchase::Purchase(int a, vector<vector<string>> u)
{
    pid = a;
    nxt = NULL;
    v = u;
}
// Method to add a purchase, with root,purchase id, vector of products bought under this particular purchase as parameter to the global pointer
// of purchaselist in main.cpp

void addPurchase(Purchase *p, int pid, vector<vector<string>> &v)
{
    cout << pid << endl;
    if (p->nxt == NULL)
    {
        p->nxt = new Purchase(pid, v);
        return;
    }
    else
    {
        addPurchase(p->nxt, pid, v);
    }
}
// Method to display all the Purchases made by the Retail Store using Recursion
void displaypurchases(Purchase *head)
{
    if (head == NULL)
    {
        return;
    }
    cout << "Purchase Id " << head->pid << endl;
    for (int i = 0; i < (head->v).size(); i++)
    {
        cout << "Product name: " << (head->v)[i][0] << endl;
        cout << "Product price: " << (head->v)[i][1] << endl;
        cout << "Product quantity: " << (head->v)[i][2] << endl;
        cout << "Product category: " << (head->v)[i][3] << endl;
        cout << "Product supplier: " << (head->v)[i][4] << endl;
        cout << endl;
    }
    displaypurchases(head->nxt);
}
// Gets the details of the Purchase with id purchaseid if made, else NULL is returned
Purchase *getpurchase(Purchase *root, int purchaseid)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->pid == purchaseid)
    {
        return root;
    }
    else
    {
        return getpurchase(root->nxt, purchaseid);
    }
}
// checks if there is any purchase made with the given id
bool ispresentid(Purchase *root, int id)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->pid == id)
    {
        return true;
    }
    return ispresentid(root->nxt, id);
}
