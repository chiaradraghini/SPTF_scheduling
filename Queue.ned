simple Queue
{
	parameters:
        @display("i=block/queue;q=queue");
        
        double L @unit(s);
        
        @signal[queueLength](type=int);
        @signal[queueingTime](type=simtime_t);
        @signal[serverUtilization](type=double);
        @signal[responseTime](type=simtime_t);
        @signal[processTimeValues](type=double);
        
        
        @statistic[queueLength](title="Queue length";record=vector,timeavg,max;interpolationmode=sample-hold);
        @statistic[queueingTime](title="Queueing time";unit=s;record=vector,mean,max;interpolationmode=none);
        @statistic[serverUtilization](title="Utilization Factor of the server";record=vector,timeavg;interpolationmode=sample-hold);
        @statistic[responseTime](title="Response Time";unit=s;record=vector,mean,max;interpolationmode=none);
        @statistic[processTimeValues](title="Produced Process Time Values";record=vector,mean,timeavg,max;interpolationmode=sample-hold);
    
    gates:
        input in;
        output out;
}