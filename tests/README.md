# Manual scenarios: framework reference

This framework-only reference contains no scenario entry point. Feature
branches add the relevant scenarios. One-shot tasks use
`SMARTS.declareTask(taskFunction, taskName)`.

Use a compatible 16-bit DOS/Turbo C++ toolchain, with `include/` on the header
search path. Link the sources in `src/` with exactly one selected scenario
from `tests/`; each scenario has its own `main()`. Do not combine scenario
entry points. The code uses DOS headers, `far`, interrupts, and compiler-specific
assembly. No DOS compilation, execution, or successful runtime verification is
claimed. Scenario outcomes and busy-loop timing remain unverified.
