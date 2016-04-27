#include "../include/CacheDescriptor.hpp"

namespace cpuinfo
{
/*!
 * CacheDescriptor constructor
 */
CacheDescriptor::CacheDescriptor ()
{
}

/*!
 * CacheDescriptor destructor
 */
CacheDescriptor::~CacheDescriptor ()
{
}

/*!
 * Load cache descriptors json into memory
 */
void CacheDescriptor::loadCacheDescriptor (std::string manufacturer)
{
    Json::Value root;
    Json::Reader reader;
    std::string text;

    std::ifstream json_file("/usr/local/include/cpuinfo/res/cache_descriptors.json");

    json_file.seekg(0, std::ios::end);
    text.reserve(json_file.tellg());
    json_file.seekg(0, std::ios::beg);

    text.assign(
        (std::istreambuf_iterator<char>(json_file)),
        std::istreambuf_iterator<char>()
    );

    bool result = reader.parse(text, root);

    if (!result) {
        std::cout << reader.getFormattedErrorMessages();
        return;
    }

    table_ = root[manufacturer];
}

/*!
 * Display the description of all given cache descriptors
 *
 * \param[in] descriptors A list of cache descriptors
 *
 * \return void
 */
void CacheDescriptor::describe (std::vector< uint32_t > descriptors)
{
    std::vector< uint32_t >::iterator it;

    for (it = descriptors.begin(); it != descriptors.end(); it++) {
        std::cout << getDescription(*it) << std::endl;
    }
}

/*!
 * Recover the description of a given descriptor
 *
 * \param[in] descriptor A cache descriptor code
 *
 * \return The description of the cache descriptor according to the
 *         manufacturer cache descriptor table
 */
std::string CacheDescriptor::getDescription (uint32_t descriptor)
{
    Json::ValueConstIterator it;

    for (it = table_.begin(); it != table_.end(); ++it) {
        Json::Value entry = *it;
        uint32_t tmp = entry.get("value", 0).asUInt();

        if (descriptor == tmp)
            return entry.get("description", "Undefined").asString();;
    }

    return "Undefined";
}
}
