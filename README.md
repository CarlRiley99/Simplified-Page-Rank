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

![alt text](Images/General_Graph.jpeg)

Each webpage is thus a node in the directed graph and has incoming edges and outgoing edges.
Each node has a rank. According to PageRank, this rank is equally split among the node's outgoing links and this 
rank is equal to the sum of the incoming ranks. The rank is based on the indegree (the number
of nodes pointing to it) and the importance of incoming node. This is important considering, let's
say, you create your personal website and have a million links to other pages of importance.
If this was not the case and rank used out links, we can easily dupe the algorithm. Therefore,
the rank is based on in-links.

### Input
Line 1 contains the number of lines (n) that will follow and the number of power iterations you need
to perform. Each line from 2 to *n* will contain two URL's - *from_page  to_page* separated by a space.
This means *from_page* points to the URL *to_page*. <br />

\* The first power iteration is simply the starting point for page ranks\* <br />
\* 2 power iterations means one matrix multiplication \* <br />
\* 3 power iterations means two matrix multuplications \* <br />

### Output
Print the PageRank of all pages after *n* power iterations in ascending alphabetical order of webpage.
Also, round off the rank of the page to two decimal places. 

## Sample Problem
### Input:
7 2 <br />
google.com  gmail.com <br />
google.com  maps.com <br />
