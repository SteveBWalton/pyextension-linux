#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

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
    "walton_module",                // Name of the module.
    "Description of the module",    // Module documentation, may be NULL.
    -1,                             // Size of per-interpreter state of the module, of -1 if the module keeps state in global variables.
    waltonTestMethods
};

/******************* WaltonObject ************************************/

typedef struct
{
    PyObject_HEAD

    PyObject*   first;
    PyObject*   last;
    double      height;
    int         number;
} WaltonObject;



static void Walton_dealloc
(
    WaltonObject* self
)
{
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject* Walton_new
(
    PyTypeObject*   type,
    PyObject*       args,
    PyObject*       kwds
)
{
    WaltonObject* self;
    self = (WaltonObject*)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
        self->last = PyUnicode_FromString("");
        if (self->last == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
        self->height = 1.0;
        self->number = 0;
    }
    return (PyObject*) self;
}



static int Walton_init
(
    WaltonObject*   self,
    PyObject*       args,
    PyObject*       kwds
)
{
    static char *kwlist[] = {"first", "last", "height", "number", NULL};
    PyObject *first = NULL, *last = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOdi", kwlist, &first, &last, &self->height, &self->number))
    {
        return -1;
    }

    if (first)
    {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_XDECREF(tmp);
    }
    if (last)
    {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_XDECREF(tmp);
    }
    return 0;
}



static PyMemberDef Walton_members[] =
{
    {"first", T_OBJECT_EX, offsetof(WaltonObject, first), 0, "first name"},
    {"last", T_OBJECT_EX, offsetof(WaltonObject, last), 0, "last name"},
    {"height", T_DOUBLE, offsetof(WaltonObject, height), 0, "height float"},
    {"number", T_INT, offsetof(WaltonObject, number), 0, "custom number"},
    {NULL}  /* Sentinel */
};



static PyObject* Walton_name
(
    WaltonObject*   self,
    PyObject*       Py_UNUSED(ignored)
)
{
    if (self->first == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "first");
        return NULL;
    }
    if (self->last == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "last");
        return NULL;
    }
    return PyUnicode_FromFormat("%S %S", self->first, self->last);
}



static PyMethodDef Walton_methods[] =
{
    {"name", (PyCFunction)Walton_name, METH_NOARGS, "Return the name, combining the first and last name" },
    {NULL}  /* Sentinel */
};



static PyTypeObject WaltonType =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "walton_module.Walton",
    .tp_doc = PyDoc_STR("Walton objects"),
    .tp_basicsize = sizeof(WaltonObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = Walton_new,
    .tp_init = (initproc)Walton_init,
    .tp_dealloc = (destructor)Walton_dealloc,
    .tp_members = Walton_members,
    .tp_methods = Walton_methods,
};

/******************* WaltonObject ************************************/


/// Module initation.
PyMODINIT_FUNC PyInit_walton_module(void)
{
    Py_Initialize();

    // Initialises the WaltonType.
    if (PyType_Ready(&WaltonType) < 0)
    {
        return NULL;
    }

    // Create the module.
    PyObject* module = PyModule_Create(&waltonTestDefinition);
    if (module == NULL)
    {
        return NULL;
    }

    // Add a constants to the module.
    PyModule_AddIntConstant(module, "TEST", 1);
    PyModule_AddIntMacro(module, STEVE);

    // Add the object to the module.
    Py_INCREF(&WaltonType);
    if (PyModule_AddObject(module, "Walton", (PyObject*)&WaltonType) < 0)
    {
        Py_DECREF(&WaltonType);
        Py_DECREF(module);
        return NULL;
    }

    // Return success.
    return module;
}
