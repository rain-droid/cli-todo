#ifndef CLIDO_ITEM_H
#define CLIDO_ITEM_H

#include <string>


enum Status
{
    PENDING,
    IN_PROGRESS,
    DONE
};

enum Priority
{
    LOW,
    MEDIUM,
    HIGH
};


class Item
{
    private:
    std::string header;
    std::string description;
    int id;
    int list_id;
    Status status;
    Priority priority;
    std::string created_at;
    std::string updated_at;
    std::string deadline;

    public:

    Item(
        int list_id,
        const std::string& header,
        const std::string& description = "",
        Priority priority = LOW,
        Status status = PENDING,
        const std::string& deadline = ""
    );

    ~Item();

    int get_ßßßßßß id();
    int get_list_id();

    Priority get_priority();
    int set_priority(Priority new_priority);

    Status get_status();
    int set_status(Status new_status);

    std::string get_description();
    int set_description(const std::string& new_description);

    std::string get_header();
    int set_header(const std::string& new_header);

    std::string get_created_at();

    std::string get_updated_at();
    int set_updated_at(const std::string& new_updated_at);

};

#endif //  CLIDO_ITEM_H
