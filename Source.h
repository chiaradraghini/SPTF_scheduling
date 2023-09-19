#ifndef __SPTF_SOURCE_H_
#define __SPTF_SOURCE_H_

#include <omnetpp.h>
#include <NewFieldsMessage_m.h>

using namespace omnetpp;

class Source : public cSimpleModule
{
    public:
        Source();
        virtual ~Source();
    private:
        cMessage *sendMessageEvent;
        int nbGenMessages;
        double avgInterArrivalTime; //This is lambda

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif
