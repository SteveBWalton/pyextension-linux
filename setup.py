# from distutils.core import setup, Extension
from setuptools import setup, Extension

module1 = Extension('walton_test', sources = ['walton_test.cpp'])

setup(name="walton_test", version="1.0", description="This is a test package.", ext_modules = [module1])
