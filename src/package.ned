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
        coordinator: Coordinator {
            @display("p=238,157");
        }
    connections:
        node1.out --> node2.in[1];
        node2.out --> node1.in[1];
        coordinator.node[1] --> node2.in[0];
        coordinator.node[0] --> node1.in[0];
}

