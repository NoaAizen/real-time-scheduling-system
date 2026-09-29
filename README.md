# Real Time Scheduling System

An academic Real Time Systems project based on the SMARTS77 framework used at
the Jerusalem College of Technology, organized as one unified scheduling and
synchronization project.

## Attribution and scope

SMARTS77, including the legacy DOS framework, timer interrupt foundation,
Events, context-switch foundation, and Round Robin scheduler, was provided by
A. Teitelbaum, based on an idea by H. G. Mendelbaum. Round Robin is framework
code, not a project implementation.

The project additions integrate periodic task scheduling, EDF, RMS, deadline
handling, task reactivation, mutex synchronization, priority-based mutex
waiting, priority-inversion experiments, direct priority inheritance, and
per-task context-switch control.

## Scheduling

- **Round Robin:** provided SMARTS77 cyclic selection of READY tasks.
- **EDF:** selects the READY task with the earliest remaining deadline.
- **RMS:** derives base priority from period; a shorter period has higher
  priority. It selects the READY task with the highest current priority.

Periodic tasks track their remaining deadline and requested cycle count.
Completed cycles are reactivated at the next period boundary, or retired after
their final cycle.

## Synchronization

`Mutex` provides mutual exclusion and temporarily suppresses context switches
while updating its internal state. Blocked waiters are selected by current
priority. The included experiments explore priority inversion with one and two
resources.

Priority inheritance is optional and direct: a mutex owner can inherit the
priority of a blocked higher-priority task, then returns to base priority on
release. Recursive or transitive priority inheritance is not implemented.

Events provide the task ordering used by the synchronization experiments.

## Project structure

```text
include/        Clean SMARTS77 interface
src/            Clean scheduler, runtime, interrupt, Event, and mutex sources
tests/          Manual scheduling and synchronization scenarios
```

## Scenarios

The `tests/` directory contains selectable scheduling configurations, a mutex
experiment, and selectable one- and two-resource priority-inversion
experiments. See [`tests/README.md`](tests/README.md) for configuration and
build notes.

## Legacy environment

This is legacy DOS/Turbo C++-style code using DOS headers, interrupts, `far`,
and compiler-specific assembly. The scenarios were not re-executed in the
original 16-bit DOS environment during repository cleanup. Scenario outcomes
remain unverified; this project is an academic scheduler exercise, not a
production RTOS.
