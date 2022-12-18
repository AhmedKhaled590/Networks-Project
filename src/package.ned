package cnproject;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=545,250");
    submodules:
        node0: Node {
            @display("p=90,73");
        }
        node1: Node {
            @display("p=380,73");
        }
        coordinator: Coordinator {
            @display("p=238,157");
        }
    connections:
        node0.out --> node1.in[1];
        node1.out --> node0.in[1];
        coordinator.node[1] --> node1.in[0];
        coordinator.node[0] --> node0.in[0];
}

