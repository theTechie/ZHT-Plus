/*
 * Copyright 2010-2020 DatasysLab@iit.edu(http://datasys.cs.iit.edu/index.html)
 *      Director: Ioan Raicu(iraicu@cs.iit.edu)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is part of ZHT library(http://datasys.cs.iit.edu/projects/ZHT/index.html).
 *      Tonglin Li(tli13@hawk.iit.edu) with nickname Tony,
 *      Xiaobing Zhou(xzhou40@hawk.iit.edu) with nickname Xiaobingo,
 *      Ke Wang(kwang22@hawk.iit.edu) with nickname KWang,
 *      Dongfang Zhao(dzhao8@@hawk.iit.edu) with nickname DZhao,
 *      Ioan Raicu(iraicu@cs.iit.edu).
 *
 * zhtgraph.h
 *
 *  Created on: Mar 15, 2015
 *      Author: Benjamin Miwa
 *      Contributor: Gagan Munisiddha Gowda, Anirudh Sunkineni
 */

#ifndef ZHTPLUSGRAPH_H_
#define ZHTPLUSGRAPH_H_

#include <stdint.h>
#include <string>
#include <map>

using namespace std;

#include "cpp_zhtclient.h"
#include "ZHTplusGraph.pb.h"
#include <queue>

class ZHTplusClient {

public:
    ZHTplusClient();
    virtual ~ZHTplusClient();

    int init(const string& zhtConf, const string& neighborConf);
    int ZHTplusGraphAddNode(string NodeID, string NodeName);
    int ZHTplusGraphAddNodeProperty(string NodeID, string PropertyID, string PropertyName, string PropertyValue);
    int ZHTplusGraphAddNodeEdge(string Node1ID, string Node2ID, string EdgeID, string EdgeName);
    int ZHTplusGraphAddNodeEdgeProperty(string NodeID, string EdgeID, string PropertyID, string PropertyName, string PropertyValue);

    string ZHTplusGraphGetNodePropertyValue(string NodeID, string PropertyID);
    string ZHTplusGraphGetNodeEdgeTarget(string NodeID, string EdgeID);
    string ZHTplusGraphGetNodeEdgePropertyValue(string NodeID, string EdgeID, string PropertyID);

    string ZHTplusGraphDFS(string StartNodeID);
    string ZHTplusGraphDFStraverse(string StartNodeID, map<string, string> &hashtable);

    string ZHTplusGraphBFS(string StartNodeID);
    string ZHTplusGraphBFStraverse(queue<string> Q, map<string, string> &hashtable);

    int teardown();

private:
    string serializeNodeToString(const ZHTplusGraph::Node& node);
    ZHTplusGraph::Node parseNodeFromString(const string& data);

    ZHTplusGraph::Node createNode(string ID, string name);
    bool isNodeExists(string NodeID);
    bool deleteNode(ZHTplusGraph::Node* node);

    ZHTplusGraph::Property* newNodeProperty(ZHTplusGraph::Node& node, string ID, string name, string value);
    ZHTplusGraph::Property* getNodeProperty(ZHTplusGraph::Node& node, int index);
    ZHTplusGraph::Property* getNodeProperty(ZHTplusGraph::Node& node, string propertyID);
    bool removeNodeProperty(ZHTplusGraph::Node* node, string propertyID);

    ZHTplusGraph::Edge* newNodeEdge(ZHTplusGraph::Node& node1, string node2ID, string ID, string name);
    ZHTplusGraph::Edge* getNodeEdgeSource(ZHTplusGraph::Node& node, int index);
    ZHTplusGraph::Edge* getNodeEdgeSource(ZHTplusGraph::Node& node, string edgeID);
    ZHTplusGraph::Edge* getNodeEdgeTarget(ZHTplusGraph::Node& node, int index);
    ZHTplusGraph::Edge* getNodeEdgeTarget(ZHTplusGraph::Node& node, string edgeID);
    string getEdgeTarget(ZHTplusGraph::Edge* edge);
    int getNodeEdgeSourceCount(ZHTplusGraph::Node& node);
    bool removeNodeEdge(ZHTplusGraph::Node* node, string edgeID);

    ZHTplusGraph::Property* newEdgeProperty(ZHTplusGraph::Edge* edge, string ID, string name, string value);
    ZHTplusGraph::Property* getEdgeProperty(ZHTplusGraph::Edge* edge, int index);
    ZHTplusGraph::Property* getEdgeProperty(ZHTplusGraph::Edge* edge, string propertyID);
    bool removeEdgeProperty(ZHTplusGraph::Edge* edge, string propertyID);

private:
    ZHTClient _zc;

    int DFSnodeCount;
    int DFSnodeVisits;

    int BFSnodeCount;
    int BFSnodeVisits;
};

#endif /* ZHTPLUSGRAPH_H_ */
