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
 * zhtgraph.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: Benjamin Miwa
 *      Contributor: Gagan Munisiddha Gowda, Anirudh Sunkineni
 */

#include "ZHTplusGraph.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Util.h"

using namespace iit::datasys::zht::graph;

ZHTplusClient::ZHTplusClient()
{
}

ZHTplusClient::~ZHTplusClient()
{
}

// Initialize zht-client using zht and neighbor conf

int ZHTplusClient::init(const string& zhtConf, const string& neighborConf)
{

//    return _zc.init(zhtConf, neighborConf);
	_zc.init(zhtConf, neighborConf);
}

// If the nodeID does not already exist, create a new node, serialize it, and store it in ZHT

int ZHTplusClient::ZHTplusGraphAddNode(string NodeID, string NodeName)
{
    ZHTplusGraph::Node newNode;
    string KVSvalue;

    if(isNodeExists(NodeID))
    {
//        cout << "Node Exists : '" << NodeID << "'" << endl;
        return 0;
    }

    newNode = createNode(NodeID, NodeName);
    KVSvalue = serializeNodeToString(newNode);

    return _zc.insert(NodeID, KVSvalue);
}

// Find the node, deserialize it, add the property, reserialize it, remove the old node value, insert the new node value
// TODO : Check if node exisits before adding Node Property
int ZHTplusClient::ZHTplusGraphAddNodeProperty(string NodeID, string PropertyID, string PropertyName, string PropertyValue)
{

    string KVSvalue;
    ZHTplusGraph::Node theNode;
    ZHTplusGraph::Property *newProperty;

    _zc.lookup(NodeID, KVSvalue);
    theNode = parseNodeFromString(KVSvalue);
    newProperty = newNodeProperty(theNode, PropertyID, PropertyName, PropertyValue);
    KVSvalue = serializeNodeToString(theNode);
    _zc.remove(NodeID);

    return _zc.insert(NodeID, KVSvalue);
}


// Find node1, deserialize it, add the edge from node1 to node2, reserialize node1, remove the old node1 value, insert the new node1 value

int ZHTplusClient::ZHTplusGraphAddNodeEdge(string Node1ID, string Node2ID, string EdgeID, string EdgeName)
{

    string KVSvalue;
    ZHTplusGraph::Node theNode;
    ZHTplusGraph::Edge* newEdge;

    _zc.lookup(Node1ID, KVSvalue);
    theNode = parseNodeFromString(KVSvalue);
	if(getNodeEdgeSource(theNode, EdgeID) == NULL) {
	    newEdge = newNodeEdge(theNode, Node2ID, EdgeID, EdgeName);
	    KVSvalue = serializeNodeToString(theNode);
	    _zc.remove(Node1ID);
	    return _zc.insert(Node1ID, KVSvalue);
	}
	else {
//		cout << "Edge Exists : '" << EdgeID << "'" << endl;
		return 0;
	}
}


// Find the node, deserialize it, find the edge, add the property, reserialize it, remove the old node value, insert the new node value

int ZHTplusClient::ZHTplusGraphAddNodeEdgeProperty(string NodeID, string EdgeID, string PropertyID, string PropertyName, string PropertyValue)
{

    string KVSvalue;
    ZHTplusGraph::Node theNode;
    ZHTplusGraph::Edge* theEdge;
    ZHTplusGraph::Property* newProperty;

    _zc.lookup(NodeID, KVSvalue);
    theNode = parseNodeFromString(KVSvalue);
    theEdge = getNodeEdgeSource(theNode, EdgeID);
    newProperty = newEdgeProperty(theEdge, PropertyID, PropertyName, PropertyValue);
    KVSvalue = serializeNodeToString(theNode);
    _zc.remove(NodeID);
    return _zc.insert(NodeID, KVSvalue);
}

//
// Return selected Property value of a Node
// TODO : Return the lookup status; Accept result as the last parameter

string ZHTplusClient::ZHTplusGraphGetNodePropertyValue(string NodeID, string PropertyID)
{

    string KVSvalue;
    ZHTplusGraph::Node theNode;
    ZHTplusGraph::Property* theProperty;

    _zc.lookup(NodeID, KVSvalue);
    theNode = parseNodeFromString(KVSvalue);

    theProperty = getNodeProperty(theNode, PropertyID);

    return theProperty->mutable_value()->c_str();
}


