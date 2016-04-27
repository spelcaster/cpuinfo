#include "../include/IntelCpuAdapter.hpp"

#include <iostream>
#include <iomanip>
#include <string>

int main () {
    cpuinfo::IntelCpuAdapter *cpuinfo = new cpuinfo::IntelCpuAdapter();

    cpuinfo->describe();

    std::cout << "vendor id:\t" << cpuinfo->getVendorId() << std::endl;
    std::cout << "brand:\t" << cpuinfo->getBrand() << std::endl;
    std::cout << "stepping: \t" << cpuinfo->getStepping() << std::endl;
    std::cout << "model:\t" << cpuinfo->getModel() << std::endl;
    std::cout << "family:\t" << cpuinfo->getFamily() << std::endl;
    std::cout << "processor type:\t" << cpuinfo->getProcessorType() << std::endl;
    std::cout << "max logical processors:\t" << cpuinfo->getMaxLogicalProcessor() << std::endl;
    std::cout << "local apic id:\t" << cpuinfo->getLocalApicId() << std::endl;

    if (cpuinfo->hasFastSystemCall()) {
        std::cout << "fast system call is supported" << std::endl;
    }

    return 0;
}

