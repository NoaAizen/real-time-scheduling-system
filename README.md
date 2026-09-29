# Real Time Scheduling System: direct priority inheritance

Optional direct priority inheritance for mutex owners, with the same
one- and two-resource experiments selectable with or without inheritance.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

Inherits the inversion experiments, mutexes, RMS, periodic tasks, and
context-switch support. Adds mutable-priority access and restores base
priority on release. Recursive or transitive inheritance is not implemented.
EDF is not included.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `568d66048d2137dffb13d418a138dece28e25313`.

```text
git diff 568d66048d2137dffb13d418a138dece28e25313...HEAD
```

Source provenance: inheritance declaration and mutex changes from `a66ba5c`; required
priority accessors from `a4d43e1`; consolidated comparison experiments
from `db11cde`.

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
