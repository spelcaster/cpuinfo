#include "../include/functions.hpp"
#include "../include/IntelCpuAdapter.hpp"
#include "../include/CacheDescriptor.hpp"

#include <iostream>
#include <iomanip>
#include <string>

void show_cpuinfo ();

int main () {
    uint32_t cores = cpuinfo::getOnlineProcessors();


    for (uint32_t i = 0; i < cores; i++) {
        std::cout << "Processor #" << i << std::endl;

        int rc = cpuinfo::bindToCpu(i);

        if (rc)
            continue;

        show_cpuinfo();
    }

    return 0;
}

void show_cpuinfo ()
{
    cpuinfo::IntelCpuAdapter *cpuinfo = new cpuinfo::IntelCpuAdapter();

    cpuinfo::CacheDescriptor *cache_descriptor = new cpuinfo::CacheDescriptor();
    cache_descriptor->loadCacheDescriptor("intel");

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

    std::vector< uint32_t > descriptors = cpuinfo->getCacheDescriptors();

    std::cout << "Cache Descriptors:" << std::endl;
    cache_descriptor->describe(descriptors);

    std::cout << std::endl;
}

