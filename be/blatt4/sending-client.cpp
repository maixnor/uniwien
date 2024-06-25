extern "C" {
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "proto.h"

void handle_challenge(int connfd) {
    message_unit msg;
    challenge_unit challenge;

    ssize_t received = recv(connfd, &msg, sizeof(msg), 0);
    if (received != sizeof(msg) || msg.msg_type != CHALLENGE) {
        std::cerr << "Failed to receive challenge message." << std::endl;
        return;
    }

    received = recv(connfd, &challenge, sizeof(challenge), 0);
    if (received != sizeof(challenge)) {
        std::cerr << "Failed to receive challenge unit." << std::endl;
        return;
    }

    switch (challenge.op) {
        case ADD:
            challenge.answer = challenge.lhs + challenge.rhs;
            break;
        case SUB:
            challenge.answer = challenge.lhs - challenge.rhs;
            break;
        case MUL:
            challenge.answer = challenge.lhs * challenge.rhs;
            break;
        case LEFT_SHIFT:
            challenge.answer = challenge.lhs << (challenge.rhs % 32);
            break;
        case RIGHT_SHIFT:
            challenge.answer = challenge.lhs >> (challenge.rhs % 32);
            break;
        default:
            std::cerr << "Unknown operation." << std::endl;
            return;
    }

    send(connfd, &msg, sizeof(msg), 0);
    send(connfd, &challenge, sizeof(challenge), 0);

    received = recv(connfd, &msg, sizeof(msg), 0);
    if (received != sizeof(msg) || msg.msg_type != SERVER_INFO) {
        std::cerr << "Failed to receive server info." << std::endl;
        return;
    }

    if (msg.server_info == CORRECT) {
        std::cout << "Challenge solved correctly." << std::endl;
    } else {
        std::cout << "Challenge solved incorrectly." << std::endl;
    }
}

int connect_to_server(const char *ip, std::uint16_t port) {
    int bool_true = 1;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return -1;
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &bool_true, sizeof(bool_true));

    struct sockaddr_in addr {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {},
        .sin_zero = {}
    };
    if (!inet_pton(AF_INET, ip, &addr.sin_addr)) {
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr))) {
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int main() {
    const std::string ip{"127.0.0.1"};
    constexpr std::uint16_t port = 1234;

    int i{0};

    while (true) {
        int connfd = connect_to_server(ip.c_str(), port);
        if (connfd == -1) {
            return EXIT_FAILURE;
        }

        cout << i++ << " ";
        handle_challenge(connfd);

        close(connfd);
    }

    return EXIT_SUCCESS;
}

