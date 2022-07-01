#ifndef __DATA__CPP
#define __DATA__CPP
#include <bits/stdc++.h>
#include "Product.h"
#include "User.h"
#include "Worker.h"
#include "Purchase.h"
using namespace std;
map<int, Product *> ProductMap;
map<int, User *> UserMap;
map<int, Worker *> WorkerMap;
map<int, vector<vector<pair<string, string>>>> sales;
map<string, int> customers;

int discount = 0;
// queue storing the details of all the users availing the discount
queue<string> q;

// Roots to all trees present
User *Uroot = NULL;
Worker *Wroot = NULL;
Purchase *purchaselist = NULL;
Product *Proot = NULL;
#endif
