#!/bin/sh
JDK_HOME=/usr/java/default
WORKSPDIR=`pwd`
DEST_SRCDIR=./gen
echo "Workspace: $WORKSPDIR"
# rm -rf ${DEST_SRCDIR}
echo "Compiling xsd defs: `pwd` to ${DEST_SRCDIR}"
# my extension: -Xgetset
# ${JDK_HOME}/bin/xjc -cp ../../bin -Xinject-code -extension -b bindings.xml -p idea.schema.rp -d ${DEST_SRCDIR} repository-defs.xsd 
${JDK_HOME}/bin/xjc -Xinject-code -extension -b bindings.xml -p idea.schema.rp -d ${DEST_SRCDIR} repository-defs.xsd 
rc=$?
if [[ $rc != 0 ]] ; then
    echo "error code: ${rc}"
fi

# pushd ${DEST_SRCDIR}/src
# echo "Compiling java defs: `pwd` to ${DEST_SRCDIR}/bin"
# ${JDK_HOME}/bin/javac -d ${DEST_SRCDIR}/bin idea/rp/*.java 
# cd ${DEST_SRCDIR}/bin
# echo "Compiling jar: `pwd` to ${WORKSPDIR}/../lib/idea-rp.jar"
# ${JDK_HOME}/bin/jar -cf $WORKSPDIR/../lib/idea-rp.jar idea
# popd
