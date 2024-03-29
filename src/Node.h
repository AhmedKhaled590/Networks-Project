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

#ifndef __CNPROJECT_NODE_H_
#define __CNPROJECT_NODE_H_

#include <omnetpp.h>
#include <vector>
#include <string>
#include<fstream>
#include "MyFrame_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
private:
  simtime_t timeout;
  std::vector<cMessage *> timeoutEvents;
  int nextFrameToSend;
  int ackExpected;
  int frameExpected;
  int nbuffered;
  std::vector<std::string> messages;
  std::vector<std::string> codes;
  int WS;
  std::string starternode;
  int starternodeid;
  int starttime;
  std::ofstream MyFile;

public:
  Node();
  virtual ~Node();
  void messageHandler(MyFrame_Base *message, const char *code, int modifyIndex, int &index, int &nextFrameToSendTemp);

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  void initializeInputVectors(std::string inputfile);
};

#endif
