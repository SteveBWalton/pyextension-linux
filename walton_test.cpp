#define PY_SSIZE_T_CLEAN
#include <Python.h>


#define STEVE 2


/// Defines function calculate() that will be exported to Python as walton_test.calculate().
static PyObject* waltonTestCalculate
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
static PyMethodDef waltonTestMethods[] =
{
    {"calculate", waltonTestCalculate, METH_VARARGS, "Description of calculate()."},
    {NULL, NULL, 0, NULL}
};



/// Defintion of this module.
static struct PyModuleDef waltonTestDefinition =
{
    PyModuleDef_HEAD_INIT,
    "walton_test",      // Name of the module.
    "Description of the module",    // Module documentation, may be NULL.
    -1,                             // Size of per-interpreter state of the module, of -1 if the module keeps state in global variables.
    waltonTestMethods
};



/// Module initation.
PyMODINIT_FUNC PyInit_walton_test(void)
{
    Py_Initialize();

    // Create the module.
    PyObject* module = PyModule_Create(&waltonTestDefinition);

    // Add a constants to the module.
    PyModule_AddIntConstant(module, "TEST", 1);
    PyModule_AddIntMacro(module, STEVE);

    // Return success.
    return module;
}
