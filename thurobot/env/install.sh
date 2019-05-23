#!/usr/bin/env bash
BASE=$1
LIDAR=$2
echo "export RIKIBASE=$BASE" >> ~/.zshrc
echo "export RIKILIDAR=$LIDAR" >> ~/.zshrc
source ~/.zshrc
