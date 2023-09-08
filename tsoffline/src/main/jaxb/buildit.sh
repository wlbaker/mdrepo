#!/bin/sh
JDK_HOME=/usr/java/latest
${JDK_HOME}/bin/xjc -Xinject-code -extension -b bindings.xml -p idea.ts -d ../java tsoffline-defs.xsd
rc=$?
if [[ $rc != 0 ]] ; then
    echo "error compiling: ${rc}"
fi

