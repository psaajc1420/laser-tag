// Jacob Cadena
// 11/22/18
// ds_string.cpp
//
// This file implements laser tag.

#include "laser_tag.h"


LaserTag::LaserTag() {
    teams = new Team[kNumberOfTeams];
    best_players = new Player[kNumberOfTeams];
}

LaserTag::~LaserTag() {
    delete[] teams;
    delete[] file_names;
    delete[] best_players;
}

void LaserTag::Read(int num_files, char** files) {

    file_names = new String[num_files-1];
    for(std::size_t i = 0; i < num_files-1; i++) {
        file_names[i] = String(files[i+1]);
    }
}  

void LaserTag::OpenFile(const String& keyword) {

    String file_name;
    std::cout << "Open " << keyword << " file: " << std::endl;
    while(true) {

        file_name = FindFileName(keyword);
        infile.open(file_name.c_str());

        if(infile)
            break;
    
        std::cout << "Error: can't open the file" << std::endl;
    }
}

String LaserTag::FindFileName(const String& keyword) const {

    String file_name;
    while(true) {
        std::cout << "Enter filename: ";
        std::cin >> file_name;

        int found = file_name.Find(keyword);
        if(found != String::npos)
            break;

        std::cout << "Error: must contain the word ";
        std::cout << "\"" << keyword << "\"" << std::endl;
        std::cout << std::endl;
    }

    return file_name;
}

void LaserTag::ReadMatch(const String& file_name) {

    // OpenFile(file_name);
    infile.open(file_name.c_str());
    String matches_string;
    Getline(infile, matches_string);
    matches = (std::size_t) atoi(matches_string.c_str());

    String tagger_id, target_id;
    String time_elapsed, location_id;
    PlayerInfo player_info;

    for(std::size_t i = 0; i < matches; i++) {

        infile >> tagger_id >> target_id;
        infile >> time_elapsed >> location_id;

        player_info.tagger = (std::size_t) atoi(tagger_id.c_str());
        player_info.target = (std::size_t) atoi(target_id.c_str());
        player_info.time_elapsed = time_elapsed;
        player_info.tag_score = FindTagType(location_id);
        players_info.PushBack(player_info);
    }

    infile.close();
}

void LaserTag::VerbosityLevel(const String& level) {

    if(level == "vlow") {
        verbosity_level = Verbosity::kLow;
    } else if(level == "vmed") {
        verbosity_level = Verbosity::kMedium;
    } else if(level == "vhigh") {
        verbosity_level = Verbosity::kHigh;
    } else {
        std::cout << "Something is wrong" << std::endl;
    }
}  

const int LaserTag::FindTagType(const String& location_id) const {
    
    if(location_id == "1") {
        return TagType::kBack;
    } else if(location_id == "2") {
        return TagType::kChest;
    } else if(location_id == "3") {
        return TagType::kShoulder;
    } else if(location_id == "4") {
        return TagType::kLaserGun;
    } else {
       std::cout << "Something is wrong" << std::endl; 
       return 0;
    }
}

void LaserTag::CreatePlayerMap() {

    LinkedList<Player> team1 = teams[0].GetPlayers();
    LinkedList<Player> team2 = teams[1].GetPlayers();
    LinkedList<Player>::iterator it1;
    LinkedList<Player>::iterator it2;

    for(it1=team1.Begin(); it1 != team1.End(); ++it1) {
        std::size_t team1_id = (*it1).GetId();
        for(it2=team2.Begin(); it2 != team2.End(); ++it2) {
            std::size_t team2_id = (*it2).GetId();
            player_map[team1_id][team2_id] = 0;
            player_map[team2_id][team1_id] = 0;
        }
    }
}

void LaserTag::PrintPlayerMap() const {

    std::cout << std::endl << std::endl;

    PlayerMap::const_iterator it1;
    TagMap::const_iterator it2;
    for(it1 = player_map.begin(); it1 != player_map.end(); ++it1) {
        std::cout << "Tagger ID: " << it1->first;
        std::cout << std::endl;
        for(it2 = it1->second.begin(); it2 != it1->second.end(); ++it2){
            std::cout << "\t(Target ID, Tags) = (" << it2->first;
            std::cout << ", " << it2->second << ")";
            std::cout << std::endl;
        }
    }
}

void LaserTag::PrintTeamsInfo() const {
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

void LaserTag::Write(const String& file_name) {

    outfile.open(file_name.c_str());

    if(verbosity_level == Verbosity::kLow) {
        WriteLowVerbosity(file_name);
    } else if(verbosity_level == Verbosity::kMedium) {
        WriteMedVerbosity(file_name);
    } else if(verbosity_level == Verbosity::kHigh) {
        WriteHighVerbosity(file_name);
    } else {
        std::cout << "Something is wrong" << std::endl; 
    }

    outfile.close();
}

bool LaserTag::CheckForWinner() const {
  return teams[0].GetTeamScore() < teams[1].GetTeamScore();
}

bool LaserTag::ByTags(const Player& first, const Player& second) {
  return first.GetNumTags() >= second.GetNumTags();
}

bool LaserTag::ByTeam(const Team& first, const Team& second) {
  return first.GetName() < second.GetName();
}
