
#include "Brain.h"

namespace Brain{

    /**
     * calculate a BFS tree, distances from the pacman on the map.
     * @param map
     * @return
     */
    std::vector<std::vector<int>> Brain::calculateBFS(std::vector<std::string> map) {

        //init result vector
        std::vector<std::vector<int>> result(map.size());
        for(int i=0 ; i<map.size() ; i++)
            result[i] = std::vector<int>(map[0].size(),-1);

        // found the pacman location on the board
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

        // initialize the queue.
        std::queue<sf::Vector2i> q;
        q.push(pacLoc);
        result[pacLoc.y][pacLoc.x] = 0;
        int blocked = result.size()*result[0].size();
        // while the queue is not empty, continue research the map.
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

        return result;
    }

    /**
     * add the pacman to the map
     * @param pacloc the location of the pacman
     * @param map the map to add to.
     * @param tileSize tile size
     * @param topLeft to left corner coordinated
     * @param pacsize the pacman size
     * @return the map with the pacman inside
     */
    std::vector<std::string> Brain::addObjectsToMap(sf::Vector2f pacloc, std::vector<std::string> map, float tileSize, sf::Vector2f topLeft,float pacsize) {
        pacloc = pacloc - topLeft + sf::Vector2f(pacsize/2,pacsize/2);
        map[(int)(pacloc.y/tileSize)][(int)(pacloc.x/tileSize)] = PACMAN_S;
        return map;
    }

    /**
     * calculate in what tile location is
     * @param location the location to calculate
     * @param bounds the board bounce
     * @param size the size of the object
     * @return
     */
    sf::Vector2i calcMyTile(sf::Vector2f location, Bounds bounds,float size){
        auto topLeft = sf::Vector2f(bounds.topLeftX,bounds.topLeftY);
        location = location - topLeft + sf::Vector2f(size/2,size/2);
        return sf::Vector2i((int)(location.x/bounds.tile),(int)(location.y/bounds.tile));
    }
}