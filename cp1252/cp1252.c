// Various CP-1252 encode/decode functions
// This is free and unencumbered software released into the public domain.
#include <stdint.h>

// Decode one byte of CP-1252 to a Unicode code point.
//
// Undefined inputs are mapped to their "best fit" code point.
long
cp1252_to_unicode(int c)
{
    static const uint16_t t[256] = {
        0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
        0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
        0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
        0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
        0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
        0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
        0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
        0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
        0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
        0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
        0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
        0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
        0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
        0x20ac, 0x0081, 0x201a, 0x0192, 0x201e, 0x2026, 0x2020, 0x2021,
        0x02c6, 0x2030, 0x0160, 0x2039, 0x0152, 0x008d, 0x017d, 0x008f,
        0x0090, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014,
        0x02dc, 0x2122, 0x0161, 0x203a, 0x0153, 0x009d, 0x017e, 0x0178,
        0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7,
        0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
        0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
        0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
        0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7,
        0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
        0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
        0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
        0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7,
        0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
        0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
        0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff
    };
    return t[c&0xff];
}

// Encode a Unicode code point into one byte of CP-1252.
//
// The five undefined CP-1252 bytes are mapped to their "best fit" code
// points. Otherwise unrepresentable input is converted to U+001A
// (SUBSTITUTE).
int
unicode_to_cp1252(long r)
{
    static const uint16_t search[256] = {
        0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
        0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
        0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
        0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
        0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
        0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
        0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
        0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
        0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
        0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
        0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
        0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
        0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
        0x0081, 0x008d, 0x008f, 0x0090, 0x009d, 0x00a0, 0x00a1, 0x00a2,
        0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa,
        0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af, 0x00b0, 0x00b1, 0x00b2,
        0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00ba,
        0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf, 0x00c0, 0x00c1, 0x00c2,
        0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca,
        0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf, 0x00d0, 0x00d1, 0x00d2,
        0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da,
        0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df, 0x00e0, 0x00e1, 0x00e2,
        0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9, 0x00ea,
        0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef, 0x00f0, 0x00f1, 0x00f2,
        0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7, 0x00f8, 0x00f9, 0x00fa,
        0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff, 0x0152, 0x0153, 0x0160,
        0x0161, 0x0178, 0x017d, 0x017e, 0x0192, 0x02c6, 0x02dc, 0x2013,
        0x2014, 0x2018, 0x2019, 0x201a, 0x201c, 0x201d, 0x201e, 0x2020,
        0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203a, 0x20ac, 0x2122
    };
    static const unsigned char tx[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
        0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
        0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41,
        0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c,
        0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
        0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62,
        0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d,
        0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x81, 0x8d, 0x8f, 0x90,
        0x9d, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9,
        0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca,
        0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5,
        0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0,
        0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb,
        0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6,
        0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff, 0x8c, 0x9c,
        0x8a, 0x9a, 0x9f, 0x8e, 0x9e, 0x83, 0x88, 0x98, 0x96, 0x97, 0x91,
        0x92, 0x82, 0x93, 0x94, 0x84, 0x86, 0x87, 0x95, 0x85, 0x89, 0x8b,
        0x9b, 0x80, 0x99
    };
    int i = 255;  // binary search upper bound
    i -= (r < search[i - 127]) << 7;
    i -= (r < search[i -  63]) << 6;
    i -= (r < search[i -  31]) << 5;
    i -= (r < search[i -  15]) << 4;
    i -= (r < search[i -   7]) << 3;
    i -= (r < search[i -   3]) << 2;
    i -= (r < search[i -   1]) << 1;
    i -= (r < search[i -   0]) << 0;
    return search[i] == r ? tx[i] : 0x1a;
}

// Transcode one UTF-8 code point into one byte of CP-1252.
//
// The five undefined CP-1252 bytes are mapped to their "best fit" code
// points. Otherwise unrepresentable or invalid input is converted to U+001A
// (SUBSTITUTE). Always stores at exactly one byte to the output buffer.
// Returns the number of input bytes consumed (from 1 to 4).
int
utf8_to_cp1252(void *cp1252, const void *utf8)
{
    const unsigned char *p = utf8;
    unsigned char *o = cp1252;
    long r;

    if (p[0] < 0x80) {
        *o = p[0];  // ASCII fast path
        return 1;

    } else if ((p[0] & 0xe0) == 0xc0) {
        if ((p[1] & 0xc0) != 0x80) {
            goto invalid;
        }
        r = (long)(p[0] & 0x1f) << 6 |
            (long)(p[1] & 0x3f) << 0;
        if (r < 0x80) {
            goto invalid;  // overly long encoding
        }
        *o = unicode_to_cp1252(r);
        return 2;

    } else if ((p[0] & 0xf0) == 0xe0) {
        if ((p[1] & 0xc0) != 0x80 ||
            (p[2] & 0xc0) != 0x80) {
            goto invalid;
        }
        r = (long)(p[0] & 0x0f) << 12 |
            (long)(p[1] & 0x3f) <<  6 |
            (long)(p[2] & 0x3f) <<  0;
        if (r < 0x800) {
            goto invalid;  // overly long encoding
        }
        *o = unicode_to_cp1252(r);
        return 3;

    } else if ((p[0] & 0xf8) == 0xf0 && (p[0] <= 0xf4)) {
        if ((p[1] & 0xc0) != 0x80 ||
            (p[2] & 0xc0) != 0x80 ||
            (p[3] & 0xc0) != 0x80) {
            goto invalid;
        }
        r = (long)(p[0] & 0x07) << 18 |
            (long)(p[1] & 0x3f) << 12 |
            (long)(p[2] & 0x3f) <<  6 |
            (long)(p[3] & 0x3f) <<  0;
        if (r < 0x10000) {
            goto invalid;  // overly long encoding
        }
        *o = unicode_to_cp1252(r);
        return 4;
    }

    invalid:
    *o = 0x1a;
    return 1;
}

