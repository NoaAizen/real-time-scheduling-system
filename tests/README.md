# Manual scenarios: priority inversion

Build `priority_inversion_test.cpp`. Set `INVERSION_SCENARIO` to
`ONE_RESOURCE` (default) or `TWO_RESOURCES`, then rebuild. Events arrange for
low-priority tasks to own the resources before higher-priority tasks contend.
One-resource periods C/B/A are 400/401/402; two-resource periods H/M/L/X/N/Z
are 400 through 405. Each task has one cycle. Output goes to
`priority_inversion_test.txt` or `two_resources_test.txt`.

This branch has no inheritance implementation or toggle.
The inherited mutex and scheduling scenarios remain available; build each
separately. Scheduling policies are `roundRobin` and `RMS`.

Use a compatible 16-bit DOS/Turbo C++ toolchain, with `include/` on the header
search path. Link the sources in `src/` with exactly one selected scenario
from `tests/`; each scenario has its own `main()`. Do not combine scenario
entry points. The code uses DOS headers, `far`, interrupts, and compiler-specific
assembly. No DOS compilation, execution, or successful runtime verification is
claimed. Scenario outcomes and busy-loop timing remain unverified.
