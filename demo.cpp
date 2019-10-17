#include <pybind11/pybind11.h>
#include <omp.h>
#include <iostream>

// HostWidget and DeviceWidget are the same except that HostWidget uses
// omp_target_alloc to allocate memory on the host and DeviceWidget
// attempts to allocate memory on the device.
class DeviceWidget {
public:
    DeviceWidget(size_t size) :
      _size(size),
      _dnum(omp_get_default_device()),
      _hnum(omp_get_initial_device()),
      _ptr(static_cast<double*>(omp_target_alloc(_size*sizeof(double), _dnum)))
    {
        std::cout << "_ptr = " << _ptr << '\n';
    }

    ~DeviceWidget() {
        omp_target_free(_ptr, _dnum);
    }
private:
    size_t _size;
    int _dnum;
    int _hnum;
    double* _ptr;
};


class HostWidget {
public:
    HostWidget(size_t size) :
      _size(size),
      _dnum(omp_get_default_device()),
      _hnum(omp_get_initial_device()),
      _ptr(static_cast<double*>(omp_target_alloc(_size*sizeof(double), _hnum)))
    {
        std::cout << "_ptr = " << _ptr << '\n';
    }

    ~HostWidget() {
        omp_target_free(_ptr, _hnum);
    }
private:
    size_t _size;
    int _dnum;
    int _hnum;
    double* _ptr;
};


namespace py = pybind11;
namespace demo {
    PYBIND11_MODULE(_demo, m) {
        py::class_<DeviceWidget>(m, "DeviceWidget")
            .def(py::init<size_t>());
        py::class_<HostWidget>(m, "HostWidget")
            .def(py::init<size_t>());
    }
}
