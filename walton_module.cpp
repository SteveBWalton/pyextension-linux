#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#define STEVE 20


/// Defines function calculate() that will be exported to Python as walton_module.calculate().
static PyObject* waltonModuleCalculate
(
    PyObject* self,
    PyObject* args      // Specifies the Python arguments to the calculate() function.
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
}



/// Register of functions within this module.
static PyMethodDef waltonModuleMethods[] =
{
    {"calculate", waltonModuleCalculate, METH_VARARGS, "Description of the calculate() function."},
    {NULL, NULL, 0, NULL}
};



/// Defintion of this module.
static struct PyModuleDef waltonModuleDefinition =
{
    PyModuleDef_HEAD_INIT,
    // Name of the module.
    "walton_module",
    // Module documentation, may be NULL.
    "Description of the walton_module module.",
    // Size of per-interpreter state of the module, of -1 if the module keeps state in global variables.
    -1,
    waltonModuleMethods
};



// This inlines the code for the Walton object.
#include "walton_object.cpp"



/// Module initation.
/// Function name comes from the module name in waltonModuleDefinition.
PyMODINIT_FUNC PyInit_walton_module(void)
{
    Py_Initialize();

    // Initialises the Walton object.
    if (PyType_Ready(&waltonObjectDefinition) < 0)
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

    // Add the Walton object to the module.
    Py_INCREF(&waltonObjectDefinition);
    if (PyModule_AddObject(module, "Walton", (PyObject*)&waltonObjectDefinition) < 0)
    {
        Py_DECREF(&waltonObjectDefinition);
        Py_DECREF(module);
        return NULL;
    }

    // Return success.
    return module;
}
