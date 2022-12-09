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
    }
}

Node::Node()
{
    timeoutEvent = NULL;
    nextFrameToSend = 0;
    ackExpected = 0;
    frameExpected = 0;
    nbuffered = 0;
}

Node::~Node()
{
    cancelAndDelete(timeoutEvent);
}

void Node::initialize()
{

    // TODO - Generated method body
    WS = par("WS").intValue();

    if (!strcmp(getName(), "node2"))
    {
        // initialize timeout event and schedule it
        timeoutEvent = new cMessage("timeoutEvent");
        timeout = par("TO").doubleValue();
        scheduleAt(simTime() + timeout, timeoutEvent);

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
            double totalDelay = par("PT").doubleValue() + par("TD").doubleValue();

            // if error code is 0001 then add error delay
            if (!strcmp(codes.at(i).c_str(), "0001"))
            {
                totalDelay += par("ED").doubleValue();
            }
            // nbuffered is the number of frames that are sent but not yet acknowledged
            nbuffered = nbuffered + 1;

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
        EV << "Timeout expired";
        scheduleAt(simTime() + timeout, timeoutEvent);

        if (abs(nextFrameToSend - ackExpected) == 0)
        {
            EV << "\nEnding Sim ...\n";
            endSimulation();
        }

        nextFrameToSend = ackExpected;

        int nextFrameToSendTemp = nextFrameToSend;
        for (int i = nextFrameToSendTemp; i < nextFrameToSendTemp + WS && i < messages.size(); i++)
        {
            nextFrameToSend = nextFrameToSend + 1;
            MyFrame_Base *frame = new MyFrame_Base("");
            frame->setSeqNum(i % WS);
            frame->setFrameType(0);
            frame->setPayload(messages.at(i).c_str());

            double totalDelay = par("PT").doubleValue() + par("TD").doubleValue();

            if (!strcmp(codes.at(i).c_str(), "0001") && i != nextFrameToSend + 1)
            {
                totalDelay += par("ED").doubleValue();
            }
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
            ackExpected = ackExpected + 1;
            EV << getName();
            EV << " received frame with Ack Num...   ";
            EV << frame->getAckNackNumber();
            EV << "  At time ...  ";
            EV << simTime();
            EV << "  and Frame Type ... ";
            EV << frame->getFrameType();
            nbuffered = nbuffered - 1;

            cancelEvent(timeoutEvent);
            scheduleAt(simTime() + timeout, timeoutEvent);
        }

        if (nbuffered < (WS))
        {
            if (nextFrameToSend < messages.size())
            {
                for (int j = nextFrameToSend; j < nextFrameToSend + (WS - nbuffered) && j < messages.size(); j++)
                {
                    MyFrame_Base *dup_frame = frame->dup();
                    dup_frame->setSeqNum(j % WS);
                    dup_frame->setFrameType(0);
                    dup_frame->setPayload(messages.at(j).c_str());
                    double totalDelay = par("PT").doubleValue() + par("TD").doubleValue();

                    if (!strcmp(codes.at(j).c_str(), "0001"))
                    {
                        totalDelay += par("ED").doubleValue();
                    }
                    EV << "\nScheduling Frame " << j << " To be sent at " << simTime() + totalDelay << endl;
                    nextFrameToSend = nextFrameToSend + 1;
                    nbuffered = nbuffered + 1;
                    sendDelayed(dup_frame, totalDelay, "out");
                }
            }
        }
    }

    else if (strcmp(getName(), starternode))
    {
        MyFrame_Base *frame = check_and_cast<MyFrame_Base *>(msg);
        if (frame->getFrameType() == 0 && frame->getSeqNum() == frameExpected % (WS))
        {
            EV << getName();
            EV << " received frame " << frameExpected << " with seq num ";
            EV << frame->getSeqNum();
            EV << "  At time ...";
            EV << simTime();
            EV << "  and payload of ... ";
            EV << frame->getPayload();
            EV << "  and Frame Type ... ";
            EV << frame->getFrameType();
            frameExpected = (frameExpected + 1);
            MyFrame_Base *reply = frame->dup();
            reply->setFrameType(1);
            reply->setAckNackNumber(frame->getSeqNum());
            sendDelayed(reply, par("PT").doubleValue() + par("TD").doubleValue(), "out");
        }
        else if (frame->getFrameType() == 0)
        {
            EV << "\nreceived frame with seq num " << frame->getSeqNum() << " but Discarded\n";
        }
    }
}
