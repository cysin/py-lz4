#!/usr/bin/env python

from distutils.core import setup, Extension

setup(name='lz5 Module',
      version='0.1',
      description='lz4',
      author='',
      author_email='blueflycn@gmail.com',
      url='',
      packages=['lz4'],
      ext_modules=[Extension("lz4/_lz4",
                              ["src/py_lz4.c",
                               "src/lz4.c",
                               "src/lz4hc.c"
                               ],
                              libraries=["m"])]
	)
