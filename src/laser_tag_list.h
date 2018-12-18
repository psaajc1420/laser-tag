#ifndef _LASER_TAG_VEC_H_
#define _LASER_TAG_VEC_H_

#include "laser_tag.h"

class LaserTagList: public LaserTag {

    public:
        virtual void FindBestTeamScores() const override;
        virtual const int FindTeam(std::size_t) const override;      
        virtual void WriteLowVerbosity(const String&) override;
        virtual void WriteMedVerbosity(const String&) override;
        virtual void WriteHighVerbosity(const String&) override;
        virtual void Play() override;
        virtual void PrintTeamsInfo() const override;
        const bool SetPlayerData(LinkedList<Player>*,
                                 std::size_t,
                                 std::size_t,
                                 std::size_t);

};
#endif
