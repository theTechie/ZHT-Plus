#!/bin/bash 

# Created on March 13, 2015
# Author : Gagan M Gowda (theTechie)

echo "Fetching Cluster IPs from AWS..."

# Get IPs of all instances using AWS CLI
#  - filter instances based on ami-id (to identify a zht+ cluster)
#  - filter instances using instance-state-code (for Running instances)
#  - copy zht+ binary and configs using pSSH
#  - start zht+ server on all cluster nodes using pSSH

AMI_ID="ami-xxxxxxxx"		# AMI used for cluster node
INSTANCE_STATE_CODE="16"	# 0 (pending), 16 (running), 32 (shutting-down), 48 (terminated), 64 (stopping), 80 (stopped)
PRIVATE_KEY="xxxx.pem"		# ssh private-key file
HOST_FILE_LOCATION="bin/*"	# location of the files to be copied to remote node
REMOTE_FILE_LOCATION="$HOME"	# target location on remote node
ZHT_SERVER_PORT=50000		# port on which ZHT Server will run

GET_IP="aws ec2 describe-instances  --query "Reservations[*].Instances[*].PrivateIpAddress" --filter Name=instance-state-code,Values=$INSTANCE_STATE_CODE Name=image-id,Values=$AMI_ID  --output=text"

IP_LIST=$($GET_IP)

(for i in $IP_LIST; do
	echo $i $ZHT_SERVER_PORT
done) | tee bin/neighbor.conf

echo "neighbor.conf generated !"

# TODO : Use the parallel option -p  for faster copying. How to arrive at the parallelization number ?
# Copy ZHT binary and configs to remote node $HOME
for i in $IP_LIST; do
	echo "connect to $i and copy zht binary and configs"
	 parallel-scp -H $i -x "-oStrictHostKeyChecking=no -i $PRIVATE_KEY" $HOST_FILE_LOCATION $REMOTE_FILE_LOCATION
done

# Start ZHT server at remote node
for i in $IP_LIST; do
	echo "connect to $i and start zhtserver"
        parallel-ssh -H $i -x "-oStrictHostKeyChecking=no -i $PRIVATE_KEY" ./start-server.sh&
done