// Return the target NodeID of the selected Edge of a Node
// TODO : Return the lookup status; Accept result as the last parameter

string ZHTplusClient::ZHTplusGraphGetNodeEdgeTarget(string NodeID, string EdgeID)
{

    string KVSvalue;
    ZHTplusGraph::Node theNode;
    ZHTplusGraph::Edge* theEdge;

    _zc.lookup(NodeID, KVSvalue);
    theNode = parseNodeFromString(KVSvalue);
    theEdge = getNodeEdgeSource(theNode, EdgeID);
    return theEdge->mutable_target()->c_str();
}


// Return selected Property value of an Edge of a Node
// TODO : Return the lookup status; Accept result as the last parameter

string ZHTplusClient::ZHTplusGraphGetNodeEdgePropertyValue(string NodeID, string EdgeID, string PropertyID)
{

    string KVSvalue;
    ZHTplusGraph::Node theNode;
    ZHTplusGraph::Edge* theEdge;
    ZHTplusGraph::Property* theProperty;

    _zc.lookup(NodeID, KVSvalue);
    theNode = parseNodeFromString(KVSvalue);
    theEdge = getNodeEdgeSource(theNode, EdgeID);
    theProperty = getEdgeProperty(theEdge, PropertyID);
    return theProperty->mutable_value()->c_str();
}

// Mark node visited and recursively visit all nodes pointed to by edges from this node

string ZHTplusClient::ZHTplusGraphDFStraverse(string StartNodeID, map<string, string> &hashtable)
{

    string KVSvalue;
	ZHTplusGraph::Node theNode;
	ZHTplusGraph::Edge* edge;
	int edgeCount;
	string nodeID;


	DFSnodeVisits++;
	if(hashtable[StartNodeID] != "1") {
		DFSnodeCount++;
		hashtable[StartNodeID] = "1";
		_zc.lookup(StartNodeID, KVSvalue);

		theNode = parseNodeFromString(KVSvalue);
		edgeCount = getNodeEdgeSourceCount(theNode);

		for(int i = 0; i < edgeCount; i++) {
			edge = getNodeEdgeSource(theNode, i);
			nodeID = getEdgeTarget(edge);
			ZHTplusGraphDFStraverse(nodeID, hashtable);
		}
	}
	return StartNodeID;
}


// Set up the hash table and start the recursive traversal

string ZHTplusClient::ZHTplusGraphDFS(string StartNodeID)
{
    std::map<string, string> hashtable;

	DFSnodeCount = 0;
	DFSnodeVisits = 0;
	ZHTplusGraphDFStraverse(StartNodeID, hashtable);
	printf("DFS Visited %d nodes\n",DFSnodeVisits);
	printf("DFS Visited %d unique nodes\n",DFSnodeCount);
	return StartNodeID;
}


// Mark node visited and continue visiting all nodes in the queue

string ZHTplusClient::ZHTplusGraphBFStraverse(queue<string> Q, map<string, string> &hashtable)
{

    string KVSvalue;
	string StartNodeID;
	string thisNodeID;
	ZHTplusGraph::Node thisNode;
	ZHTplusGraph::Edge* edge;
	int edgeCount;
	string nodeID;


	StartNodeID = Q.front();
	while(!(Q.empty())) {
		thisNodeID = Q.front();
		Q.pop();
		BFSnodeVisits++;
		if(hashtable[thisNodeID] != "1") {
			BFSnodeCount++;
			hashtable[thisNodeID] = "1";
			_zc.lookup(thisNodeID, KVSvalue);

			thisNode = parseNodeFromString(KVSvalue);
			edgeCount = getNodeEdgeSourceCount(thisNode);

			for(int i = 0; i < edgeCount; i++) {
				edge = getNodeEdgeSource(thisNode, i);
				nodeID = getEdgeTarget(edge);
				Q.push(nodeID);
			}
		}
	}
	return StartNodeID;
}


// Set up the hash table and queue and start the traversal

