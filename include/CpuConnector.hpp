/*!
 * \file   CpuConnector.hpp
 * \brief  Class definition to recover processor information using cpuid
 *         instruction
 * \date   13/04/2016
 */

#ifndef __CPUINFO_CPU_CONNECTOR_HPP
#define __CPUINFO_CPU_CONNECTOR_HPP

#include <stdint.h>

#include <iterator>
#include <cstring>

namespace cpuinfo
{
/*!
 * Total of registers used in cpuid instruction (EAX, EBX, ECX and EDX)
 */
const int kCpuidRegisters = 4;

//! CpuConnector
/*!
 * CpuConnector is used to execute cpuid instruction and recover data from
 * registers EAX, EBX, ECX and EDX
 */
class CpuConnector
{
 private:
    /*!
     * An array representing the general purpose registers used in cpuid
     * instruction
     */
    uint32_t gprs_[kCpuidRegisters];

 public:
    /*!
     * CpuConnector constructor
     */
    CpuConnector ();

    /*!
     * CpuConnector destructor
     */
    ~CpuConnector ();

    /*!
     * Executes the cpuid instruction
     *
     * \param[in] function_id The function id from cpuid set of functions that
     *                        will be used to execute cpuid
     *
     * \return void
     */
    void cpuid (uint32_t function_id);

    /*!
     * Method to clear the registers before executing cpuid instruction
     *
     * \return void
     */
    void setupRegisters ();

    /*!
     * Set a value to general purpose registers used cpuid instructions
     *
     * \return void
     */
    void setRegisters (uint32_t *reg);

    /*!
     * Method to recover information in registers after executing cpuid
     * instruction
     *
     * \param[in] index The register position
     *
     * \return The value of the register in the given position:
     *         0 -> EAX
     *         1 -> EBX
     *         2 -> ECX
     *         3 -> EDX
     */
    uint32_t getRegister (uint32_t index);
};

}

#endif // __CPUINFO_CPU_CONNECTOR_HPP

