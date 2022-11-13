#include "exceptions.hpp"
#include "../server/server.hpp"

NotFound::NotFound(string msg)
{
    throw Server::Exception(msg);
    description = "Not Found";
}
string NotFound::get_description()
{
    return description;
}

BadRequest::BadRequest(string msg)
{
    throw Server::Exception(msg);
    description = msg;
}
string BadRequest::get_description()
{
    return description;
}

PermissionDenied::PermissionDenied(string msg)
{
    throw Server::Exception(msg);
    description = "Permission Denied";
}
string PermissionDenied::get_description()
{
    return description;
}