// Andrew Bennett <andrew.bennett@unsw.edu.au>
// Week 13 Practice Prac q2 sample solution
//
// Find all vertices which are <= d edges from v
//
// Idea for solving this:
// We want to go a maximum of d hops from the start node, so
// we want some sort of graph search algorithm that goes to things
// of distance 1, distance 2, distance 3 .. distance n
// Sounds like we need a BFS!
//
// The algorithm would go soemthing like this:
//
// add the start node to the queue
//
// whike the queue isn't empty:
//   take the next thing from the queue
//   if we've seen it before, skip over this one
//   if we haven't seen it before, mark it as seen
//
//   for each of its neighbours:
//     if they haven't been visited, add them to the queue
//
// We'd need to make sure while doing this that we have
// some way of stopping when we hit a maximum number of hops.
// It would be really nice if we could somehow keep track of
// how many steps it took to get to the previous node, and if
// we had some way of knowing who the previous node was, so
// we can just check if steps-to-prev-node + 1 is going to be our
// max distance (d).
//
// In terms of actually implementing that....
// if we could modify our queue to hold (vertex_id, steps_to_prev_plus_1)
// we could just check that steps field as we go through. But we
// can't modify the data structures :(
//
// We could try changing our BFS a bit though. If you think about
// other graph search algorithms we know about:
//   * BFS: will find the shortest path from A to B on an unweighted graph
//   * DFS: visits nodes depth-first / children of children of children...
//   * Dijkstra's: finds the shortest path from A to all nodes in a weighted graph
//
// So, maybe we can steal some of the ideas from Dijkstra's algorithm
// to help us out here?
//
// We effectively need some way of keeping track of how many hops away
// we are. That could sort of be seen as equivalent to distance.
// Rather than comparing the possible distance to see if it's better, we
// know that because we're doing a BFS we'll always visit it the closest
// way first. 
//
// So, we can just check whether we've seen the neighbouring nodes yet;
// if not we know that they're one hop further away from us.
//
// Now we just need to check whether we've done too many hops, and we need to 
// add the nodes as we see them into our array that we return.

int within(Graph g, Vertex s, int d, Vertex *vs)
{
    int numReached = 0; // how many vertices we've reached

    // clear out our visited array
    for (int i = 0; i < g->nV; i++) {
        visited[i] = -1;
    }

    // Set up our queue
    Queue queue = newQueue();
    QueueJoin(queue, s);

    visited[s] = 0; // took us 0 hops

    while (!QueueIsEmpty(queue)) {
        // take the top thing off the queue
        Vertex curr = QueueLeave(queue);

        int dist_to_curr = visited[curr]; // how many hops to this node

        // if we're too many hops away
        if (dist_to_curr > d) {
            break;
        }

        // don't include the start node in our list
        if (curr != s) {
            vs[numReached++] = curr;
        }

        // go through each of its neighbours
        for (Vertex neighbour = 0; neighbour < g->nV; neighbour++) {
            if (!g->edges[curr][neighbour]) continue; // not joined

            if (visited[neighbour] == -1) { // haven't seen it yet
                visited[neighbour] = visited[curr] + 1; // one hop more
                QueueJoin(queue, neighbour);
            }
        }
    }

    return numReached;
}
