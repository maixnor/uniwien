extern "C" {
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <csignal>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <sys/time.h>
#include "proto.h"

int random_int() {
    return rand() % std::numeric_limits<int>::max();
}

void generate_challenge(int connfd) {
    message_unit msg;
    challenge_unit challenge;

    msg.msg_type = CHALLENGE;
    msg.server_info = 0;

    challenge.op = random_int() % OP_END;
    challenge.lhs = random_int();
    challenge.rhs = random_int();
    challenge.answer = 0;

    uint32_t op = challenge.op;
    uint32_t lhs = challenge.lhs;
    uint32_t rhs = challenge.rhs;

    if (send(connfd, &msg, sizeof(msg), MSG_NOSIGNAL) == -1) {
        std::cerr << "Failed to send message unit." << std::endl;
        return;
    }
    if (send(connfd, &challenge, sizeof(challenge), MSG_NOSIGNAL) == -1) {
        std::cerr << "Failed to send challenge unit." << std::endl;
        return;
    }
  
    // max 50 ms delay
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 50000;

    if (setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        std::cerr << "Failed to set socket timeout." << std::endl;
        close(connfd);
        return;
    }

    ssize_t received = recv(connfd, &msg, sizeof(msg), 0);
    if (received != sizeof(msg) || msg.msg_type != CHALLENGE) {
        std::cerr << "Failed to receive challenge response." << std::endl;

        msg.msg_type = SERVER_INFO;
        msg.server_info = WRONG;

        if (send(connfd, &msg, sizeof(msg), MSG_NOSIGNAL) == -1) {
            std::cerr << "Failed to send challenge msg_type server info." << std::endl;
        }

        return;
    }

    received = recv(connfd, &challenge, sizeof(challenge), 0);
    if (received != sizeof(challenge)) {
        std::cerr << "Failed to receive challenge unit." << std::endl;

        msg.msg_type = SERVER_INFO;
        msg.server_info = WRONG;

        if (send(connfd, &msg, sizeof(msg), MSG_NOSIGNAL) == -1) {
            std::cerr << "Failed to send challenge sizeof server info." << std::endl;
        }

        return;
    }

    if (challenge.op != op || challenge.lhs != lhs || challenge.rhs != rhs) {
        std::cerr << "client did some wonky stuff with the challenge variables!" << std::endl;

        msg.msg_type = SERVER_INFO;
        msg.server_info = WRONG;

        if (send(connfd, &msg, sizeof(msg), MSG_NOSIGNAL) == -1) {
            std::cerr << "failed to send" << std::endl;
        }

        return;
    }

    bool correct = false;
    switch (challenge.op) {
        case ADD:
            correct = (challenge.answer == challenge.lhs + challenge.rhs);
            break;
        case SUB:
            correct = (challenge.answer == challenge.lhs - challenge.rhs);
            break;
        case MUL:
            correct = (challenge.answer == challenge.lhs * challenge.rhs);
            break;
        case LEFT_SHIFT:
            correct = (challenge.answer == (challenge.lhs << (challenge.rhs % 32)));
            break;
        case RIGHT_SHIFT:
            correct = (challenge.answer == (challenge.lhs >> (challenge.rhs % 32)));
            break;
    }

    msg.msg_type = SERVER_INFO;
    msg.server_info = correct ? CORRECT : WRONG;

    if (send(connfd, &msg, sizeof(msg), MSG_NOSIGNAL) == -1) {
        std::cerr << "Failed to send feedback server info." << std::endl;
    }
}

void accept_and_handle(int sockfd) {
    int connfd;
    struct sockaddr_in conn_addr{};
    socklen_t addr_len = sizeof(conn_addr);

    connfd = accept(sockfd, reinterpret_cast<struct sockaddr *>(&conn_addr), &addr_len);
    if (connfd == -1) {
        return;
    }

    generate_challenge(connfd);

    close(connfd);
}

int create_server_socket(std::uint16_t port) {
    int bool_true = 1;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return -1;
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &bool_true, sizeof(bool_true));

    struct sockaddr_in addr {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {.s_addr = INADDR_ANY},
        .sin_zero = {}
    };

    if (bind(sockfd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr))) {
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, 1)) {
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int main() {
    srand(69420);
    constexpr std::uint16_t port = 1234;

    int sockfd = create_server_socket(port);
    if (sockfd == -1) {
        return EXIT_FAILURE;
    }

    int i = 0;
    while (true) {
        std::cout << "pre handle " << i << std::endl;
        accept_and_handle(sockfd);
        std::cout << "post handle " << i << std::endl;
        i++;
    }

    std::cout << "exit loop unexpectedly";

    close(sockfd);

    return EXIT_SUCCESS;
}

