#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <pthread.h>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

// Initialize Windows Sockets (WinSock)
void init_winsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        exit(EXIT_FAILURE);
    }
}

// Cleanup Windows Sockets (WinSock)
void cleanup_winsock() {
    WSACleanup();
}

// Function to handle receiving messages from another peer
void* receive_messages(void* sockfd) {
    SOCKET sock = *((SOCKET*)sockfd);
    char message[BUFFER_SIZE];
    string peer_username;

    while (true) {
        int bytes_received = recv(sock, message, sizeof(message) - 1, 0);
        if (bytes_received <= 0) {
            cout << "Connection closed or error occurred." << endl;
            break;
        }
        message[bytes_received] = '\0';  // Null-terminate the message
        cout << "\n" << peer_username << ": " << message << endl;
        cout << "You: ";  // Prompt for new input
    }

    closesocket(sock);
    return nullptr;
}

// Function to connect to a peer and send messages
void connect_to_peer(const string& peer_ip, const string& my_username) {
    SOCKET sock;
    sockaddr_in peer_addr;
    char message[BUFFER_SIZE];

    // Create a socket for communication
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "Socket creation failed" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(PORT);
    peer_addr.sin_addr.s_addr = inet_addr(peer_ip.c_str());  // IP address of the peer

    // Connect to the peer
    if (connect(sock, (SOCKADDR*)&peer_addr, sizeof(peer_addr)) == SOCKET_ERROR) {
        cerr << "Connection failed" << endl;
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Send username to the peer to identify the user
    send(sock, my_username.c_str(), my_username.length(), 0);

    // Create a thread to receive messages
    pthread_t receive_thread;
    pthread_create(&receive_thread, nullptr, receive_messages, (void*)&sock);

    // Main loop to send messages
    while (true) {
        cout << "You: ";
        cin.getline(message, sizeof(message));

        // Send the message to the peer (prepend with username)
        string full_message = my_username + ": " + message;
        send(sock, full_message.c_str(), full_message.length(), 0);
    }

    closesocket(sock);
}

// Function to listen for incoming connections from a peer
void listen_for_peers(const string& my_username) {
    SOCKET server_sock, new_sock;
    sockaddr_in server_addr, peer_addr;
    int addr_len = sizeof(peer_addr);
    char message[BUFFER_SIZE];
    char peer_username[BUFFER_SIZE];

    // Create a socket for listening for incoming connections
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET) {
        cerr << "Socket creation failed" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_sock, (SOCKADDR*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        cerr << "Bind failed" << endl;
        closesocket(server_sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_sock, 1) == SOCKET_ERROR) {
        cerr << "Listen failed" << endl;
        closesocket(server_sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    cout << "Waiting for a peer to connect..." << endl;

    // Accept a connection from a peer
    new_sock = accept(server_sock, (SOCKADDR*)&peer_addr, &addr_len);
    if (new_sock == INVALID_SOCKET) {
        cerr << "Accept failed" << endl;
        closesocket(server_sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Receive the peer's username
    int bytes_received = recv(new_sock, peer_username, sizeof(peer_username) - 1, 0);
    if (bytes_received <= 0) {
        cerr << "Failed to receive username from peer." << endl;
        closesocket(new_sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    peer_username[bytes_received] = '\0';  // Null-terminate the username
    cout << peer_username << " has joined the chat!" << endl;

    // Create a thread to receive messages from the peer
    pthread_t receive_thread;
    pthread_create(&receive_thread, nullptr, receive_messages, (void*)&new_sock);

    // Main loop to send messages
    while (true) {
        cout << "You: ";
        cin.getline(message, sizeof(message));

        // Send the message to the peer (prepend with username)
        string full_message = my_username + ": " + message;
        send(new_sock, full_message.c_str(), full_message.length(), 0);
    }

    closesocket(new_sock);
    closesocket(server_sock);
}

int main() {
    string peer_ip, my_username;

    // Initialize Windows sockets
    init_winsock();

    // Ask the user for their username
    cout << "Enter your username: ";
    getline(cin, my_username);

    // Ask the user whether to connect to an existing peer or wait for a connection
    cout << "Enter peer IP address (or type 'wait' to listen for incoming connection): ";
    getline(cin, peer_ip);

    if (peer_ip == "wait") {
        listen_for_peers(my_username);  // Wait for incoming connection
    } else {
        connect_to_peer(peer_ip, my_username);  // Connect to the specified peer
    }

    // Cleanup Windows sockets
    cleanup_winsock();

    return 0;
}
