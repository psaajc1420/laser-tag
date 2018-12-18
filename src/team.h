#ifndef DATA_STRUCTURES_PROJECTS_LASER_TAG_TEAM_H_
#define DATA_STRUCTURES_PROJECTS_LASER_TAG_TEAM_H_

#include <fstream>

#include "custom-string/ds_string.h"
#include "linked-lists/linked_list.h"
#include "player.h"

class Team {

    private:
        String name_;
        std::ifstream infile_;
        LinkedList<Player> players_;        
        std::size_t number_of_players_;
        std::size_t team_score_;

    public:
        Team();
        Team(const String& file_name);
        String FindFileName(const String&) const;
        void OpenFile(const String&);
        void CreatePlayers(const String&);
        String GetName() const;
        void SetName(String);
        std::size_t GetTeamScore();
        void SetTeamScore(std::size_t);
        std::size_t GetNumberOfPlayers() const;
        void SetNumberOfPlayers(std::size_t);
        Player* FindPlayer(std::size_t);
        LinkedList<Player>& GetPlayers();
};

inline void Team::SetName(String name) { 
    name_ = name; 
}

inline String Team::GetName() const { 
    return name_; 
}

inline void Team::SetTeamScore(std::size_t team_score) {
    team_score_ = team_score;
}

inline void Team::SetNumberOfPlayers(std::size_t number_of_players) {
    number_of_players_ = number_of_players;
}

inline std::size_t Team::GetNumberOfPlayers() const {
    return number_of_players_;
}

inline LinkedList<Player>& Team::GetPlayers() {
    return players_;
}

#endif // DATA_STRUCTURES_PROJECTS_LASER_TAG_TEAM_H_


