# Real Time Scheduling System: priority inversion

One- and two-resource priority-inversion experiments without priority
inheritance, using Events for ordering and RMS for priority selection.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

Inherits mutexes and their periodic RMS/context-switch dependencies.
Events come from the provided framework. EDF and inheritance are excluded.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `6cfcbfb6b1f8f1bd1f096317adaa26baced578d3`.

```text
git diff 6cfcbfb6b1f8f1bd1f096317adaa26baced578d3...HEAD
```

Source provenance: inversion experiments from `d2ecbff`, using the consolidated scenario
layout and preserved workload-yield behavior from `db11cde`. The
inheritance constructor and toggle are deliberately not imported.

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
