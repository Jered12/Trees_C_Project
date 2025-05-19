# Trees_C_Project

 NetFlow Summary – Smart City Network Optimizer
The NetFlow program simulates and manages a smart city’s router network using a Binary Search Tree (BST) structure. Each node in the tree represents a router, storing its unique ID and traffic load. The program provides core functionalities to analyze, optimize, and maintain the network for efficiency and scalability.

## Core Functionalities:
Router Management

Add Router: Inserts a router (by ID and traffic) into the BST, ensuring hierarchical organization.

Remove Router: Deletes a router while preserving the BST structure.

Network Analysis

Tree Depth: Calculates the maximum depth of the network to evaluate the longest routing path.

Symmetry Check: Determines whether the network is symmetrically balanced — a sign of optimal and even distribution.

Network Optimization

Invert Network: Mirrors the entire network tree by swapping left and right subtrees, useful for simulation or rebalancing.

Traffic Insights

Display Routers In-Order: Lists all routers sorted by their IDs with traffic values, giving a clear view of the topology.

High Traffic Routers: Identifies and prints routers exceeding a specified traffic threshold — helpful for load balancing and congestion monitoring.

## Use Case:
Ideal for city-wide smart networks where administrators need to:

Monitor router loads.

Maintain a clean hierarchical structure.

Optimize traffic flow and routing decisions.

Simulate alternate network structures.
