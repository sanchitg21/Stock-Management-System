#ifndef Purchase_H
#define Purchase_H
#include <string>
#include <vector>
class Purchase
{
public:
    int pid;
    Purchase *nxt;
    std::vector<std::vector<std::string>> v;
    Purchase(int x, std::vector<std::vector<std::string>> v);
};
#endif
