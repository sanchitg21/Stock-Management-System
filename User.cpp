#include <bits/stdc++.h>
#include "User.h"
#include "Data.cpp"
using namespace std;
User::User(int x, string a, string b)
    : id{x}, name{a}, mobilenum{b}, left{NULL}, right{NULL}
{
}
User::User()
{
}
// Adding a user into the tree
void insertuser(User **u, int x, string a, string b)
{
    if (*u == NULL)
    {
        *u = new User(x, a, b);
        return;
    }
    if (((*u)->name) < a)
    {
        insertuser(&((*u)->right), x, a, b);
    }
    else if (((*u)->name) > a)
    {
        insertuser(&((*u)->left), x, a, b);
    }
    else
    {
        if ((*u)->id > x)
        {
            insertuser(&((*u)->left), x, a, b);
        }
        else
        {
            insertuser(&((*u)->right), x, a, b);
        }
    }
}
// Displaying all the Users
void displayusers(User **u)
{
    if (*u == NULL)
    {
        return;
    }
    displayusers(&((*u)->left));
    cout << "User Name: " << (*u)->name << endl;
    cout << "User ID: " << (*u)->id << endl;
    cout << endl;
    displayusers(&((*u)->right));
}
// Searching in the tree if there is user with name 'name'
User *searchInUbst(User *root, int id, string name)
{
    if (!root)
    {
        return NULL;
    }
    if (root->name > name)
    {
        searchInUbst(root->left, id, name);
    }
    else if (root->name < name)
    {
        searchInUbst(root->right, id, name);
    }

    if (id > root->id)
    {
        searchInUbst(root->right, id, name);
    }
    else if (id < root->id)
    {
        searchInUbst(root->left, id, name);
    }

    return root;
}
// Searching in the tree if val is an id for any node
bool ispresentuserid(int val)
{
    for (auto x : UserMap)
    {
        if (x.first == val)
        {
            return true;
        }
    }
    return false;
}
