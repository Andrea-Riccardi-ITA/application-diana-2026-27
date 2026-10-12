# Solution explanation

I solved the problem by reading the generated matrix from `map.txt`, then applying dynamic programming to compute the minimum total cost from the top-left cell to the bottom-right cell.

## Why this approach works

The map only allows movement:
- down
- right

That means each cell can only be reached from either:
- the cell above it, or
- the cell to its left

This creates an optimal substructure: the cheapest path to any cell depends only on the cheapest path to a previous cell. Because every value in the map is positive, a shortest path will never need to revisit a cell or take a more expensive detour.

## Dynamic programming formula

Let `dp[i][j]` be the minimum total cost needed to reach cell `(i, j)`.

The recurrence is:

`dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]`

with the base case:

`dp[0][0] = grid[0][0]`

This works in $O(rows \times cols)$ time and uses $O(rows \times cols)$ memory, which is efficient even for large maps like `100 x 100`.

## Reconstructing the path

After computing the minimum cost for every cell, I backtracked from the destination to the start:

- if the path came from the cell above, I recorded a `d`
- if it came from the left, I recorded an `r`

Then I reversed the list to get the correct order from the start to the destination.

Finally, I printed the move sequence and returned the total time.

## Why not use Dijkstra's algorithm?

Dijkstra is a very good general-purpose shortest-path algorithm, but it is not necessary here.

This problem is not a general graph with arbitrary edges. The movement rules are restricted to only down and right, so the graph is a directed acyclic graph (DAG). Because of that, dynamic programming is simpler, faster to implement, and more direct for this exact structure.

In short:

- Dijkstra is more general, but heavier
- DP uses the special movement constraints to solve the problem optimally in one pass
- the result is easier to trace and reconstruct for the required move sequence
