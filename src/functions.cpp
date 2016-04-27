#include "../include/functions.hpp"

namespace cpuinfo
{
/*!
 * Get the total of online processors
 *
 * \return Number of online processors
 */
uint32_t getOnlineProcessors ()
{
   return (uint32_t) sysconf(_SC_NPROCESSORS_ONLN);
}

/*!
 * Bind the process to a processor
 *
 * \param[in] processor_id The processor index
 *
 * \return 0 in case of success
 *         errno otherwise
 */
uint32_t bindToCpu (uint32_t index)
{
    int retval;
    cpu_set_t cpuset;

    memset(&cpuset, 0, sizeof(cpu_set_t));
    CPU_SET(index, &cpuset);
    retval = sched_setaffinity(0, sizeof( cpu_set_t ), &cpuset);

    if (retval)
        retval = errno;

    return retval;
}
}
