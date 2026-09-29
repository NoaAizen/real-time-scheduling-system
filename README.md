# Real Time Scheduling System: periodic tasks

Periodic tasks, deadline accounting, finite execution cycles, and reactivation
at period boundaries, using the provided Round Robin scheduler.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

Requires only the reconstructed framework reference. EDF, RMS, mutexes,
and per-task switching enhancements are not included.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `ea0a6c85a6ad95d196d2976bb9eb5a8823c4ab11`.

```text
git diff ea0a6c85a6ad95d196d2976bb9eb5a8823c4ab11...HEAD
```

Source provenance: periodic runtime and lifecycle correction from `0fe2d4c`; `getPeriod()`
from `a4d43e1`; periodic deadlock eligibility from `13b6ee2`; workload
configurations from `91231fb` and consolidated workloads from `db11cde`.

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
