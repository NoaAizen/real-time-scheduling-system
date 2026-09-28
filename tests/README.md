# Part 1 scheduling scenarios

These programs extract the three configurations already present in
`original-part1/APP77.CPP`. They use the same A, B, and C workloads and retain
the original Part 1 runtime behavior except for the lifecycle correction
documented below. These scenarios have not been compiled or executed in the
original DOS toolchain.

## Attribution and scope

SMARTS77 is the course framework credited to A. Teitelbaum, based on an idea
by H. G. Mendelbaum, at the Jerusalem College of Technology. Round Robin is
provided framework code. EDF, periodic-task bookkeeping, deadline handling,
and task reactivation are the Part 1 work built on that framework.

The extracted workload bodies are preserved from the supplied application;
this organization does not establish separate authorship of those bodies.
The six files in `original-part1/` are the unchanged source of truth.

## Scenario programs

| Program | Periods A / B / C (timer ticks) | Cycles per task | Expectation recorded in the original comments |
| --- | --- | --- | --- |
| `short_deadlines_test.cpp` | 100 / 150 / 200 | 3 | Both Round Robin and EDF miss a deadline. |
| `edf_vs_rr_test.cpp` | 3000 / 9000 / 12000 | 3 | EDF completes; Round Robin fails. |
| `balanced_test.cpp` | 7000 / 5000 / 9000 | 3 | Both algorithms complete successfully. |

These are intended manual experiments, not automated tests with established
pass/fail results. The comments' expectations are unverified, and the preserved
busy-loop timing depends on the compiler, optimization settings, and execution
environment. They have not been compiled or executed in the original DOS
toolchain.

## Select a scheduling algorithm

Each scenario defaults to:

```cpp
#define PART1_SCHEDULER roundRobin
```

To run EDF, change that definition in the chosen scenario to:

```cpp
#define PART1_SCHEDULER EDF
```

Rebuild the scenario after changing the selection. The `#ifndef` also permits
a compiler/project preprocessor definition of `PART1_SCHEDULER=EDF` without
editing the file. Use the syntax supported by the course compiler.

## Build one scenario at a time

Use the compatible 16-bit DOS C++ compiler and runtime from the course.
The source depends on DOS headers, `far`, `interrupt`, inline assembly, and
compiler-specific register access. The exact compiler version, memory model,
and project options still need to be recovered; no verified build command is
provided here.

Set the header search path to `include/` and `tests/`. Each executable uses:

```text
src/smarts77.cpp
src/scheduler.cpp
src/interrupts.cpp
src/events.cpp
tests/task_workloads.cpp
tests/<one scenario file>.cpp
```

Select exactly one of the three scenario files. Each defines its own `main()`.
Use an explicit source list: exclude `original-part1/` and the existing
version-suffixed working files. Also exclude `src/EVENT77.CPP`, which duplicates
the event implementation in `src/events.cpp`. Do not compile all source files
through a wildcard.

## Part 1 lifecycle correction

- While organizing the original Part 1 project, its periodic-task lifecycle
  bookkeeping was corrected. When a periodic task finishes its current
  execution, `taskEnd()` marks the cycle complete and leaves the task in the
  `NOT_ACTIVE` state until its period boundary. `activeTasks` is not decremented
  when that execution finishes. At the period boundary, `handleTimers()` either
  reactivates the task for another cycle or retires it after its final requested
  cycle.

## Deliberately preserved behavior

- The disabled deferred-switch branch in the original interrupt handler remains
  disabled. Its commented statements were omitted from the clean copy, without
  enabling a replacement.
- Deadline failure still prints a message, waits in `getch()`, and calls
  `exit(1)` from timer processing. It does not use the normal return path that
  restores interrupt vectors.
- Task reactivation, the global context-switch flag, scheduler selection rules,
  workload output, and delay loops retain their Part 1 implementations.

These issues remain outside the lifecycle correction made during project
organization.

## Differences introduced by extraction

The saved original application comments out all task declarations. Each new
scenario enables only its corresponding existing A/B/C configuration. This
intentional activation is the executable behavior difference from the saved
application. Round Robin remains the default; selecting EDF explicitly chooses
the other existing Part 1 policy.

The runtime and workloads retain their active code. Header guards and workload
declarations support the new file boundaries. No later-stage behavior is
imported.

## Record observations when the environment is available

Run each scenario separately with Round Robin and EDF. Record the compiler and
runtime configuration, selected policy, task start/finish output, and deadline
messages. Check whether each task executes three cycles and whether normal
termination occurs. Report the observed behavior, including the known baseline
issues, rather than treating the original comments as passing results.
