# Legacy outputs (course version, June 2026)

These are saved console outputs from the course version of the project, which
was built and run in Borland/Turbo C (files dated 8 June 2026 in the archived
project folder). They come from the course version, not from the cleaned-up
code in this repository. Task names and print formats differ from the
scenarios in `tests/`. The cleaned-up code has not been re-run.

| File | What it shows |
| --- | --- |
| `TEST.TXT` | One-resource priority inversion with a high (C), medium (B) and low (A) priority task. A takes the mutex and wakes C and B. C blocks on the mutex. A finishes its critical section and releases, C acquires the mutex and finishes, and only then does B run. |
| `TEST_B.TXT` | Two independent inversions (mutex1 with tasks 1 and 2, mutex2 with tasks 3 and 4, plus intermediate tasks M1 and M2). For each mutex, the owner finishes its critical section, the high-priority task acquires the mutex, and the intermediate task runs after it. |
| `TEST_CH.TXT` | Nested chain test: five tasks and four mutexes, where a task that holds one mutex acquires another. The output stops mid-run (the last line is cut off), so it does not show the chain completing. |
| `TEST_CHA.TXT` | A variant of the nested chain test. It also stops mid-run; the last line is T4 trying to acquire mutex3. |

The nested-mutex tests (`TEST_CH.TXT`, `TEST_CHA.TXT`) cover a case that is
not part of the cleaned-up code. The cleaned-up mutex implements direct
priority inheritance only, not recursive or transitive inheritance.
