#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include "test.hpp"
class NotFound
{
public:
    NotFound();
    string get_description();
private:
    string description;
};

class BadRequest
{
public:
    BadRequest();
    string get_description();
private:
    string description;
};

class PermissionDenied
{
public:
    PermissionDenied();
    string get_description();
private:
    string description;
};

#endif