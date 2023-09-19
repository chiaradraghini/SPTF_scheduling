//
// Generated file, do not edit! Created by nedtool 5.4 from NewFieldsMessage.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __NEWFIELDSMESSAGE_M_H
#define __NEWFIELDSMESSAGE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>NewFieldsMessage.msg:1</tt> by nedtool.
 * <pre>
 * message NewFieldsMessage
 * {
 *     double msgProcessingTime; //This is the processing time of the message
 * 
 *     int dxIntervalIndex; //This is the index of its related delta x interval 
 * 
 *     simtime_t startedQueuingAt; //This is time at which the msg has arrived in the queue
 * 
 * }
 * </pre>
 */
class NewFieldsMessage : public ::omnetpp::cMessage
{
  protected:
    double msgProcessingTime;
    int dxIntervalIndex;
    ::omnetpp::simtime_t startedQueuingAt;

  private:
    void copy(const NewFieldsMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NewFieldsMessage&);

  public:
    NewFieldsMessage(const char *name=nullptr, short kind=0);
    NewFieldsMessage(const NewFieldsMessage& other);
    virtual ~NewFieldsMessage();
    NewFieldsMessage& operator=(const NewFieldsMessage& other);
    virtual NewFieldsMessage *dup() const override {return new NewFieldsMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getMsgProcessingTime() const;
    virtual void setMsgProcessingTime(double msgProcessingTime);
    virtual int getDxIntervalIndex() const;
    virtual void setDxIntervalIndex(int dxIntervalIndex);
    virtual ::omnetpp::simtime_t getStartedQueuingAt() const;
    virtual void setStartedQueuingAt(::omnetpp::simtime_t startedQueuingAt);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NewFieldsMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NewFieldsMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __NEWFIELDSMESSAGE_M_H
