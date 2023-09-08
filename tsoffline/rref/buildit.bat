xjc -p idea.ts.setup -d c:/tmp/gen-ts-src tsoffline-defs.xsd 
cd c:\tmp\gen-ts-src
javac -d ../gen-ts-dest idea/ts/setup/*.java 
cd ..
cd gen-ts-dest
jar -cf c:/opt/workspace/caddo/tsOffline/lib/ts-setup.jar idea
cd c:\opt\workspace\caddo\tsOffline\ref
