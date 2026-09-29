# Real Time Scheduling System: synchronization dependencies

Shared dependency integration: periodic RMS scheduling with per-task
context-switch control and deferred scheduling requests.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

Combines the RMS and context-switch branches. This internal merge
provides the scheduling and switching support required by the mutex scenario.
EDF, mutexes, inversion experiments, and inheritance are not included.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `0cf690e354f39cc9d121353a2fa62e5b0e31c8b2`.

```text
git diff 0cf690e354f39cc9d121353a2fa62e5b0e31c8b2...HEAD
```

Source provenance: the reconstructed RMS and context-switch branches, preserving their
feature-specific changes and shared framework ancestry.

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
