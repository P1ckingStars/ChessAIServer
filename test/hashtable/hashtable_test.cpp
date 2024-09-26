#include "hashtable.hpp"
#include <cstddef>
#include <cstdint>
#include "../memoryallocator/allocator.h"
#include <cstdlib>
#include <memory>
#include <unordered_map>


#define ASSERT_EQ(a, b) (if (!(a) == (b)) { printf("ASSERT FAILED\n");} )
/*

template <class K, class V, class C, C EmptyCompressedKey, V EmptyVal, CollisionHandler handler, 
    HashFunc<K> hash, CompressFunc<K, C> compress>

 */
size_t collision_hdlr(size_t idx, size_t count, size_t size) {
    return (idx + count) / size;
}

int hash_func(int64_t x) {
    return (int)x;
}
int32_t compress_func(int64_t x) {
    return (int)x;
}
int main() {

 //   HashTable(Allocator * allocator, HashFunc * hfunc, CompressFunc *cfunc,
 //      size_t reserved_size, bool can_grow) : 
    size_t size = 2048;
    HashTable<int64_t, int64_t, int32_t, collision_hdlr> test(new LinearAllocator(malloc(size), size), 
                                                                                hash_func, compress_func, 2048, false);
    unordered_map<int64_t, int64_t> orig;
    for (int i = 0; i < 1000; i++) {
        test[i] = i;
        orig[i] = i;
    }
    for (int i = 0; i < 1000; i++) {
        test[i] = i;
        orig[i] = i;
    }
    return 0;
}
