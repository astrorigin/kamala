#!bin/sh
# fetch all strings in files that are not source code
$EXTRACTRC `find . -name \*.rc -o -name \*.ui -o -name \*.kcfg` >> rc.cpp
# fetch all strings in source code files
$XGETTEXT `find . -name \*.c -o -name \*.cpp -o -name \*.h -o -name \*.hpp` -o $podir/kamala.pot
