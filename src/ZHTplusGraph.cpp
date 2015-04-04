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

ZHTplusClient::ZHTplusClient() {
}

ZHTplusClient::~ZHTplusClient() {
}

// Initialize zht-client using zht and neighbor conf

int ZHTplusClient::init(const string& zhtConf, const string& neighborConf) {
    printf("init\n");
    return _zc.init(zhtConf, neighborConf);
}

// Create a new node, serialize it, and store it in ZHT

int ZHTplusClient::ZHTplusGraphAddNode(string NodeID, string NodeName) {
    printf("ZHTplusGraphAddNode.......\n");
    ZHTplusGraph::Node newNode;
	string* KVSvalue;

	newNode = createNode(NodeID, NodeName);
	printf("ZHTplusGraphAddNode...node created\n");
	KVSvalue = serializeNodeToString(newNode);
	printf("serialize done\n");
	//printf("ZHTplusGraphAddNode...KVSvalue : %s\n", KVSvalue->c_str());
	return _zc.insert(NodeID, *KVSvalue);
}


//// Find the node, deserialize it, add the property, reserialize it, remove the old node value, insert the new node value
//
//int ZHTplusClient::ZHTplusGraphAddNodeProperty(ZHTClient* zc, string NodeID, string PropertyID, string PropertyName, string PropertyValue) {
//
//	string* KVSvalue;
//	ZHTplusGraph::Node* theNode;
//	ZHTplusGraph::Property* newProperty;
//
//	zc->lookup(NodeID, *KVSvalue);
//	theNode = parseNodeFromString(*KVSvalue);
//	newProperty = newNodeProperty(theNode, PropertyID, PropertyName, PropertyValue);
//	KVSvalue = serializeNodeToString(theNode);
//	zc->remove(NodeID);
//	return zc->insert(NodeID, *KVSvalue);
//}
//
//
//// Find node1, deserialize it, add the edge from node1 to node2, reserialize node1, remove the old node1 value, insert the new node1 value
//
//int ZHTplusClient::ZHTplusGraphAddNodeEdge(ZHTClient* zc, string Node1ID, string Node2ID, string EdgeID, string EdgeName) {
//
//	string* KVSvalue;
//	ZHTplusGraph::Node* theNode;
//	ZHTplusGraph::Edge* newEdge;
//
//	zc->lookup(Node1ID, *KVSvalue);
//	theNode = parseNodeFromString(*KVSvalue);
//	newEdge = newNodeEdge(theNode, Node2ID, EdgeID, EdgeName);
//	KVSvalue = serializeNodeToString(theNode);
//	zc->remove(Node1ID);
//	return zc->insert(Node1ID, *KVSvalue);
//}
//
//
//// Find the node, deserialize it, find the edge, add the property, reserialize it, remove the old node value, insert the new node value
//
//int ZHTplusClient::ZHTplusGraphAddNodeEdgeProperty(ZHTClient* zc, string NodeID, string EdgeID, string PropertyID, string PropertyName, string PropertyValue) {
//
//	string* KVSvalue;
//	ZHTplusGraph::Node* theNode;
//	ZHTplusGraph::Edge* theEdge;
//	ZHTplusGraph::Property* newProperty;
//
//	zc->lookup(NodeID, *KVSvalue);
//	theNode = parseNodeFromString(*KVSvalue);
//	theEdge = getNodeEdgeSource(theNode, EdgeID);
//	newProperty = newEdgeProperty(theEdge, PropertyID, PropertyName, PropertyValue);
//	KVSvalue = serializeNodeToString(theNode);
//	zc->remove(NodeID);
//	return zc->insert(NodeID, *KVSvalue);
//}
//
//
//// Return selected Property value of a Node
//// TODO : Return the lookup status; Accept result as the last parameter
//
//string* ZHTplusClient::ZHTplusGraphGetNodePropertyValue(ZHTClient* zc, string NodeID, string PropertyID) {
//
//	string* KVSvalue;
//	ZHTplusGraph::Node* theNode;
//	ZHTplusGraph::Property* theProperty;
//
//	zc->lookup(NodeID, *KVSvalue);
//	theNode = parseNodeFromString(*KVSvalue);
//	theProperty = getNodeProperty(theNode, PropertyID);
//	return theProperty->mutable_value();
//}
//
//
//// Return the target NodeID of the selected Edge of a Node
//// TODO : Return the lookup status; Accept result as the last parameter
//
//string* ZHTplusClient::ZHTplusGraphGetNodeEdgeTarget(ZHTClient* zc, string NodeID, string EdgeID) {
//
//	string* KVSvalue;
//	ZHTplusGraph::Node* theNode;
//	ZHTplusGraph::Edge* theEdge;
//
//	zc->lookup(NodeID, *KVSvalue);
//	theNode = parseNodeFromString(*KVSvalue);
//	theEdge = getNodeEdgeSource(theNode, EdgeID);
//	return theEdge->mutable_target();
//}
//
//
//// Return selected Property value of an Edge of a Node
//// TODO : Return the lookup status; Accept result as the last parameter
//
//string* ZHTplusClient::ZHTplusGraphGetNodeEdgePropertyValue(ZHTClient* zc, string NodeID, string EdgeID, string PropertyID) {
//
//	string* KVSvalue;
//	ZHTplusGraph::Node* theNode;
//	ZHTplusGraph::Edge* theEdge;
//	ZHTplusGraph::Property* theProperty;
//
//	zc->lookup(NodeID, *KVSvalue);
//	theNode = parseNodeFromString(*KVSvalue);
//	theEdge = getNodeEdgeSource(theNode, EdgeID);
//	theProperty = getEdgeProperty(theEdge, PropertyID);
//	return theProperty->mutable_value();
//}


