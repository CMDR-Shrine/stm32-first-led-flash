# Verified Solution

`00_c_without_a_runtime/` contains the foundation exercise answer. `final/`
contains the 288-byte blinker that was built, programmed, and verified before
the learner course was created. Neither is imported or copied by the normal
build.

Use it only after attempting Lesson 05. Compare deliberately:

```sh
diff -u main.c solutions/final/main.c
```

Do not treat textual differences as failures. Explain whether both versions
perform the same register operations and why.
