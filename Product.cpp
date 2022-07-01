#ifndef __PRODUCT_CPP__
#define __PRODUCT_CPP__
#include <bits/stdc++.h>
#include "Product.h"
#include "Data.cpp"
using namespace std;
void deleteProduct(string name);
// For Prompting the user

Product::Product()
{
}

void listAllProducts()
{
    // Show all the Products in the Map
    cout << endl
         << "<----------STOCKS--------->" << endl
         << endl
         << endl;
    for (auto i = ProductMap.begin(); i != ProductMap.end(); i++)
    {
        cout << "Name: " << i->second->name << endl;
        cout << "Quantity available as stock: " << i->second->quantity << endl;
        cout << "Price: " << i->second->price << endl;
        cout << "Category: " << i->second->category << endl
             << endl
             << endl;
    }
}

void insertAtBsT(Product **root, Product **pointerToNewNode)
{
    // Adding a Product in the BST using Recursion
    if ((*root) == NULL)
    {
        *root = *(pointerToNewNode);
        return;
    }
    if ((*pointerToNewNode)->name < (*root)->name)
    {
        insertAtBsT(&((*root)->left), pointerToNewNode);
    }
    if ((*pointerToNewNode)->name > (*root)->name)
    {
        insertAtBsT(&((*root)->right), pointerToNewNode);
    }
}
Product *searchInBst(Product **Proot, string name_val)
{
    // searching a node in the tree with the name name_val
    if ((*Proot) == NULL)
    {
        return NULL;
    }
    if ((*Proot)->name == name_val)
    {
        return *Proot;
    }
    else if ((*Proot)->name > name_val)
    {
        return searchInBst(&((*Proot)->left), name_val);
    }
    else
    {
        return searchInBst(&((*Proot)->right), name_val);
    }
    return NULL;
}
// Constructor
Product::Product(int id_val, string name_val, int quntity_val, int price_val, string category_val)
{
    id = id_val;
    name = name_val;
    quantity = quntity_val;
    price = price_val;
    category = category_val;
    left = NULL;
    right = NULL;
}

void inorder(Product *root)
{
    // Printing all the Nodes in inorder fashion
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    cout << root->name << " ";
    inorder(root->right);
}

bool checkValidityOfID(int id)
{
    // checks if the id is associated with any product in the tree
    cout << "Checking valiity of ID..." << endl;
    auto i = ProductMap.begin();
    for (; i != ProductMap.end(); i++)
    {
        if (i->second->id == id)
        {
            break;
        }
    }
    if (i == ProductMap.end())
    {
        return true;
    }
    cout << "The Product with ID " << id << " already exists" << endl;
    return false;
}
bool checkValidityOfName(string old_name)
{
    // checks if the name is associated with any product in the tree
    bool gate = false;
    cout << "Checking validity of name" << endl;
    auto i = ProductMap.begin();
    for (; i != ProductMap.end(); i++)
    {
        if (i->second->name == old_name)
        {
            gate = true;
        }
    }
    if (!gate)
    {

        cout << "Product with such name does not exist" << endl;
    }
    return gate;
}

Product *minsucc(Product *node)
{
    // calculates the minimum successor of the given node
    Product *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
Product *deleteProduct(Product *u, string name)
{
    if (u == NULL)
        return u;

    if (name < u->name)
        u->left = deleteProduct(u->left, name);

    // If the name to be deleted is
    // greater than the root's
    // name, then it lies in right subtree
    else if (name > u->name)
        u->right = deleteProduct(u->right, name);

    // if name is same as root's name, then This is the node
    // to be deleted
    else
    {
        // node has no child
        if (u->left == NULL and u->right == NULL)
            return NULL;

        else if (u->left == NULL)
        {
            Product *temp = u->right;
            free(u);
            return temp;
        }
        else if (u->right == NULL)
        {
            Product *temp = u->left;
            free(u);
            return temp;
        }

        Product *temp = minsucc(u->right);

        u->name = temp->name;

        u->right = deleteProduct(u->right, temp->name);
    }
    return u;
}
#endif
