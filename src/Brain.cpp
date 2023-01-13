
#include "Brain.h"

namespace Brain{
    std::vector<std::vector<int>> Brain::calculateBFS(std::vector<std::string> map) {
        //init result vector
        std::vector<std::vector<int>> result(map.size());
        for(int i=0 ; i<map.size() ; i++)
            result[i] = std::vector<int>(map[0].size(),-1);

        sf::Vector2i pacLoc;
        bool found = false;
        for(int i=0 ; i<map.size() && !found; i++)
            for(int j=0 ; j<map.size() && !found; j++){
                if(map[i][j] == PACMAN_S){
                    pacLoc.x = j;
                    pacLoc.y = i;
                    found = true;
                }
            }

        std::queue<sf::Vector2i> q;
        q.push(pacLoc);
        result[pacLoc.y][pacLoc.x] = 0;
        int blocked = result.size()*result[0].size();
//        blocked = -2;
        while(!q.empty()){
            auto current = q.front();
            q.pop();
            if(current.x+1<map[0].size() && result[current.y][current.x+1] == -1){
                if(map[current.y][current.x+1] == WALL_S || map[current.y][current.x+1]==DOOR_S){
                    result[current.y][current.x+1] = blocked;
                }else{
                    q.push(sf::Vector2i(current.x+1,current.y));
                    result[current.y][current.x+1] = result[current.y][current.x]+1;
                }
            }
            if(current.x-1>=0 && result[current.y][current.x-1] == -1){
                if(map[current.y][current.x-1] == WALL_S || map[current.y][current.x-1]==DOOR_S){
                    result[current.y][current.x-1] = blocked;
                }else{
                    q.push(sf::Vector2i(current.x-1,current.y));
                    result[current.y][current.x-1] = result[current.y][current.x]+1;
                }
            }
            if(current.y+1<map.size() && result[current.y+1][current.x] == -1){
                if(map[current.y+1][current.x] == WALL_S || map[current.y+1][current.x]==DOOR_S){
                    result[current.y+1][current.x] = blocked;
                }else{
                    q.push(sf::Vector2i(current.x,current.y+1));
                    result[current.y+1][current.x] = result[current.y][current.x]+1;
                }
            }
            if(current.y-1>=0 && result[current.y-1][current.x] == -1){
                if(map[current.y-1][current.x] == WALL_S || map[current.y-1][current.x]==DOOR_S){
                    result[current.y-1][current.x] = blocked;
                }else{
                    q.push(sf::Vector2i(current.x,current.y-1));
                    result[current.y-1][current.x] = result[current.y][current.x]+1;
                }
            }
        }


//        for(int i=0 ; i<result.size() ; i++){
//            for(int j=0 ; j<result[i].size() ; j++)
//                std::cout << result[i][j] << "   ";
//            std::cout << "\n";
//        }
        return result;
    }

    std::vector<std::string> Brain::addObjectsToMap(std::vector<std::unique_ptr<DynamicObject>> *objects, std::vector<std::string> map, float tileSize, sf::Vector2f topLeft) {
        auto pacmanLoc = (*objects)[0]->getSprite().getPosition()-topLeft + sf::Vector2f(1,1);
        map[(int)(pacmanLoc.y/tileSize)][(int)(pacmanLoc.x/tileSize)] = PACMAN_S;
        for(int i=1 ; i<objects->size() ; i++){
            auto ghostLoc = (*objects)[i]->getSprite().getPosition()-topLeft+ sf::Vector2f(1,1);
            map[(int)(ghostLoc.y/tileSize)][(int)(ghostLoc.x/tileSize)] = GHOST_S;
        }
        return map;
    }
}