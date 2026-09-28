# Real Time Systems Project Instructions

## Project Goal

Turn this academic Real Time Systems project into a clean and professional GitHub portfolio project for Junior Embedded, Firmware, and Software positions.

The project is based on the SMARTS77 framework used at the Jerusalem College of Technology.

## Important Rules

1. Preserve the original project logic.

2. Do not rewrite working algorithms unless explicitly requested.

3. Do not delete code before checking whether it represents an important stage or test from the original project.

4. Do not invent features, experience, results, or functionality.

5. Clearly distinguish between the original SMARTS77 framework and the student's own additions.

6. Do not claim that the student created the original SMARTS77 framework.

7. Keep the project focused on the Real Time concepts actually implemented in the supplied code.

8. Preserve and document relevant implementations and experiments involving:
   Round Robin scheduling
   EDF scheduling
   RMS scheduling
   Periodic tasks
   Deadline handling
   Timer interrupts
   Context switching
   Mutex synchronization
   Priority inversion
   Priority inheritance

9. Before changing a file, inspect it and explain what should be changed and why.

10. Make small changes. Do not refactor the entire project at once.

11. Keep backup copies of the original academic files until the cleaned version is complete.

## Code Comments

Use short professional English comments.

Comments should explain important Real Time concepts or non obvious behavior.

Do not add comments to every line.

Do not add comments that simply repeat the code.

Example:

// Select the READY task with the earliest deadline

## Code Style

Prefer simple and readable C++.

Use clear names for files, functions, and variables when renaming is safe.

Do not modernize legacy DOS specific code unless explicitly requested.

Remember that this is a legacy academic Real Time environment and may contain DOS specific headers, interrupts, and context switching code.

## GitHub Presentation

The final repository should make it easy for a recruiter to understand:

What the project does

Which Real Time concepts are demonstrated

Which parts were provided by the course framework

Which parts were implemented or extended by the student

How the scheduling algorithms work

How priority inversion and priority inheritance are demonstrated

## Attribution

Preserve the original SMARTS77 attribution found in the source files.

Do not remove author or course attribution from framework code.

The README must clearly explain that SMARTS77 was the base academic framework and separately describe the student's implementations and extensions.

## Workflow

Work on one component at a time.

Before editing:
1. Inspect the relevant files.
2. Explain the proposed changes.
3. Wait for approval if the change is significant.
4. Make the smallest necessary change.
5. Verify that existing behavior was not accidentally changed.

The final goal is a clean portfolio repository, not a complete rewrite of the original academic project.