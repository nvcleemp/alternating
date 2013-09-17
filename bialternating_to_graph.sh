#!/bin/bash

# Translates a vertex alternating k-angulation into a alternating planar graph
# with two types of vertices: degree 2 and degree k

# This scripts expects the programs below to be in the same directory.

./filter_vertex_alternating | ./dual_pl -E | ./bialternating_to_graph
