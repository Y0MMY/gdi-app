//#include "../../headers/mics/FileTXT.hpp"
//void FileTXT::writeTXT(const Books& book, const std::string fileName)
//{
//    fstream myfile;
//    try
//    {
//        myfile.open(fileName, fstream::in | fstream::out | fstream::app);
//        printf("File has been opened!\n");
//        // myfile.write((char*)&book,sizeof(Books));
//        myfile.write((char*)&book,sizeof(Books));
//    }
//    catch(const std::ofstream::failure& e)
//    {
//        std::cerr << e.code() << '\n';
//    }
//    myfile.close();
//}   
//void FileTXT::readTXT(Books& book, const std::string fileName)
//{
//    ifstream myfile;
//    Books *temp = new Books();
//    try
//    {
//        myfile.open(fileName);
//        printf("File has been opened for read!\n");
//        while(myfile.read((char*)temp,sizeof(Books)))
//            book.booksVector.push_back(*temp);
//    }
//    catch(const std::ofstream::failure& e)
//    {
//        std::cerr << e.code() << '\n';
//    }
//    myfile.close();
//}
//
//// FileTXT::FileTXT():Books()
//// {
//    
//// }
//
//FileTXT::~FileTXT()
//{
//}