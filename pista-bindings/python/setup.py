import setuptools.command.install
import shutil
from distutils.sysconfig import get_python_lib


class CompiledLibInstall(setuptools.command.install.install):
    """
    Specialized install to install to python libs
    """

    def run(self):
        """
        Run method called by setup
        :return:
        """
        # Get filenames from CMake variable
        filenames = 'C:/msys64/opt/git/pista/pista-bindings/python/swig_example.py;C:/msys64/opt/git/pista/pista-bindings/python/_swig_example.so'.split(';')

        # Directory to install to
        install_dir = get_python_lib()

        # Install files
        [shutil.copy(filename, install_dir) for filename in filenames]


if __name__ == '__main__':
    pypistax_module = Extension('_pypistax', 
                           extra_compile_args=['-g', '-O0'],
                           extra_link_args=['-g'],
                           sources=[bindings_dir+'/pistax_wrap.cxx'],
                           libraries=libraries,
                           library_dirs=library_dirs,
                           include_dirs=include_dirs,
                           extra_objects=extra_objects
                           )

    setuptools.setup (
        name = 'pypistax',
        version = '0.2.6',
        author      = "William L Baker",
        author_email = "william.l.baker2.civ@mail.mil",
        description = """Bindings for Pista interface""",
        license = "LGPL",
        ext_modules = [pypistax_module],
        py_modules = ["pypistax"],
        packages=['pypistax'],
        cmdclass={'install': CompiledLibInstall}
    )
