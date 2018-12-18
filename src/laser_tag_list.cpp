#include "laser_tag_list.h"

void LaserTagList::Play() {
    
    std::cout << "Creating teams... " << std::endl;
    teams[0] = Team(file_names[0]);
    teams[1] = Team(file_names[1]);
    
    std::sort(teams, teams+kNumberOfTeams, ByTeam);

    std::cout << "Reading match file to play... " << std::endl;
    ReadMatch(file_names[2]);
    std::cout << "Initializing the verbosity level... " << std::endl;
    VerbosityLevel(file_names[4]);
    std::cout << "Playing game..." << std::endl;

    CreatePlayerMap();
  
    Team* team;
    PlayerInfo player_info;
    LinkedList<Player>* players;
    String team_name;

    for(LinkedList<PlayerInfo>::iterator it = players_info.Begin();
        it != players_info.End(); ++it) {
        
        player_info = *it;
        int team_index = FindTeam(player_info.tagger);
        
        if(team_index != -1) {
            team = &teams[team_index];
        } else {
            std::cerr << "Couldn't find team " << std::endl;
            std::exit(EXIT_FAILURE);
        }
        
        player_map[player_info.tagger][player_info.target]++;
        players = &team->GetPlayers();
        SetPlayerData(players, player_info.tagger, 
                      player_info.target, player_info.tag_score);
        players->Sort(ByTags);
    }
    
    Write(file_names[3]);
}

void LaserTagList::PrintTeamsInfo() const {
    LinkedList<Player> players;
    LinkedList<Player>::iterator it;
    Player player;
    for(int i = 0; i < kNumberOfTeams; i++) {
        std::cout << "Team Name: " << teams[i].GetName() << std::endl;
        std::cout << "Number of Players: " << teams[i].GetNumberOfPlayers();
        std::cout << std::endl;

        std::cout << "Player List: " << std::endl;
        players = teams[i].GetPlayers();
        for(it = players.Begin(); it != players.End(); ++it) {
            player = *it;
            std::cout << "ID: " << player.GetId();
            std::cout << ", Name: " << player.GetName();
        }
        std::cout << std::endl;
    }
}

const bool LaserTagList::SetPlayerData(LinkedList<Player>* players, 
                                   std::size_t tagger_id,
                                   std::size_t target_id,
                                   std::size_t score) {
    Player player;
    LinkedList<Player>::iterator it;
    for(it=players->Begin(); it != players->End(); ++it) {
        player = *it;
        if(player.GetId() == tagger_id) {
            (*it).AddScore(score);
            (*it).IncreaseTags();
            return true;
        }
    }
    return false;
}


const int LaserTagList::FindTeam(std::size_t user_id) const {
    LinkedList<Player> players;
    LinkedList<Player>::iterator it;
    Player player;
    for(int i = 0; i < kNumberOfTeams; i++) {
        LinkedList<Player> players = teams[i].GetPlayers();
        for(it = players.Begin(); it !=  players.End(); ++it) {  
            player = *it;
            if(player.GetId() == user_id) return i;
        }
    }
    return -1;
}

void LaserTagList::FindBestTeamScores() const {
    LinkedList<Player>* players;
    LinkedList<Player>::iterator it;
    Player player;
    for(int i = 0; i < kNumberOfTeams; i++) {
        players = &teams[i].GetPlayers();
        best_players[i] = players->Front();
        for(it = players->Begin(); it !=  players->End(); ++it) {  
            player = *it;
            int player_score = player.GetScore();
            if(player_score >  best_players[i].GetScore()){
                best_players[i] = player;
            }
        }
    }
}

void LaserTagList::WriteLowVerbosity(const String& file_name) {

    for(int i = 0; i < kNumberOfTeams; i++) {
        outfile << teams[i].GetName() << ": ";
        outfile << teams[i].GetTeamScore() << " points\n";
    }
    String team_name = "";
    if(CheckForWinner()) {
        team_name = teams[1].GetName();
    } else {
        team_name = teams[0].GetName();
    }
    outfile << "Overall Winner: " << team_name << "\n";
}

