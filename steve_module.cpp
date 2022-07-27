#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#define STEVE 20


/// Defines function calculate() that will be exported to Python as steve_module.calculate().
static PyObject* steveModuleCalculate
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
    return PyFloat_FromDouble(argOne + argTwo);
}



/// Register of functions within this module.
static PyMethodDef steveModuleMethods[] =
{
    {"calculate", steveModuleCalculate, METH_VARARGS, "Description of the calculate() function."},
    {NULL, NULL, 0, NULL}
};



/// Defintion of this module.
static struct PyModuleDef steveModuleDefinition =
{
    PyModuleDef_HEAD_INIT,
    // Name of the module.
    "steve_module",
    // Module documentation, may be NULL.
    "Description of the steve_module module.",
    // Size of per-interpreter state of the module, of -1 if the module keeps state in global variables.
    -1,
    steveModuleMethods
};



/// Module initation.
/// Function name comes from the module name in steveModuleDefinition.
PyMODINIT_FUNC PyInit_steve_module(void)
{
    Py_Initialize();

    // Create the module.
    PyObject* module = PyModule_Create(&steveModuleDefinition);
    if (module == NULL)
    {
        return NULL;
    }

    // Add a constants to the module.
    PyModule_AddIntConstant(module, "TEST", 1);
    PyModule_AddIntMacro(module, STEVE);

    // Return success.
    return module;
}
