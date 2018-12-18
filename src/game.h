#ifndef DATA_STRUCTURES_PROJECTS_LASER_TAG_GAME_H_
#define DATA_STRUCTURES_PROJECTS_LASER_TAG_GAME_H_

class Game {
    public:
        virtual void Play() = 0;
        virtual bool CheckForWinner() const = 0;
};
#endif // DATA_STRUCTURES_PROJECTS_LASER_TAG_GAME_H