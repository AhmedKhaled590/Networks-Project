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
std::string getFramedMessage(std::string message)
{
    char FLAG_BYTE = '$';
    char ESC_BYTE = '/';
    std::string framed_message = "";
    framed_message += FLAG_BYTE;
    for (int i = 0; i < message.size(); ++i)
    {
        if (message[i] == FLAG_BYTE || message[i] == ESC_BYTE)
        {
            framed_message += ESC_BYTE;
        }
        framed_message += message[i];
    }
    framed_message += FLAG_BYTE;
    return framed_message;
}
std::vector<std::bitset<8>> getBitsVector(std::string message)
{
    std::vector<std::bitset<8>> bits_vector;
    for (int i = 0; i < message.size(); ++i)
    {
        bits_vector.push_back(std::bitset<8>(message[i]));
    }
    return bits_vector;
}

std::bitset<8> getParityByte(std::vector<std::bitset<8>> bits_vector)
{
    std::bitset<8> parity_byte;
    for (int i = 0; i < bits_vector.size(); ++i)
    {
        parity_byte ^= bits_vector[i];
    }
    return parity_byte;
}

std::bitset<8> checkMessage(std::vector<std::bitset<8>> bits_vector, std::bitset<8> parity_byte)
{
    std::bitset<8> parity_byte_check;
    for (int i = 0; i < bits_vector.size(); ++i)
    {
        parity_byte_check ^= bits_vector[i];
    }
    parity_byte_check ^= parity_byte;
    return parity_byte_check;
}

std::string modifyBit(std::vector<std::bitset<8>> bits_vector, int bit_to_modify)
{
    int bucket = bit_to_modify / 8;
    int index = 7 - (bit_to_modify % 8);
    bits_vector[bucket].flip(index);
    std::string modified_message = "";
    for (int i = 0; i < bits_vector.size(); ++i)
    {
        modified_message += (char)bits_vector[i].to_ulong();
    }
    return modified_message;
}

