# Part 1 and Part 2 scheduling scenarios

These programs extract the three configurations already present in
`original-part1/APP77.CPP`. They use the same A, B, and C workloads and retain
the original Part 1 runtime behavior except for the lifecycle correction
documented below and the RMS support described here. These scenarios have not
been compiled or executed in the original DOS toolchain.

## Attribution and scope

SMARTS77 is the course framework credited to A. Teitelbaum, based on an idea
by H. G. Mendelbaum, at the Jerusalem College of Technology. Round Robin is
provided framework code. EDF, periodic-task bookkeeping, deadline handling,
and task reactivation are the Part 1 work built on that framework. RMS support
and mutex, priority inversion, and priority inheritance support are Part 2
integrations based on the saved Part 2 source; exact authorship of the original
additions is not established by these files.

The extracted workload bodies are preserved from the supplied application;
this organization does not establish separate authorship of those bodies.
The six files in `original-part1/` and the saved Part 2 files in
`original-part2/` are unchanged sources of truth.

## Scenario programs

| Program | Periods A / B / C (timer ticks) | Cycles per task | Expectation recorded in the original comments |
| --- | --- | --- | --- |
| `short_deadlines_test.cpp` | 100 / 150 / 200 | 3 | Both Round Robin and EDF miss a deadline. |
| `edf_vs_rr_test.cpp` | 3000 / 9000 / 12000 | 3 | EDF completes; Round Robin fails. |
| `balanced_test.cpp` | 7000 / 5000 / 9000 | 3 | Both algorithms complete successfully. |
| `rms_equal_periods_test.cpp` | 1000 / 1000 / 1000 | 3 | Part 2 comment: RMS does not work. |
| `rms_harmonic_periods_test.cpp` | 5000 / 10000 / 20000 | 5 | Part 2 comment: RMS works. |
| `mutex_rms_test.cpp` | 400 / 401 / 402 | 3 | Original mutex experiment; no verified result. |
| `priority_inversion_test.cpp` | C / B / A: 400 / 401 / 402 | 1 | Original experiment; no verified result. |
| `two_resource_priority_inversion_test.cpp` | H / M / L / X / N / Z: 400--405 | 1 | Original experiment; no verified result. |

These are intended manual experiments, not automated tests with established
pass/fail results. The comments' expectations are unverified, and the preserved
busy-loop timing depends on the compiler, optimization settings, and execution
environment. They have not been compiled or executed in the original DOS
toolchain. The Part 2 comments additionally state that RMS misses the short-
deadline scenario, completes the EDF-versus-Round-Robin scenario, and completes
the balanced scenario; those are also unverified original expectations.

## Select a scheduling algorithm

Each scenario defaults to:

```cpp
#define PART1_SCHEDULER roundRobin
```

To run EDF or RMS, change that definition in the chosen scenario to:

```cpp
#define PART1_SCHEDULER EDF
```

or:

```cpp
#define PART1_SCHEDULER RMS
```

Rebuild the scenario after changing the selection. The `#ifndef` also permits
a compiler/project preprocessor definition of `PART1_SCHEDULER=EDF` or
`PART1_SCHEDULER=RMS` without editing the file. Use the syntax supported by the
course compiler.

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
src/mutex.cpp
tests/task_workloads.cpp
tests/<one scenario file>.cpp
```

Select exactly one scenario file. Each defines its own `main()`.
The two priority-inversion scenarios are self-contained and do not use
`tests/task_workloads.cpp`.
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
imported except Part 2 RMS scheduling, per-task context-switch state, mutex
synchronization, and direct priority inheritance.

## Part 2 synchronization scenarios

`priority_inversion_test.cpp` uses Events to ensure the low-priority task owns
the mutex before the medium- and high-priority tasks run. The high-priority task
then blocks on that mutex. `two_resource_priority_inversion_test.cpp` composes
two such resource interactions using Events.

Both scenarios default to the original no-inheritance mode. Define
`USE_INHERITANCE=1` in the project/compiler settings to use the original direct
priority-inheritance mode; define it as `0` to disable inheritance. These are
manual DOS experiments with unverified original expectations, not automated
passing tests. The implementation is not recursive or transitive priority
inheritance.

## Record observations when the environment is available

Run each scenario separately with Round Robin, EDF, and RMS where applicable.
Record the compiler and runtime configuration, selected policy, task
start/finish output, and deadline messages. Check whether each task executes
its configured cycle count and whether normal termination occurs. Report the
observed behavior, including the known baseline issues, rather than treating the
original comments as passing results.