void LaserTagList::WriteMedVerbosity(const String& file_name) {
    LinkedList<Player> players;
    LinkedList<Player>::iterator it;
    Player player;
    for(int i = 0; i < kNumberOfTeams; i++) {
        players = teams[i].GetPlayers();
        outfile << teams[i].GetName() << std::endl;
        for(it = players.Begin(); it !=  players.End(); ++it) {  
            Player player = *it;
            outfile << "\t" << player.GetName() << " has a total of ";
            std::size_t num_tags = player.GetNumTags();
            if(num_tags != 1) {
              outfile << num_tags << " tags" << std::endl;
            } else {
              outfile << num_tags << " tag" << std::endl;
            }
        }
        outfile << std::endl;
    }
    FindBestTeamScores();
    for(int i = 0; i < kNumberOfTeams; i++) {
        outfile << "Best score from ";
        outfile << teams[i].GetName() << ": ";
        outfile << best_players[i].GetName() << " (";
        outfile << best_players[i].GetScore();
        outfile << " points)" << std::endl;
    }
    for(int i = 0; i < kNumberOfTeams; i++) {
        outfile << teams[i].GetName() << ": ";
        outfile << teams[i].GetTeamScore() << " points\n";
    }
    String team_name = "";
    if(CheckForWinner()) {
        team_name = teams[1].GetName();
    } else {
        team_name = teams[0].GetName();
    }
    outfile << "Overall Winner: " << team_name << "\n";
}

void LaserTagList::WriteHighVerbosity(const String& file_name) {

    Player* target_player;
    Player player;
    LinkedList<Player> players;
    LinkedList<Player>::iterator list_it;
    TagMap::iterator tag_it;
    TagMap tag_map;
    String target_player_name;
    String tagger_player_name;
    for(int i = 0; i < kNumberOfTeams; i++) {
        players = teams[i].GetPlayers();
        outfile << teams[i].GetName() << std::endl;
        for(list_it = players.Begin(); list_it != players.End(); ++list_it) {  
            player = *list_it;
            tagger_player_name = player.GetName();
            std::size_t tagger_id = player.GetId();
            tag_map = player_map[tagger_id];
            for(tag_it = tag_map.begin(); tag_it != tag_map.end(); ++tag_it) {
                if(i == 0) {
                    target_player = teams[1].FindPlayer(tag_it->first);
                } else {
                    target_player = teams[0].FindPlayer(tag_it->first);
                }
                target_player_name = target_player->GetName();
                outfile << "\t" << tagger_player_name << " tagged ";
                outfile << target_player_name << " " << tag_it->second;
                outfile << " times" << std::endl; 
            } 
            outfile << "\t" << tagger_player_name << " had a total of ";
            std::size_t num_tags = player.GetNumTags();
            if(num_tags != 1) {
              outfile << num_tags << " tags" << std::endl;
            } else {
              outfile << num_tags << " tag" << std::endl;
            }
        }
        outfile << std::endl;
    }
    FindBestTeamScores();
    for(int i = 0; i < kNumberOfTeams; i++) {
        outfile << "Best score from ";
        outfile << teams[i].GetName() << ": ";
        outfile << best_players[i].GetName() << " (";
        outfile << best_players[i].GetScore();
        outfile << " points)" << std::endl;
    }
    for(int i = 0; i < kNumberOfTeams; i++) {
        outfile << teams[i].GetName() << ": ";
        outfile << teams[i].GetTeamScore() << " points\n";
    }
    String team_name = "";
    if(CheckForWinner()) {
        team_name = teams[1].GetName();
    } else {
        team_name = teams[0].GetName();
    }
    outfile << "Overall Winner: " << team_name << "\n";
}

