
xjc -Xinject-code -extension -b bindings.xml -p idea.ts -d ..\java tsoffline-defs.xsd 
rem javac -d bin -sourcepath gen idea/ts/setup/*.java 
rem jar -C bin -cf ts-setup.jar idea
