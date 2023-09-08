apply plugin: 'application'
apply plugin: 'java'

repositories {
    mavenCentral()
}

//
// dependencies {
//    compile 'org.lwjgl.lwjgl:lwjgl:2.8.4'
// }
//

platforms = ['windows', 'linux', 'osx']
platforms.each { platform ->
    task "${platform}Natives" {
        outputDir = "$buildDir/natives/$platform"
        inputs.files(configurations.compile)
        outputs.dir(outputDir)
        doLast {
            copy {
                def artifacts = configurations.compile.resolvedConfiguration.resolvedArtifacts
                    .findAll { it.classifier == "natives-$platform" }
                artifacts.each { 
                    from zipTree(it.file)
                }            
                into outputDir
            }
        }
    }
}

task natives {
    description "Copies native libraries to an appropriate directory."
    dependsOn platforms.collect { "${it}Natives" }.findAll { tasks[it] }
}

run { 
	systemProperties = [ 'java.library.path' : './build/natives/linux' ]
	it.dependsOn natives
}