string ZHTplusClient::ZHTplusGraphBFS(string StartNodeID)
{

    std::map<string, string> hashtable;
    queue<string> Q;

	BFSnodeCount = 0;
	BFSnodeVisits = 0;
	Q.push(StartNodeID);
	ZHTplusGraphBFStraverse(Q, hashtable);
	printf("BFS Visited %d nodes\n",BFSnodeVisits);
	printf("BFS Visited %d unique nodes\n",BFSnodeCount);
	return StartNodeID;
}


// Mark node visited, set its count to 1, and continue visiting all nodes in the queue

string ZHTplusClient::ZHTplusGraphPageRankTraverse(queue<string> Q, map<string, string> &hashtable, map<string, float> &pagecounts)
{

    string KVSvalue;
	string StartNodeID;
	string thisNodeID;
	ZHTplusGraph::Node thisNode;
	ZHTplusGraph::Edge* edge;
	int edgeCount;
	string nodeID;
	float thisPageCount;

	StartNodeID = Q.front();
	while(!(Q.empty())) {
		thisNodeID = Q.front();
		Q.pop();
		PRnodeVisits++;
		if(hashtable[thisNodeID] != "1") {
			PRnodeCount++;
			pagecounts[thisNodeID] = 1;
			hashtable[thisNodeID] = "1";
			_zc.lookup(thisNodeID, KVSvalue);

			thisNode = parseNodeFromString(KVSvalue);
			edgeCount = getNodeEdgeSourceCount(thisNode);
			for(int i = 0; i < edgeCount; i++) {
				edge = getNodeEdgeSource(thisNode, i);
				nodeID = getEdgeTarget(edge);
				Q.push(nodeID);
			}
		}
	}
	return StartNodeID;
}


// Mark node visited, distribute its count nodes it point to, and continue visiting all nodes in the queue

string ZHTplusClient::ZHTplusGraphPageRankCalculate(queue<string> Q, map<string, string> &hashtable, map<string, float> &pagecounts)
{

    string KVSvalue;
	string StartNodeID;
	string thisNodeID;
	ZHTplusGraph::Node thisNode;
	ZHTplusGraph::Edge* edge;
	int edgeCount;
	string nodeID;
	float thisPageCount;
    std::map<string, float> prev_pagecounts;
    std::map<string, float>::iterator it_pagecount;

	// Save the current pagecounts and reset to 0
	for(it_pagecount = pagecounts.begin(); it_pagecount != pagecounts.end(); it_pagecount++) {
		prev_pagecounts[it_pagecount->first] = it_pagecount->second;
		pagecounts[it_pagecount->first] = 0;
		hashtable[it_pagecount->first] = '0';
	}
	PRdistributed = 0;
	StartNodeID = Q.front();
	while(!(Q.empty())) {
		thisNodeID = Q.front();
		Q.pop();
		if(hashtable[thisNodeID] != "1") {
			hashtable[thisNodeID] = "1";
			_zc.lookup(thisNodeID, KVSvalue);
			thisPageCount = prev_pagecounts[thisNodeID];
			thisNode = parseNodeFromString(KVSvalue);
			edgeCount = getNodeEdgeSourceCount(thisNode);
			if(edgeCount > 0)
			    PRdistributed += thisPageCount;
			for(int i = 0; i < edgeCount; i++) {
				edge = getNodeEdgeSource(thisNode, i);
				nodeID = getEdgeTarget(edge);
				Q.push(nodeID);
				pagecounts[nodeID] += thisPageCount / edgeCount;
			}
		}
	}
	return StartNodeID;
}


// Set up the hash table, pagecounts, and queue, start the traversal, then collect top N pages

string ZHTplusClient::ZHTplusGraphPageRank(string StartNodeID, int ShowTopN)
{

    std::map<string, string> hashtable;
    std::map<string, float> pagecounts;
    queue<string> Q;
    int i;

	PRnodeCount = 0;
	PRnodeVisits = 0;
	Q.push(StartNodeID);
	ZHTplusGraphPageRankTraverse(Q, hashtable, pagecounts);
	printf("PageRank Visited %d nodes\n",PRnodeVisits);
	printf("PageRank Visited %d unique nodes\n",PRnodeCount);

	for(i=0; i < 10; i++){
		printf("\nRunning PageRank pass %d\n", i+1);
		ZHTplusGraphPageRankCalculate(Q, hashtable, pagecounts);
		ZHTplusGraphPageRankShowTopN(pagecounts, ShowTopN);
	}
	return StartNodeID;
}


