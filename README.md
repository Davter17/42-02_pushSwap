# Push Swap

A C implementation of the push_swap algorithm from 42 School. Sorts a stack of integers using two stacks (A and B) with a limited set of operations, aiming for the minimum number of instructions.

## Algorithm

Uses the **Turk algorithm** - an optimized approach that achieves near-optimal instruction counts:
- **100 numbers**: ~600-700 instructions
- **500 numbers**: ~5500-6500 instructions

## Building

```bash
make
```

This compiles the `push_swap` binary. Requires `cc` (C compiler).

## Usage

```bash
./push_swap 4 67 3 87 70 15 100 2 69 1
```

Outputs the list of instructions to sort the numbers.

## Visual Tester

An interactive web-based visualizer is included in the `tester/` folder.

### Setup

```bash
cd tester
npm install
npm run dev
```

Open http://localhost:3000 in your browser.

### Features

- **Bar visualization**: Each number is displayed as a horizontal bar proportional to its rank, forming a pyramid when sorted
- **Adjustable speed**: From instant (all steps at once) to slow step-by-step animation
- **Dynamic bar sizing**: Bars automatically resize based on the number of elements (1px for 500, 8px for 1)
- **Random generation**: Generate 100 or 500 random numbers
- **Live stats**: Track current step and total moves

## Operations

| Instruction | Description |
|-------------|-------------|
| `sa` | Swap top two elements of stack A |
| `sb` | Swap top two elements of stack B |
| `ss` | `sa` and `sb` at the same time |
| `pa` | Push top element from B to A |
| `pb` | Push top element from A to B |
| `ra` | Rotate stack A (shift up) |
| `rb` | Rotate stack B (shift up) |
| `rr` | `ra` and `rb` at the same time |
| `rra` | Reverse rotate stack A (shift down) |
| `rrb` | Reverse rotate stack B (shift down) |
| `rrr` | `rra` and `rrb` at the same time |

## Cleaning

```bash
make clean    # Remove object files
make fclean   # Remove binary and object files
make re       # Recompile
```
