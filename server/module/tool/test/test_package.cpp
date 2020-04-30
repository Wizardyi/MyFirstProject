#include "../src/package.h"

#define CHECK(exp) \
    if (exp != 0) {\
        fprintf(stderr, "do exp '%s' failed\n", #exp); \
    }\

int main(int argc, char** argv)
{
    Package package;
    item_t item;

    item.item_id = 1;
    item.count = 2;
    item.expire_time = 12345;
    item.slot_id = 1;

    CHECK(package.put_item(&item));

    item.item_id = 2;
    item.count = 3;
    item.expire_time = 0;
    item.slot_id = 0;
    CHECK(package.put_item(&item));

    package.dump(stdout);

    CHECK(package.reduce_item_by_item_id(2, 1, &item));
    package.dump(stdout);

    return 0;
}
