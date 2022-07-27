# from distutils.core import setup, Extension
from setuptools import setup, Extension

moduleWalton = Extension('walton_module', sources = ['walton_module.cpp'])
moduleSteve = Extension('steve_module', sources = ['steve_module.cpp'])

setup(name="walton_package", version="1.0.0", description="This is a test package.", ext_modules = [moduleWalton, moduleSteve])
