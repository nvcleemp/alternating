#!/bin/bash

./vertex_alternating -c2m2 -q -d -E $1 | ./bialternating_to_graph
