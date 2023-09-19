#include "Source.h"

Define_Module(Source);

Source::Source()
{
    sendMessageEvent = nullptr;
}

Source::~Source()
{
    cancelAndDelete(sendMessageEvent);
}

void Source::initialize()
{
    sendMessageEvent = new cMessage("sendMessageEvent");
    nbGenMessages = 0;

    avgInterArrivalTime = par("avgInterArrivalTime").doubleValue();

    scheduleAt(simTime()+exponential(avgInterArrivalTime), sendMessageEvent);
}

void Source::handleMessage(cMessage *msg)
{

    int randomNumber;

    //Generating packet name
    char msgname[20];
    sprintf(msgname, "message-%d", ++nbGenMessages);

    //Generating the message with the added fields in "ModifiedMessage.msg"
    NewFieldsMessage *message = new NewFieldsMessage(msgname);

    send(message, "out");

    scheduleAt(simTime()+exponential(avgInterArrivalTime), sendMessageEvent); // in this course we'll use only sendMessageEvent as message event
}
