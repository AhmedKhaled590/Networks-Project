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

Define_Module(Node);

std::string modifyBit(std::string message, int bit_to_modify)
{
    int n = message.size() * 8;
    std::bitset<n> messageBits(message);
    messageBits.flip(bit_to_modify);
    std::string modified_message = messageBits.to_string();
    return modified_message;
}

void Node::initialize()
{
    FLAG_BYTE = '$';
    ESC_BYTE = '/';
    // TODO - Generated method body
    if (strcmp(getName(), "Sender") == 0)
    {
        cMessage *msg = new cMessage("Start from sender:");
        send(msg, "out");
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (strcmp(getName(), "Receiver") == 0) // if the node is receiver
    {
        std::string message = msg->getName();    // get the message
        std::string deframed = "";               // final message after deframing
        std::bitset<8> parity_byte;              // parity byte check
        std::vector<std::bitset<8>> bits_vector; // vector to store the message to be sent(Header->seq_nr Frame->flag[Payload]flag Trailer->parityByte FrameType->data/ACK ACK)
        for (int i = 1; i < message.size() - 2; i++)
        {
            bits_vector.push_back(message[i]);           // put the chars from the first flag to the parity byte (from the message) in the vector
            if (message[i] == (char)ESC_BYTE.to_ulong()) // if the char is Escaped
            {
                deframed += message[i + 1]; // put the next char in the deframed message
                i++;                        // skip the next char
            }
            else if (message[i] != (char)FLAG_BYTE.to_ulong() && i != message.size() - 3) // if the char is not flag or parity byte
            {
                deframed += message[i];
            }
        }
        for (int i = 0; i < bits_vector.size(); ++i) // loop over all the bits in the vector to calculate the parity byte
        {
            parity_byte ^= bits_vector[i];
        }
        if (parity_byte.to_string() == "00000000") // if the parity byte is correct it will be zeros
        {
            // if(message[message.size()-1] == '1')                  // if the frame type is data
            // {
            std::cout << "Data Frame Received Successfully" << endl;
            std::cout << deframed << endl;
            // }
            // else if(message[message.size()-1] == '0')             // if the frame type is ACK
            // {
            //     EV<<"ACK Frame Received"<<endl;
            //     EV<<deframed<<endl;
            // }
        }
        else
        {
            std::cout << "Data Frame Received With Error" << endl;
        }

        msg->setName(deframed.c_str());
        send(msg, "out");
    }
    else if (strcmp(getName(), "Sender") == 0)
    {
        std::string message;                     // message (payload)
        std::cin >> message;                     // message from user(should be from file)
        std::string final_msg = "";              // final message after framing
        std::vector<std::bitset<8>> bits_vector; // vector to store the message to be sent(Header->seq_nr Frame->flag[Payload]flag Trailer->parityByte FrameType->data/ACK ACK)
        bits_vector.push_back(0);                // sequence number (0 For now)
        bits_vector.push_back(FLAG_BYTE);        // first Flag
        std::bitset<8> parity_byte;              // parity byte check
        std::stringstream ss;
        ss << 0;
        final_msg += ss.str();
        final_msg += (char)FLAG_BYTE.to_ulong();
        for (int i = 0; i < message.size(); i++)
        {
            if(message[i]==(char)FLAG_BYTE.to_ulong() or message[i]==(char)ESC_BYTE.to_ulong())            // if the char is flag or ESC
            {
                bits_vector.push_back(ESC_BYTE); // Put escape before the char
                bits_vector.push_back(message[i]);
                final_msg += (char)ESC_BYTE.to_ulong();
                final_msg += message[i];
            }
            else
            {
                bits_vector.push_back(message[i]);
                final_msg += message[i];
            }
        }
        bits_vector.push_back(FLAG_BYTE); // Put the last flag
        final_msg += (char)FLAG_BYTE.to_ulong();
        for (int i = 1; i < bits_vector.size(); ++i)
        {
            parity_byte ^= bits_vector[i];
        }
        std::cout<<"Before modifying"<<final_msg<<endl;
        modifyBit(final_msg, 3);
        std::cout<<"After modifying"<<final_msg<<endl;
        bits_vector.push_back(parity_byte); // Put the parity byte
        final_msg += (char)parity_byte.to_ulong();
        bits_vector.push_back(1); // Put the frame type (1 for data)
        ss.str("");
        ss << 1;
        final_msg += ss.str();
        bits_vector.push_back(3); // Put ACK number (3 for now)
        ss.str("");
        ss << 3;
        final_msg += ss.str();
        msg->setName(final_msg.c_str());

        send(msg, "out");
    }
}
