#include <Python.h>
#include "lz4.h"
#include "lz4hc.h"


static PyObject *
py_compress(PyObject *self, PyObject *args);

static PyObject *
py_decompress(PyObject *self, PyObject *args);

static PyMethodDef lz4Methods[] = {
    {"compress",  py_compress, METH_VARARGS,
     "compress"},
    {"decompress",  py_decompress, METH_VARARGS,
     "decompress"},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static PyObject *
py_compress(PyObject *self, PyObject *args)
{
    PyObject *ret;
    char *data;
    int data_len;
    int output_size;
    char* dest;
    
    if (!PyArg_ParseTuple(args, "s#",  &data, &data_len)) {
        return NULL;
    }
    
    output_size = LZ4_compressBound(data_len) + 4;
    dest = (char *)malloc(output_size);

    output_size = LZ4_compressHC (data,  dest, data_len);
    memcpy(dest+output_size, &data_len, 4);
    
    
    ret = PyString_FromStringAndSize(dest, output_size+4);
    return ret;
}

static PyObject *
py_decompress(PyObject *self, PyObject *args)
{
    PyObject *ret;
    char *data;
    int data_len;
    int output_size;
    char *dest;
    int decompressed_size;
    
    if (!PyArg_ParseTuple(args, "s#", &data, &data_len)) {
        return NULL;
    }
    
    memcpy(&output_size, data + data_len - 4, 4);
    data_len -= 4;

    dest = (char *)malloc(output_size);

    decompressed_size =  LZ4_decompress_safe (data, dest, data_len, output_size);

        
    
    ret = PyString_FromStringAndSize(dest, decompressed_size);
    return ret;
}

/**
 * Python module initialization 
 *
 */
PyMODINIT_FUNC
init_lz4(void)
{
    PyObject *m;

    m = Py_InitModule("_lz4", lz4Methods);
    if (m == NULL)
        return;

}


