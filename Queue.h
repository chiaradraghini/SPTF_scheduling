#ifndef __SPTF_QUEUE_H_
#define __SPTF_QUEUE_H_

#include <omnetpp.h>
#include <NewFieldsMessage_m.h>
#include <random>
#include <vector>

using namespace omnetpp;

class Queue : public cSimpleModule
{
    private:
        NewFieldsMessage *msgInServer;
        cMessage *endOfServiceMsg;

        double L; //Max value for the uniform distribution

        simsignal_t queueLengthSignal;
        simsignal_t queueingTimeSignal;
        simsignal_t serverUtilizationSignal;
        simsignal_t responseTimeSignal;
        simsignal_t processTimeValuesSignal; //This is to save the process times during the simulation

        cQueue queue;

        //Server utilization statistic
        simtime_t startOfBusyTime; //This stores the time at which the server becomes busy
        simtime_t totalBusyTime; //This stores the total time the server is busy

    public:
        Queue();
        virtual ~Queue();

    protected:
        static int myCompareFunc(cObject *a, cObject *b);
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        void startPacketService();
        void putPacketInQueue(NewFieldsMessage *msg);
};

#endif
