# Real Time Scheduling System

An academic real-time scheduling project built on the SMARTS77 framework by A. Teitelbaum, based on an idea by H. G. Mendelbaum at the Jerusalem College of Technology.

## Scope

SMARTS77 supplies the legacy DOS-oriented framework, timer interrupt support, context switching, Events, and Round Robin scheduling. The project work integrates periodic task scheduling, EDF, RMS, deadline handling, task reactivation, mutex synchronization, priority inversion experiments, and direct priority inheritance.

RMS derives a task's base priority from its period: a smaller period is a higher priority. The scheduler uses current priority so mutex priority inheritance can temporarily boost a mutex owner.

## Scheduling policies

- Round Robin is provided SMARTS77 code.
- EDF selects the READY task with the earliest remaining deadline.
- RMS selects the READY task with the highest current priority.

## Synchronization

The mutex implementation provides atomic Acquire and Release operations through context-switch control. Blocked waiters are selected by current priority. Priority inheritance is optional in the Part 2 scenarios. It is direct only; recursive or transitive priority inheritance is not implemented.

## Running scenarios

See `tests/README.md`. The sources require the original compatible 16-bit DOS C++ toolchain. The scenarios have not been compiled or executed in that toolchain, and original scenario comments are preserved as unverified expectations.

## Source preservation

`original-part1/` and `original-part2/` are unchanged academic source references. The clean files in `include/`, `src/`, and `tests/` organize the selected functionality without claiming authorship of SMARTS77.
