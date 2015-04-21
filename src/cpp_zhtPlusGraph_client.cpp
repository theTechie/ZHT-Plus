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
 * cpp_zhtPlusGraph_client.cpp
 *
 *  Created on: March 30, 2015
 *      Author: Gagan Munisiddha Gowda
 *      Contributor: Benjamin Miwa, Anirudh Sunkineni
 */

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <exception>

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

void test_insert();
void test_lookup();
void loadGraph();

void printUsage(char *argv_0);

ZHTplusClient zpc;

void test_all() {

	printf("starting test_insert...\n");

	test_insert();

	printf("starting test_lookup...\n");

	test_lookup();
}


int main(int argc, char **argv) {

	extern char *optarg;

	int printHelp = 0;
	string zhtConf = "";
	string neighborConf = "";

	int c;
	while ((c = getopt(argc, argv, "z:n:h")) != -1) {
		switch (c) {
		case 'z':
			zhtConf = string(optarg);
			break;
		case 'n':
			neighborConf = string(optarg);
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

		if (!zhtConf.empty() && !neighborConf.empty()) {

			printf("starting...\n");

			zpc.init(zhtConf, neighborConf);

			printf("configured...\n");

			//test_all();

			loadGraph();

			zpc.teardown();

			printf("end...\n");

		} else {

			if (!helpPrinted)
				printUsage(argv[0]);
		}
	} catch (exception& e) {

		fprintf(stderr, "%s, exception caught:\n\t%s", "ZHTServer::main",
				e.what());
	}

}

void printUsage(char *argv_0) {

	fprintf(stdout, "Usage:\n%s %s\n", argv_0,
			"-z zht.conf -n neighbor.conf [-h(help)]");
}

// Load Graph using the graph dataset stored in file
void loadGraph() {
    std::ifstream infile("../datasets/web-Stanford.txt");
    string a, b;

    double start = 0;
    double end = 0;
    start = TimeUtil::getTime_msec();
    char buffer[80];

    cout << "Loading Graph..." << endl;

    //while (infile >> a >> b) {
    for(int i = 0; i < 1; i++) {

    	infile >> a >> b;
        zpc.ZHTplusGraphAddNode(a, a);
        zpc.ZHTplusGraphAddNode(b, b);

        stringstream stream;
        stream << a << "-" << b;

        zpc.ZHTplusGraphAddNodeEdge(a, b, stream.str(), stream.str());

    //cout << stream.str() << endl;
    }


    end = TimeUtil::getTime_msec();

    cout << "Graph Loading Completed ! Time in (ms) => " << end - start << endl;

    for(int i = 5; i < 6; i++) {

    	stringstream num;
    	num << i;

 //   	start = TimeUtil::getTime_msec();

 //   	cout << "DFS : " << zpc.ZHTplusGraphDFS(num.str().c_str()) << endl;

 //   	end = TimeUtil::getTime_msec();

 //   	cout << "DFS Completed ! Time in (ms) => " << end - start << endl;


 //   	start = TimeUtil::getTime_msec();

 //   	cout << "BFS : " << zpc.ZHTplusGraphBFS(num.str().c_str()) << endl;

 //   	end = TimeUtil::getTime_msec();

 //   	cout << "BFS Completed ! Time in (ms) => " << end - start << endl;


	   	start = TimeUtil::getTime_msec();

	   	cout << "PageRank : " << zpc.ZHTplusGraphPageRank(num.str().c_str(), 20) << endl;

	   	end = TimeUtil::getTime_msec();

	   	cout << "PageRank Completed ! Time in (ms) => " << end - start << endl;

    }
}

void test_insert() {

    printf("inserting.....\n");

	int rc = zpc.ZHTplusGraphAddNode("1", "1");

	if (rc == 0)
		printf("ADD NODE 1 OK, rc(%d)\n", rc);
	else
		printf("ADD NODE 1 ERR, rc(%d)\n", rc);

	rc = zpc.ZHTplusGraphAddNode("1", "2");

	if (rc == 0)
		printf("ADD NODE 2 OK, rc(%d)\n", rc);
	else
		printf("ADD NODE 2 ERR, rc(%d)\n", rc);

	rc = zpc.ZHTplusGraphAddNodeProperty("1", "1p", "prop-1", "prop12value");

	if (rc == 0)
		printf("ADD NODE 1 Property OK, rc(%d)\n", rc);
	else
		printf("ADD NODE 1 Property ERR, rc(%d)\n", rc);


	rc = zpc.ZHTplusGraphAddNodeEdge("1", "2", "12", "12-Edge");

	if (rc == 0)
		printf("ADD NODE EDGE OK, rc(%d)\n", rc);
	else
		printf("ADD NODE EDGE ERR, rc(%d)\n", rc);

	rc = zpc.ZHTplusGraphAddNodeEdgeProperty("1", "12", "prop-1-12", "Directed", "No");

	if (rc == 0)
		printf("ADD NODE EDGE PROPERTY OK, rc(%d)\n", rc);
	else
		printf("ADD NODE EDGE PROPERTY ERR, rc(%d)\n", rc);

    printf("inserting complete ! \n");

}

void test_lookup() {

	test_insert();

    string result = zpc.ZHTplusGraphGetNodePropertyValue("1", "1p");
    cout << "NodePropertyValue Lookup Result, value : " << result << "\n";

    result = zpc.ZHTplusGraphGetNodeEdgeTarget("1", "12");
    cout << "NodeEdgeTarget Lookup Result, value : " << result << "\n";

    result = zpc.ZHTplusGraphGetNodeEdgePropertyValue("1", "12", "prop-1-12");
    cout << "NodeEdgePropertyValue Lookup Result, value : " << result << "\n";
}
