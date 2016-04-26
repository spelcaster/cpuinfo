/*!
 * \file  IntelCpuAdapter.hpp
 * \brief Class definition to interpret the results from cpuid functions from
 *        intel processors
 * \date  18/04/2016
 */

#ifndef __CPUINFO_INTEL_CPU_ADAPTER_HPP
#define __CPUINFO_INTEL_CPU_ADAPTER_HPP

#include "CpuAdapter.hpp"

namespace cpuinfo
{
//! IntelCpuAdapter
/*!
 * IntelCpuAdapter is used to interpret the results of cpuid instruction in
 * intel processors
 */
class IntelCpuAdapter : public CpuAdapter
{
 private:
    /*!
     * Describe cache descriptors, this method is called from describe
     *
     * \return void
     */
    void describeCacheDescriptors ();

 public:
     /*!
      * IntelCpuAdapter constructor
      */
    IntelCpuAdapter();

    /*!
     * IntelCpuAdapter destructor
     */
    ~IntelCpuAdapter();

    /*!
     * Describe all the functions supported by the intel processor
     *
     * \return void
     */
    void describe ();

    /*!
     * \copydoc CpuAdapter::getModel()
     */
    uint32_t getModel ();

    /*!
     * \copydoc CpuAdapter::getProcessorType
     * Possible Intel processor types are:
     *     > 0x00 - Original OEM Processor
     *     > 0x01 - OverDrive Processor
     *     > 0x10 - Dual Processor
     *     > 0x11 - Intel Reserved
     * \return The processor type
     */
    uint32_t getProcessorType ();

    /*!
     *\copydoc CpuAdapter::getMaxLogicalProcessor()
     */
    uint32_t getMaxLogicalProcessor ();

    /*!
     * \copydoc CpuAdapter::hasFastSystemCall()
     */
    bool hasFastSystemCall ();
};

/**
 * Intel
 *
 * Standard CPUID Functions
 * 0x00000000 Vendor ID and Largest Standard Function
 * 0x00000001 Feature Information
 * 0x00000002 Cache Descriptors
 * 0x00000003 Processor Serial Number
 * 0x00000004 Deterministic Cache Parameters
 * 0x00000005 MONITOR/ MWAIT Parameters
 * 0x00000006 Digital Thermal Sensor and Power Management Parameters
 * 0x00000007 Structured Extended Feature Flags Enumeration
 * 0x00000008 Reserved
 * 0x00000009 Direct Cache Access (DCA) Parameters
 * 0x0000000A Architectural Performance Monitor Features
 * 0x0000000B x2APIC Features / Processor Topology
 * 0x0000000C Reserved
 * 0x0000000D XSAVE Features
 *
 * Extended CPUID Functions
 * 0x80000000 Largest Extended Function
 * 0x80000001 Extended Feature Bits
 * 0x80000002 Processor Brand String (i)
 * 0x80000003 Processor Brand String (ii)
 * 0x80000004 Processor Brand String (iii)
 * 0x80000005 Reserved
 * 0x80000006 Extended L2 Cache Features
 * 0x80000007 Advanced Power Management
 * 0x80000008 Virtual and Physical Address Sizes
 */

}

#endif // __CPUINFO_INTEL_CPU_ADAPTER_HPP

