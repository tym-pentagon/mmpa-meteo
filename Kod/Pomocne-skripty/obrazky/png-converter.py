from PIL import Image
import sys
import os

def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)

def generate_bitmap_struct(image_path, image_name, output_file):
    img = Image.open(image_path).convert('RGB')

    width = img.width
    height = img.height
    
    # Generate pixel array
    pixels = []
    for y in range(height - 1, -1, -1): # Svisle překlopit
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            pixels.append(f"RC(0x{rgb565(r, g, b):04x})")
    
    # Write to file
    with open(output_file, 'w') as f:
        f.write(f"""#include <stdint.h>
#include "lcd.h"
#include "bmp.h"
#include "obrazky.h"

#define WIDTH    {width}
#define HEIGHT   {height}

#if LCD_REVERSE16 == 0
#define RC(a)   a
#endif
#if LCD_REVERSE16 == 1
#define RC(a)   ((((a) & 0xFF) << 8) | (((a) & 0xFF00) >> 8))
#endif

#ifdef __GNUC__
#pragma pack(push, 1)
#elif defined(__CC_ARM)
#pragma push
#pragma pack(1)
#endif

const BITMAPSTRUCT {image_name}_{width}x{height}_16 __attribute__((aligned)) = 
{{
  {{
    0x4d42u,
    sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + (WIDTH * HEIGHT * 2),
    0x0000u,
    0x0000u,
    sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)
  }},
  {{
    sizeof(BITMAPINFOHEADER),
    WIDTH,
    HEIGHT,
    1u,
    16,
    0x00000003u,
    (WIDTH * HEIGHT * 2),
    0x00000000ul,
    0x00000000ul,
    0x00000000ul,
    0x00000000ul
  }},
  {{
""")
        
        for i in range(0, len(pixels), width):
            line = "    " + ", ".join(pixels[i:i+width])
            if i + width < len(pixels):
                line += ","
            f.write(line + "\n")
        
        f.write(f"""  }}
}};

#ifdef  __GNUC__
#pragma pack (pop)
#elif   defined(__CC_ARM)
#pragma pop
#endif
""")
    return True # Successful conversion

def main():
    if len(sys.argv) < 2:
        print("PNG to STM32 Image Converter")
        print("=================================")
        print("Converts PNG image files to STM32 image format (RGB565 encoding)")
        print("\nUsage:")
        print(f"  {sys.argv[0]} input.png image_name output.c")
        print("\nArguments:")
        print("  input.png   - Input PNG image file")
        print("  image_name  - Name of the image array")
        print("  output.c    - Output C file")
        print("\nExamples:")
        print(f"  {sys.argv[0]} icon.png save_icon save_icon.c")
        print(f"  {sys.argv[0]} image.png main_menu_image main_menu_image.c")
        return
    
    image_path = sys.argv[1]
    
    # Check if input file exists
    if not os.path.exists(image_path):
        print(f"Error: Input file '{image_path}' not found")
        return
    
    # Set image name
    image_name = sys.argv[2]

    # Set default output path
    output_file = sys.argv[3]
    
    # Convert the image
    success = generate_bitmap_struct(image_path, image_name, output_file)
    
    if success:
        print("\n✓ Conversion complete!")
    else:
        print("\n✗ Conversion failed!")

if __name__ == "__main__":
    main()