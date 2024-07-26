#ifndef SERVER_NODE_HPP
#define SERVER_NODE_HPP

class server_node;

class service {
    server_node *node;
public:
    service(server_node *node) {
        this->node = node;
    }
    virtual void req()  = 0;
    virtual void recv() = 0;
};

class append_service : public service {
public:
    append_service(server_node *node) : service(node) {}
    void req();
    void recv();
};

class data_transport_service : public service {
public:
    data_transport_service(server_node *node) : service(node) {}
    void req();
    void recv();
};

class chess_move_service : public service {
public:
    chess_move_service(server_node *node) : service(node) {}
    void req();
    void resp();
};

class chess_move_service {
    void req();
    void resp();
};

class server_node {
    server_node();
};

#endif