#include "CpuAdapter.hpp"

#include <string>
#include <iostream>
#include <iomanip>

namespace cpuinfo
{
/*!
 * CpuAdapter constructor
 */
CpuAdapter::CpuAdapter ()
{
    conn_ = new CpuConnector();

    setupQuery(0x0);

    highest_standard_fn_ = getEAX();

    setupQuery(0x80000000);

    highest_extended_fn_ = getEAX();
}

/*!
 * CpuAdapter destructor
 */
CpuAdapter::~CpuAdapter ()
{
}

/*!
 * Recover data stored in EAX register
 *
 * \return The value stored in EAX register
 */
uint32_t CpuAdapter::getEAX () const
{
    return conn_->getRegister(0);
}

/*!
 * Recover data stored in EBX register
 *
 * \return The value stored in EBX register
 */
uint32_t CpuAdapter::getEBX () const
{
    return conn_->getRegister(1);
}

/*!
 * Recover data stored in ECX register
 *
 * \return The value stored in ECX register
 */
uint32_t CpuAdapter::getECX () const
{
    return conn_->getRegister(2);
}

/*!
 * Recover data stored in EDX register
 *
 * \return The value stored in EDX register
 */
uint32_t CpuAdapter::getEDX () const
{
    return conn_->getRegister(3);
}

/*!
 * Execute cpuid instruction without any restriction, should be called
 * once from constructor
 *
 * \param[in] function_id The function id from cpuid set of functions that
 *                        will be used to execute cpuid
 *
 * \return void
 */
void CpuAdapter::setupQuery (uint32_t function_id)
{
    conn_->cpuid(function_id);
}

/*!
 * Execute cpuid instruction restraining by the highest standard function
 * or highest extended function supported by the processor
 *
 * \param[in] function_id The function id from cpuid set of functions that
 *                        will be used to execute cpuid
 *
 * \return void
 */
void CpuAdapter::query (uint32_t function_id)
{
    if (((function_id >= 0x80000000) && (function_id <= highest_extended_fn_))
        || (function_id <= highest_standard_fn_)
    ) {
        conn_->cpuid(function_id);
    }
}

/*!
 * Get the highest standard function supported by the processor
 *
 * \return The highest standard function supported by the processor
 */
uint32_t CpuAdapter::getStandarHighestFn ()
{
    return highest_standard_fn_;
}

/*!
 * Get the highest standard function supported by the processor
 *
 * \return The highest standard function supported by the processor
 */
uint32_t CpuAdapter::getExtendedHighestFn ()
{
    return highest_extended_fn_;
}

/*!
 * Execute a function with cpuid instruction and print the function id and
 * the values stored in the register in hexadecimal
 *
 * \param[in] function_id The function id from cpuid set of functions that
 *                        will be used to execute cpuid
 *
 * \return void
 */
void CpuAdapter::describeRegisters (const uint32_t function_id)
{
    query(function_id);
    std::cout << std::hex;
    std::cout << std::setfill('0') << std::setw(8) << function_id << "\t";
    std::cout << std::setfill('0') << std::setw(8) << getEAX() << "-";
    std::cout << std::setfill('0') << std::setw(8) << getEBX() << "-";
    std::cout << std::setfill('0') << std::setw(8) << getECX() << "-";
    std::cout << std::setfill('0') << std::setw(8) << getEDX();
    std::cout << std::dec;
    std::cout << std::endl;
}

/*!
 * Transform a 32 bits register in a 4 bytes string using right shift
 *
 * \param[in] reg The register that will be converted
 *
 * \return A 4 byte string
 */
std::string CpuAdapter::toAscii (const uint32_t reg)
{
    std::string str;
    uint32_t tmp = reg;

    for (int i = 0; i < 32; i += 8) {
        unsigned char c = tmp & 0xff;
        str += c;
        tmp = tmp >> 8;
    }

    return str;
}

/*!
 * Get the processor vendor id
 *
 * \return A 12 byte string representing the vendor id
 */
std::string CpuAdapter::getVendorId ()
{
    query(0x0);

    std::string vendor;

    vendor += toAscii(getEBX());
    vendor += toAscii(getEDX());
    vendor += toAscii(getECX());

    return vendor;
}

/*!
 * Get the processor brand
 *
 * \return The processor brand
 */
std::string CpuAdapter::getBrand ()
{
    uint32_t function = 0x80000000;
    std::string brand;
    int distance = 0;

    for (int i = 2; i <= 4; i++) {
        query(function + i);

        brand += toAscii(getEAX());
        brand += toAscii(getEBX());
        brand += toAscii(getECX());
        brand += toAscii(getEDX());
    }

    // trim
    for (std::string::iterator it = brand.begin(); it != brand.end(); it++) {
        if (*it != 32)
            break;

        distance++;
    }

    brand.erase(0, distance);

    return brand;
}

/*!
 * The processor family identifies one or more processors as belonging to a
 * group that possesses some commom definition for software or hardware
 * purposes
 *
 * \return The processors family
 */
uint32_t CpuAdapter::getFamily ()
{
    query(0x1);

    uint32_t base_family = (getEAX() >> 8) & 0x0f;
    uint32_t extended_family = (getEAX() >> 20) & 0xff;
    uint32_t family = base_family + extended_family;

    if (base_family < 0xf)
        family = base_family;

    return family;
}

/*!
 * The stepping identifies a particular version of a specific model
 *
 * \return The processor stepping
 */
uint32_t CpuAdapter::getStepping ()
{
    query(0x1);

    return getEAX() & 0xf;
}

/*!
 * The index of the cpu where the program is running
 *
 * \return The cpu index
 */
uint32_t CpuAdapter::getLocalApicId ()
{
    query(0x1);

    return (getEBX() >> 24) & 0xff;
}

}
