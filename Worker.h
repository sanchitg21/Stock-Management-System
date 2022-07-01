#ifndef WORKER_H
#define WORKER_H
#include <string>
class Worker
{
public:
    int id;
    std::string name;
    std::string phonenum;
    Worker *left;
    Worker *right;
    Worker();
    Worker(int x, std::string a, std::string b);
};
#endif