#ifndef DATA_STRUCTURES_PROJECTS_LASER_TAG_PLAYER_H_
#define DATA_STRUCTURES_PROJECTS_LASER_TAG_PLAYER_H_

#include "custom-string/ds_string.h"

// Creates a player that is able to keep
// track of the number of tags and tag scores
class Player { 

    private:
        String name_;        
        std::size_t id_;
        std::size_t num_tags_;
        std::size_t tag_scores_;

    public:
        Player(String name=" ", std::size_t ID=0);
        String GetName() const;
        void SetName(String);
        std::size_t GetId() const;
        void SetId(std::size_t);
        std::size_t GetNumTags() const;
        void SetNumTags(std::size_t);
        std::size_t GetScore() const;
        void SetScore(std::size_t);
        void AddScore(std::size_t);
        void IncreaseTags();

};

// Standards getters and setters
inline String Player::GetName() const { return name_; }
inline void Player::SetName(String name) { name_ = name; } 
inline std::size_t Player::GetId() const { return id_; }
inline void Player::SetId(std::size_t id) { id_ = id; }
inline std::size_t Player::GetNumTags() const { return num_tags_; }
inline void Player::SetNumTags(std::size_t num_tags) { num_tags_ = num_tags; }
inline std::size_t Player::GetScore() const { return tag_scores_; }
inline void Player::SetScore(std::size_t tag_scores) { tag_scores_ = tag_scores; }
inline void Player::IncreaseTags() { num_tags_++; }

// Adds points to the previous accumulated score
inline void Player::AddScore(std::size_t new_tag_score) { 
    tag_scores_ += new_tag_score; 
}

#endif // DATA_STRUCTURES_PROJECTS_LASER_TAG_PLAYER_H_


