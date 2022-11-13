#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include "test.hpp"
class NotFound
{
public:
    NotFound(string msg = "Not Found");
    string get_description();
private:
    string description;
};

class BadRequest
{
public:
    BadRequest(string msg = "Bad Request");
    string get_description();
private:
    string description;
};

class PermissionDenied
{
public:
    PermissionDenied(string msg = "Permission Denied");
    string get_description();
private:
    string description;
};

#endif