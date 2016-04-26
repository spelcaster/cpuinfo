#include "CpuConnector.hpp"

namespace cpuinfo
{

/*!
 * CpuConnector constructor
 */
CpuConnector::CpuConnector ()
{
}

/*!
 * CpuConnector destructor
 */
CpuConnector::~CpuConnector ()
{
}

/*!
 * Method to clear the registers before executing cpuid instruction
 *
 * \return void
 */
void CpuConnector::setupRegisters ()
{
    std::fill(gprs_, gprs_ + kCpuidRegisters, 0);
}

/*!
 * Executes the cpuid instruction
 *
 * \param[in] function_id The function id from cpuid set of functions that
 *                        will be used to execute cpuid
 *
 * \return void
 */
void CpuConnector::cpuid (uint32_t function_id)
{
    setupRegisters();

#ifdef __GNUC__
    __asm__ __volatile__
    (
        "cpuid;"
        : "=a" (gprs_[0]), "=b" (gprs_[1]), "=c" (gprs_[2]), "=d" (gprs_[3])
        : "a" (function_id)
    );
#else
#ifndef __x86_64
   __asm__ __volatile__
   (
      "mov    %0, %%edi\n\t"
      "cpuid;\n\t"
      "mov    %%eax, 0(%%edi)\n\t"
      "mov    %%ebx, 4(%%edi)\n\t"
      "mov    %%ecx, 8(%%edi)\n\t"
      "mov    %%edx, 12(%%edi)\n\t"
      :
      :"m" (gprs_),"a" (function_id)
      :"ebx","ecx","edx","edi"
   );
#else
   __asm__ __volatile__
   (
      "movq    %0, %%rdi\n\t"
      "cpuid;\n\t"
      "mov    %%eax, 0(%%rdi)\n\t"
      "mov    %%ebx, 4(%%rdi)\n\t"
      "mov    %%ecx, 8(%%rdi)\n\t"
      "mov    %%edx, 12(%%rdi)\n\t"
      :
      :"m" (gprs_),"a" (function_id)
      :"ebx","ecx","edx","rdi"
   );
#endif /* __x86_64 */
#endif /* __GNUC__ */
}

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
uint32_t CpuConnector::getRegister (uint32_t index)
{
    // should return error if index >= kCpuidRegisters?
    return gprs_[index];
}

}
