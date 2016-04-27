/*!
 * \file   CacheDescriptor.hpp
 * \brief  Class definition to describe processor cache descriptors
 * \date   27/04/2016
 */

#ifndef __CPUINFO_CACHE_DESCRIPTOR_HPP
#define __CPUINFO_CACHE_DESCRIPTOR_HPP

#include <stdint.h>

#include <iostream>
#include <fstream>
#include <vector>

#include <json/json.h>

namespace cpuinfo
{
//! CacheDescriptor
/*!
 * CacheDescriptor is used to describe processor cache descriptors
 */
class CacheDescriptor
{
 private:
    /*!
     * The manufacturer table to resolve the cache descriptors
     */
    Json::Value table_;

 public:
    /*!
     * CacheDescriptor constructor
     */
    CacheDescriptor ();

    /*!
     * CacheDescriptor destructor
     */
    ~CacheDescriptor ();

    /*!
     * Load cache descriptors json into memory
     */
    void loadCacheDescriptor (std::string manufacturer);

    /*!
     * Display the description of all given cache descriptors
     *
     * \param[in] descriptors A list of cache descriptors
     *
     * \return void
     */
    void describe (std::vector< uint32_t > descriptors);

    /*!
     * Recover the description of a given descriptor
     *
     * \param[in] descriptor A cache descriptor code
     *
     * \return The description of the cache descriptor according to the
     *         manufacturer cache descriptor table
     */
    std::string getDescription (uint32_t descriptor);
};

}

#endif // __CPUINFO_CACHE_DESCRIPTOR_HPP

