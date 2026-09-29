# Manual scenarios: EDF

Build `scheduling_test.cpp`. Select `SCHEDULING_SCENARIO` and
`SCHEDULING_POLICY` in the source or compiler settings and rebuild.
Default: `SCENARIO_EDF_VS_RR` with `EDF`.
Available policies: `roundRobin`, `EDF`.

| Scenario | Periods A / B / C (timer ticks) | Cycles per task |
| --- | --- | --- |
| `SCENARIO_SHORT_DEADLINES` | 100 / 150 / 200 | 3 |
| `SCENARIO_EDF_VS_RR` | 3000 / 9000 / 12000 | 3 |
| `SCENARIO_BALANCED` | 7000 / 5000 / 9000 | 3 |


Use a compatible 16-bit DOS/Turbo C++ toolchain, with `include/` on the header
search path. Link the sources in `src/` with exactly one selected scenario
from `tests/`; each scenario has its own `main()`. Do not combine scenario
entry points. The code uses DOS headers, `far`, interrupts, and compiler-specific
assembly. No DOS compilation, execution, or successful runtime verification is
claimed. Scenario outcomes and busy-loop timing remain unverified.
