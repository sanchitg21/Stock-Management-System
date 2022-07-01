#ifndef Product_H
#define Product_H
#include <string>
class Product
{

public:
  std::string name;
  int id;
  int quantity;
  int price;
  Product *left;
  Product *right;
  std::string category;
  Product();
  Product(int id_val, std::string name_val, int quntity_val, int price_val, std::string category_val);
};
#endif
