#include "exceptions.hpp"

NotFound::NotFound()
{
    description = "Not Found";
}
string NotFound::get_description()
{
    return description;
}

BadRequest::BadRequest()
{
    description = "Bad Request";
}
string BadRequest::get_description()
{
    return description;
}

PermissionDenied::PermissionDenied()
{
    description = "Permission Denied";
}
string PermissionDenied::get_description()
{
    return description;
}