#ifndef DATA_H
#define DATA_H
#include <string>

class Data
{
public:
    int No;
    int Page;
    int Chapter;
    int Line;
    std::string BookName;
    Data():No(0),Page(1),Chapter(0),BookName(""){};
    void reset();
};

#endif // DATA_H
