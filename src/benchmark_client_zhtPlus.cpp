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
 * benchmark_client_zhtGraph.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: Gagan
 *      Contributor: Ben, Anirudh
 */
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <vector>
#include <error.h>
#include <getopt.h>
#include <unistd.h>

#include "ZHTplusGraph.pb.h"
#include "ZHTplusGraph.h"
#include "Util.h"

#include "cpp_zhtclient.h"
#include "ZHTUtil.h"

using namespace std;
using namespace iit::datasys::zht::dm;
using namespace iit::datasys::zht::graph;

ZHTplusClient zpc;
int numOfOps = -1;
int keyLen = 10;
int valLen = 1000;
vector<string> pkgList;

void init_packages() {

	for (int i = 0; i < numOfOps; i++) {

		ZHTplusGraph::Node node;
		node.set_nodeid(HashUtil::randomString(keyLen));
		node.set_name(HashUtil::randomString(valLen));

		//package.set_virtualpath(HashUtil::randomString(lenString)); //as key
		//package.set_isdir(true);
		//package.set_opcode();

		//package.set_replicanum(5); //orginal--Note: never let it be nagative!!!

		/*
		package.set_realfullpath(
				"Some-Real-longer-longer-and-longer-Paths--------");
		package.add_listitem("item-----1");
		package.add_listitem("item-----2");
		package.add_listitem("item-----3");
		package.add_listitem("item-----4");
		package.add_listitem("item-----5");
		package.add_listitem(HashUtil::randomString(8192));
		*/
		pkgList.push_back(node.SerializeAsString());
	}
}

int benchmarkInsert() {

	double start = 0;
	double end = 0;
	start = TimeUtil::getTime_msec();
	int errCount = 0;

	int c = 0;
	vector<string>::iterator it;
	for (it = pkgList.begin(); it != pkgList.end(); it++) {

		c++;

		string pkg_str = *it;
		ZHTplusGraph::Node node;
		node.ParseFromString(pkg_str);

		int ret = zpc.ZHTplusGraphAddNode(node.nodeid(), node.name());

		if (ret < 0) {
			errCount++;
		}
	}

	end = TimeUtil::getTime_msec();

	char buf[200];
	sprintf(buf, "Inserted packages, %d, %d, cost(ms), %f", numOfOps - errCount,
			numOfOps, end - start);
	cout << buf << endl;

	return 0;
}




int benchmarkAppend() {

	vector<string> pkgList_append = pkgList;

	vector<string>::iterator it;
	//for (it = pkgList.begin(); it != pkgList.end(); it++) {

	//	ZPack package;
	//	package.ParseFromString((*it));

	//	package. add_listitem("item-----6-append");

	//	pkgList_append.push_back(package.SerializeAsString());
	//}

	double start = 0;
	double end = 0;
	start = TimeUtil::getTime_msec();
	int errCount = 0;

	int c = 0;
	for (it = pkgList_append.begin(); it != pkgList_append.end(); it++) {

		c++;

		string pkg_str = *it;

		ZHTplusGraph::Node node;
		node.ParseFromString(pkg_str);

		int ret = zpc.ZHTplusGraphAddNodeProperty(node.nodeid(), node.nodeid(), HashUtil::randomString(valLen).c_str(), HashUtil::randomString(valLen).c_str());

		if (ret < 0) {
			errCount++;
		}
	}

	end = TimeUtil::getTime_msec();

	char buf[200];
	sprintf(buf, "Appended packages, %d, %d, cost(ms), %f", numOfOps - errCount,
			numOfOps, end - start);
	cout << buf << endl;

	return 0;
}

float benchmarkLookup() {

	double start = 0;
	double end = 0;
	start = TimeUtil::getTime_msec();
	int errCount = 0;

	int c = 0;
	vector<string>::iterator it;
	for (it = pkgList.begin(); it != pkgList.end(); it++) {

		string result;
		c++;

		string pkg_str = *it;
		ZHTplusGraph::Node node;

		node.ParseFromString(pkg_str);

		zpc.ZHTplusGraphGetNodePropertyValue(node.nodeid(), node.nodeid());
		//cout << "Found result: "<< result << endl;
//		if (ret < 0) {
//			errCount++;
//		} else if (result.empty()) { //empty string
//			errCount++;
//		}
	}

	end = TimeUtil::getTime_msec();

	char buf[200];
	sprintf(buf, "Lookuped packages, %d, %d, cost(ms), %f", numOfOps - errCount,
			numOfOps, end - start);
	cout << buf << endl;

	return 0;
}

float benchmarkRemove() {

	double start = 0;
	double end = 0;
	start = TimeUtil::getTime_msec();
	int errCount = 0;

	int c = 0;
	vector<string>::iterator it;
	for (it = pkgList.begin(); it != pkgList.end(); it++) {

		string result;
		c++;

		string pkg_str = *it;

		ZHTplusGraph::Node node;
		node.ParseFromString(pkg_str);

		int ret = 0;

		if (ret < 0) {
			errCount++;
		}
	}

	end = TimeUtil::getTime_msec();

	char buf[200];
	sprintf(buf, "Removed packages, %d, %d, cost(ms), %f", numOfOps - errCount,
			numOfOps, end - start);
	cout << buf << endl;

	return 0;
}


int benchmark(string &zhtConf, string &neighborConf) {

	srand(getpid() + TimeUtil::getTime_usec());

	if (zpc.init(zhtConf, neighborConf) != 0) {

		cout << "ZHTClient initialization failed, program exits." << endl;
		return -1;
	}

	init_packages();

	benchmarkInsert();

    benchmarkAppend();

	benchmarkLookup();


	//benchmarkRemove();

	zpc.teardown();

	return 0;

}

void printUsage(char *argv_0);

int main(int argc, char **argv) {

	extern char *optarg;

	int printHelp = 0;

	string zhtConf = "";
	string neighborConf = "";

	int c;
	while ((c = getopt(argc, argv, "z:n:o:v:h")) != -1) {
		switch (c) {
		case 'z':
			zhtConf = string(optarg);
			break;
		case 'n':
			neighborConf = string(optarg);
			break;
		case 'o':
			numOfOps = atoi(optarg);
			break;
		case 'v':
			valLen = atoi(optarg);
			break;
		case 'h':
			printHelp = 1;
			break;
		default:
			fprintf(stderr, "Illegal argument \"%c\"\n", c);
			printUsage(argv[0]);
			exit(1);
		}
	}

	int helpPrinted = 0;
	if (printHelp) {
		printUsage(argv[0]);
		helpPrinted = 1;
	}

	try {
		if (!zhtConf.empty() && !neighborConf.empty() && numOfOps != -1) {

			benchmark(zhtConf, neighborConf);

		} else {

			if (!helpPrinted)
				printUsage(argv[0]);
		}
	} catch (exception& e) {

		fprintf(stderr, "%s, exception caught:\n\t%s",
				"benchmark_client.cpp::main", e.what());
	}

}

void printUsage(char *argv_0) {

	fprintf(stdout, "Usage:\n%s %s\n", argv_0,
			"-z zht.conf -n neighbor.conf -o number_of_operations -v value_size [-h(help)] ");
}
