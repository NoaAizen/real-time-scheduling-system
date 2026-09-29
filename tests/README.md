# Manual scenarios

These are legacy DOS/Turbo C++-style manual scenarios, not automated tests.
They were not re-executed in the original 16-bit DOS environment during
repository cleanup; any expectations from the academic material remain
unverified.

| File | Purpose | Selection |
| --- | --- | --- |
| `scheduling_test.cpp` | Periodic scheduling with RR, EDF, or RMS | Set `SCHEDULING_SCENARIO` and `SCHEDULING_POLICY`. |
| `mutex_test.cpp` | RMS mutex serialization | No additional configuration. |
| `priority_inversion_test.cpp` | One- or two-resource inversion | Set `INVERSION_SCENARIO` and `USE_INHERITANCE`. |

`scheduling_test.cpp` retains the short-deadline, EDF-versus-RR, balanced,
equal-period RMS, and harmonic-period RMS configurations. Round Robin is
provided by SMARTS77; EDF and RMS are selectable policies.

Set `SCHEDULING_SCENARIO` to one of the following constants. Periods are in
timer ticks; the cycle count applies to each task.

| `SCHEDULING_SCENARIO` | Periods A / B / C | Cycles | Default policy |
| --- | --- | --- | --- |
| `SCENARIO_SHORT_DEADLINES` | 100 / 150 / 200 | 3 | `roundRobin` |
| `SCENARIO_EDF_VS_RR` | 3000 / 9000 / 12000 | 3 | `roundRobin` |
| `SCENARIO_BALANCED` | 7000 / 5000 / 9000 | 3 | `roundRobin` |
| `SCENARIO_RMS_EQUAL_PERIODS` | 1000 / 1000 / 1000 | 3 | `RMS` |
| `SCENARIO_RMS_HARMONIC_PERIODS` | 5000 / 10000 / 20000 | 5 | `RMS` |

The default scenario is `SCENARIO_BALANCED`. Override `SCHEDULING_POLICY` with
`roundRobin`, `EDF`, or `RMS` to compare policies. Set these definitions in the
source or compiler/project settings and rebuild after changing them.

`priority_inversion_test.cpp` defaults to the one-resource experiment. Set
`INVERSION_SCENARIO=TWO_RESOURCES` for the two-resource experiment. Set
`USE_INHERITANCE=1` to enable direct priority inheritance or `0` to disable it.
The implementation is not recursive or transitive priority inheritance.

Build one scenario at a time with a compatible 16-bit DOS compiler and an
explicit source list containing the clean files in `src/` plus the chosen test.
Set the header search path to `include/`. Each scenario defines its own
`main()`, so do not link the three scenario files together. The code depends
on DOS headers, `far`, interrupts, and compiler-specific assembly.
