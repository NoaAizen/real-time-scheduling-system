# Manual scenarios: context-switch control

This branch isolates runtime control methods and has no standalone scenario.
A one-shot application can call `contextSwitchOff()`, request scheduling with
`callScheduler()`, and then use `contextSwitchOn()` to service the deferred
request. It uses the two-argument `declareTask(taskFunction, taskName)` API.

Use a compatible 16-bit DOS/Turbo C++ toolchain, with `include/` on the header
search path. Link the sources in `src/` with exactly one selected scenario
from `tests/`; each scenario has its own `main()`. Do not combine scenario
entry points. The code uses DOS headers, `far`, interrupts, and compiler-specific
assembly. No DOS compilation, execution, or successful runtime verification is
claimed. Scenario outcomes and busy-loop timing remain unverified.
