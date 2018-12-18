#include "player.h"

Player::Player(String name, std::size_t id) {
    SetName(name);
    SetId(id);
    SetScore(0);
    SetNumTags(0);
}
