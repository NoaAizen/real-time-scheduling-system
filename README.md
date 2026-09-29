# Real Time Scheduling System: EDF

Earliest Deadline First selection among READY tasks, with periodic deadlines
and an EDF-versus-Round-Robin comparison scenario.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

Inherits periodic task bookkeeping and the framework. EDF reads
`getRemainingTime()`; RMS and synchronization features are not included.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `5d0b927647048986cbb60b73b9a804b8e9e846f1`.

```text
git diff 5d0b927647048986cbb60b73b9a804b8e9e846f1...HEAD
```

Source provenance: EDF declaration and algorithm from `d3d1c29`; comparison configuration
from `91231fb`; consolidated workload presentation from `db11cde`.

## Structure and build

`include/` contains the interface, `src/` the runtime and supported policies,
and `tests/` the manual scenarios and selection notes.
See [tests/README.md](tests/README.md).

Use a compatible 16-bit DOS/Turbo C++ toolchain, with `include/` on the header
search path. Link the sources in `src/` with exactly one selected scenario
from `tests/`; each scenario has its own `main()`. Do not combine scenario
entry points. The code uses DOS headers, `far`, interrupts, and compiler-specific
assembly. No DOS compilation, execution, or successful runtime verification is
claimed. Scenario outcomes and busy-loop timing remain unverified.
