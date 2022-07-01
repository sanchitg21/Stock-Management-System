#include <bits/stdc++.h>
#include "Worker.h"
#include "Data.cpp"
using namespace std;
const regex mptrn("[0-9]{10}");
Worker::Worker()
{
}
Worker::Worker(int x, string a, string b)
{
    id = x;
    name = a;
    phonenum = b;
    left = NULL;
    right = NULL;
}
// calculating the minimum successor of a node in tree
Worker *minsucc(Worker *node)
{
    Worker *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
Worker *deleteworker(Worker *u, string name)
{
    if (u == NULL)
        return u;

    if (name < u->name)
        u->left = deleteworker(u->left, name);

    // If the name to be deleted is
    // greater than the root's
    // name, then it lies in right subtree
    else if (name > u->name)
        u->right = deleteworker(u->right, name);

    // if name is same as root's name, then This is the node
    // to be deleted
    else
    {
        // node has no child
        if (u->left == NULL and u->right == NULL)
            return NULL;

        else if (u->left == NULL)
        {
            Worker *temp = u->right;
            free(u);
            return temp;
        }
        else if (u->right == NULL)
        {
            Worker *temp = u->left;
            free(u);
            return temp;
        }

        Worker *temp = minsucc(u->right);

        u->name = temp->name;

        u->right = deleteworker(u->right, temp->name);
    }
    return u;
}
// fetching a worker pointer with name nn
int getid(Worker *u, string nn)
{
    if (u == NULL)
    {
        return -1;
    }

    if (u->name > nn)
    {
        getid(u->left, nn);
    }
    else if (u->name < nn)
    {
        getid(u->right, nn);
    }
    else
    {
        return u->id;
    }
    return -1;
}
// Inserting a node into the Workers tree
void insertworker(Worker **u, int x, string a, string b)
{
    if (*u == NULL)
    {
        *u = new Worker(x, a, b);
        return;
    }
    if (((*u)->name) < a)
    {
        insertworker(&((*u)->right), x, a, b);
    }
    else if (((*u)->name) > a)
    {
        insertworker(&((*u)->left), x, a, b);
    }
    else
    {
        if ((*u)->id > x)
        {
            insertworker(&((*u)->left), x, a, b);
        }
        else
        {
            insertworker(&((*u)->right), x, a, b);
        }
    }
}
// Displaying all the details of the workers present in the tree
void displayWorkers(Worker **u)
{
    if (*u == NULL)
    {

        return;
    }
    displayWorkers(&((*u)->left));
    cout << "Worker Name: " << (*u)->name << endl;
    cout << "Worker ID: " << (*u)->id << endl;
    cout << "Worker Contact: " << (*u)->phonenum << endl;
    cout << endl;
    displayWorkers(&((*u)->right));
}
// checks if a worker is present in the tree with id id
bool ispresentworkerid(int val)
{
    for (auto x : WorkerMap)
    {
        if (x.first == val)
        {
            return true;
        }
    }
    return false;
}
// Returns a pointer to the Node in the tree with name n and id id if present
Worker *searchinWbst(Worker *root, string n, int id)
{
    if (!root)
    {
        return NULL;
    }
    if (root->id == id and root->name == n)
    {
        return root;
    }
    if (root->name > n)
    {
        return searchinWbst(root->left, n, id);
    }
    else if (root->name < n)

    {
        return searchinWbst(root->right, n, id);
    }

    if (root->id > id)
    {
        return searchinWbst(root->left, n, id);
    }
    else if (root->id < id)
    {
        return searchinWbst(root->right, n, id);
    }
    return root;
}
void updateWorker(int id)
{
    Worker *to_update = WorkerMap[id];
    cout << "Enter updated name" << endl;
    string updated_name;
    cin >> updated_name;
    cout << "Enter updated phone number" << endl;
    string updated_phonenum;
    cin >> updated_phonenum;
    while (!regex_match(updated_phonenum, mptrn))
    {
        cout << "Enter a valid Number: ";
        cin >> updated_phonenum;
    }

    deleteworker(Wroot, WorkerMap[id]->name);
    to_update->name = updated_name;
    to_update->phonenum = updated_phonenum;
    insertworker(&(Wroot), id, updated_name, updated_phonenum);
}

void displayworker()
{
    cout << "Enter worker name" << endl;
    string name;
    cin >> name;
    int id = getid(Wroot, name);
    if (id == -1)
    {
        cout << "No such worker exists" << endl;
        return;
    }
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Phone number: " << WorkerMap[id]->phonenum << endl;
}