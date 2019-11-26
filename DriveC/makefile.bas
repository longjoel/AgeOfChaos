' Step 1: grab all .c files
SHELL "find a: > tmp.txt"
args$ = ""

OPEN "tmp.txt" FOR INPUT AS #1
DO WHILE NOT EOF(1)
        LINE INPUT #1, line$
        IF MID$(line$, LEN(line$) - 1) = ".c" THEN
                args$ = args$ + line$ + " "
        END IF

LOOP
CLOSE #1
PRINT args$
SHELL "gcc -std=gnu99 " + args$ + " -o b:\game.exe"
SHELL "del TMP.txt"


SYSTEM

