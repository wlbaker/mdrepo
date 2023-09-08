JEP is required for python integration.  Building JEP can be an issue.  For best results,
download Visual Studio 2015 or 2017 and add the following key to the rgistry:

[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\DevDiv\VCForPython]

[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\DevDiv\VCForPython\14.1]
"installdir"="c:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\BuildTools\\VC\\Auxiliary\\Build"

Then follow the standard build instructions from github.

----------

Environment necessary for JEP:

(1) PATH=c:\programdata\Anaconda3
(2) PYTHONPATH=c:\ProgramData\Anaconda3\lib
(3) VC14.0 runtime

-----------

Console development...called a REPL loop:

// Consider https://github.com/beryx/text-io
// https://github.com/jline/jline2/wiki


