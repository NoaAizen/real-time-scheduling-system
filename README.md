# Real Time Scheduling System: context-switch control

Per-task context-switch permission and deferred scheduling requests.
Interrupts record a pending request while switching is disabled; re-enabling
switching services that request.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

Requires only the framework task contexts and interrupt machinery.
Periodic tasks, EDF, RMS, mutexes, and inheritance are not included.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `ea0a6c85a6ad95d196d2976bb9eb5a8823c4ab11`.

```text
git diff ea0a6c85a6ad95d196d2976bb9eb5a8823c4ab11...HEAD
```

Source provenance: per-task flag, control methods, initialization, and deferred interrupt
handling from `13b6ee2`. Its periodic-aware deadlock condition belongs
to the periodic branch and is excluded here.

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
