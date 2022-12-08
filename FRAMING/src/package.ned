package framing;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=830,387");
    submodules:
        Sender: Node {
            @display("p=149,163");
        }
        Receiver: Node {
            @display("p=588,172");
        }
    connections:
        Sender.out --> Receiver.in;
        Receiver.out --> Sender.in;
}

