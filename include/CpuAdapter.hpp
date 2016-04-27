/*!
 * \file  CpuAdapter.hpp
 * \brief Class definition to interpret the results from cpuid functions
 * \date  13/04/2016
 */

#ifndef __CPUINFO_CPU_ADAPTER_HPP
#define __CPUINFO_CPU_ADAPTER_HPP

#include "definitions.hpp"
#include "CpuConnector.hpp"

#include <stdint.h>

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

namespace cpuinfo
{
//! CpuAdapter
/*!
 * CpuAdapter is used to interpret the results of cpuid instruction
 */
class CpuAdapter
{
 private:
    /*!
     * This will be used to execute cpuid instruction and recover data from
     * registers
     */
    CpuConnector *conn_;

    /*!
     * The highest standard function that the processor supports
     */
    uint32_t highest_standard_fn_ = 0x0;

    /*!
     * The highest extended function that the processor supports
     */
    uint32_t highest_extended_fn_ = 0x0;

    /*!
     * Execute cpuid instruction without any restriction, should be called
     * once from constructor
     *
     * \param[in] function_id The function id from cpuid set of functions that
     *                        will be used to execute cpuid
     *
     * \return void
     */
    void setupQuery (uint32_t function_id);

 public:
    /*!
     * CpuAdapter constructor
     */
    CpuAdapter ();

    /*!
     * CpuAdapter destructor
     */
    ~CpuAdapter ();

    /*!
     * Recover data stored in EAX register
     *
     * \return The value stored in EAX register
     */
    uint32_t getEAX () const;

    /*!
     * Recover data stored in EBX register
     *
     * \return The value stored in EBX register
     */
    uint32_t getEBX () const;

    /*!
     * Recover data stored in ECX register
     *
     * \return The value stored in ECX register
     */
    uint32_t getECX () const;

    /*!
     * Recover data stored in EDX register
     *
     * \return The value stored in EDX register
     */
    uint32_t getEDX () const;

    /*!
     * Execute cpuid instruction restraining by the highest standard function
     * or highest extended function supported by the processor
     *
     * \param[in] function_id The function id from cpuid set of functions that
     *                        will be used to execute cpuid
     *
     * \return void
     */
    void query (uint32_t function_id);

    /*!
     * Get the highest standard function supported by the processor
     *
     * \return The highest standard function supported by the processor
     */
    uint32_t getStandarHighestFn ();

    /*!
     * get the highest extended function supported by the processor
     *
     * \return the highest extended function supported by the processor
     */
    uint32_t getExtendedHighestFn ();

    /*!
     * Execute a function with cpuid instruction and print the function id and
     * the values stored in the register in hexadecimal
     *
     * \param[in] function_id The function id from cpuid set of functions that
     *                        will be used to execute cpuid
     *
     * \return void
     */
    void describeRegisters (const uint32_t function_id);

    /*!
     * Transform a 32 bits register in a 4 bytes string using right shift
     *
     * \param[in] reg The register that will be converted
     *
     * \return A 4 byte string
     */
    std::string toAscii (const uint32_t reg);

    /*!
     * Get the processor vendor id
     *
     * \return A 12 byte string representing the vendor id
     */
    std::string getVendorId ();

    /*!
     * Get the processor brand
     *
     * \return The processor brand
     */
    std::string getBrand ();

    /*!
     * The processor family identifies one or more processors as belonging to a
     * group that possesses some commom definition for software or hardware
     * purposes
     *
     * \return The processors family
     */
    uint32_t getFamily ();

    /*!
     * The stepping identifies a particular version of a specific model
     *
     * \return The processor stepping
     */
    uint32_t getStepping ();

    /*!
     * The index of the cpu where the program is running
     *
     * \return The cpu index
     */
    uint32_t getLocalApicId ();

    // Abstract methods
    /*!
     * Describe all the functions supported by the processor
     *
     * \return void
     */
    virtual void describe () = 0;

    /*!
     * Get the processor model that specifies one instance of a processor
     * family
     *
     * \return The processor model
     */
    virtual uint32_t getModel () = 0;

    /*!
     * Get the type of the processor
     *
     * \return The processor's type
     */
    virtual uint32_t getProcessorType () = 0;

    /*!
     * Get the maximum number of logical processors supported
     *
     * \return The maximum number of logical processors
     */
    virtual uint32_t getMaxLogicalProcessor () = 0;

    /*!
     * Check if the processor supports SYSENTER/SYSEXIT instructions
     *
     * \return true if the instructions are supported
     *         false otherwise
     */
    virtual bool hasFastSystemCall () = 0;

    /*!
     * Get the processor cache descriptors without repetitions
     *
     * \return An array of cache descriptors
     */
    virtual std::vector< uint32_t > getCacheDescriptors () = 0;
};

}

#endif // __CPUINFO_CPU_ADAPTER_HPP

