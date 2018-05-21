#ifndef SHA1_DEFINED
#define SHA1_DEFINED

namespace sha1 {

    /**
     @param src points to any kind of data to be hashed.
     @param bytelength the number of bytes to hash from the src pointer.
     @param hash should point to a buffer of at least 20 bytes of size for storing the sha1 result in.
     */
    void calc(const void* src, const int bytelength, unsigned char* hash);

    /**
     @param hash is 20 bytes of sha1 hash. This is the same data that is the result from the calc function.
     @param hexstring should point to a buffer of at least 41 bytes of size for storing the hexadecimal representation of the hash. A zero will be written at position 40, so the buffer will be a valid zero ended string.
     */
    void toHexString(const unsigned char* hash, char* hexstring);

}  // namespace sha1

#include "sha1.inl"

#endif // SHA1_DEFINED
