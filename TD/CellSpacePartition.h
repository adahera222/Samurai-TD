//
//  CellSpacePartition.h
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#ifndef __TD__CellSpacePartition__
#define __TD__CellSpacePartition__

#include <iostream>
#include "cocos2d.h"

//class BaseGameEntity;
class CollisionComponent;

//-------------------------
//          Cell
//-------------------------

/**
 * A cell is the basic unit that makes up the collision space in the game.
 
 * Entities that need to check collision against each other should be added into the cells according to their position.
 */
class Cell : public cocos2d::CCObject {
public:
    cocos2d::CCArray *m_pMembers;
    
    cocos2d::CCRect m_box;
    
    ~Cell();
    
    Cell(cocos2d::CCRect box);
    
    static Cell *create(cocos2d::CCRect box);
    
    void addEntity(CollisionComponent *entity);
    
    void removeEntity(CollisionComponent *entity);
};



//-------------------------
//   CellSpacePartition
//-------------------------

/**
 * This class contains all the cells and is in charge of the logic of collision detection.
 */
class CellSpacePartition : public cocos2d::CCObject {
private:
    cocos2d::CCArray *m_pCells;
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCArray *, m_pNeighbours, Neighbours);
    
    // The size for the whole collision space in the game.
    // Usually the whole game map/world.
    cocos2d::CCSize m_spaceSize;
    
    // Number of cells in the direction of X/Y axis.
    int m_iNumCellsX;
    int m_iNumCellsY;
    
    // Size of each cell, can be calculated by m_spaceSize & m_iNumCellsX and m_iNumCellsY.
    cocos2d::CCSize m_cellSize;
    
    // get index for a specific position in game space
    inline int getIndexForPosition(const cocos2d::CCPoint pos) const;
    
public:
    ~CellSpacePartition();
    
    static CellSpacePartition *create(const cocos2d::CCSize &spaceSize, int numCellsX, int numCellsY, int maxEntities);

    bool init(const cocos2d::CCSize &spaceSize, int numCellsX, int numCellsY, int maxEntities);

    // Add/Remove an entity, add/remove them to/from proper cell.
    void addEntity(CollisionComponent *entity);
    void removeEntity(CollisionComponent *entity);

    // Update an entity's cell by calling this from your entity's update method
    void updateEntity(CollisionComponent *entity, const cocos2d::CCPoint &oldPosition);
    
    // Calculate and set the neigbours of a specified entity.
    // We cannot use the query radius for collision detection and vise versa.
    void calculateNeighbours(const CollisionComponent *entity, double queryRadius, double collisionR);

    //void calculateNeighbours(const CollisionComponent *entity, double queryRadius);
    
    // Clear all cells
    void clearCells();
    
    // For testing
    cocos2d::CCArray *getCells() {
        return m_pCells;
    }
};


#endif /* defined(__TD__CellSpacePartition__) */
