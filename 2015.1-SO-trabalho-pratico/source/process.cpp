#include "process.h"

process::process(int id, int creationDate, int durationTime, int priority)
{
    //ctor
    this->ID = id;
    this->creationDate = creationDate;
    this->startDate = creationDate;
    this->endDate = creationDate;
    this->durationTime = durationTime;
    this->executionTime = durationTime;
    this->priority = priority;
    this->state = 0;
}


process::~process()
{
    //dtor
}