// Serialize the node and store the bytes in the returned string.

string* ZHTplusClient::serializeNodeToString(ZHTplusGraph::Node node) {

	string* output;

    printf("Serializing...");

	if (node.SerializeToString(output))
		return output;
	else
		return (string*) NULL;
}


// Return a parsed node from the given string.

ZHTplusGraph::Node* ZHTplusClient::parseNodeFromString(string& data) {

	ZHTplusGraph::Node* newNode;

	if(newNode->ParseFromString(data))
		return newNode;
	else
		return NULL;
}


// Create a new Node and set its ID and name

ZHTplusGraph::Node ZHTplusClient::createNode(string ID, string name) {

	ZHTplusGraph::Node newNode;

	newNode.set_nodeid(ID);
	newNode.set_name(name);

	return newNode;
}


// Delete a node and all its properties and relationships (both origin and terminus)

bool ZHTplusClient::deleteNode(ZHTplusGraph::Node* node) {
// stuff goes here
	return true;
}


// Create a new Property for a Node and set its ID, name, and value

ZHTplusGraph::Property* ZHTplusClient::newNodeProperty(ZHTplusGraph::Node* node, string ID, string name, string value) {

	ZHTplusGraph::Property* newProperty = node->add_property();

	newProperty->set_propertyid(ID);
	newProperty->set_name(name);
	newProperty->set_value(value);

	return newProperty;
}


// Return selected Property of a Node by index

ZHTplusGraph::Property* ZHTplusClient::getNodeProperty(ZHTplusGraph::Node* node, int index) {

	if (index < node->property_size())
		return node->mutable_property(index);
	return NULL;
}


// Return selected Property of a Node by ID

ZHTplusGraph::Property* ZHTplusClient::getNodeProperty(ZHTplusGraph::Node* node, string propertyID) {

	ZHTplusGraph::Property* property = NULL;

	int numProperties = node->property_size();
	for (int i = 0; i < numProperties; i++) {
		property = node->mutable_property(i);
		if (property->has_propertyid())
			if(property->propertyid() == propertyID)
				return property;
	}
	return NULL;
}


// Remove selected Property of a Node

bool ZHTplusClient::removeNodeProperty(ZHTplusGraph::Node* node, string propertyID) {

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

ZHTplusGraph::Edge* ZHTplusClient::newNodeEdge(ZHTplusGraph::Node* node1, string node2ID, string ID, string name) {

	ZHTplusGraph::Edge* newEdge = node1->add_edge_source();

	newEdge->set_edgeid(ID);
	newEdge->set_name(name);
	newEdge->set_source(node1->nodeid());
	newEdge->set_target(node2ID);

	return newEdge;
}


// Return selected source Edge of a Node by index

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeSource(ZHTplusGraph::Node* node, int index) {

	if (index < node->edge_source_size())
		return node->mutable_edge_source(index);
	return NULL;
}


// Return selected source Edge of a Node by ID

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeSource(ZHTplusGraph::Node* node, string edgeID) {

	ZHTplusGraph::Edge* edge = NULL;

	int numEdges = node->edge_source_size();
	for (int i = 0; i < numEdges; i++) {
		edge = node->mutable_edge_source(i);
		if (edge->has_edgeid())
			if(edge->edgeid() == edgeID)
				return edge;
	}
	return NULL;
}


// Return selected target Edge of a Node by index

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeTarget(ZHTplusGraph::Node* node, int index) {

	if (index < node->edge_target_size())
		return node->mutable_edge_target(index);
	return NULL;
}


// Return selected target Edge of a Node by ID

ZHTplusGraph::Edge* ZHTplusClient::getNodeEdgeTarget(ZHTplusGraph::Node* node, string edgeID) {

	ZHTplusGraph::Edge* edge = NULL;

	int numEdges = node->edge_target_size();
	for (int i = 0; i < numEdges; i++) {
		edge = node->mutable_edge_target(i);
		if (edge->has_edgeid())
			if(edge->edgeid() == edgeID)
				return edge;
	}
	return NULL;
}


// Remove an edge originating from a node

bool ZHTplusClient::removeNodeEdge(ZHTplusGraph::Node* node, string edgeID) {
// stuff goes here
	return true;
}


// Create a new Property for an Edge and set its ID, name, and value

ZHTplusGraph::Property* ZHTplusClient::newEdgeProperty(ZHTplusGraph::Edge* edge, string ID, string name, string value) {

	ZHTplusGraph::Property* newProperty = edge->add_property();

	newProperty->set_propertyid(ID);
	newProperty->set_name(name);
	newProperty->set_value(value);

	return newProperty;

}


// Return selected Property of an Edge by index

ZHTplusGraph::Property* ZHTplusClient::getEdgeProperty(ZHTplusGraph::Edge* edge, int index) {

	if (index < edge->property_size())
		return edge->mutable_property(index);
	return NULL;
}


// Return selected Property of a Node by ID

ZHTplusGraph::Property* ZHTplusClient::getEdgeProperty(ZHTplusGraph::Edge* edge, string propertyID) {

	ZHTplusGraph::Property* property = NULL;

	int numProperties = edge->property_size();
	for (int i = 0; i < numProperties; i++) {
		property = edge->mutable_property(i);
		if (property->has_propertyid())
			if(property->propertyid() == propertyID)
				return property;
	}
	return NULL;
}


// Remove a property of an Edge

bool ZHTplusClient::removeEdgeProperty(ZHTplusGraph::Edge* edge, string propertyID) {
// stuff goes here
	return true;
}