// Decode one byte of CP-1252 into bytes of UTF-8.
//
// Undefined bytes mapped to their "best bit" code points. Returns the
// number of bytes stored (from 1 to 3).
int
cp1252_to_utf8(void *utf8, int c)
{
    static const uint32_t t[256] = {
        0x000000, 0x000001, 0x000002, 0x000003, 0x000004, 0x000005, 0x000006,
        0x000007, 0x000008, 0x000009, 0x00000a, 0x00000b, 0x00000c, 0x00000d,
        0x00000e, 0x00000f, 0x000010, 0x000011, 0x000012, 0x000013, 0x000014,
        0x000015, 0x000016, 0x000017, 0x000018, 0x000019, 0x00001a, 0x00001b,
        0x00001c, 0x00001d, 0x00001e, 0x00001f, 0x000020, 0x000021, 0x000022,
        0x000023, 0x000024, 0x000025, 0x000026, 0x000027, 0x000028, 0x000029,
        0x00002a, 0x00002b, 0x00002c, 0x00002d, 0x00002e, 0x00002f, 0x000030,
        0x000031, 0x000032, 0x000033, 0x000034, 0x000035, 0x000036, 0x000037,
        0x000038, 0x000039, 0x00003a, 0x00003b, 0x00003c, 0x00003d, 0x00003e,
        0x00003f, 0x000040, 0x000041, 0x000042, 0x000043, 0x000044, 0x000045,
        0x000046, 0x000047, 0x000048, 0x000049, 0x00004a, 0x00004b, 0x00004c,
        0x00004d, 0x00004e, 0x00004f, 0x000050, 0x000051, 0x000052, 0x000053,
        0x000054, 0x000055, 0x000056, 0x000057, 0x000058, 0x000059, 0x00005a,
        0x00005b, 0x00005c, 0x00005d, 0x00005e, 0x00005f, 0x000060, 0x000061,
        0x000062, 0x000063, 0x000064, 0x000065, 0x000066, 0x000067, 0x000068,
        0x000069, 0x00006a, 0x00006b, 0x00006c, 0x00006d, 0x00006e, 0x00006f,
        0x000070, 0x000071, 0x000072, 0x000073, 0x000074, 0x000075, 0x000076,
        0x000077, 0x000078, 0x000079, 0x00007a, 0x00007b, 0x00007c, 0x00007d,
        0x00007e, 0x00007f, 0xe282ac, 0x00c281, 0xe2809a, 0x00c692, 0xe2809e,
        0xe280a6, 0xe280a0, 0xe280a1, 0x00cb86, 0xe280b0, 0x00c5a0, 0xe280b9,
        0x00c592, 0x00c28d, 0x00c5bd, 0x00c28f, 0x00c290, 0xe28098, 0xe28099,
        0xe2809c, 0xe2809d, 0xe280a2, 0xe28093, 0xe28094, 0x00cb9c, 0xe284a2,
        0x00c5a1, 0xe280ba, 0x00c593, 0x00c29d, 0x00c5be, 0x00c5b8, 0x00c2a0,
        0x00c2a1, 0x00c2a2, 0x00c2a3, 0x00c2a4, 0x00c2a5, 0x00c2a6, 0x00c2a7,
        0x00c2a8, 0x00c2a9, 0x00c2aa, 0x00c2ab, 0x00c2ac, 0x00c2ad, 0x00c2ae,
        0x00c2af, 0x00c2b0, 0x00c2b1, 0x00c2b2, 0x00c2b3, 0x00c2b4, 0x00c2b5,
        0x00c2b6, 0x00c2b7, 0x00c2b8, 0x00c2b9, 0x00c2ba, 0x00c2bb, 0x00c2bc,
        0x00c2bd, 0x00c2be, 0x00c2bf, 0x00c380, 0x00c381, 0x00c382, 0x00c383,
        0x00c384, 0x00c385, 0x00c386, 0x00c387, 0x00c388, 0x00c389, 0x00c38a,
        0x00c38b, 0x00c38c, 0x00c38d, 0x00c38e, 0x00c38f, 0x00c390, 0x00c391,
        0x00c392, 0x00c393, 0x00c394, 0x00c395, 0x00c396, 0x00c397, 0x00c398,
        0x00c399, 0x00c39a, 0x00c39b, 0x00c39c, 0x00c39d, 0x00c39e, 0x00c39f,
        0x00c3a0, 0x00c3a1, 0x00c3a2, 0x00c3a3, 0x00c3a4, 0x00c3a5, 0x00c3a6,
        0x00c3a7, 0x00c3a8, 0x00c3a9, 0x00c3aa, 0x00c3ab, 0x00c3ac, 0x00c3ad,
        0x00c3ae, 0x00c3af, 0x00c3b0, 0x00c3b1, 0x00c3b2, 0x00c3b3, 0x00c3b4,
        0x00c3b5, 0x00c3b6, 0x00c3b7, 0x00c3b8, 0x00c3b9, 0x00c3ba, 0x00c3bb,
        0x00c3bc, 0x00c3bd, 0x00c3be, 0x00c3bf
    };
    unsigned long r = t[c&0xff];
    unsigned char *p = utf8;
    p += !!(*p = r >> 16);
    p += !!(*p = r >>  8);
    *p = r;
    return p - (unsigned char *)utf8 + 1;
}