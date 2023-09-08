#!/usr/bin/env python

# 
# Notes on static linking of libraries in python modules:
#
#
# https://stackoverflow.com/questions/4597228/how-to-statically-link-a-library-when-compiling-a-python-module-extension?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
#

import sys
import os.path
from distutils.core import setup, Extension

bindings_dir=os.path.dirname( sys.argv[0] )
if len(bindings_dir) == 0:
	bindings_dir="."

build_root=os.getcwd( )

# static_libraries = ['pistacxx', 'pista', 'websockets', 'protobuf-c']
static_libraries = ['pistacxx', 'pista', 'protobuf-c', 'expat' ]
static_lib_dirs=[ build_root + '/.libs', build_root + '/bindings/cxx/.libs', '../../.libs', '../cxx/.libs' ]
# , '../../../deps/libwebsockets/build/lib' ]

libraries = [ 'yajl' ]

# for now...but hackish
if sys.platform != 'win32':
    #ifhave ZOLL          
    libraries.extend( ['websockets', 'ssl'] )
    #ifhave ZOLL_DISCOVER 
    libraries.extend( ['avahi-common', 'avahi-client'] )


library_dirs = [ '/usr/lib64' ]
include_dirs= [ bindings_dir+'/../../include', bindings_dir+'/../cxx', 'include', '../../include' ]


extra_objects = []


if sys.platform == 'win32':
    # libraries.extend( [ "-Wl,-Bstatic"] )
    libraries.extend(static_libraries)
    library_dirs.extend(static_lib_dirs)
    # libraries.extend( [ "-Wl,-Bdynamic"] )
else: # POSIX
    for l in static_libraries:
        def doWork():
            for m in static_lib_dirs:
                fname = '{}/lib{}.a'.format(m,l)
                print(" checking fname=" + fname )
                if os.path.isfile(fname):
                    extra_objects.append( fname ) 
                    print("         appending...static")
                    return
            print("         appending...dynamic")
            libraries.append( l ) 
        doWork();

print( "platform =" + sys.platform )
print( "libraries=" + str(libraries) )
print( "library_dirs =" + str(library_dirs) )
print( "include_dirs =" + str(include_dirs) )
print( "extra_objects=" + str(extra_objects) )
print( "src_dir=" + str(bindings_dir) )
print( "pwd=" + str(os.getcwd() ) )

#
# Issue here for out of tree builds: need includes from both
# source tree and build tree
#

pypistax_module = Extension('_pypistax', 
                           extra_compile_args=['-g', '-O0'],
                           extra_link_args=['-g'],
                           sources=[bindings_dir+'/pistax_wrap.cxx'],
                           libraries=libraries,
                           library_dirs=library_dirs,
                           include_dirs=include_dirs,
                           extra_objects=extra_objects
                           )

setup (name = 'pypistax',
       version = '0.2.6',
       author      = "William L Baker",
       author_email = "william.l.baker2.civ@mail.mil",
       description = """Bindings for Pista interface""",
       license = "LGPL",
       ext_modules = [pypistax_module],
       py_modules = ["pypistax"],
       )

