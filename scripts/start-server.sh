#!/bin/bash

echo "Starting ZHT+ Server.."

export LD_LIBRARY_PATH=/usr/local/lib/

./zhtserver -z zht.conf -n neighbor.conf

echo "ZHT Server Started !"
