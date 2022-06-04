#ifndef __VIRTUALCLASS_H__
#define __VIRTUALCLASS_H__
#include <iostream>
class DOCKInterface //purely virtual class for all *.* docks
{
private:
    /* data */
public:
    DOCKInterface(/* args */) = default;
    virtual ~DOCKInterface() = 0;
    virtual uint16_t& getID(void) = 0; //unsigned 16b int (0..65.535)
    virtual bool is_empety(void) const = 0;
};
#endif // __VIRTUALCLASS_H__