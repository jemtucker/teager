from distutils.core import setup, Extension

module1 = Extension('jem',
                    include_dirs=['inc'],
                    libraries=['clang'],
                    extra_compile_args=['-std=c++14'],
                    sources = [
                        'src/main.cpp',
                        'src/Parser.cpp'])

setup (name = 'jem',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
