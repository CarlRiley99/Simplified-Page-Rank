# Simplified-Page-Rank
Code implements a simplified version of Google's Page Rank algorithm

### Representing the Web as a Graph
The idea is that the entire internet can be represented as a graph. Each node represents a webpage
and each edge represents a link between two webpages. This graph can be implemented as an
Adjacency Matrix or an Adjacency List. <br />

This explanation assumes the graph is implemented as an Adjacency Matrix . We represent the
graph in the form of a |V|x|V| matrix where |V| is the total number of vertices in the graph.
A vertex represents a webpage in the internet. Thus, if there is an edge from V <sub> i </sub> to
V <sub> j </sub> page *i* points to page *j*. In the adjacency matrix M <sub> ji </sub> > 0 if there
is an edge and 0 otherwise. <br />

### Core Ideas of PageRank
1. Improtant webpages will point to other important webpages.
2. Each page will have a score and the results of the search will be based on the page score
(called page rank).
