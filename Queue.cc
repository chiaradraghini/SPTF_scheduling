#include "Queue.h"

Define_Module(Queue);

Queue::Queue()
{
    endOfServiceMsg = nullptr;
    msgInServer = nullptr;
}

Queue::~Queue()
{
    delete msgInServer;
    cancelAndDelete(endOfServiceMsg);
}

void Queue::initialize()
{
    endOfServiceMsg = new cMessage("end-service");
    queue.setName("queue");
    queue.setup(&myCompareFunc); //This will use the myCompareFunc to sort the queue

    totalBusyTime = SIMTIME_ZERO;

    L = par("L").doubleValue();

    //Signal registering
    queueLengthSignal = registerSignal("queueLength");
    queueingTimeSignal = registerSignal("queueingTime");
    serverUtilizationSignal = registerSignal("serverUtilization");
    responseTimeSignal = registerSignal("responseTime");
    processTimeValuesSignal = registerSignal("processTimeValues");

}

void Queue::handleMessage(cMessage *msg)
{
    NewFieldsMessage *modifiedMsg;

    if (msg->isSelfMessage()) { //Self message of service completion has arrived

        EV << "At simulation time " << simTime() << " s: completed service of " << msgInServer->getName() << " with processing time " << msgInServer->getMsgProcessingTime() << " s" << endl;

        emit(responseTimeSignal, simTime() - msgInServer->getStartedQueuingAt());

        //Send the processed packet to the sink
        send(msgInServer, "out");

        if (!queue.isEmpty()) { //The queue is not empty: starting new packet processing

            msgInServer = (NewFieldsMessage *)queue.pop();

            EV << "At simulation time " << simTime() << " s: removed " << msgInServer->getName() << " --> it's now going to be served" << endl;
            EV << "Info on " << msgInServer->getName() << ": it had processing time value of " << msgInServer->getMsgProcessingTime() << " s and waited in the queue for "<< simTime() - msgInServer->getStartedQueuingAt()<< " s" << endl;

            emit(queueLengthSignal, queue.getLength());
            emit(queueingTimeSignal, simTime() - msgInServer->getStartedQueuingAt() );
            startPacketService();

        } else { //The queue is empty: server can go idle

            msgInServer = nullptr;

            //Update the totalBusyTime value: previous value + time passed since the time the server became busy
            totalBusyTime = totalBusyTime + (simTime() - startOfBusyTime);
            startOfBusyTime = SIMTIME_ZERO;
            emit(serverUtilizationSignal, totalBusyTime / simTime());

            EV << "Empty queue, the server goes IDLE" <<endl;
        }
    }
    else { // Message from the source has arrived (NOT A SELFMESSAGE!)

        modifiedMsg = check_and_cast<NewFieldsMessage *>(msg); //This is casting the cMessage into a ModifiedMessage (with the processing time parameter)

        //Assigning the fields to the modifiedMsg
        modifiedMsg->setMsgProcessingTime(uniform(0,L)); //Because we're implementing a M/G/1 system
        modifiedMsg->setStartedQueuingAt(simTime());
        emit(processTimeValuesSignal, modifiedMsg->getMsgProcessingTime());

        if (msgInServer != nullptr) { //The server is busy: putting new message in queue

            // put the packet in queue
            putPacketInQueue(modifiedMsg);

        }
        else { //The server is idle: starting new packet processing

            emit(queueingTimeSignal, SIMTIME_ZERO);
            emit(serverUtilizationSignal, totalBusyTime / simTime());

            //Storing the time at which the server becomes busy
            startOfBusyTime = simTime();

            msgInServer = modifiedMsg;
            startPacketService();

        }
    }
}

void Queue::startPacketService()
{

    //Generate processing time and schedule completion accordingly
    simtime_t processingTime = msgInServer->getMsgProcessingTime();
    scheduleAt(simTime()+processingTime, endOfServiceMsg);

    EV << "At simulation time " << simTime() << " s: starting service of " << msgInServer->getName() << " with processing time " << msgInServer->getMsgProcessingTime() << " s" << endl;
}

void Queue::putPacketInQueue(NewFieldsMessage *msg)
{

    msg = check_and_cast<NewFieldsMessage *>(msg);
    queue.insert(msg);
    EV << "At simulation time " << simTime() << " s: the " << msg->getName() << " with processing time " << msg->getMsgProcessingTime() << " s enters queue" << endl;
}

int Queue::myCompareFunc(cObject *a, cObject *b) //This is the comparison function that orders the queue with increasing processing time of the messages
{
    NewFieldsMessage* messageA = check_and_cast<NewFieldsMessage *>(a);
    NewFieldsMessage* messageB =check_and_cast<NewFieldsMessage *>(b);

    double delta = messageA->getMsgProcessingTime() - messageB->getMsgProcessingTime();

    if (delta > 0)
        delta = ceil(delta);
    else
        delta = floor(delta);

    return (int) delta;
}
