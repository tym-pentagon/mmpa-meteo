#!/usr/bin/env python3
"""
BDF Font to STM32 Font Converter
Converts BDF font files to STM32 font format (ISO-8859-2 encoding)
Supports fonts wider than 8 pixels (multiple bytes per row)
"""

import sys
import os
import re

def parse_bdf_font(bdf_path):
    """Parse BDF font file and extract character data"""
    
    characters = {}
    font_props = {
        'FONTBOUNDINGBOX': (0, 0, 0, 0),
        'SIZE': 0,
        'FONT': '',
        'FONT_ASCENT': 0,
        'FONT_DESCENT': 0
    }
    
    try:
        with open(bdf_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        lines = content.split('\n')
        
        i = 0
        while i < len(lines):
            line = lines[i].strip()
            
            if line.startswith('FONTBOUNDINGBOX'):
                parts = line.split()
                if len(parts) >= 4:
                    font_props['FONTBOUNDINGBOX'] = (int(parts[1]), int(parts[2]), int(parts[3]), int(parts[4]))
            
            elif line.startswith('SIZE'):
                parts = line.split()
                if len(parts) >= 2:
                    font_props['SIZE'] = int(parts[1])
            
            elif line.startswith('FONT '):
                font_props['FONT'] = line[5:].strip('"')
            
            elif line.startswith('FONT_ASCENT'):
                parts = line.split()
                if len(parts) >= 2:
                    font_props['FONT_ASCENT'] = int(parts[1])
            
            elif line.startswith('FONT_DESCENT'):
                parts = line.split()
                if len(parts) >= 2:
                    font_props['FONT_DESCENT'] = int(parts[1])
            
            elif line.startswith('STARTCHAR'):
                char_info = {}
                char_code = None
                char_name = line.split()[1] if len(line.split()) > 1 else ""
                
                # Parse character header
                while i < len(lines) and not lines[i].startswith('BITMAP'):
                    line = lines[i].strip()
                    
                    if line.startswith('ENCODING'):
                        parts = line.split()
                        if len(parts) >= 2:
                            char_code = int(parts[1])

                            iso8859_2_bytes = None
                            
                            # Extended ISO-8859-2 characters
                            try:
                                # Step 1: Decode printable ASCII
                                char = chr(char_code) # bytes([char_code]).decode('iso-8859-1')
                                
                                # Step 2: Encode the character as ISO-8859-2
                                iso8859_2_bytes = char.encode('iso-8859-2', errors='replace')

                                # Step 3: Update `char_code`
                                char_code = iso8859_2_bytes[0]
                            except:
                                pass
                    
                    elif line.startswith('BBX'):
                        parts = line.split()
                        if len(parts) >= 5:
                            char_info['BBX'] = (int(parts[1]), int(parts[2]), int(parts[3]), int(parts[4]))
                    
                    elif line.startswith('DWIDTH'):
                        parts = line.split()
                        if len(parts) >= 3:
                            char_info['DWIDTH'] = (int(parts[1]), int(parts[2]))
                    
                    i += 1
                
                # Parse bitmap data
                if char_code is not None and i < len(lines):
                    i += 1  # Skip BITMAP line
                    bitmap_lines = []
                    
                    while i < len(lines) and not lines[i].startswith('ENDCHAR'):
                        if lines[i].strip():
                            bitmap_lines.append(lines[i].strip())
                        i += 1
                    
                    char_info['BITMAP'] = bitmap_lines
                    char_info['NAME'] = char_name
                    characters[char_code] = char_info
                
                if i < len(lines) and lines[i].startswith('ENDCHAR'):
                    i += 1
                continue
            
            i += 1
        
        print(f"Parsed {len(characters)} characters from BDF file")
        return font_props, characters
    
    except Exception as e:
        print(f"Error parsing BDF file: {e}")
        import traceback
        traceback.print_exc()
        return None, None

def hex_to_bytes_big_endian(hex_str, target_width):
    """Convert hex string to bytes in BIG ENDIAN order (MSB first)"""
    if not hex_str:
        return [0] * ((target_width + 7) // 8)
    
    try:
        # Calculate number of bytes needed
        num_bytes = (target_width + 7) // 8
        
        # Convert hex string to integer
        value = int(hex_str, 16)
        
        # Create bytes array in BIG ENDIAN order (most significant byte first)
        bytes_list = []
        
        for byte_idx in range(num_bytes):
            # Calculate which bits to take
            # For big endian, first byte gets the most significant bits
            bits_shift = (num_bytes - byte_idx - 1) * 8
            byte_val = (value >> bits_shift) & 0xFF
            bytes_list.append(byte_val)
        
        return bytes_list
    
    except ValueError:
        return [0] * ((target_width + 7) // 8)

def bytes_to_visual_big_endian(bytes_list, width):
    """Convert bytes in BIG ENDIAN order to visual representation"""
    if not bytes_list:
        return " " * width
    
    # Combine bytes in big endian order
    visual_bits = ""
    for byte in bytes_list:
        visual_bits += format(byte, '08b')
    
    # Now we have all bits concatenated
    # For width=16 and 2 bytes: visual_bits = "0000000011111111" (first byte then second byte)
    # But we need to display it left to right
    
    # If we have more bits than width, take the leftmost 'width' bits
    """if len(visual_bits) > width:
        visual_bits = visual_bits[-width:]
    elif len(visual_bits) < width:
        visual_bits = visual_bits.rjust(width, '0')"""
    
    if (len(visual_bits) > width):
        visual_bits.ljust(width)

    print(visual_bits)
    
    # Convert to visual representation
    return visual_bits.replace('0', ' ').replace('1', '#')

def create_font_data(font_props, characters):
    """Create font data array for ISO-8859-2 encoding"""
    
    bbx_width, bbx_height, bbx_xoff, bbx_yoff = font_props['FONTBOUNDINGBOX']
    
    print(f"Font bounding box: {bbx_width}x{bbx_height}")
    print(f"Font offset: x={bbx_xoff}, y={bbx_yoff}")
    
    # Calculate bytes per row (BIG ENDIAN: MSB first)
    bytes_per_row = (bbx_width + 7) // 8
    print(f"Bytes per row: {bytes_per_row}")
    
    # Create font data array
    font_data = []
    
    # Characters we need to include (ISO-8859-2: 0x20-0xFF, excluding control chars 0x80-0x9F)
    required_chars = list(range(0x20, 0x100))
    
    # Remove Windows control characters (0x80-0x9F)
    # required_chars = [c for c in required_chars if not (0x80 <= c < 0xA0)]
    
    print(f"Will generate {len(required_chars)} characters")
    
    for char_code in required_chars:
        if char_code in characters:
            char_info = characters[char_code]
            
            # Get character bitmap
            bitmap_lines = char_info.get('BITMAP', [])
            
            # Get character dimensions
            if 'BBX' in char_info:
                char_width, char_height, char_xoff, char_yoff = char_info['BBX']
            else:
                char_width, char_height = bbx_width, bbx_height
                char_xoff, char_yoff = 0, 0
            
            # Calculate vertical positioning
            # In BDF, yoff is relative to baseline (positive = above baseline)
            # We need to convert to our coordinate system
            ascent = font_props.get('FONT_ASCENT', bbx_height + bbx_yoff)
            y_adjust = ascent - char_yoff - char_height
            
            # Process each row
            for row in range(bbx_height):
                if row < y_adjust or row >= y_adjust + char_height:
                    # Row is above or below character, add empty row
                    font_data.extend([0] * bytes_per_row)
                else:
                    # Get bitmap row
                    bitmap_row = row - y_adjust
                    if bitmap_row < len(bitmap_lines):
                        hex_str = bitmap_lines[bitmap_row]
                        
                        # Convert hex to bytes in BIG ENDIAN order
                        row_bytes = hex_to_bytes_big_endian(hex_str, char_width)
                        
                        # Ensure we have the right number of bytes
                        if len(row_bytes) < bytes_per_row:
                            # Pad with zeros on the left (MSB side)
                            row_bytes = [0] * (bytes_per_row - len(row_bytes)) + row_bytes
                        elif len(row_bytes) > bytes_per_row:
                            # Truncate from the left (keep least significant bytes)
                            row_bytes = row_bytes[-bytes_per_row:]
                        
                        # Apply horizontal offset
                        if char_xoff > 0:
                            # We need to shift the entire row to the right by char_xoff bits
                            # Combine bytes into integer
                            combined = 0
                            for byte in row_bytes:
                                combined = (combined << 8) | byte
                            
                            # Shift right by char_xoff bits
                            combined = combined << char_xoff
                            
                            # Split back into bytes
                            shifted_bytes = []
                            for i in range(bytes_per_row - 1, -1, -1):
                                byte = (combined >> (i * 8)) & 0xFF
                                shifted_bytes.insert(0, byte)
                            
                            font_data.extend(shifted_bytes)
                        else:
                            font_data.extend(row_bytes)
                    else:
                        # No bitmap data for this row
                        font_data.extend([0] * bytes_per_row)
        else:
            # Character not found in font, add blank character
            for _ in range(bbx_height):
                font_data.extend([0] * bytes_per_row)
    
    return font_data, bbx_width, bbx_height, bytes_per_row

def generate_font_c_code(font_data, char_width, char_height, bytes_per_row, font_name, font_props):
    """Generate C font structure from font data"""
    
    total_chars = 256 - 32  # 0x20-0xFF
    
    c_code = f"""/**
  ******************************************************************************
  * @file    {font_name}.c
  * @author  Font Converter, for original BDF font license see OFL.txt
  * @brief   This file provides text {font_name} for STM32xx-EVAL's LCD driver.
  ******************************************************************************
  */

#include "fonts.h"

// Font data for {font_props.get('FONT', font_name)}
// Size: {char_width}x{char_height} pixels
// Bytes per row: {bytes_per_row}
// Encoding: ISO-8859-2 (characters 0x20-0xFF)

const uint8_t {font_name}_Table[] = 
{{
"""
    
    # Calculate characters to generate
    required_chars = list(range(0x20, 0x100))
    # required_chars = [c for c in required_chars if not (0x80 <= c < 0xA0)]
    
    rows_per_char = char_height
    bytes_per_char = rows_per_char * bytes_per_row
    
    for char_idx, char_code in enumerate(required_chars):
        # Calculate starting index in font_data
        start_idx = char_idx * bytes_per_char
        
        # Get character representation
        char_repr = ' '
        if 0x20 <= char_code <= 0x7E:
            # Printable ASCII
            char_repr = chr(char_code)
            if char_repr == '\\':
                char_repr = '\\\\'
            elif char_repr == '\'':
                char_repr = '\\\''
        elif 0xA0 <= char_code <= 0xFF:
            # Extended ISO-8859-2 character
            try:
                char_repr = bytes([char_code]).decode('iso-8859-2')
            except:
                char_repr = ' '
        
        c_code += f'\t// @{start_idx} \'{char_repr}\' ({char_width} pixels wide)\n'
        
        # Add each row of the character
        for row in range(rows_per_char):
            row_start = start_idx + (row * bytes_per_row)
            row_bytes = font_data[row_start:row_start + bytes_per_row]
            
            # Format bytes for C array (in the order they should be stored)
            bytes_str = ', '.join([f'0x{b:02X}' for b in row_bytes])
            c_code += f'\t{bytes_str}, // '
            
            # Create visual representation from bytes (BIG ENDIAN)
            visual = bytes_to_visual_big_endian(row_bytes, char_width)
            
            c_code += f'{visual}\n'
        
        c_code += '\n'
    
    c_code += f"""}};

sFONT {font_name} = {{
  {font_name}_Table,
  {char_width}, /* Width */
  {char_height}, /* Height */
}};

/************************ (C) Font Converter **********************/
"""
    
    return c_code

def test_byte_order():
    """Test function to verify byte order handling"""
    print("Testing byte order...")
    
    # Test case: 16 pixels wide, should have 2 bytes per row
    width = 16
    bytes_per_row = (width + 7) // 8  # = 2
    
    # Example: Binary pattern 1100000011111111
    # This should be stored as: 0xC0 (11000000), 0xFF (11111111)
    # Visual: "##      ########"
    
    hex_str = "C0FF"  # 16 bits
    bytes_big_endian = hex_to_bytes_big_endian(hex_str, width)
    visual = bytes_to_visual_big_endian(bytes_big_endian, width)
    
    print(f"Hex: {hex_str}")
    print(f"Bytes (big endian): {[hex(b) for b in bytes_big_endian]}")
    print(f"Visual: {visual}")
    print(f"Expected: ##      ########")
    
    return bytes_big_endian == [0xC0, 0xFF]

def convert_bdf_to_font(bdf_path, output_path, font_name="Font12"):
    """Convert BDF font file to STM32 C font file"""
    
    print(f"Converting BDF font: {bdf_path}")
    
    # Test byte order handling first
    if not test_byte_order():
        print("Warning: Byte order test failed!")
    
    # Parse BDF file
    font_props, characters = parse_bdf_font(bdf_path)
    
    if font_props is None or characters is None:
        print("Failed to parse BDF file")
        return False
    
    # Check if we have FONT_ASCENT and FONT_DESCENT
    if font_props['FONT_ASCENT'] == 0:
        # Estimate from bounding box
        font_props['FONT_ASCENT'] = font_props['FONTBOUNDINGBOX'][1] + font_props['FONTBOUNDINGBOX'][3]
        font_props['FONT_DESCENT'] = -font_props['FONTBOUNDINGBOX'][3]
    
    print(f"Font ascent: {font_props['FONT_ASCENT']}, descent: {font_props['FONT_DESCENT']}")
    
    # Create font data
    font_data, char_width, char_height, bytes_per_row = create_font_data(font_props, characters)
    
    print(f"Generated font data: {len(font_data)} bytes")
    print(f"Character size: {char_width}x{char_height}")
    print(f"Bytes per row: {bytes_per_row}")
    
    # Generate C code
    c_code = generate_font_c_code(font_data, char_width, char_height, bytes_per_row, font_name, font_props)
    
    # Write to output file
    try:
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(c_code)
        
        print(f"\nSuccessfully converted to: {output_path}")
        print(f"Font name: {font_name}")
        print(f"Character width: {char_width} pixels")
        print(f"Character height: {char_height} pixels")
        print(f"Bytes per row: {bytes_per_row}")
        
        # Calculate statistics
        required_chars = list(range(0x20, 0x100))
        # required_chars = [c for c in required_chars if not (0x80 <= c < 0xA0)]
        
        available_chars = sum(1 for code in required_chars if code in characters)
        
        print(f"\nStatistics:")
        print(f"  Characters in source BDF: {len(characters)}")
        print(f"  Characters needed (ISO-8859-2): {len(required_chars)}")
        print(f"  Characters available: {available_chars}")
        print(f"  Blank characters added: {len(required_chars) - available_chars}")
        
        # Show some extended characters that were included
        print(f"\nIncluded extended characters (ISO-8859-2):")
        extended_chars = [c for c in required_chars if c > 0x7F]
        found_extended = [c for c in extended_chars if c in characters]
        
        for code in found_extended[:10]:  # Show first 10
            try:
                char = bytes([code]).decode('iso-8859-2')
                print(f"  0x{code:02X}: '{char}'")
            except:
                print(f"  0x{code:02X}: [non-printable]")
        
        if len(found_extended) > 10:
            print(f"  ... and {len(found_extended) - 10} more")
        
        # Show a sample of the output
        print(f"\nSample output format:")
        print(f"  For a {char_width}x{char_height} font:")
        print(f"  Each row has {bytes_per_row} bytes")
        if bytes_per_row == 1:
            print(f"  Format: 0xXX, // visual")
        elif bytes_per_row == 2:
            print(f"  Format: 0xXX, 0xXX, // visual")
        elif bytes_per_row == 3:
            print(f"  Format: 0xXX, 0xXX, 0xXX, // visual")
        
        return True
        
    except Exception as e:
        print(f"Error writing output file: {e}")
        import traceback
        traceback.print_exc()
        return False

def main():
    if len(sys.argv) < 2:
        print("BDF Font to STM32 Font Converter")
        print("=================================")
        print("Converts BDF font files to STM32 font format (ISO-8859-2 encoding)")
        print("Supports fonts wider than 8 pixels (multiple bytes per row)")
        print("\nUsage:")
        print(f"  {sys.argv[0]} input.bdf [output.c] [font_name]")
        print("\nArguments:")
        print("  input.bdf   - Input BDF font file")
        print("  output.c    - Output C file (default: font_output.c)")
        print("  font_name   - Name for font structure (default: Font12)")
        print("\nExamples:")
        print(f"  {sys.argv[0]} courier.bdf font12.c Font12")
        print(f"  {sys.argv[0]} arial24.bdf font24.c Font24")
        return
    
    bdf_path = sys.argv[1]
    
    # Check if input file exists
    if not os.path.exists(bdf_path):
        print(f"Error: Input file '{bdf_path}' not found")
        return
    
    # Set default output path
    if len(sys.argv) > 2:
        output_path = sys.argv[2]
    else:
        base_name = os.path.splitext(bdf_path)[0]
        output_path = f"{base_name}.c"
    
    # Set font name
    if len(sys.argv) > 3:
        font_name = sys.argv[3]
    else:
        font_name = "Font12"
    
    # Convert the font
    success = convert_bdf_to_font(bdf_path, output_path, font_name)
    
    if success:
        print("\n✓ Conversion complete!")
    else:
        print("\n✗ Conversion failed!")

if __name__ == "__main__":
    main()