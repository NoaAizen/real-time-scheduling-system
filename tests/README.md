# Manual scenarios: mutex synchronization

Build `mutex_test.cpp` to exercise RMS mutex serialization. Tasks A/B/C
have periods 400/401/402 timer ticks and run three cycles each.
The mutex selects blocked waiters by current priority and transfers ownership
on release. There is no inheritance option on this branch.

The inherited `scheduling_test.cpp` supports `roundRobin` and `RMS`; its
default is `SCENARIO_RMS_HARMONIC_PERIODS` with `RMS`.

Use a compatible 16-bit DOS/Turbo C++ toolchain, with `include/` on the header
search path. Link the sources in `src/` with exactly one selected scenario
from `tests/`; each scenario has its own `main()`. Do not combine scenario
entry points. The code uses DOS headers, `far`, interrupts, and compiler-specific
assembly. No DOS compilation, execution, or successful runtime verification is
claimed. Scenario outcomes and busy-loop timing remain unverified.