// Search the pagecounts map for the top N and show them in descending order.

int ZHTplusClient::ZHTplusGraphPageRankShowTopN(map<string, float> &pagecounts, int ShowTopN)
{
    std::map<string, float>::iterator it_pagecount;
    nodecount TopN[ShowTopN];
	int i;
	float t_float;
	float PRtotal = 0;
	string t_string;

	for(i=0;i<ShowTopN;i++) {
		TopN[i].node = "Unused";
		TopN[i].count = 0;
	}
	// Iterate through the pagecounts map
	for(it_pagecount = pagecounts.begin(); it_pagecount != pagecounts.end(); it_pagecount++) {
		PRtotal += it_pagecount->second;
		if(it_pagecount->second > TopN[0].count) {
			// New Top N
			TopN[0].node = it_pagecount->first;
			TopN[0].count = it_pagecount->second;
			i = 1;
			// swap it up into the correct position
			while((i < ShowTopN) && (TopN[i-1].count > TopN[i].count)) {
				t_string = TopN[i].node;
				TopN[i].node = TopN[i-1].node;
				TopN[i-1].node = t_string;
				t_float = TopN[i].count;
				TopN[i].count = TopN[i-1].count;
				TopN[i-1].count = t_float;
				i++;
			}
		}
	}
	for(i = ShowTopN; i > 0; i--)
		printf("Node %s has PageRank %12.10f\n", TopN[i-1].node.c_str(), TopN[i-1].count/PRdistributed);
	return 0;
}


// Serialize the node and store the bytes in the returned string.

string ZHTplusClient::serializeNodeToString(const ZHTplusGraph::Node& node)
{

    string output = "";

    if (node.SerializeToString(&output))
        return output;
    else
        return output;
}


// Return a parsed node from the given string.

ZHTplusGraph::Node ZHTplusClient::parseNodeFromString(const string& data)
{

    ZHTplusGraph::Node newNode;

    if(newNode.ParseFromString(data))
        return newNode;
    else
        return newNode;
}


// Create a new Node and set its ID and name
// TODO : Check is Node exists before adding a new node

ZHTplusGraph::Node ZHTplusClient::createNode(string ID, string name)
{
    ZHTplusGraph::Node newNode;

    newNode.set_nodeid(ID);
    newNode.set_name(name);

    return newNode;
}

bool ZHTplusClient::isNodeExists(string NodeID)
{
    string KVSvalue;

    if(_zc.lookup(NodeID, KVSvalue) == 0)
        return true;
    else
        return false;
}

// Delete a node and all its properties and relationships (both origin and terminus)

bool ZHTplusClient::deleteNode(ZHTplusGraph::Node* node)
{
// stuff goes here
    return true;
}


// Create a new Property for a Node and set its ID, name, and value
// TODO: Check if Property with same id/name already exisits; if yes, can we update the value ?

ZHTplusGraph::Property* ZHTplusClient::newNodeProperty(ZHTplusGraph::Node& node, string ID, string name, string value)
{

    ZHTplusGraph::Property* newProperty = node.add_property();

    newProperty->set_propertyid(ID);
    newProperty->set_name(name);
    newProperty->set_value(value);

    return newProperty;
}


// Return selected Property of a Node by index

ZHTplusGraph::Property* ZHTplusClient::getNodeProperty(ZHTplusGraph::Node& node, int index)
{

    ZHTplusGraph::Property* property = NULL;

    if (index < node.property_size())
        property = node.mutable_property(index);

    return property;
}


// Return selected Property of a Node by ID

ZHTplusGraph::Property* ZHTplusClient::getNodeProperty(ZHTplusGraph::Node& node, string propertyID)
{

    ZHTplusGraph::Property* property = NULL;

    int numProperties = node.property_size();
    for (int i = 0; i < numProperties; i++)
    {
        property = node.mutable_property(i);
        if (property->has_propertyid())
            if(property->propertyid() == propertyID)
                return property;
    }

    return property;
}


// Remove selected Property of a Node

