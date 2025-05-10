#ifndef DATA_H
#define DATA_H
#include <string>

class Data
{
public:
    int No;
    int Page;
    int Chapter;
    std::string BookName;
    Data():No(0),Page(0),Chapter(0),BookName(""){};
    void reset();
};

#endif // DATA_H
