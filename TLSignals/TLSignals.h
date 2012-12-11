//
//  TLSignals.h
//  TLSignals
//
//  Created by BSiDeUp on 11.12.12.
//  Copyright (c) 2012 Trylogic. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <functional>
#include <vector>

#ifndef __TLSignal_H_
#define __TLSignal_H_

using namespace std;

template <typename... T>
class TLSignal
{
    typedef void (^TLSignalBlock)(id, T ...args);
    vector<TLSignalBlock> blocks;
    id _target;
	
public:
	
    TLSignal(id target)
    {
        _target = target;
    }
	
    ~TLSignal()
    {
        _target = nil;
        removeAllObservers();
    }
	
	id getTarget()
	{
		return _target;
	}
	
    void addObserver( TLSignalBlock block)
    {
        if(find(blocks.begin(), blocks.end(), block) == blocks.end())
        {
            blocks.push_back(block);
        }
    }
	
    void removeObserver( TLSignalBlock block)
    {
        blocks.erase(remove(blocks.begin(), blocks.end(), block), blocks.end());
    }
	
    void removeAllObservers()
    {
        blocks.erase(blocks.begin(), blocks.end());
    }
	
    void notify ( T ...args)
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            blocks[i](_target, args...);
        }
    }
};

#endif //__TLSignal_H_
