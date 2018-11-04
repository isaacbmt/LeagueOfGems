cmake_minimum_required(VERSION 3.12)
project(LeagueOfGems)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 '-L/path/to/your/allegro/libs -lalleg'")


add_executable(LeagueOfGems main.cpp Characters/Player.cpp Characters/Player.h GameLevels/Game.cpp
        GameLevels/Game.h DataStructures/LinkedList.cpp Characters/Enemy.cpp Characters/Enemy.h
        GreedyAlgorithms/Dijkstra.cpp GreedyAlgorithms/Dijkstra.h Characters/Explosion.cpp Characters/Explosion.h
        Characters/Bullet.cpp Characters/Bullet.h Characters/Sword.cpp Characters/Sword.h
        GreedyAlgorithms/AstarDirectory/AStarSearch.h GreedyAlgorithms/AstarDirectory/MapSearchNode.cpp
        GreedyAlgorithms/AstarDirectory/MapSearchNode.h GreedyAlgorithms/AstarDirectory/execAStar.cpp
        GreedyAlgorithms/AstarDirectory/execAStar.h GreedyAlgorithms/AstarDirectory/globalArray.cpp
        GreedyAlgorithms/AstarDirectory/globalArray.h GreedyAlgorithms/AstarDirectory/coordinate.h Characters/Laser.cpp Characters/Laser.h Characters/Gem.cpp Characters/Gem.h GreedyAlgorithms/Kruskal.cpp GreedyAlgorithms/Kruskal.h DataStructures/Node.h DataStructures/LinkedListGen.h DataStructures/AlgoritmoGen.h GreedyAlgorithms/Prim/generadorGrafo.cpp GreedyAlgorithms/Prim/generadorGrafo.h GreedyAlgorithms/Prim/Grafo.cpp GreedyAlgorithms/Prim/Grafo.h GreedyAlgorithms/Prim/Heap.h GreedyAlgorithms/Prim/PrimSolver.cpp GreedyAlgorithms/Prim/PrimSolver.h GreedyAlgorithms/Prim/mainPrim.cpp)


target_link_libraries(LeagueOfGems -lallegro -lallegro_font -lallegro_image -lallegro_ttf -lallegro_color
        -lallegro_primitives -lallegro_audio -lallegro_acodec)



