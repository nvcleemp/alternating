#!/bin/bash

./vertex_alternating -c1m2 -d -E $1 | ./bialternating_to_graph
