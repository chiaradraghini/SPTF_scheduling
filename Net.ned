network Net
{
    submodules:
        sys: Queue {
            @display("p=196,79");
        }
        source: Source {
            @display("p=80,79");
        }
        sink: Sink {
            @display("p=306,79");
        }
        
    connections:
        source.out --> sys.in;
        sys.out --> sink.in;
}
