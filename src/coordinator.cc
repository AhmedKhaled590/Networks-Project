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

#include "coordinator.h"
#include <iostream>
#include <fstream>
#include <string>

Define_Module(Coordinator);

void Coordinator::readInputFile(const char *filename)
{
    std::ifstream filestream;
    std::string line;
    std::vector<std::string> lines;

    filestream.open(filename, std::ifstream::in);

    if (!filestream)
    {
        throw cRuntimeError("Error opening file '%s'?", filename);
    }
    else
    {
        while (getline(filestream, line))
        {
            node = line.substr(0, line.find(" "));
            startTime = line.substr(line.find(" ") + 1, line.length());
        }
    }
    filestream.close();
}


void Coordinator::initialize()
{
    // TODO - Generated method body
    char path[200];
    GetFullPathName("coordinator.txt", 200, path, NULL);

    readInputFile(path);
    scheduleAt(simTime()+ 0, new cMessage(""));
}

void Coordinator::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage())
    {
        std::string message = node + " "+ startTime;
        msg->setName(message.c_str());
        send(msg, "node", 0);
        cMessage*duplicate = msg->dup();
        send(duplicate, "node", 1);
    }
    else
    {
        delete msg;
    }
}
