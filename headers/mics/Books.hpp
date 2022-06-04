//#ifndef __BOOKS_H__
//#define __BOOKS_H__
//#include <iostream>
//#include "../../headers/stdafx.h"
//#include "virtualClass.hpp"
//using namespace std;
//class Books: public DOCKInterface
//{
//private:
//    uint16_t realeseDate;
//    uint16_t price;
//    uint16_t currentID;
//    std::string temp;   
//    char name[120];
//    char description[120];
//    char author[120];
//public:
//    uint16_t& getID() override;
//    uint16_t& getDate(void) ;
//    uint16_t& getPrice(void) ;
//    bool is_empety(void) const override;
//    char* getAuthor(void) ;
//    char* getNameBook(void) ;
//    char* getDescription(void) ;
//    static int booksCount;
//    Books() = default;
//    Books(std::string author,std::string name,std::string description,int price, int realeseDate);
//    ~Books() override;
//    vector<Books> booksVector; 
//    // friend std::ostream& operator<< (std::ostream &out, const Books &book);
//};
//
//
//#endif // __BOOKS_H__