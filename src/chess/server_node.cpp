// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <iostream>
// #include <cstring>
// #include <string>
// #include <sstream>
// #include <stdexcept>
// #include <algorithm>

// // max request length check
// #define MAX_REQUEST_LENGTH (13 + 1 + FS_MAXUSERNAME + 1 + FS_MAXPATHNAME + 1 + 3 + 1)

// // map for request handlers
// // std::map<std::string, handler> dispatch;

// /**
//  * Creates a tcp socket server, listens and accepts client messages
//  */
// int tcp_server(unsigned int server_port) {
//     // create socket
//     int server_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (server_socket == -1) {
//         return -1;
//     }

//     // set socket options
//     int opt = 1;
//     if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
//         return -1;
//     }

//     // initializes with zeroes
//     sockaddr_in addr{};
//     addr.sin_family = AF_INET;
//     addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     addr.sin_port = htons(server_port);

//     // bind the socket to the server
//     if (bind(server_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == -1) {
//         return -1;
//     }

//     // listen, with queue of length 30
//     if(listen(server_socket, 30) == -1) {
//         return -1;
//     }

//     // use getsockname and ntohs to get the host port #
//     sockaddr_in assigned_addr{};
//     socklen_t assigned_addr_len = sizeof(assigned_addr);
//     if (getsockname(server_socket, reinterpret_cast<sockaddr *>(&assigned_addr), &assigned_addr_len) == -1) {
//         return -1;
//     }
//     unsigned int host_port = ntohs(assigned_addr.sin_port);

//     while(true) {
//         // accept incoming connections
//         sockaddr_in client_addr{};
//         socklen_t client_size = sizeof(client_addr);
//         int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_addr), &client_size);
//         if (client_socket == -1) {
//             return -1;
//         }
//         // boost::thread(boost::bind(handle_client_req, client_socket)).detach();
//     }

//     // close socket
//     close(server_socket);
// }