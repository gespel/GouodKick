/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   KNOB_V6_png;
    const int            KNOB_V6_pngSize = 8747;

    extern const char*   KICKTATOR_V2_BG_png;
    const int            KICKTATOR_V2_BG_pngSize = 60103;

    extern const char*   KICKTATOR_V3_BG_png;
    const int            KICKTATOR_V3_BG_pngSize = 264486;

    extern const char*   KICKTATOR_V4_BG_png;
    const int            KICKTATOR_V4_BG_pngSize = 78552;

    extern const char*   KNOB_V3_png;
    const int            KNOB_V3_pngSize = 5236;

    extern const char*   KNOB_V4_png;
    const int            KNOB_V4_pngSize = 6735;

    extern const char*   KNOB_V5_png;
    const int            KNOB_V5_pngSize = 6735;

    extern const char*   FADER_SHADOW_png;
    const int            FADER_SHADOW_pngSize = 11258;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
