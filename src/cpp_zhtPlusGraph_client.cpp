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

#include "cpp_zhtclient.h"
#include "ZHTplusGraph.pb.h"
#include "ZHTplusGraph.h"

#include  <getopt.h>
#include  <stdlib.h>
#include  <stdio.h>
#include  <string>
#include  <exception>
using namespace std;

void test_insert();
void test_lookup();

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

			//zc.init(zhtConf, neighborConf);
			printf("starting...\n");

			zpc.init(zhtConf, neighborConf);

			printf("configured...\n");

			test_all();

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

void test_insert() {

    printf("inserting.....\n");

	int rc = zpc.ZHTplusGraphAddNode("11", "1");

	if (rc == 0)
		printf("ADD NODE 1 OK, rc(%d)\n", rc);
	else
		printf("ADD NODE 1 ERR, rc(%d)\n", rc);

	rc = zpc.ZHTplusGraphAddNode("21", "2");

	if (rc == 0)
		printf("ADD NODE 2 OK, rc(%d)\n", rc);
	else
		printf("ADD NODE 2 ERR, rc(%d)\n", rc);

	rc = zpc.ZHTplusGraphAddNodeProperty("12", "2p", "prop12", "12value");

	if (rc == 0)
		printf("ADD NODE 1 Property OK, rc(%d)\n", rc);
	else
		printf("ADD NODE 1 Property ERR, rc(%d)\n", rc);

//	if (rc == 0)
//		printf("ADD NODE 2 OK, rc(%d)\n", rc);
//	else
//		printf("ADD NODE 2 ERR, rc(%d)\n", rc);
//
//	rc = zpc.ZHTplusGraphAddNodeEdge("1", "2", "12", "12");
//
//	if (rc == 0)
//		printf("ADD NODE EDGE OK, rc(%d)\n", rc);
//	else
//		printf("ADD NODE EDGE ERR, rc(%d)\n", rc);
//
//	rc = zpc.ZHTplusGraphAddNodeEdgeProperty("1", "12", "111", "Directed", "No");
//
//	if (rc == 0)
//		printf("ADD NODE EDGE PROPERTY OK, rc(%d)\n", rc);
//	else
//		printf("ADD NODE EDGE PROPERTY ERR, rc(%d)\n", rc);

    printf("inserting complete !");

}

void test_lookup() {

	test_insert();

    string* result = zpc.ZHTplusGraphGetNodePropertyValue("12", "2p");

    printf("NodePropertyValue Lookup Result, value={%s}", result->c_str());

//	int rc = zc.lookup(key, result);
//
//	if (rc == 0)
//		printf("LOOKUP OK, rc(%d), value={%s}\n", rc, result.c_str());
//	else
//		printf("LOOKUP ERR, rc(%d), value={%s}\n", rc, result.c_str());

}
