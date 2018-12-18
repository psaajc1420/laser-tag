#include "laser_tag.h"
#include "laser_tag_list.h"
#include "laser_tag_vector.h"

int main(int argc, char** argv) {
    
    LaserTag* laser_tag;
    LaserTagList laser_tag_list;

    laser_tag = &laser_tag_list;
    laser_tag->Read(argc, argv);
    laser_tag->Play();

    return 0;
}