bool ZHTplusClient::removeNodeProperty(ZHTplusGraph::Node* node, string propertyID)
{

// since there is no way to remove a repeated element once it is added
// this will have to be implemented by setting it to null
// getting the number of properties
// looping from the beginning
// finding the index of the matching property
// continuing until the end or a null string property is found
// swapping the last property with removed property
// setting the last property to null
// and deleting the Property object
    return true;
}


// Create a new Edge for a Node and set its ID, name, source, and target

ZHTplusGraph::Edge* ZHTplusClient::newNodeEdge(ZHTplusGraph::Node& node1, string node2ID, string ID, string name)
{

    ZHTplusGraph::Edge* newEdge = node1.add_edge_source();

    newEdge->set_edgeid(ID);
    newEdge->set_name(name);
    newEdge->set_source(node1.nodeid());
    newEdge->set_target(node2ID);

    return newEdge;
}


// Return selected source Edge of a Node by index

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeSource(ZHTplusGraph::Node& node, int index)
{
    ZHTplusGraph::Edge* edge = NULL;

    if (index < node.edge_source_size())
        edge = node.mutable_edge_source(index);

    return edge;
}


// Return selected source Edge of a Node by ID

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeSource(ZHTplusGraph::Node& node, string edgeID)
{

    ZHTplusGraph::Edge* edge_source = NULL;

    int numEdges = node.edge_source_size();
    for (int i = 0; i < numEdges; i++)
    {
        ZHTplusGraph::Edge* edge = node.mutable_edge_source(i);
        if (edge->has_edgeid())
            if(edge->edgeid() == edgeID)
                edge_source = edge;
    }

    return edge_source;
}


// Return selected target Edge of a Node by index

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeTarget(ZHTplusGraph::Node& node, int index)
{

    ZHTplusGraph::Edge* edge = NULL;

    if (index < node.edge_target_size())
        edge = node.mutable_edge_target(index);

    return edge;
}


// Return selected target Edge of a Node by ID

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeTarget(ZHTplusGraph::Node& node, string edgeID)
{

    ZHTplusGraph::Edge* edge_target = NULL;

    int numEdges = node.edge_target_size();
    for (int i = 0; i < numEdges; i++)
    {
        ZHTplusGraph::Edge* edge = node.mutable_edge_target(i);
        if (edge->has_edgeid())
            if(edge->edgeid() == edgeID)
                edge_target = edge;
    }

    return edge_target;
}


// Remove an edge originating from a node

bool ZHTplusClient::removeNodeEdge(ZHTplusGraph::Node* node, string edgeID)
{
// stuff goes here
    return true;
}


// Create a new Property for an Edge and set its ID, name, and value

ZHTplusGraph::Property* ZHTplusClient::newEdgeProperty(ZHTplusGraph::Edge* edge, string ID, string name, string value)
{

    ZHTplusGraph::Property* newProperty = edge->add_property();

    newProperty->set_propertyid(ID);
    newProperty->set_name(name);
    newProperty->set_value(value);

    return newProperty;

}


// Return selected Property of an Edge by index

ZHTplusGraph::Property* ZHTplusClient::getEdgeProperty(ZHTplusGraph::Edge* edge, int index)
{

    if (index < edge->property_size())
        return edge->mutable_property(index);
    return NULL;
}


// Return selected Property of a Node by ID

ZHTplusGraph::Property* ZHTplusClient::getEdgeProperty(ZHTplusGraph::Edge* edge, string propertyID)
{

    ZHTplusGraph::Property* property = NULL;

    int numProperties = edge->property_size();
    for (int i = 0; i < numProperties; i++)
    {
        property = edge->mutable_property(i);
        if (property->has_propertyid())
            if(property->propertyid() == propertyID)
                return property;
    }
    return NULL;
}


// Remove a property of an Edge

bool ZHTplusClient::removeEdgeProperty(ZHTplusGraph::Edge* edge, string propertyID)
{
// stuff goes here
    return true;
}


// Return the number of source edges the node has

int ZHTplusClient::getNodeEdgeSourceCount(ZHTplusGraph::Node& node) {

	return node.edge_source_size();
}

// Return the target node ID for an edge

string ZHTplusClient::getEdgeTarget(ZHTplusGraph::Edge* edge) {

	return edge->mutable_target()->c_str();
}


// Teardown ZHT-Clinet

int ZHTplusClient::teardown()
{

    return _zc.teardown();
}
