# pyextension_linux
An example python extension on linux.

The intension was to create a counter part pyextension_windows project.  However, this all seems to work the same under Windows.

## Build

```
python setup.py build
```

This may require the python3-devel package.

## Install

```
sudo python setup.py install --record files.txt
```

The --record files.txt is not actually required but shows the files installed in case the uninstall does not work.

## Uninstall

```
sudo pip uninstall walton_module
```

You can install subsequent builds without uninstalling the previous version.
