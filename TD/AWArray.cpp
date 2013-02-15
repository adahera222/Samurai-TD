//
//  AWArray.cpp
//  TD
//
//  Created by Yifeng Wu on 16/01/13.
//
//

#include "AWArray.h"
#include "cocos2d.h"

using namespace std;

#define INVALID_INDEX   -1


int AWArray::size() {
    return m_arr.size();
}


// Add Data
//--------------
void AWArray::push(int data) {
    m_arr.push_back(data);
}


void AWArray::insert(int data, int index) {
    CCAssert(index >= 0 && index <= m_arr.size(), "---[C++]: index out of range!");
    
    vector<int>::iterator iter;
    iter = m_arr.begin();
    for (int i=0; i<index; i++, iter++);
    m_arr.insert(iter, data);
}


// Remove Data
//--------------
int AWArray::pop() {
    CCAssert(m_arr.size() > 0, "---[C++]: trying to pop from an empty array");
    
    int data = m_arr[m_arr.size()];
    m_arr.pop_back();

    return data;
}

void AWArray::removeData(int data) {
    vector<int>::iterator iter = m_arr.begin();
    for (; iter != m_arr.end(); iter++) {
        if (*iter == data) {
            m_arr.erase(iter);
            return ;
        }
    }
}

void AWArray::removeDataAtIndex(int index) {
    CCAssert(index >= 0 && index < m_arr.size(), "---[C++]: index out of range!");
    
    vector<int>::iterator iter = m_arr.begin();
    for (int i=0; i<index; i++, iter++);
    m_arr.erase(iter);
}

void AWArray::removeAllData() {
    m_arr.clear();
}


// Functions
//--------------

bool AWArray::contains(int data) {
    return getIndexForData(data) != INVALID_INDEX;
}


int AWArray::getDataAtIndex(int index) {
    CCAssert(index < m_arr.size() && index >= 0, "---[c++]: index out of range!");
    
    return m_arr[index];
}


int AWArray::getIndexForData(int data) {
    for (int i=0; i<m_arr.size(); i++) {
        if (m_arr[i] == data) {
            return i;
        }
    }
    return INVALID_INDEX;
}


void AWArray::removeDataFromArray(AWArray &arr) {
    for (int i=0; i<arr.size(); i++) {
        removeData(arr.getDataAtIndex(i));
    }
}