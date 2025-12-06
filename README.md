# AI_Lab — State Space Search & Classic AI Examples

A small collection of AI example programs (C, Prolog and search algorithms) demonstrating state-space search techniques, heuristics, and classic planning problems.

Contents of this repository include implementations and sample inputs for puzzles and problems such as the sliding-tile puzzle (A*), Tower of Hanoi, N-Queens, Missionaries & Cannibals, and simple neural network demo for the IRIS dataset.

Table of contents
- [Demo (playable video)](#demo-playable-video)
- [Quick overview](#quick-overview)
- [Repository structure](#repository-structure)
- [Build & run (example)](#build--run-example)

## Demo (playable video)

Watch the A* algorithm solve the N-puzzle problem in action:

<video controls width="720" poster="docs/demo-promo.png">
  <source src="docs/demo.mp4" type="video/mp4">
  Your browser does not support the video tag. <a href="docs/demo.mp4">Download the video</a> to watch it locally.
</video>

> **Note:** If the video doesn't play directly on GitHub's web interface, you can download it using the link above or view the repository via GitHub Pages.

## Quick overview

- Language: primarily C and Prolog
- Topics: state-space search, A* heuristic search, BFS, classic planning problems, simple neural network example for IRIS dataset

## Repository structure

- `Neural Network done in C/` — small C neural network and IRIS dataset sample
- `Prolog Programs/` — a set of classic Prolog problems and solutions
- `State Space Search/` — C implementations for N-Puzzle-Problem and search techniques

## Build & run (example)

General steps for compiling C examples (example uses the sliding-puzzle file name, adjust to the file you want):

1. Open a terminal and change to the folder containing the C file you want to run. Example:

```bash
cd "State Space Search"
gcc -o sliding "Sliding-puzzle Proble using A-star algorithm.c" -O2
./sliding
```

Notes:
- Filenames in this repo sometimes contain spaces; wrap them in quotes when using the shell.
- You only need a C compiler (e.g., `gcc`) for the C programs.