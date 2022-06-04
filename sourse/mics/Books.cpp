//#include "../../headers/mics/Books.hpp"
//Books::Books(std::string author,std::string name,std::string description,int price, int realeseDate)
//{
//    ++booksCount;
//    currentID = booksCount;
//    this->realeseDate = realeseDate;
//    this->price = price;
//    strcpy(this->author ,author.c_str());
//    strcpy(this->name ,name.c_str());
//    strcpy(this->description ,description.c_str());
//}
//
//Books::~Books()
//{
//    --booksCount;
//}
//uint16_t& Books::getDate(void) 
//{
//    return realeseDate;
//}
//uint16_t& Books::getID() 
//{
//    return currentID;
//}
//uint16_t& Books::getPrice(void) 
//{
//    return price;
//}
//char* Books::getAuthor(void) 
//{
//    return author;
//}
//char* Books::getNameBook(void) 
//{
//    return name;
//}
//char* Books::getDescription(void) 
//{
//    return description;
//}
//bool Books::is_empety(void) const 
//{
//    return booksVector.size() == 0 ? true : false;
//}