void Node::messageHandler(MyFrame_Base *message, const char *code, int modifyIndex, int &index, int &nextFrameToSendTemp)
{
    // some vars for printing
    std::string lostString = "No";
    int duplicateInt = 0;

    int delay = code[3] - '0';
    int duplicate = code[2] - '0';
    int lost = code[1] - '0';
    int modify = code[0] - '0';

    if (!modify)
    {
        modifyIndex = -1;
    }

    if (delay == 0 && duplicate == 0 && lost == 0 && modify == 0)
    {
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        sendDelayed(message, totalDelay, "out");
    }
    else if (delay && !duplicate && !lost && !modify)
    {
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        totalDelay += par("ED").doubleValue();
        sendDelayed(message, totalDelay, "out");
    }
    else if (duplicate && !delay && !lost && !modify)
    {
        duplicateInt = 1;
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        sendDelayed(message, totalDelay, "out");
        MyFrame_Base *dup_frame = message->dup();
        totalDelay += par("DD").doubleValue();
        sendDelayed(dup_frame, totalDelay, "out");
    }
    else if (delay && duplicate && !lost && !modify)
    {
        duplicateInt = 1;
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        totalDelay += par("ED").doubleValue();
        sendDelayed(message, totalDelay, "out");
        MyFrame_Base *dup_frame = message->dup();
        totalDelay += par("DD").doubleValue();
        sendDelayed(dup_frame, totalDelay, "out");
    }
    else if (lost && !duplicate && !delay && !modify)
    {
        lostString = "Yes";
    }
    else if (lost && delay)
    {
        lostString = "Yes";
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
    }
    else if (lost && duplicate && !delay && !modify)
    {
        lostString = "Yes";
        duplicateInt = 1;
        MyFrame_Base *dup_frame = message->dup();
    }
    else if (lost && duplicate && delay && !modify)
    {
        lostString = "Yes";
        duplicateInt = 1;
        MyFrame_Base *dup_frame = message->dup();
    }
    else if (modify && !duplicate && !lost && !delay)
    {
        std::string payload = modifyBit(getBitsVector(message->getPayload()), modifyIndex);
        message->setPayload(payload.c_str());
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        sendDelayed(message, totalDelay, "out");
    }
    else if (modify && delay && !duplicate && !lost)
    {
        std::string payload = modifyBit(getBitsVector(message->getPayload()), modifyIndex);
        message->setPayload(payload.c_str());
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        totalDelay += par("ED").doubleValue();
        sendDelayed(message, totalDelay, "out");
    }
    else if (modify && duplicate && !lost && !modify)
    {
        std::string payload = modifyBit(getBitsVector(message->getPayload()), modifyIndex);
        message->setPayload(payload.c_str());
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        sendDelayed(message, totalDelay, "out");
        MyFrame_Base *dup_frame = message->dup();
        totalDelay += par("DD").doubleValue();
        sendDelayed(dup_frame, totalDelay, "out");
    }
    else if (modify && duplicate && delay && !lost)
    {
        std::string payload = modifyBit(getBitsVector(message->getPayload()), modifyIndex);
        message->setPayload(payload.c_str());
        double totalDelay = (par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("TD").doubleValue());
        totalDelay += par("ED").doubleValue();
        sendDelayed(message, totalDelay, "out");
        MyFrame_Base *dup_frame = message->dup();
        totalDelay += par("DD").doubleValue();
        sendDelayed(dup_frame, totalDelay, "out");
    }

    if (!delay)
    {
        EV << "At time [" << simTime() + par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) << "], Node[2] sent frame "
           << "with seq_num=[" << message->getSeqNum() << "] and payload= [" << message->getPayload()
           << "] and trailer= [" << message->getParity() << "] , Modified [" << modifyIndex << "] , Lost [" << lostString << "], Duplicate [" << duplicateInt << "], Delay [0]" << endl;
    }
    else
    {
        EV << "At time [" << simTime() + par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) << "], Node[2] sent frame "
           << "with seq_num=[" << message->getSeqNum() << "] and payload= [" << message->getPayload()
           << "] and trailer= [" << message->getParity() << "] , Modified [" << modifyIndex << "] , Lost [" << lostString << "], Duplicate "
           << "[" << duplicateInt << "], Delay [" << par("ED").doubleValue() << "]" << endl;
    }
    if (duplicate)
    {
        if (!delay)
        {
            EV << "At time [" << simTime() + par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("DD").doubleValue() << "], Node[2] sent frame "
               << "with seq_num=[" << message->getSeqNum() << "] and payload= [" << message->getPayload()
               << "] and trailer= [" << message->getParity() << "] , Modified [" << modifyIndex << "] , Lost [" << lostString << "], Duplicate [2], Delay [0]" << endl;
        }
        else
        {
            EV << "At time [" << simTime() + par("PT").doubleValue() * (index + 1 - nextFrameToSendTemp) + par("DD").doubleValue() << "], Node[2] sent frame "
               << "with seq_num=[" << message->getSeqNum() << "] and payload= [" << message->getPayload()
               << "] and trailer= [" << message->getParity() << "] , Modified [" << modifyIndex << "] , Lost [" << lostString << "], Duplicate "
               << "[2], Delay [" << par("ED").doubleValue() << "]" << endl;
        }
    }
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
    nextFrameToSend = 0;
    ackExpected = 0;
    frameExpected = 0;
    nbuffered = 0;
}

