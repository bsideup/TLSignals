//
//  TLSignals.h
//  TLSignals
//
//  Created by BSiDeUp on 11.12.12.
//  Copyright (c) 2012 Trylogic. All rights reserved.
//

#include <objc/objc.h>

#define tl_synthesize_signal(propName, T...) \
\
-(TLSignal<T> *)propName \
{\
if(_##propName == nil) { _##propName = new TLSignal<T>(self);} \
return _##propName; \
} \
TLSignal<T> *_##propName;

#ifndef __TLSignal_H_
#define __TLSignal_H_

#include <functional>
#include <vector>
#include <algorithm>
#import <objc/message.h>

template <typename... T>
class TLSignal
{
	
public:
    typedef void (^TLSignalBlock)(TLSignal *sig, T ...args);
	
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
        if(std::find(blocks.begin(), blocks.end(), block) == blocks.end())
        {
            blocks.push_back(block);
        }
    }
	
    void removeObserver( TLSignalBlock block)
    {
        blocks.erase(std::remove(blocks.begin(), blocks.end(), block), blocks.end());
    }
	
    void removeAllObservers()
    {
        blocks.erase(blocks.begin(), blocks.end());
    }
	
    void notify ( T ...args)
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            blocks[i](this, args...);
        }
    }
	
private:
    std::vector<TLSignalBlock> blocks;
    id _target;
};

#endif //__TLSignal_H_
