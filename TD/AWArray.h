//
//  AWArray.h
//  TD
//
//  Created by Yifeng Wu on 16/01/13.
//
//

#ifndef __TD__AWArray__
#define __TD__AWArray__

#include <iostream>
#include <vector.h>


class AWArray {
    std::vector<int> m_arr;
    
public:
    int size();
    
    void push(int data);
    void insert(int data, int index);
    
    int pop();
    void removeData(int data);
    void removeDataAtIndex(int index);
    void removeDataFromArray(AWArray &arr);
    void removeAllData();
    

    bool contains(int data);
    int getDataAtIndex(int index);
    int getIndexForData(int data);

};

#endif /* defined(__TD__AWArray__) */
