#ifndef __SUPPLIER_H__
#define __SUPPLIER_H__

#include <functional>

template<typename ReturnType>
class Supplier : public std::function<ReturnType()> {};
#endif