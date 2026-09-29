# Real Time Scheduling System: mutex synchronization

Mutex ownership, blocking, priority-ordered waiters, and ownership transfer
on release, without priority inheritance.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

Inherits periodic RMS scheduling, suspension/resumption, and per-task
context-switch control with deferred switching. Mutex operations suppress
switching while updating internal state; the critical section itself can
be preempted. EDF is not included.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `8274c11c6328f2603b6c068113784c47ddadde73`.

```text
git diff 8274c11c6328f2603b6c068113784c47ddadde73...HEAD
```

Source provenance: mutex declaration and implementation from `2db718d`, with the
consolidated RMS mutex scenario from `db11cde`.

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
