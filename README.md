# Real Time Scheduling System: framework reference

Reconstructed reference containing the provided SMARTS77 framework and
Round Robin, with one-shot task completion and no periodic scheduling.

## Attribution

SMARTS77, including the DOS runtime, timer interrupt and context-switch
foundation, Events, and Round Robin scheduler, was provided by A. Teitelbaum,
based on an idea by H. G. Mendelbaum, at the Jerusalem College of Technology.
Round Robin is provided framework code, not a project implementation.

## Branch scope and dependencies

This internal baseline supplies task contexts, interrupts, Events, sleeping,
Round Robin, and global context-switch controls. Feature additions are separate.

This is a reconstructed feature demonstration, not a claim about the original
development order. The complete public project remains on `main` at `db11cde`.

Intended comparison base: `ece9e26`.

```text
git diff ece9e26...HEAD
```

Source provenance: `ece9e26` and the framework portions of `0fe2d4c`; periodic and EDF additions
are excluded from the reconstructed source tree.

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
