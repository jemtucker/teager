#!/usr/bin/env python3

from distutils.core import setup, Extension, Command

teager = Extension('teager',
                    include_dirs=[
                        'inc',
                    ],
                    libraries=[
                        'clang',
                    ],
                    extra_compile_args=[
                        '-std=c++14',
                    ],
                    sources=[
                        'src/main.cpp',
                        'src/Parser.cpp',
                    ])

class TestCommand(Command):
    """
    Execute unit tests
    """
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        import os
        import sys
        import unittest

        # get setup.py directory
        setup_file = sys.modules['__main__'].__file__
        setup_dir = os.path.abspath(os.path.dirname(setup_file))

        # use the default shared TestLoader instance
        test_loader = unittest.defaultTestLoader

        # use the basic test runner that outputs to sys.stderr
        test_runner = unittest.TextTestRunner()

        # automatically discover all tests
        test_suite = test_loader.discover(setup_dir)

        # run the test suite
        test_runner.run(test_suite)

setup(
    name='teager',
    version='0.1',
    description='AST parsing implemented with libclang',
    ext_modules=[
        teager,
    ],
    cmdclass={ 
        'test': TestCommand,
    })
