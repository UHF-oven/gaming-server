#include "struct.hpp"


Socket::Socket() {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw std::runtime_error("Socket creation failed");
}

Socket::~Socket() {
    if (fd >= 0) close(fd);
}

//Socket::Socket(const Socket&) =delete;
//Socket::Socket& operator=(const Socket&) = delete;
 
Socket::Socket(Socket&& other) noexcept : fd(other.fd){
    other.fd = -1;
}

int Socket::get() const {
    return fd;
}




GameProcess::GameProcess(int p1, int p2) {
    player1_fd = p1;
    player2_fd = p2;
    score1 = 0;
    score2 = 0;
    player1_move = 0;
    player2_move = 0;
    winner = -1;
    moves_done = false;
}

GameProcess::~GameProcess(){}


int GameProcess::ProcessMove(int fd, int command) {
        mtx.lock();
        if (fd == player1_fd) {
            if (player1_move != 0) {
                return 1;
            }
        } else if (fd == player2_fd) {
            if (player2_move != 0){
                return 1;
            }
        } else {
            return 1;
        }

        if (command < 1 || command > 3){
            return 1;
        }

        if (fd == player1_fd){
            player1_move = command;
        } else {
            player2_move = command;
        }

        if (player1_move != 0 && player2_move != 0) {
            DetermineWinner(); 
            moves_done = true;
            cv.notify_all();
        } else {
            mtx.unlock();
            return 2;
        }

        return 0;
}



void GameProcess::DetermineWinner() {
        if (player1_move == player2_move) {
            score1++;
            score2++;
            winner = 0;
        } else  if ((player1_move == 1 && player2_move == 2) || (player1_move == 2 && player2_move == 3) || (player1_move == 3 && player2_move == 1)) {
            score1++;
            winner = player1_fd;
        
        } else {
            score2++;
            winner = player2_fd;
        
        }
    
    mtx.unlock();
    }



void GameProcess::GetResults(int fd, int* is_winner, int* my_score, int* opponent_score) {

        if (winner == 0){
            *is_winner = 0;
        } else if (winner == fd) {
            *is_winner = 1;
        } else {
            *is_winner = 2;
        }

        if (fd == player1_fd){
            *my_score = score1;
            *opponent_score = score2;
        } else {
            *my_score = score2;
            *opponent_score = score1;
        }
    }


