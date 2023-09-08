
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>

#include <unistd.h>

int verbose = 0;
const char *cl = NULL;

int class_argc = 1;
char **class_argv;

JavaVM* jvm;

JNIEnv* create_vm(int argc, char **argv) {
	JNIEnv* env;
	JavaVMInitArgs args;
	JavaVMOption options[argc + 1];
	
	/* There is a new JNI_VERSION_1_4, but it doesn't add anything for the purposes of our example. */
	args.version = JNI_VERSION_1_2;
	args.nOptions = 0;

	// options[0].optionString = "-Djava.class.path=/home/bbaker/workspace/nijava/jdaqmx-java/bin";
	// options[1].optionString = "-Djava.library.path=/home/bbaker/workspace/nijava/jdaqmx-c/build/rhel/daqmxbase";
	int idx = 0;

	for( int i=0; i < argc; i++) {
	    char *v = argv[i];
	    if( strcmp( v, "-v" ) == 0 ) {
		verbose++;
	    } else if( *v == '-' ) {
	        options[idx++].optionString = v;
		args.nOptions++;
	    } else {
		cl = v;
		class_argc = i + 1;
		break;
	    }
	}

	args.options = options;
	args.ignoreUnrecognized = JNI_FALSE;

	if( verbose ) {
	    fprintf( stdout, "tot options: %d\n", args.nOptions );
	    for( int i = 0; i < args.nOptions ; i++ ) {
		fprintf( stdout, " vm arg: %s\n", options[i].optionString );
	    }
	}

	JNI_CreateJavaVM(&jvm, (void **)&env, &args);
	return env;
}

void invoke_class(JNIEnv* env, const char *cl, int argc, char **argv ) {
	jclass helloWorldClass;
	jmethodID mainMethod;
	jobjectArray applicationArgs = NULL;

	// const char *cl = "ni/user/T1"
	helloWorldClass = env->FindClass( cl );
	if( helloWorldClass == NULL ) {
		fprintf( stderr, "CLASS NOT FOUND: %s\n", cl );
		return;
	}

	mainMethod = env->GetStaticMethodID( helloWorldClass, "main", "([Ljava/lang/String;)V");

	if( argc > 0 ) {
	    applicationArgs = env->NewObjectArray( argc, env->FindClass( "java/lang/String"), NULL);
	}

	for (int i = 0; i < argc; i++ ) {
	    if( verbose ) {
		printf(" method argv=%s\n", argv[i] );
	    }
	    jstring applicationArg0 = env->NewStringUTF( argv[i] );
	    env->SetObjectArrayElement( applicationArgs, i, applicationArg0);
	}

	env->CallStaticVoidMethod( helloWorldClass, mainMethod, applicationArgs);
	printf( "invoked\n" );

	if( env->ExceptionOccurred() ) {
         /* We don't do much with the exception, except that
            we print a debug message for it, clear it, and 
            throw a new exception. */
         jclass newExcCls;
         env->ExceptionDescribe();
         env->ExceptionClear();
     
	 fprintf( stderr, "exception described!\n" );
        }

}


int main(int argc, char **argv) {

	if( argc < 2 ) {
		printf( "Usage: launch <class>\n" );
		exit(0);
	}

	JNIEnv* env = create_vm( argc - 1, argv + 1 );

	if( verbose ) {
		fprintf( stdout, "class: %s\n", cl );
	}

	fprintf( stdout, "class_argc= %d\n", class_argc);
	int new_argc = argc - class_argc - 1;
	fprintf( stdout, "new_argc= %d\n", new_argc);
	class_argv = argv + class_argc + 1;

	invoke_class( env, cl, new_argc, class_argv );  // program is arg0, class=arg1

	for( ;; ) {
		printf("<ting>\n");
		sleep(5);
	}
}


