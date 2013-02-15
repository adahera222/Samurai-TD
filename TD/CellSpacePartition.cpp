//
//  CellSpacePartition.cpp
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#include "CellSpacePartition.h"
//#include "BaseGameEntity.h"
#include "CollisionComponent.h"

USING_NS_CC;

//-------------------------
//          Cell
//-------------------------

Cell::~Cell() {
    CC_SAFE_RELEASE(m_pMembers);
}


Cell::Cell(CCRect box) : m_box(box) {
    m_pMembers = CCArray::create();
    m_pMembers->retain();
}


Cell *Cell::create(cocos2d::CCRect box) {
    Cell *cell = new Cell(box);
    if (cell) {
        cell->autorelease();
        return cell;
    }
    CCLog("--- Note: cannot create cell");
    CC_SAFE_DELETE(cell);
    return NULL;
}


void Cell::addEntity(CollisionComponent *entity) {
    // If the entity has already been in the cell, ignore it.
    if (m_pMembers->containsObject(entity)) {
        return ;
    }
    m_pMembers->addObject(entity);
}


void Cell::removeEntity(CollisionComponent *entity) {
    m_pMembers->removeObject(entity);
}


//-------------------------
//   CellSpacePartition
//-------------------------


//
// Construction && Deconstruction - BEGIN
//
CellSpacePartition::~CellSpacePartition() {
    CC_SAFE_RELEASE(m_pCells);
    
    CC_SAFE_RELEASE(m_pNeighbours);
}


CellSpacePartition *CellSpacePartition::create(const cocos2d::CCSize &spaceSize, int numCellsX, int numCellsY, int maxEntities) {
    CellSpacePartition *partition = new CellSpacePartition();
    if (partition && partition->init(spaceSize, numCellsX, numCellsY, maxEntities)) {
        partition->autorelease();
        return partition;
    }
    CCLog("--- Note: cannot create CellSpacePartition");
    CC_SAFE_DELETE(partition);
    return NULL;
}


bool CellSpacePartition::init(const cocos2d::CCSize &spaceSize, int numCellsX, int numCellsY, int maxEntities) {
    m_spaceSize = spaceSize;
    
    m_iNumCellsX = numCellsX;
    
    m_iNumCellsY = numCellsY;
    
    float h = spaceSize.height / numCellsY;
    float w = spaceSize.width / numCellsX;
    
    m_cellSize = CCSizeMake(w, h);
    
    m_pNeighbours = CCArray::create();
    m_pNeighbours->retain();
    
    m_pCells = CCArray::create();
    m_pCells->retain();
    
    for (int y=0; y<numCellsY; y++) {
        for (int x=0; x<numCellsX; x++) {
            float originX = x * m_cellSize.width;
            float originY = y * m_cellSize.height;
            
            Cell *cell = Cell::create(CCRectMake(originX, originY, m_cellSize.width, m_cellSize.height));
            m_pCells->addObject(cell);
            
            //CCLog("cell x:%f, y:%f, w:%f, h:%f", cell->m_box.origin.x, cell->m_box.origin.y, cell->m_box.size.width, cell->m_box.size.height);
        }
    }
    
    return true;
}
// END


//
// Logics - BEGIN
//
int CellSpacePartition::getIndexForPosition(const cocos2d::CCPoint pos) const {
    int column = (int)(pos.x/m_cellSize.width);
    int row = (int)(pos.y/m_cellSize.height);
    
    return row * m_iNumCellsX + column;
}


void CellSpacePartition::addEntity(CollisionComponent *entity) {
    CCAssert(entity, "--- addEntity: entity is NULL");
    
    int index = getIndexForPosition(entity->getPosition());
    
    Cell *cell = (Cell *)m_pCells->objectAtIndex(index);
    cell->addEntity(entity);
}


void CellSpacePartition::removeEntity(CollisionComponent *entity) {
    CCAssert(entity, "--- removeEntity: entity is NULL");
    
    int index = getIndexForPosition(entity->getPosition());
    
    Cell *cell = (Cell *)m_pCells->objectAtIndex(index);
    cell->removeEntity(entity);
}


void CellSpacePartition::updateEntity(CollisionComponent *entity, const cocos2d::CCPoint &oldPosition) {
    int oldIndex = getIndexForPosition(oldPosition);
    int newIndex = getIndexForPosition(entity->getPosition());
    
    if (newIndex == oldIndex) {
        return ;
    }
    
    // the entity has moved into another cell
    ((Cell *)m_pCells->objectAtIndex(oldIndex))->removeEntity(entity);
    ((Cell *)m_pCells->objectAtIndex(newIndex))->addEntity(entity);
    
}


void CellSpacePartition::calculateNeighbours(const CollisionComponent *entity, double queryR, double collisionR) {
    m_pNeighbours->removeAllObjects();
    
    // Create a query box for the specified entity.
    // The center of the box is the entity's position.
    //CCRect queryBox = CCRectMake(entity->getPosition().x-queryR, entity->getPosition().y-queryR, 2*queryR, 2*queryR);
    
    static CCRect queryBox;
    queryBox.origin.x = entity->getPosition().x - queryR;
    queryBox.origin.y = entity->getPosition().y - queryR;
    queryBox.size.width = 2 * queryR;
    queryBox.size.height = 2 * queryR;
    
    for (int i=0; i<m_pCells->count(); i++) {   // each cell
        Cell *curCell = (Cell *)m_pCells->objectAtIndex(i);
        if (queryBox.intersectsRect(curCell->m_box)) {
            for (int j=0; j<curCell->m_pMembers->count(); j++) {    // members in a cell
                CollisionComponent *member = (CollisionComponent *)curCell->m_pMembers->objectAtIndex(j);
                
                // If the member is the entity itself, ignore it.
                if (entity == member) {
                    continue;
                }
                
                double maxDist = collisionR + member->getCollisionRadius();
                
                if (ccpDistanceSQ(entity->getPosition(), member->getPosition()) < maxDist * maxDist) {
                    m_pNeighbours->addObject(member);
                }
            }
        }
    }
}


void CellSpacePartition::clearCells() {
    for (int i=0; i<m_pCells->count(); i++) {
        ((Cell *)m_pCells->objectAtIndex(i))->m_pMembers->removeAllObjects();
    }
}