#include "client_tread.hpp"


int client_thread(int client_fd, GameProcess& game) {

    std::string draw = "Draw!\r\n";
    std::string win = "You won!\r\n";
    std::string lose = "You lost!\r\n";
    std::string result = "Your score: \t Your opponent's score:\r\n";
    std::string answer;

    std::ostringstream oss;

    std::string hello_message = "Hi! It's 'Rock, scissors, paper' game.\n\r";
    write(client_fd, hello_message.c_str(), hello_message.length());
    std::string start_message = "New game! \r\nMake your choise: rock, scissors or paper:\r\n";
    
    int my_score, opponent_score, is_winner;

    char choise;

    while(1) {
    
        write(client_fd, start_message.c_str(), start_message.length());
        recv(client_fd, &choise, 1, 0);
        choise -= '0';


        if (game.ProcessMove(client_fd, choise) == 2) {
            std::unique_lock<std::mutex> lock(game.mtx);
            game.cv.wait(lock, [&]() { return game.moves_done == true; });
        }

        game.GetResults(client_fd, &is_winner, &my_score, &opponent_score);
        

        if (is_winner == 0) {
            write(client_fd, draw.c_str(), draw.length());
        } else if (is_winner == 1) {
            write(client_fd, win.c_str(), win.length());
        } else {
            write(client_fd, lose.c_str(), lose.length());
        }
        
        write(client_fd, result.c_str(), result.length());

        oss << std::left << std::setw(17) << my_score << opponent_score << '\n';
        answer = oss.str();

        write(client_fd, answer.c_str(), answer.length());


    }












}



