# cli-todo named clido 

> a simple cli todo tool using a single sqlite database for improving daily life, C++ and sqlite programming 

### Usage

- clido init : creates a new todo list
- clido add  : adds a new todo to the list
- clido edit : edits a given todo in the list
- clido rm   : remove a todo of the list 
- clido show : shows the todo items
- clido set  : set status of the todo  


### RoadMap 

- [ ] Basic Usability (init, add)
- [ ] SQLite-Integration 
- [ ] Add Deadlines
- [ ] Extended Operations (edit, rm, show, set)
- [ ] Filters in show 
- [ ] Custom Priorities & Statuses

### Technicals
#### Entities
##### ToDo List 
- name        : unique name set by user
- description : optional descriptive text set by the user 
- password    : optional password securing the list 
--- 
- list-id     : internal id (primary key)
- created_at  : timestamp automatically created
- last_up_at  : timestamp of last update

##### ToDo Item: 
- name        : unique header set by user
- description : optional description of the task
- status      : pending, in progress, done 
- priority    : low, medium, high 
---
- item-id     : internal id (primary key)
- list-id     : reference to list (foreign key)
- created_at  : timestamp automatically created 
- last_up_at  : timestamp of last update

#### SQL

CREATE TABLE list (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE,
    description TEXT NULL,
    password TEXT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE item (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    list_id INTEGER NOT NULL,
    header TEXT NOT NULL,
    description TEXT NULL,
    status TEXT NOT NULL DEFAULT 'pending',
    priority TEXT NOT NULL DEFAULT 'medium',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (list_id) REFERENCES list(id) ON DELETE CASCADE
);

#### Possible Output

Clido - <List Name> ---- 
|-<priority>- [ ] <high priority item> <small_description> <deadline> 
|-<priority>- [ ] <medi priority item> <small_description> <deadline> 
|-<priority>- [ ] <low priority item> <small_description> <deadline> 
|-<priority>- [ ] <low priority item> <small_description> <deadline> 
|-<priority>- [ ] <low priority item> <small_description> <deadline> 
|-<priority>- [x] <high priority item> <small_description> <deadline> (---) 
|-<priority>- [x] <high priority item> <small_description> <deadline> (---)
