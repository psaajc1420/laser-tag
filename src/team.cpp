#include "team.h"

Team::Team() {
    SetName("");
    SetNumberOfPlayers(0);
    SetTeamScore(0);
}

Team::Team(const String& file_name) {
    SetName("");
    SetNumberOfPlayers(0);
    CreatePlayers(file_name);
    SetTeamScore(0);
}

void Team::CreatePlayers(const String& file_name) {

    // OpenFile(file_name);
    infile_.open(file_name.c_str());
    String team_name, player_name;
    String num_players_str, user_id_str, line;
    std::size_t user_id, num_players;
    
    Getline(infile_, team_name);
    Getline(infile_, num_players_str);

    num_players = (std::size_t) atoi(num_players_str.c_str());

    SetName(team_name);
    SetNumberOfPlayers(num_players);

    while(infile_ >> user_id_str >> player_name) {
        user_id = (std::size_t) atoi(user_id_str.c_str());
        players_.PushBack(Player(player_name, user_id));
    }  

    infile_.close();
}

void Team::OpenFile(const String& keyword) {

    String file_name;
    std::cout << "Open " << keyword << " file: " << std::endl;
    while(true) {

        file_name = FindFileName(keyword);
        infile_.open(file_name.c_str());

        if(infile_)
            break;
        
        std::cout << "Error: can't open the file" << std::endl;
    }
}

String Team::FindFileName(const String& keyword) const {

    String file_name;
    while(true) {
        std::cout << "Enter filename: ";
        std::cin >> file_name;

        std::size_t found = file_name.Find(keyword);
        if(found != String::npos)
            break;

        std::cout << "Error: must contain the word ";
        std::cout << "\"" << keyword << "\"" << std::endl;
        std::cout << std::endl;
    }

    return file_name;
}

std::size_t Team::GetTeamScore() {
    Player player;
    for(LinkedList<Player>::iterator it=players_.Begin();
        it != players_.End(); ++it) {
         player = *it;
        team_score_ += player.GetScore();
    }
    return team_score_;
}

Player* Team::FindPlayer(std::size_t user_id) {
    
    Player player;
    for(LinkedList<Player>::iterator it=players_.Begin();
        it != players_.End(); ++it) {
        player = *it;
        if(player.GetId() == user_id)
            return &*it;
    }
    
    std::cerr << "Couldn't find a player" << std::endl;
    std::exit(EXIT_FAILURE);
}
