# from distutils.core import setup, Extension
from setuptools import setup, Extension

module1 = Extension('walton_module', sources = ['walton_test.c'])

setup(name="walton_package", version="1.0", description="This is a test package.", ext_modules = [module1])
