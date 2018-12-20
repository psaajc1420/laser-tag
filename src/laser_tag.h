// Jacob Cadena
// 

#ifndef DATA_STRUCTURES_PROJECTS_LASER_TAG_LASER_TAG_H_
#define DATA_STRUCTURES_PROJECTS_LASER_TAG_LASER_TAG_H_

#include <algorithm> 
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "laser-tag/strings/ds_string.h"
#include "laser-tag/linked-lists/linked_list.h"
#include "game.h"
#include "player.h"
#include "team.h"

// Represents the levels of verbosity for the
// output file. 
enum class Verbosity {
    kLow, kMedium, kHigh
};

// An abstract class to implement a laser tag game.
class LaserTag : public Game {

    protected:
        // Contains the values(points) given depending
        // on the location of the tag.
        struct TagType {
            static const int kBack = 5;
            static const int kChest = 8;
            static const int kShoulder = 10;
            static const int kLaserGun = 15;
        };

        // A helper struct that holds all the information
        // read in by the match file. 
        struct PlayerInfo {
            std::size_t tagger;
            std::size_t target;
            String time_elapsed;
            std::size_t tag_score;
        };

        Team* teams;
        String* file_names;
        Verbosity verbosity_level;
        Player* best_players;
        LinkedList<PlayerInfo> players_info;

        // A map that relates a user to number of tags recieved
        typedef std::unordered_map<std::size_t, std::size_t> TagMap;

        // A map that relates the tagger id to another map that 
        // contains the targets user id with the corresponding 
        // number of tags received by the tagger.
        typedef std::unordered_map<std::size_t, TagMap> PlayerMap;
  
        PlayerMap player_map;

        std::ifstream infile;
        std::ofstream outfile;
        std::size_t matches;
        
        // The number of teams allowed for laser tag
        const int kNumberOfTeams = 2;

        // The number of command line arguments used
        const int kNumberOfFiles = 5;
    
    public:
        LaserTag();
        virtual ~LaserTag();

        virtual void FindBestTeamScores() const = 0;
        virtual const int FindTeam(std::size_t) const = 0;
        virtual void Play() = 0;
        virtual void PrintTeamsInfo() const = 0;
        virtual void WriteLowVerbosity(const String&) = 0;
        virtual void WriteMedVerbosity(const String&) = 0;
        virtual void WriteHighVerbosity(const String&) = 0;

        void CreatePlayerMap();
        void PrintPlayerMap() const;
        const int FindTagType(const String&) const;
        String FindFileName(const String&) const;
        void OpenFile(const String&);
        void Read(int, char**);
        void ReadMatch(const String&);
        void VerbosityLevel(const String&);        
        void Write(const String&);
        bool CheckForWinner() const;

        // binary predicates that take two values of the same
        // type as the list.
        static bool ByTags(const Player&, const Player&);
        static bool ByTeam(const Team&, const Team&);
};
#endif // DATA_STRUCTURES_PROJECTS_LASER_TAG_LASER_TAG_H_
