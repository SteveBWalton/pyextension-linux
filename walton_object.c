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
