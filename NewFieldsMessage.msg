message NewFieldsMessage {
    
    double msgProcessingTime; //This is the processing time of the message
    
    int dxIntervalIndex; //This is the index of its related delta x interval 
	
	simtime_t startedQueuingAt; //This is time at which the msg has arrived in the queue

}