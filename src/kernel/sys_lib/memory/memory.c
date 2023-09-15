#include <memory/memory.h>


volatile struct limine_memmap_request memmap_req =
{
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void memminit(void)
{
    print("here:%h%n",memmap_req.response);
}

void *memcpy(void *dest, const void *src, uint64_t n)
{
            uint8_t *pdest = (uint8_t *)        dest;
    const   uint8_t *psrc  = (const uint8_t *)  src;

    for (uint64_t i = 0; i < n; i++)
    {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *s, int c, uint64_t n)
{
    uint8_t *p = (uint8_t *)s;

    for (uint64_t i = 0; i < n; i++)
    {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, uint64_t n)
{
            uint8_t *pdest = (uint8_t *)dest;
    const   uint8_t *psrc  = (const uint8_t *)src;

    if (src > dest)
    {
        for (uint64_t i = 0; i < n; i++)
        {
            pdest[i]    = psrc[i];
        }
    }
    else if (src < dest)
    {
        for (uint64_t i = n; i > 0; i--)
        {
            pdest[i-1]  = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, uint64_t n)
{
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (uint64_t i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

//***********************************************************************


