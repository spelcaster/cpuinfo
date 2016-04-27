#ifndef __FUNCTIONS_HPP
#define __FUNCTIONS_HPP

#include <string.h>
#include <stdint.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>

namespace cpuinfo
{
/*!
 * Get the total of online processors
 *
 * \return Number of online processors
 */
uint32_t getOnlineProcessors ();

/*!
 * Bind the process to a processor
 *
 * \param[in] processor_id The processor index
 *
 * \return 0 in case of success
 *         errno otherwise
 */
uint32_t bindToCpu (uint32_t processor_id);
}
#endif // __FUNCTIONS_HPP
