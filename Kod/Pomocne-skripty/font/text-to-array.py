#!/usr/bin/env python3
"""
Simple String to ISO-8859-2 C Array
"""

import sys

def simple_convert():
    if len(sys.argv) < 2:
        print("Usage: python string_to_c.py \"your text here\" [array_name]")
        print("Example: python string_to_c.py \"Hello Šťastný den!\" my_text")
        return
    
    text = sys.argv[1]
    array_name = sys.argv[2] if len(sys.argv) > 2 else "text"
    
    # Convert to ISO-8859-2
    iso_bytes = text.encode('iso-8859-2', errors='replace')

    iso_bytes += bytes([0]) # Add null terminator
    
    print(f"// Original string: \"{text}\"")
    print(f"// Length: {len(iso_bytes)} bytes")
    print(f"// Encoding: ISO-8859-2")
    print(f"const char {array_name}[] = {{")
    
    # Print hex values (16 per line)
    for i in range(0, len(iso_bytes), 16):
        chunk = iso_bytes[i:i + 16]
        hex_str = ", ".join([f"0x{b:02X}" for b in chunk])
        
        # Show ASCII representation for the chunk
        ascii_chunk = text[i:i + 16]
        ascii_repr = ""
        for char in ascii_chunk:
            if char == '\\':
                ascii_repr += '\\\\'
            elif char == '\"':
                ascii_repr += '\\"'
            elif char == '\'':
                ascii_repr += '\\\''
            elif char == '\n':
                ascii_repr += '\\n'
            elif char == '\t':
                ascii_repr += '\\t'
            elif char == '\r':
                ascii_repr += '\\r'
            else:
                ascii_repr += char
        
        print(f"    {hex_str},  // \"{ascii_repr}\"")
    
    print("};")
    print(f"const uint32_t {array_name}_len = {len(iso_bytes)};")

if __name__ == "__main__":
    simple_convert()