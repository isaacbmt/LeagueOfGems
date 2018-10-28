cmake_minimum_required(VERSION 3.12)
project(LeagueOfGems)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 '-L/path/to/your/allegro/libs -lalleg'")


add_executable(LeagueOfGems main.cpp Characters/Player.cpp Characters/Player.h GameLevels/Game.cpp GameLevels/Game.h DataStructures/LinkedList.cpp Characters/Enemy.cpp Characters/Enemy.h GreedyAlgorithms/Dijkstra.cpp GreedyAlgorithms/Dijkstra.h Characters/Explosion.cpp Characters/Explosion.h)


target_link_libraries(LeagueOfGems -lallegro -lallegro_font -lallegro_image -lallegro_ttf -lallegro_color
        -lallegro_primitives)



