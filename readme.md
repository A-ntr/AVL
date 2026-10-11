# GatorID AVL Tree

A custom AVL tree implementation that organizes University of Florida student account records using GatorIDs as keys.

## Overview

This project uses an AVL tree — a self-balancing binary search tree — as the backing data structure for storing and looking up student account records keyed by GatorID. The AVL tree's self-balancing invariant keeps its height proportional to the logarithm of the number of stored records, so lookups and updates stay efficient as the index grows ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)).

## Why an AVL Tree

As a general property of the AVL data structure ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)):

- **Fast lookups by key.** Because the tree stays height-balanced, searching for a specific GatorID takes time proportional to the tree's height rather than to the number of stored records ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)).
- **Efficient updates.** After an insertion or deletion, balance is restored by rotating subtrees so the AVL invariant holds again ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)).
- **Predictable performance.** The self-balancing invariant prevents the degenerate, linked-list-like behavior of an unbalanced binary search tree when keys are inserted in a non-random order.

## Complexity

For a tree holding `n` records, an AVL tree provides the following theoretical bounds. These are properties of the AVL data structure in general, not measurements taken from this specific codebase ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)).

| Operation | Average case | Worst case |
| --- | --- | --- |
| Search | O(log n) ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)) | O(log n) ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)) |
| Insert | O(log n) ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)) | O(log n) ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)) |
| Delete | O(log n) ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)) | O(log n) ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)) |

One nuance worth noting: an insertion may require only a constant number of rotations to rebalance, but a deletion can require rebalancing that propagates toward the root, meaning up to O(log n) rotations in the worst case ([Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)). Insertion and deletion each take O(log n) time in the worst case.

## Getting Started

See the source files in this repository for the implementation.
