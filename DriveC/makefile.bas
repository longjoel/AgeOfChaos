' Step 1: grab all .c files
SHELL "dir a:\*.c /b /s > tmp.txt"
args$ = ""

OPEN "tmp.txt" FOR INPUT AS #1
DO WHILE NOT EOF(1)
        LINE INPUT #1, line$
        args$ = args$ + "a:\" + line$ + " "
LOOP
CLOSE #1
PRINT args$
SHELL "gcc " + args$ + " -o b:\game.exe"
SHELL "del TMP.txt"


SYSTEM

