#include "cli-todo/item.hpp"
#include <string>

Item::Item(
    int list_id,
    const std::string& header,
    const std::string& description,
    Priority priority,
    Status status,
    const std::string& deadline
):(
    list_id(list_id),
    header(header),
    description(description),
    priority(priority),
    status(status),
    deadline(deadline),
    created_at("N/A"),
    updated_at("N/A"),
    id(-1)
) {}

int Item::get_id()
{
    return id;
}

int Item::get_list_id()
{
    return list_id;
}

Priority Item::get_priority()
{
    return priority;
}

int Item::set_priority(Priority new_priority)
{
    priority = new_priority;
}

Status Item::get_status()
{
    return status;
}

int Item::set_status(Status new_status)
{
    status = new_status;
}

std::string Item::get_description()
{
    return description;
}

int Item::set_description(const std::string& new_description)
{
    description = new_description;
}

std::string Item::get_header()
{
    return header;
}

int Item::set_header(const std::string& new_header)
{
    header = new_header;
}

std::string Item::get_created_at()
{
    return created_at;
}

std::string Item::get_updated_at()
{
    return updated_at;
}

int Item::set_updated_at(const std::string& new_updated_at)
{
    updated_at = new_updated_at;
}
