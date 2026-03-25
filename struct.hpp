#ifndef MY_STRUCTURES
#define MY_STRUCTURES

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <condition_variable>
#include <mutex>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>




class Socket {
  private:
    int fd;

  public:
    Socket();
    ~Socket();
    
    Socket(const Socket&) = delete;
    Socket(Socket&& other) noexcept;
    Socket& operator=(const Socket&) = delete;

    int get() const;
};




class GameProcess {
  public:
    std::mutex mtx;
    std::condition_variable cv;


    int player1_fd, player2_fd;
    int score1, score2;
    int condition;
    int player1_move, player2_move;
    int winner;

    bool moves_done;

    GameProcess(int p1, int p2);
    ~GameProcess();
    int ProcessMove(int fd, int command);
    void DetermineWinner();
    void GetResults(int fd, int* is_winner, int* my_score, int* opponent_score);
    void ResetNewRound();
};






#endif
