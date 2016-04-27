#include "IntelCpuAdapter.hpp"

namespace cpuinfo
{
 /*!
  * IntelCpuAdapter constructor
  */
IntelCpuAdapter::IntelCpuAdapter ()
{
}

/*!
 * IntelCpuAdapter destructor
 */
IntelCpuAdapter::~IntelCpuAdapter ()
{
}

/*!
 * Describe cache descriptors, this method is called from describe
 *
 * \return void
 */
void IntelCpuAdapter::describeCacheDescriptors ()
{
    uint32_t times = 0;

    query(0x2);

    times = getEAX() & 0xff;

    std::cout << std::hex;
    for (uint32_t i = 0; i < times; i++) {
        describeRegisters(0x2);
    }
}

/*!
 * Describe all the functions supported by the intel processor
 *
 * \return void
 */
void IntelCpuAdapter::describe ()
{
    std::cout << std::hex;
    for (uint32_t i = 0; i <= getStandarHighestFn(); i++) {
        if (i == 0x2) {
            describeCacheDescriptors();
            continue;
        }

        describeRegisters(i);
    }

    for (uint32_t i = 0x80000000; i <= getExtendedHighestFn(); i++) {
        describeRegisters(i);
    }

    std::cout << std::endl;
}

/*!
 * \copydoc CpuAdapter::getModel()
 */
uint32_t IntelCpuAdapter::getModel ()
{
    query(0x1);

    uint32_t base_model = (getEAX() >> 4) & 0xf;
    uint32_t extended_model = (getEAX() >> 16) & 0xff;
    uint32_t model = (extended_model << 4) + base_model;

    return model;
}

/*!
 * \copydoc CpuAdapter::getProcessorType
 * Possible Intel processor types are:
 *     > 0x00 - Original OEM Processor
 *     > 0x01 - OverDrive Processor
 *     > 0x10 - Dual Processor
 *     > 0x11 - Intel Reserved
 * \return The processor type
 */
uint32_t IntelCpuAdapter::getProcessorType ()
{
    query(0x1);

    uint32_t tmp = getEAX();

    tmp = tmp >> 12;

    return tmp & 0x3;
}

/*!
 *\copydoc CpuAdapter::getMaxLogicalProcessor()
 */
uint32_t IntelCpuAdapter::getMaxLogicalProcessor ()
{
    query(0x1);

    return (getEBX() >> 16) & 0xff;
}

/*!
 * \copydoc CpuAdapter::hasFastSystemCall()
 */
bool IntelCpuAdapter::hasFastSystemCall ()
{
    query(0x1);

    if (getEDX() & INTEL_FF_SEP) {
        if ((getEAX() & 0x0fff3fff) > 0x663)
            return true;
    }

    return false;
}

/*!
 * \copydoc CpuAdapter::getCacheDescriptors()
 */
std::vector< uint32_t > IntelCpuAdapter::getCacheDescriptors ()
{
    std::vector< uint32_t > descriptors;
    uint32_t times = 0;
    bool tmp[255];
    uint32_t reg;

    std::fill(tmp, tmp + 255, false);

    query(0x2);
    times = getEAX() & 0xff;

    for (uint32_t i = 0; i < times; i++) {
        reg = getEAX();

        if (!(reg & BIT_31)) {
            tmp[reg & 0xff] = true;
            tmp[(reg >> 8) & 0xff] = true;
            tmp[(reg >> 16) & 0xff] = true;
            tmp[(reg >> 24) & 0xff] = true;
        }

        reg = getEBX();

        if (!(reg & BIT_31)) {
            tmp[reg & 0xff] = true;
            tmp[(reg >> 8) & 0xff] = true;
            tmp[(reg >> 16) & 0xff] = true;
            tmp[(reg >> 24) & 0xff] = true;
        }

        reg = getECX();

        if (!(reg & BIT_31)) {
            tmp[reg & 0xff] = true;
            tmp[(reg >> 8) & 0xff] = true;
            tmp[(reg >> 16) & 0xff] = true;
            tmp[(reg >> 24) & 0xff] = true;
        }

        reg = getEDX();

        if (!(reg & BIT_31)) {
            tmp[reg & 0xff] = true;
            tmp[(reg >> 8) & 0xff] = true;
            tmp[(reg >> 16) & 0xff] = true;
            tmp[(reg >> 24) & 0xff] = true;
        }
        query(0x2);
    }

    for (uint32_t i = 0; i < 256; i++) {
        if (tmp[i])
            descriptors.push_back(i);
    }

    return descriptors;
}

}
