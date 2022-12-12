//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
Define_Module(Node);

std::vector<std::string> readInputFile(const char *filename)
{
    std::ifstream filestream;
    std::string line;
    std::vector<std::string> lines;

    filestream.open(filename, std::ifstream::in);

    if (!filestream)
    {
        throw cRuntimeError("Error opening file '%s'?", filename);
        return lines;
    }
    else
    {
        while (getline(filestream, line))
        {
            lines.push_back(line);
        }
    }
    filestream.close();

    return lines;
}

void Node::initializeInputVectors()
{
    std::vector<std::string> lines = readInputFile("D:/omnetpp-6.0.1/samples/CNProject/input1.txt");
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        codes.push_back((*it).substr(0, 4));
        messages.push_back((*it).substr(5, (*it).length() - 5));

        EV<<"At time 0, node2 , Introducing channel error with code="<<(*it).substr(0, 4)<<endl;
    }
}

Node::Node()
{
    nextFrameToSend = 0;
    ackExpected = 0;
    frameExpected = 0;
    nbuffered = 0;
}

Node::~Node()
{
    for(int i=0;i<timeoutEvents.size();i++){
        cancelEvent(timeoutEvents[i]);
        cancelAndDelete(timeoutEvents[i]);
    }
}

void Node::initialize()
{

    // TODO - Generated method body
    WS = par("WS").intValue();

    if (!strcmp(getName(), "node2"))
    {
        // initialize timeout event and schedule it
        timeout = par("TO").doubleValue();

        // initialize input vectors messages and codes
        initializeInputVectors();

        // check if window size is greater than the number of messages
        if (WS > messages.size())
        {
            WS = messages.size();
        }

        // schedule first window of frames
        for (int i = 0; i < WS; i++)
        {
            MyFrame_Base *frame = new MyFrame_Base("");

            frame->setSeqNum(i);
            nextFrameToSend = nextFrameToSend + 1;

            frame->setFrameType(0);
            frame->setPayload(messages.at(i).c_str());

            // calculate total delay all channels have processing delay and transmission delay
            double totalDelay = (par("PT").doubleValue() + par("TD").doubleValue())*(i+1);

            // if error code is 0001 then add error delay
            if (!strcmp(codes.at(i).c_str(), "0001"))
            {
                totalDelay += par("ED").doubleValue();
            }

            // nbuffered is the number of frames that are sent but not yet acknowledged
            nbuffered = nbuffered + 1;

            cMessage*timeoutEvent = new cMessage("timeoutEvent");
            timeoutEvents.push_back(timeoutEvent);
            scheduleAt(simTime()+timeout+(par("PT").doubleValue()*(i+1)), timeoutEvents[i]);

            EV<<"At time "<<simTime()+par("PT").doubleValue()*(i+1)<<", Node[2] sent frame \
                    with seq_num="<<frame->getSeqNum()<<" and payload= "<<frame->getPayload()<<" and trailer= […….in bits….. ] , Modified 0 , Lost No, Duplicate 0"<<endl;
            // schedule frame with total delay
            sendDelayed(frame, totalDelay, "out");
        }
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    // TODO:receive msg from coordinator to decide which node will begin

    // starternode is the sender node (will be handled later after implementing coordinator)
    const char *starternode = "node2";

    // if timeout event is received
    // schedule next window of frames

    if (!strcmp(msg->getName(), "timeoutEvent"))
    {
        EV << "Time out event at time "<<simTime()<<", at Node[2] for frame with seq_num= "<<ackExpected%WS<<endl;

        if (abs(nextFrameToSend - ackExpected) == 0)
        {
            EV << "\nEnding Sim ...\n";
            endSimulation();
        }

        nextFrameToSend = ackExpected;

        int nextFrameToSendTemp = nextFrameToSend;
        nbuffered = 0;
        int nbufferedTemp = nbuffered;
        for (int i = nextFrameToSendTemp; i < nextFrameToSendTemp + (WS) && i < messages.size(); i++)
        {
            nextFrameToSend = nextFrameToSend + 1;

            MyFrame_Base *frame = new MyFrame_Base("");
            frame->setSeqNum(i % WS);
            frame->setFrameType(0);
            frame->setPayload(messages.at(i).c_str());

            double totalDelay = (par("PT").doubleValue() + par("TD").doubleValue())*(i+1-nextFrameToSendTemp);

            if (!strcmp(codes.at(i).c_str(), "0001") && i != nextFrameToSend + 1)
            {
                totalDelay += par("ED").doubleValue();
            }

            cancelEvent(timeoutEvents[i]);
            scheduleAt(simTime()+timeout+(par("PT").doubleValue()*(i+1-nextFrameToSendTemp)), timeoutEvents[i]);
            nbuffered = nbuffered + 1;

            EV<<"At time "<<simTime()+par("PT").doubleValue()*(i+1-nextFrameToSendTemp)<<", Node[2] sent frame";
            EV<<" with seq_num="<<frame->getSeqNum()<<" and payload= "<<frame->getPayload()<<" and trailer= […….in bits….. ] , Modified 0 , Lost No, Duplicate 0"<<endl;
            sendDelayed(frame, totalDelay, "out");
        }
    }

    // if frame is received
    // check if frame is of type 1
    // if yes then ack is received
    // if no then data is received
    // if ack is received increment ackExpected and decrement nbuffered
    // and cancel timeout event and schedule it again from current time

    else if (!strcmp(getName(), starternode))
    {
        MyFrame_Base *frame = check_and_cast<MyFrame_Base *>(msg);
        if (frame->getFrameType() == 1 && frame->getAckNackNumber() == ackExpected % (WS))
        {
            nbuffered = nbuffered - 1;

            EV<<"At time "<<simTime()<<", Node[2] received ack \
                    with seq_num="<<frame->getSeqNum()<<" and payload= "<<frame->getPayload()<<" and trailer= […….in bits….. ] , Modified 0 , Lost No, Duplicate 0"<<endl;

            cancelEvent(timeoutEvents[ackExpected]);
            ackExpected = ackExpected + 1;
        }

        if (nbuffered < (WS))
        {
            if (nextFrameToSend < messages.size())
            {
                int nextFrameToSendTemp = nextFrameToSend;
                for (int j = nextFrameToSendTemp; j < nextFrameToSendTemp + (WS - nbuffered) && j < messages.size(); j++)
                {
                    MyFrame_Base *dup_frame = frame->dup();
                    dup_frame->setSeqNum(j % WS);
                    dup_frame->setFrameType(0);
                    dup_frame->setPayload(messages.at(j).c_str());
                    double totalDelay = (par("PT").doubleValue() + par("TD").doubleValue())*(j+1-nextFrameToSendTemp);

                    if (!strcmp(codes.at(j).c_str(), "0001"))
                    {
                        totalDelay += par("ED").doubleValue();
                    }

                    cMessage*timeoutEvent = new cMessage("timeoutEvent");
                    timeoutEvents.push_back(timeoutEvent);
                    scheduleAt(simTime()+timeout+(par("PT").doubleValue()*(j+1-nextFrameToSendTemp)), timeoutEvents[j]);

                    nextFrameToSend = nextFrameToSend + 1;
                    nbuffered = nbuffered + 1;

                    EV<<"At time "<<simTime()+par("PT").doubleValue()*(j+1-nextFrameToSendTemp)<<", Node[2] sent frame \
                            with seq_num="<<frame->getSeqNum()<<" and payload= "<<frame->getPayload()<<" and trailer= […….in bits….. ] , Modified 0 , Lost No, Duplicate 0"<<endl;
                    sendDelayed(dup_frame, totalDelay, "out");
                }
            }
        }
        cancelAndDelete(frame);
    }


    else if (strcmp(getName(), starternode))
    {
        MyFrame_Base *frame = check_and_cast<MyFrame_Base *>(msg);
        if (frame->getFrameType() == 0 && frame->getSeqNum() == frameExpected % (WS))
        {
            frameExpected = (frameExpected + 1);
            MyFrame_Base *reply = frame->dup();
            reply->setFrameType(1);
            reply->setAckNackNumber(frame->getSeqNum());
            EV<<"At time "<<simTime()+par("PT").doubleValue()<<", Node[1] Sending ACK with number "<<frame->getSeqNum()<<endl;
            sendDelayed(reply, par("PT").doubleValue() + par("TD").doubleValue(), "out");
        }

        cancelAndDelete(frame);
    }
}