Node::~Node()
{
    for (int i = 0; i < timeoutEvents.size(); i++)
    {
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
            EV << "At time [" << simTime() + par("PT").doubleValue() * (i) << "], Node [2] , Introducing channel error with code=[" << codes.at(i) << "]" << endl;

            MyFrame_Base *frame = new MyFrame_Base("");

            frame->setSeqNum(i);
            nextFrameToSend = nextFrameToSend + 1;
            std::string payload = getFramedMessage(messages.at(i));
            frame->setFrameType(0);
            frame->setParity(getParityByte(getBitsVector(payload)));
            frame->setPayload(payload.c_str());

            // nbuffered is the number of frames that are sent but not yet acknowledged
            nbuffered = nbuffered + 1;

            cMessage *timeoutEvent = new cMessage("timeoutEvent");
            timeoutEvents.push_back(timeoutEvent);
            scheduleAt(simTime() + timeout + (par("PT").doubleValue() * (i + 1)), timeoutEvents[i]);

            // if error code is 0000 then no error delay
            int randBit = int(uniform(0, payload.size() * 8));
            int next = 0;
            // if error code is 0000 then no error delay

            messageHandler(frame, codes.at(i).c_str(), randBit, i, next);
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
        EV << "Time out event at time " << simTime() << ", at Node[2] for frame with seq_num= " << ackExpected % WS << endl;

        nextFrameToSend = ackExpected;

        int nextFrameToSendTemp = nextFrameToSend;
        nbuffered = 0;
        for (int i = nextFrameToSendTemp; i < nextFrameToSendTemp + (WS) && i < messages.size(); i++)
        {
            //            EV << "At time [" << simTime() + par("PT").doubleValue() * (i) << "], Node [2] , Introducing channel error with code=[" << codes.at(i) << "]" << endl;

            nextFrameToSend = nextFrameToSend + 1;

            MyFrame_Base *frame = new MyFrame_Base("");
            frame->setSeqNum(i % WS);
            frame->setFrameType(0);
            std::string payload = getFramedMessage(messages.at(i));
            frame->setParity(getParityByte(getBitsVector(payload)));
            frame->setPayload(payload.c_str());

            cancelEvent(timeoutEvents[i]);
            scheduleAt(simTime() + timeout + (par("PT").doubleValue() * (i + 1 - nextFrameToSendTemp)), timeoutEvents[i]);
            nbuffered = nbuffered + 1;

            if (i == nextFrameToSendTemp)
            {
                messageHandler(frame, "0000", -1, i, nextFrameToSendTemp);
            }
            else
            {
                int randBit = int(uniform(0, payload.size() * 8));
                messageHandler(frame, codes.at(i).c_str(), randBit, i, nextFrameToSendTemp);
            }
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
        if (frame->getFrameType() == 1 && frame->getAckNackNumber() == (ackExpected + 1) % (WS))
        {
            nbuffered = nbuffered - 1;

            // EV << "At time [" << simTime() << "], Node[2] received ack "
            //    << "with seq_num=[" << frame->getSeqNum() << "] and payload= [" << frame->getPayload()
            //    << "] and trailer= [] , Modified [0] , Lost [No], Duplicate [0]" << endl;

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
                    EV << "At time [" << simTime() + par("PT").doubleValue() * (j - nextFrameToSendTemp) << "], Node [2] , Introducing channel error with code=[" << codes.at(j) << "]" << endl;

                    MyFrame_Base *dup_frame = frame->dup();
                    dup_frame->setSeqNum(j % WS);
                    dup_frame->setFrameType(0);
                    std::string payload = getFramedMessage(messages.at(j));
                    dup_frame->setParity(getParityByte(getBitsVector(payload)));
                    dup_frame->setPayload(payload.c_str());

                    cMessage *timeoutEvent = new cMessage("timeoutEvent");
                    timeoutEvents.push_back(timeoutEvent);
                    scheduleAt(simTime() + timeout + (par("PT").doubleValue() * (j + 1 - nextFrameToSendTemp)), timeoutEvents[j]);

                    nextFrameToSend = nextFrameToSend + 1;
                    nbuffered = nbuffered + 1;

                    int randBit = int(uniform(0, payload.size() * 8));
                    messageHandler(dup_frame, codes.at(j).c_str(), randBit, j, nextFrameToSendTemp);
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
            MyFrame_Base *reply = frame->dup();
            std::string recPayload = reply->getPayload();
            std::cout << "recPayload1: " << recPayload << endl;
            std::bitset<8> recParity = reply->getParity();
            std::cout << "recParity: " << recParity << endl;
            std::bitset<8> recBits = checkMessage(getBitsVector(recPayload), recParity);
            std::string ParityStr = recBits.to_string();

            std::cout << "recBits: " << recBits << endl;

            int LossProbability = int(uniform(0, 100));
            int LP = (int)par("LP").doubleValue();
            if (!(strcmp(ParityStr.c_str(), "00000000")) && LossProbability > LP)
            {
                frameExpected = frameExpected + 1;
                reply->setAckNackNumber(frameExpected % WS);

                reply->setFrameType(1);
                EV << "At time [" << simTime() + par("PT").doubleValue() << "], Node[1] Sending ACK with number " << reply->getAckNackNumber() << " loss [No]" << endl;
                sendDelayed(reply, par("PT").doubleValue() + par("TD").doubleValue(), "out");
            }
            else if (strcmp(ParityStr.c_str(), "00000000") && LossProbability > LP)
            {
                reply->setFrameType(2);
                EV << "At time [" << simTime() + par("PT").doubleValue() << "], Node[1] Sending NACK with number " << reply->getAckNackNumber() << " loss [No]" << endl;
                sendDelayed(reply, par("PT").doubleValue() + par("TD").doubleValue(), "out");
            }
            else if (!(strcmp(ParityStr.c_str(), "00000000")) && LossProbability < LP)
            {
                frameExpected = frameExpected + 1;
                reply->setAckNackNumber(frameExpected % WS);
                reply->setFrameType(1);
                EV << "At time [" << simTime() + par("PT").doubleValue() << "], Node[1] Sending ACK with number " << reply->getAckNackNumber() << " loss [Yes]" << endl;
            }
            else if (strcmp(ParityStr.c_str(), "00000000") && LossProbability < LP)
            {
                reply->setFrameType(2);
                EV << "At time [" << simTime() + par("PT").doubleValue() << "], Node[1] Sending NACK with number " << reply->getAckNackNumber() << " loss [Yes]" << endl;
            }
        }

        cancelAndDelete(frame);
    }
}
