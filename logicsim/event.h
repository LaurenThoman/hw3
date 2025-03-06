
#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
    bool operator()(const Event* lhs, const Event* rhs){
      return lhs->time < rhs->time; 
    }
} EventLess;
	
#endif
#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
        //write the operator() required to make this a functor that compares Events by tim
    bool operator()(Event* s1, Event* s2) const{
        return s1->time > s2->time; 
    }
} EventLess;
	
#endif
