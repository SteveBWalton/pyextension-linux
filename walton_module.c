#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#define STEVE 20


/// Defines function calculate() that will be exported to Python as walton_test.calculate().
static PyObject* waltonModuleCalculate
(
    PyObject* self,
    PyObject* args
)
{
    // Fetch the 2 double parameters.
    double argOne;
    double argTwo;
    if (!PyArg_ParseTuple(args, "dd", &argOne, &argTwo))
    {
        // Parameters are wrong.
        return NULL;
    }

    // Return success.
    return PyFloat_FromDouble(argOne * argTwo);
    // int returnCode = 1;
    // return PyLong_FromLong(returnCode);
}



/// Register of functions within this module.
static PyMethodDef waltonModuleMethods[] =
{
    {"calculate", waltonModuleCalculate, METH_VARARGS, "Description of calculate()."},
    {NULL, NULL, 0, NULL}
};



/// Defintion of this module.
static struct PyModuleDef waltonModuleDefinition =
{
    PyModuleDef_HEAD_INIT,
    "walton_module",                // Name of the module.
    "Description of the module",    // Module documentation, may be NULL.
    -1,                             // Size of per-interpreter state of the module, of -1 if the module keeps state in global variables.
    waltonModuleMethods
};



// This inlines the code for the Walton object.
#include "walton_object.c"



/// Module initation.
PyMODINIT_FUNC PyInit_walton_module(void)
{
    Py_Initialize();

    // Initialises the WaltonType.
    if (PyType_Ready(&waltonType) < 0)
    {
        return NULL;
    }

    // Create the module.
    PyObject* module = PyModule_Create(&waltonModuleDefinition);
    if (module == NULL)
    {
        return NULL;
    }

    // Add a constants to the module.
    PyModule_AddIntConstant(module, "TEST", 1);
    PyModule_AddIntMacro(module, STEVE);

    // Add the object to the module.
    Py_INCREF(&waltonType);
    if (PyModule_AddObject(module, "Walton", (PyObject*)&waltonType) < 0)
    {
        Py_DECREF(&waltonType);
        Py_DECREF(module);
        return NULL;
    }

    // Return success.
    return module;
}
