#include <Python.h>

#include "Parser.h"

static void Teager_callback(
    PyObject *callable,
    const std::string& symbol,
    SymbolType type,
    const std::string& filename,
    unsigned lineno) {
    
    // Call the callback with all supported kwargs, the caller can then
    // choose which to actually handle.
    auto kwargs = Py_BuildValue(
        "{s:s, s:s, s:I}",
        "symbol", symbol.c_str(),
        "filename", filename.c_str(),
        "lineno", lineno);
    
    if (kwargs) {
        PyObject *result = PyEval_CallObjectWithKeywords(
                callable, // Callable object to call
                nullptr,  // Argument list (not needed in this instance)
                kwargs);  // Keyword argument dict
     
        // TODO: result can be null if an exception is thrown in the above
        //       call. We should somehow pass that back to the original
        //       caller. 
    
        if (result)
            Py_DECREF(result);
    
        Py_DECREF(kwargs);
    }
}

static PyObject * Teager_parse(PyObject *self, PyObject *args) {
    const char *filename = nullptr;
    PyObject *callback = nullptr;

    if (!PyArg_ParseTuple(args, "sO", &filename, &callback))
        return nullptr;
    
    if (!PyCallable_Check(callback)) {
        PyErr_SetString(PyExc_TypeError, "Callback must be callable");
        return nullptr;
    }
    
    namespace ph = std::placeholders;

    Parser parser;
    parser.parse_file(
        filename, 
        std::bind(
            Teager_callback, 
            callback, 
            ph::_1, 
            ph::_2, 
            ph::_3, 
            ph::_4));
       
    Py_RETURN_NONE;
}

static PyMethodDef TeagerMethods[] = {
    {"parse",  Teager_parse, METH_VARARGS, "Parse a file"},
    {NULL, NULL, 0, NULL}  
};

static struct PyModuleDef TeagerModule = {
    PyModuleDef_HEAD_INIT,
    "teager", // Module Name 
    nullptr,  // Documentation
    -1,
    TeagerMethods 
};

PyMODINIT_FUNC PyInit_teager(void) {
    return PyModule_Create(&TeagerModule);
}
