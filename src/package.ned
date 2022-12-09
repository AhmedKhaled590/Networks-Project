package cnproject;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=545,250");
    submodules:
        node1: Node {
            @display("p=90,73");
        }
        node2: Node {
            @display("p=380,73");
        }
    connections:
        node1.out --> node2.in;
        node2.out --> node1.in;
}

