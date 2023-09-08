xjc -Xinject-code -extension -b bindings.xml -p idea.schema.rp -d ..\java repository-defs.xsd 
rem javac -sourcepath gen -source 1.6 -target 1.6 -d gen-bin idea/rp/*.java 
rem jar -cf c:/users/william.l.baker2/git/icuvisopengl/lib/repository-defs.jar idea -C gen-bin
